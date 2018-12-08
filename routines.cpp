//---------------------------------------------------------------------------

#pragma hdrstop

#include "routines.h"
#include <System.JSON.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "frmain.h"

HWND getMainHandle()
{
	return myClient.mainForm;
}

void addLog(int type, UnicodeString message)
{
	UnicodeString *buf = new UnicodeString(type_log[type] + ": " + message);
	PostMessage(getMainHandle(), WM_VISIT_LOG, 0, (long)buf);

	if (type < TYPE_LOG_DETAIL) {
		buf = new UnicodeString(type_log[type] + ": " + message);
		PostMessage(getMainHandle(), WM_VISIT_STATUS, 0, (long)buf);
	}
}

Message makeMessage(int type, int count_poles, ...)
{
	Message message;
	message.type = type;
	message.count_poles = count_poles;

    va_list vl;
	va_start(vl, count_poles);

	for (int i = 0; i < count_poles; i++) {
		wchar_t *m = va_arg(vl, wchar_t *);
		message.messages[i] = UnicodeString(m);
	}

	va_end(vl);

	return message;
}

Message parseMessage(UnicodeString messages)
{
	Message message;
	message.type = 0;
	message.count_poles = 0;

	TJSONObject *json = (TJSONObject*) TJSONObject::ParseJSONValue(messages);
	if(!json) {
		return message;
	}

	__try {
		TJSONPair *TMessage = json->Get("TMessage");
		message.type = StrToInt(TMessage->JsonValue->Value());

		TJSONArray *Messages = (TJSONArray*)json->Get( "Messages" )->JsonValue;
		message.count_poles = Messages->Size();
		for(int i = 0; i < Messages->Size(); i++) {
			message.messages[i] = Messages->Items[i]->Value();
		}

	}
	__finally {
		json->Free();
	}

	return message;
}

UnicodeString printMessage(Message message)
{
	UnicodeString res = "{\"tmessage\":" + UnicodeString(message.type) + ",\"messages\":[";
	for (int i = 0; i < message.count_poles; i++) {
		res = res + "\"" + message.messages[i] + "\"";
		if (i != message.count_poles - 1) {
			res = res + ",";
		}
	}
	res = res + "]}";

	return res;
}

bool StartProgram(UnicodeString cmd)
{
	UnicodeString name;
	UnicodeString arg;

	if(cmd.Pos("\\")){
		UnicodeString p = cmd.SubString(0, cmd.LastDelimiter('\\'));
		if(!_wchdir(p.w_str())) {
			UnicodeString s = cmd.SubString(cmd.LastDelimiter('\\'), cmd.Length());

			name = p + s.SubString(0, s.Pos(" "));
			arg = s.SubString(s.Pos(" "), s.Length());
		}
		else{
			return false;
		}
	}
	else{
		name = cmd.SubString(0, cmd.LastDelimiter(' '));
		arg = cmd.SubString(cmd.LastDelimiter(' '), cmd.Length());
	}

	return ExecProgram(name, arg, false, false);
}

bool ExecProgram(UnicodeString cmd, UnicodeString arg, bool elevate, bool invisible)
{
	SHELLEXECUTEINFOW TempInfo = {0};
	TempInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
	TempInfo.fMask = 0;
	TempInfo.hwnd = NULL;
	if(elevate) TempInfo.lpVerb = L"runas";
	TempInfo.lpDirectory = L" ";
	TempInfo.lpFile = cmd.w_str();
	TempInfo.lpParameters = arg.w_str();
	if(invisible)
		TempInfo.nShow = SW_HIDE;
	else
		TempInfo.nShow = SW_SHOWNORMAL;
	if(::ShellExecuteExW(&TempInfo)){
		return true;
	}

	//todo убрать??
	//SysErrorMessage(GetLastError());
	return false;
}

bool ExistService()
{
	TRegistry *r = new TRegistry();
	r->RootKey = HKEY_LOCAL_MACHINE;
	bool result = r->OpenKeyReadOnly("SYSTEM\\CurrentControlSet\\services\\reService");
	r->CloseKey();
	delete r;
	return result;
}

int CountVisits()
{
	TCHAR buff[MAX_PATH];
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnapshot == INVALID_HANDLE_VALUE) return 1;

	UnicodeString fname = Application->ExeName.SubString(Application->ExeName.LastDelimiter("\\") + 1, Application->ExeName.Length());
	int count = 0;

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof pe;
	BOOL result = Process32First(hSnapshot, &pe);

	while(result)
	{
		if(wcsstr(pe.szExeFile, fname.c_str())) count++;
		result = Process32Next(hSnapshot, &pe);
	}
	CloseHandle(hSnapshot);
	return count;
}

void CloseCommunicator()
{
	TCHAR buff[MAX_PATH];
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnapshot == INVALID_HANDLE_VALUE) return;

	UnicodeString fname = COMMUNICATORNAME;

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof pe;
	BOOL result = Process32First(hSnapshot, &pe);
	while(result)
	{
		bool eq = lstrcmpi(pe.szExeFile, fname.c_str());
		if(eq)
		{
			GetFileTitle(pe.szExeFile, buff, MAX_PATH);
			eq = lstrcmpi(buff, fname.c_str());
		}
		if(eq)
		{
			GetShortPathName(pe.szExeFile, buff, MAX_PATH);
			eq = lstrcmpi(buff, fname.c_str());
		}
		if(pe.th32ProcessID == GetCurrentProcessId()) eq = 1; //если это текущий процесс - пропустим
		if(!eq)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
			if(TerminateProcess(hProcess, 0))
			{
				WaitForSingleObject(hProcess, INFINITE);
			}
			CloseHandle(hProcess);
		}
		result = Process32Next(hSnapshot, &pe);
	}
	CloseHandle(hSnapshot);
	return;
}

void CloseVisits()
{
	TCHAR buff[MAX_PATH];
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnapshot == INVALID_HANDLE_VALUE) return;

	UnicodeString fname = Application->ExeName.SubString(Application->ExeName.LastDelimiter("\\") + 1, Application->ExeName.Length());

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof pe;
	BOOL result = Process32First(hSnapshot, &pe);
	while(result)
	{
		bool eq = lstrcmpi(pe.szExeFile, fname.c_str());
		if(eq)
		{
			GetFileTitle(pe.szExeFile, buff, MAX_PATH);
			eq = lstrcmpi(buff, fname.c_str());
		}
		if(eq)
		{
			GetShortPathName(pe.szExeFile, buff, MAX_PATH);
			eq = lstrcmpi(buff, fname.c_str());
		}
		if(pe.th32ProcessID == GetCurrentProcessId()) eq = 1; //если это текущий процесс - пропустим
		if(!eq)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
			if(TerminateProcess(hProcess, 0))
			{
				WaitForSingleObject(hProcess, INFINITE);
			}
			CloseHandle(hProcess);
		}
		result = Process32Next(hSnapshot, &pe);
	}
	CloseHandle(hSnapshot);
	return;
}

bool SetCurrentUserThread()
{
	bool _res = 0;
	DWORD cid = WTSGetActiveConsoleSessionId();

	if(cid != MAXDWORD)
	{
		HANDLE token = NULL;
		if(WTSQueryUserToken(cid, &token))
		{
			HANDLE ntoken = NULL;
			if(DuplicateToken(token, SecurityImpersonation, &ntoken))
			{
				if(SetThreadToken(0, ntoken))
				{
					_res = 1;
				}
				CloseHandle(ntoken);
			}
			CloseHandle(token);
		}
	}

	return(_res);
}

Contact* parseContact(UnicodeString &p)
{
	Contact *contact = new Contact;
	contact->status = 0;

	TJSONObject *json = (TJSONObject*) TJSONObject::ParseJSONValue(p);
	if(!json) {
	   return contact;
	}

	__try {
		TJSONPair *caption = json->Get("Caption");
		contact->caption = caption->JsonValue->Value();

		TJSONPair *type = json->Get("Type");
		contact->type = type->JsonValue->Value();

		TJSONPair *pid = json->Get("Pid");
		contact->pid = pid->JsonValue->Value();

		TJSONPair *id = json->Get("Id");
		contact->id = StrToInt(id->JsonValue->Value());

		TJSONPair *next = json->Get("Next");
		String nextv = next->JsonValue->ToString();
		if (nextv != "null") {
			contact->next = parseContact(nextv);
		}
		else{
			contact->next = NULL;
		}

		TJSONPair *inner = json->Get("Inner");
		String innerv = inner->JsonValue->ToString();
		if (innerv != "null") {
			contact->inner = parseContact(innerv);
		}
		else {
			contact->inner = NULL;
		}
	}
	__finally {
		json->Free();
	}

	return contact;
}

void swapNodes(Contact *a, Contact *b)
{
	Contact tmp;
	tmp.caption = b->caption;
	tmp.id = b->id;
	tmp.inner = b->inner;
	tmp.pid = b->pid;
	tmp.pas = b->pas;
	tmp.type = b->type;

	b->caption = a->caption;
	b->id = a->id;
	b->inner = a->inner;
	b->pid = a->pid;
	b->pas = a->pas;
	b->type = a->type;

	a->caption = tmp.caption;
	a->id = tmp.id;
	a->inner = tmp.inner;
	a->pid = tmp.pid;
	a->pas = tmp.pas;
    a->type = tmp.type;
}

Contact* getContact(Contact *first, int id)
{
	while (first != NULL) {
		if (first->id == id) {
			return first;
		}

		if (first->inner) {
			Contact* z = getContact(first->inner, id);
			if (z != NULL) {
				return z;
			}
		}

		first = first->next;
	}

	return NULL;
}

Contact* getContact(Contact *first, UnicodeString pid)
{
	while (first != NULL) {
		if (cleanPid(first->pid) == pid) {
			return first;
		}

		if (first->inner) {
			Contact* z = getContact(first->inner, pid);
			if (z != NULL) {
				return z;
			}
		}

		first = first->next;
	}

	return NULL;
}

Contact* delContact(Contact *first, int id)
{
	Contact *r;

	if (first == NULL) {
		return first;
	}

	while (first != NULL && first->id == id) {
		first = first->next;
	}

	r = first;

	while (first != NULL) {
		while (first->next != NULL && first->next->id == id) {
			first->next = first->next->next;
		}

		if (first->inner != NULL) {
			first->inner = delContact(first->inner, id);
		}

		first = first->next;
	}

	return r;
}

void sortNodes(Contact *first)
{
	while (first != NULL) {
		Contact *b = first;
		Contact *a = b->next;
		while (a != NULL) {
			if ( a->caption < b->caption ) {
				swapNodes(b, a);
            }
			a = (*a).next;
		}
		first = (*b).next;
	}
}

UnicodeString cleanPid(UnicodeString pid)
{
	while(pid.Pos(L":")) {
		pid = pid.Delete(pid.Pos(":"), 1);
	}

	while(pid.Pos(L".")) {
		pid = pid.Delete(pid.Pos("."), 1);
	}

	while(pid.Pos(L" ")) {
		pid = pid.Delete(pid.Pos(" "), 1);
	}

	return pid;
}

UnicodeString getJsonStringOptions()
{
	TJSONObject *options = new TJSONObject();
	options->AddPair( new TJSONPair("Width", myOptions.Width) );
	options->AddPair( new TJSONPair("Height", myOptions.Height) );
	options->AddPair( new TJSONPair("Left", myOptions.Left) );
	options->AddPair( new TJSONPair("Top", myOptions.Top) );
	options->AddPair( new TJSONPair("TrayIcon", (int)myOptions.TrayIcon) );
	options->AddPair( new TJSONPair("Lang", myOptions.Lang) );

	UnicodeString result = options->ToString();
	options->Free();

	return result;
}


