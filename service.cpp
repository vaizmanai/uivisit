//---------------------------------------------------------------------------
#include "service.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <direct.h>
TreService *reService;

//---------------------------------------------------------------------------
__fastcall TreService::TreService(TComponent* Owner) : TService(Owner)
{
}
//---------------------------------------------------------------------------
void __stdcall ServiceController(unsigned CtrlCode)
{
	reService->Controller(CtrlCode);
}
//---------------------------------------------------------------------------
TServiceController __fastcall TreService::GetServiceController(void)
{
	return (TServiceController) ServiceController;
}
//---------------------------------------------------------------------------
void __fastcall TreService::ServiceAfterInstall(TService *Sender)
{
	TRegistry *r = new TRegistry();
	r->RootKey = HKEY_LOCAL_MACHINE;
	r->OpenKey("SYSTEM\\CurrentControlSet\\services\\reService", false);
	UnicodeString p = Vcl::Forms::Application->ExeName;

	wchar_t shellPath[MAX_PATH] = {0};
	wchar_t shellBuff[MAX_PATH] = {0};

	//получим информацию о program files
	if(SHGetSpecialFolderPath(NULL, shellPath, CSIDL_PROGRAM_FILES, false)){
		wcscat(shellPath, L"\\reVisit\\");

		//создаем папку
		if(CreateDirectory(shellPath, 0)){
			//игнорируем, папка уже может быть создана
		}
		wcscat(shellBuff, shellPath);
		wcscat(shellBuff, L"revisit.exe");

		//копируем себя туда
		if(CopyFile(p.w_str(), shellBuff, false)){
		   //распакуем комумникатор
			TResourceStream* ptCommunicator = new TResourceStream((int)HInstance, UnicodeString("COMMUNICATOR"), L"EXEFILE");
			ptCommunicator->SaveToFile(UnicodeString(shellPath) + COMMUNICATORNAME);
			delete ptCommunicator;

			UnicodeString attr;
			if (myClient.debug) {
				attr = attr + UnicodeString(" -debug");
			}
			if (myClient.server.Length()) {
				attr = attr + UnicodeString(" -server ") + myClient.server;
			}
			if (myClient.pass.Length()) {
				attr = attr + UnicodeString(" -password ") + myClient.pass;
			}
			if (myClient.autoreg) {
				attr = attr + UnicodeString(" -autoreg ") + myClient.autologin + UnicodeString(" ") + myClient.autopass;
			}

			r->WriteString("ImagePath", UnicodeString(shellBuff) + UnicodeString(" -service") + attr);
			r->WriteString("Description", "This is service for managing reVisIT.");
			r->CloseKey();
			delete r;

			ExecProgram("net", "start reService", false, true);
			return;
		}

	}

	ExecProgram(p.w_str(), "-service -uninstall", false, true);
	delete r;
	//если дошли до сюда, то удаляем все нахер
}
//---------------------------------------------------------------------------
void __fastcall TreService::ServiceBeforeUninstall(TService *Sender)
{
//	ExecProgram("net", " stop vService", true, false);
}
//---------------------------------------------------------------------------
void __fastcall TreService::ServiceExecute(TService *Sender)
{
	::Sleep(SERVICE_WAIT_START); //немного сделаем паузу, чтобы текущий коммуникатор успел закрыться

	ExecProgram("reg", "add HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System \/v SoftwareSASGeneration \/t REG_DWORD \/d 1 \/f", false, false);
	ExecProgram("gpupdate", "\/force", false, false);

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
	r->OpenKeyReadOnly("SYSTEM\\CurrentControlSet\\services\\reService");
	UnicodeString p = ExtractFilePath(r->ReadString("ImagePath"));
	r->CloseKey();
	delete r;

	HANDLE wtsevent = OpenEvent(SYNCHRONIZE, NULL, L"Global\\TermSrvReadyEvent");
	WaitForSingleObject(wtsevent, SERVICE_WAIT_TERMINAL_SRV);

	UnicodeString attr;
	if (myClient.debug) {
		attr = attr + UnicodeString(" -debug");
	}
	if (myClient.server.Length()) {
		attr = attr + UnicodeString(" -server ") + myClient.server;
	}
	if (myClient.pass.Length()) {
		attr = attr + UnicodeString(" -password ") + myClient.pass;
	}

	STARTUPINFO sc = {0};
	PROCESS_INFORMATION pc = {0};
	CreateProcess(NULL, UnicodeString(p + COMMUNICATORNAME + attr).w_str(), NULL, NULL, FALSE, 0, NULL, NULL, &sc, &pc);

	if (myClient.autoreg) {
		TRegistry *r = new TRegistry();
		r->RootKey = HKEY_LOCAL_MACHINE;
		r->OpenKey("SYSTEM\\CurrentControlSet\\services\\reService", false);
		UnicodeString serviceFile = Vcl::Forms::Application->ExeName;
		r->WriteString("ImagePath", serviceFile + UnicodeString(" -service") + attr);
		r->CloseKey();
		delete r;
	}

	UnicodeString autoreg;
	while(!Terminated)
	{
		cSessionId = WTSGetActiveConsoleSessionId();

		if((dwSessionId != cSessionId) || (CountVisits() < 2)) //если текущая сессия не совпадает или не запущен
		{
			CloseVisits(); //закроем все клиенты кроме текущего процесс
			dwSessionId = cSessionId;
			::Sleep(SERVICE_PAUSE_RESTART_UI);
			OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY|TOKEN_DUPLICATE|TOKEN_ADJUST_SESSIONID, &hToken);
			DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, 0, SecurityImpersonation, TokenPrimary, &hDuplicateToken);
			SetTokenInformation(hDuplicateToken, TokenSessionId, &dwSessionId, sizeof(dwSessionId));

			if(myClient.autoreg) {
			   autoreg = UnicodeString(" -autoreg ") + myClient.autologin + UnicodeString(" ") + myClient.autopass;
			   myClient.autoreg = false;
			}
			else{
                autoreg = "";
			}

			CreateProcessAsUser(hDuplicateToken, NULL, UnicodeString(p + UnicodeString("reVisit.exe -minimized") + attr + autoreg).w_str(),  NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE , NULL, NULL, &si, &pi);
		}

		ServiceThread->ProcessRequests(false);

		::Sleep(SERVICE_WAIT_CYCLE);
	}
}
//---------------------------------------------------------------------------

