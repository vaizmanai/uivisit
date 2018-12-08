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
Options myOptions;

USEFORM("service.cpp", reService); /* TService: File Type */
USEFORM("forms\fralert.cpp", falert);
USEFORM("forms\frcontact.cpp", fcontact);
USEFORM("forms\frmanage.cpp", fmanage);
USEFORM("forms\frmain.cpp", fmain);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR attr, int)
{
    myClient.initial();

	if(wcsstr(attr, L"help"))
	{
		UnicodeString help = "ƒоступные аргументы дл¤ запуска:\n\n"
								"   -clean-all - удалить настройки\n"
								"   -reload - перезапустить программу\n"
								"   -close - закрыть экземпл¤ры программы\n"
								"   -extract - распаковка коммуникатора\n"
								"   -server address - задать адрес альтернативного сервера\n"
								"   -password - задать пароль\n"
								"   -autoreg login password - добавление в профиль учетной записи\n"
								"   -debug - запуск в режиме отладки\n"
								"   -minimized - запуск в свернутом виде\n"
								"   -service - работа в режиме сервис\n"
								"   -service [install|remove] - установка, удаление сервиса в системе\n";
		ShowMessage(help);
		return 0;
	}

	if(wcsstr(attr, L"clean-all"))
	{
		if (ExistService()) {
			ExecProgram("net", "stop reService", true, true);
			ExecProgram(ApplicationE->ExeName, "-service -uninstall", true, true);

			TRegistry *r = new TRegistry();
			r->RootKey = HKEY_LOCAL_MACHINE;
			r->OpenKeyReadOnly("SYSTEM\\CurrentControlSet\\services\\reService");
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
				wcscat(shellPath, L"\\reVisit\\");
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
			r->OpenKeyReadOnly("SYSTEM\\CurrentControlSet\\services\\reService");
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
				wcscat(shellPath, L"\\reVisit\\");
			}

			ExecProgram(UnicodeString(shellPath) + UnicodeString(COMMUNICATORNAME), "reload", true, true);
		}
		return 0;
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

	if(wcsstr(attr, L"server"))
	{
		wchar_t *n = wcsstr(attr, L"server") + wcslen(L"server ");
		wchar_t buf[256];
		n = wcscpy(buf, n);
		wchar_t *t = wcstok(n, L" =");
		if(t){
			myClient.server = UnicodeString(t);
		}
	}

	if(wcsstr(attr, L"password"))
	{
		wchar_t *n = wcsstr(attr, L"password") + wcslen(L"password ");
		wchar_t buf[256];
		n = wcscpy(buf, n);
		wchar_t *t = wcstok(n, L" =");
		if(t){
			myClient.pass = UnicodeString(t);
		}
	}

	if(wcsstr(attr, L"autoreg"))
	{
		wchar_t *n = wcsstr(attr, L"autoreg") + wcslen(L"autoreg ");
		wchar_t buf[256];
		n = wcscpy(buf, n);
		wchar_t *t = wcstok(n, L" ");
		if(t) {
			myClient.autologin = UnicodeString(t);
			t = wcstok(NULL, L" ");
			if(t) {
				myClient.autopass = UnicodeString(t);
				myClient.autoreg = true;
			}
		}
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
			ApplicationS->CreateForm(__classid(TreService), &reService);
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
			ApplicationE->Title = "reVisit";
			ApplicationE->CreateForm(__classid(Tfmain), &fmain);
			ApplicationE->CreateForm(__classid(Tfcontact), &fcontact);
			ApplicationE->CreateForm(__classid(Tfmanage), &fmanage);
			ApplicationE->CreateForm(__classid(Tfalert), &falert);
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
