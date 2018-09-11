//---------------------------------------------------------------------------

#include <vcl.h>
#include <SysUtils.hpp>
#include <SvcMgr.hpp>
#pragma hdrstop
#include <tchar.h>

#include "routines.h"

#define ApplicationS Svcmgr::Application
#define ApplicationE Forms::Application

//---------------------------------------------------------------------------
Client myClient;

USEFORM("service.cpp", reClientService); /* TService: File Type */
USEFORM("forms\frcontact.cpp", fcontact);
USEFORM("forms\frmanage.cpp", fmanage);
USEFORM("forms\frmain.cpp", fmain);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR attr, int)
{
	if(wcsstr(attr, L"clean-all"))
	{
		if (ExistService()) {
			ExecProgram("net", "stop reClientService", true, true);
			ExecProgram(ApplicationE->ExeName, "-service -uninstall", true, true);

			TRegistry *r = new TRegistry();
			r->RootKey = HKEY_LOCAL_MACHINE;
			r->OpenKeyReadOnly("SYSTEM\\CurrentControlSet\\services\\reClientService");
			UnicodeString p = ExtractFilePath(r->ReadString("ImagePath"));
			r->CloseKey();
			delete r;

			ExecProgram(p + COMMUNICATORNAME, "clean-all", true, true);
		}
		else
		{
			wchar_t shellPath[MAX_PATH] = {0};

			//получим информацию о temp
			if(GetTempPath(MAX_PATH, shellPath)) {
				wcscat(shellPath, L"\\reClient\\");
			}

			ExecProgram(UnicodeString(shellPath) + UnicodeString(COMMUNICATORNAME), "clean-all", true, true);
		}
		return 0;
	}

	if(wcsstr(attr, L"reload"))
	{
		if (ExistService()) {
			TRegistry *r = new TRegistry();
			r->RootKey = HKEY_LOCAL_MACHINE;
			r->OpenKeyReadOnly("SYSTEM\\CurrentControlSet\\services\\reClientService");
			UnicodeString p = ExtractFilePath(r->ReadString("ImagePath"));
			r->CloseKey();
			delete r;

			ExecProgram(p + COMMUNICATORNAME, "reload", true, true);
		}
		else
		{
			wchar_t shellPath[MAX_PATH] = {0};

			//получим информацию о temp
			if(GetTempPath(MAX_PATH, shellPath)) {
				wcscat(shellPath, L"\\reClient\\");
			}

			ExecProgram(UnicodeString(shellPath) + UnicodeString(COMMUNICATORNAME), "reload", true, true);
		}
		return 0;
	}

	if(wcsstr(attr, L"server"))
	{
		wchar_t *buf = wcsstr(attr, L"server");
		if (wcslen(buf) > wcslen(L"server")) {
			buf = buf + wcslen(L"server") ;
			wchar_t *ipstr = wcstok(buf, L" ");
			myClient.server = UnicodeString(ipstr);
		}
	}

	if(wcsstr(attr, L"close"))
	{
		CloseVisits();
		CloseCommunicator();
		return 0;
	}

	if(wcsstr(attr, L"extract"))
	{
        TResourceStream* ptCommunicator = new TResourceStream((int)HInstance, UnicodeString("COMMUNICATOR"), L"EXEFILE");
		ptCommunicator->SaveToFile(COMMUNICATORNAME);
		delete ptCommunicator;
		return 0;
	}

	if(wcsstr(attr, L"debug"))
	{
		myClient.debug = true;
	}
	else
	{
		myClient.debug = false;
	}

	if(wcsstr(attr, L"service"))
	{
		try
		{
			ApplicationS->DelayInitialize = true;
			if ((!ApplicationS->DelayInitialize) || (ApplicationS->Installing()))
			{
				ApplicationS->Initialize();
			}
			ApplicationS->CreateForm(__classid(TreClientService), &reClientService);
			ApplicationS->Run();
		}
		catch (Exception &exception)
		{
			Sysutils::ShowException(&exception, System::ExceptAddr());
		}
		catch(...)
		{
			try
			{
				throw Exception("");
			}
			catch(Exception &exception)
			{
				Sysutils::ShowException(&exception, System::ExceptAddr());
			}
		}
		return 0;
	}
	else
	{
		try
		{
			if(wcsstr(attr, L"minimized")) ApplicationE->ShowMainForm = false;

			ApplicationE->Initialize();
			ApplicationE->MainFormOnTaskBar = false;
			ApplicationE->CreateForm(__classid(Tfmain), &fmain);
			ApplicationE->CreateForm(__classid(Tfcontact), &fcontact);
			ApplicationE->CreateForm(__classid(Tfmanage), &fmanage);
			ApplicationE->Run();
		}
		catch (Exception &exception)
		{
			ApplicationE->ShowException(&exception);
		}
		catch (...)
		{
			try
			{
				throw Exception("");
			}
			catch (Exception &exception)
			{
				ApplicationE->ShowException(&exception);
			}
		}
		return 0;
	}
}
//---------------------------------------------------------------------------
