//---------------------------------------------------------------------------
#include "service.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <direct.h>
TreClientService *reClientService;

//---------------------------------------------------------------------------
__fastcall TreClientService::TreClientService(TComponent* Owner) : TService(Owner)
{
}
//---------------------------------------------------------------------------
void __stdcall ServiceController(unsigned CtrlCode)
{
	reClientService->Controller(CtrlCode);
}
//---------------------------------------------------------------------------
TServiceController __fastcall TreClientService::GetServiceController(void)
{
	return (TServiceController) ServiceController;
}
//---------------------------------------------------------------------------
void __fastcall TreClientService::ServiceAfterInstall(TService *Sender)
{
	TRegistry *r = new TRegistry();
	r->RootKey = HKEY_LOCAL_MACHINE;
	r->OpenKey("SYSTEM\\CurrentControlSet\\services\\reClientService", false);
	UnicodeString p = r->ReadString("ImagePath");

	wchar_t shellPath[MAX_PATH] = {0};
	wchar_t shellBuff[MAX_PATH] = {0};

	//получим информацию о program files
	if(SHGetSpecialFolderPath(NULL, shellPath, CSIDL_PROGRAM_FILES, false)){
		wcscat(shellPath, L"\\reClient\\");

		//создаем папку
		if(CreateDirectory(shellPath, 0)){
			//игнорируем, папка уже может быть создана
		}
		wcscat(shellBuff, shellPath);
		wcscat(shellBuff, L"reclient.exe");

		//копируем себя туда
		if(CopyFile(p.w_str(), shellBuff, false)){
		   //распакуем комумникатор
			TResourceStream* ptCommunicator = new TResourceStream((int)HInstance, UnicodeString("COMMUNICATOR"), L"EXEFILE");
			ptCommunicator->SaveToFile(UnicodeString(shellPath) + COMMUNICATORNAME);
			delete ptCommunicator;

			UnicodeString attr;
			if (myClient.server.Length()) {
				attr = L" -server " + myClient.server;
			}
			r->WriteString("ImagePath", UnicodeString(shellBuff) + L" -service"
				+ UnicodeString(myClient.debug?L" -debug":L"")
				+ UnicodeString(attr)
					);

			r->WriteString("Description", "This is service for managing reClient.");
			r->CloseKey();
			delete r;

			ExecProgram("net", "start reClientService", true, true);
			return;
		}

	}

	delete r;
	//если дошли до сюда, то удаляем все нахер
}
//---------------------------------------------------------------------------
void __fastcall TreClientService::ServiceBeforeUninstall(TService *Sender)
{
//	ExecProgram("net", " stop vService", true, false);
}
//---------------------------------------------------------------------------
void __fastcall TreClientService::ServiceExecute(TService *Sender)
{
 	::Sleep(5000); //немного сделаем паузу, чтобы текущий коммуникатор успел закрыться

	STARTUPINFO si = {0};
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.lpDesktop = L"WinSta0\\default";
	si.wShowWindow = SW_NORMAL;

	HANDLE hToken = NULL;
	HANDLE hDuplicateToken = NULL;
	DWORD dwSessionId = NULL;
	DWORD cSessionId;
	PROCESS_INFORMATION pi = {0};

	TRegistry *r = new TRegistry();
	r->RootKey = HKEY_LOCAL_MACHINE;
	r->OpenKeyReadOnly("SYSTEM\\CurrentControlSet\\services\\reClientService");
	UnicodeString p = ExtractFilePath(r->ReadString("ImagePath"));
	r->CloseKey();
	delete r;

	HANDLE wtsevent = OpenEvent(SYNCHRONIZE, NULL, L"Global\\TermSrvReadyEvent");
	WaitForSingleObject(wtsevent, 10000);

	STARTUPINFO sc = {0};
	PROCESS_INFORMATION pc = {0};
	CreateProcess(NULL, UnicodeString(p + COMMUNICATORNAME).w_str(), NULL, NULL, FALSE, 0, NULL, NULL, &sc, &pc);

	while(!Terminated)
	{
		cSessionId = WTSGetActiveConsoleSessionId();

		if((dwSessionId != cSessionId) || (CountVisits() < 2)) //если текущая сессия не совпадает или не запущен
		{
			CloseVisits(); //закроем все клиенты кроме текущего процесс
			dwSessionId = cSessionId;
			::Sleep(1000);
			OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY|TOKEN_DUPLICATE|TOKEN_ADJUST_SESSIONID, &hToken);
			DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, 0, SecurityImpersonation, TokenPrimary, &hDuplicateToken);
			SetTokenInformation(hDuplicateToken, TokenSessionId, &dwSessionId, sizeof(dwSessionId));

			CreateProcessAsUser(hDuplicateToken, NULL, UnicodeString(p + L"reClient.exe -minimized" + UnicodeString(myClient.debug?L" -debug":L"")).w_str(),  NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE , NULL, NULL, &si, &pi);
		}

		ServiceThread->ProcessRequests(false);

		::Sleep(1500);
	}
}
//---------------------------------------------------------------------------

