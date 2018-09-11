//---------------------------------------------------------------------------

#pragma hdrstop

#include "routines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "frmain.h"

HWND getMainHandle()
{
	//return fmain->Handle;
	return myClient.mainForm;
}

void addLog(int type, UnicodeString message)
{
	UnicodeString *buf = new UnicodeString(type_log[type] + ": " + message);
	PostMessage(getMainHandle(), WM_VISIT_LOG, 0, (long)buf);
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

	if(messages.Pos('{') != 0){
		messages = messages.SubString(messages.Pos('{'), messages.Length());
	}

	messages = messages.SubString(messages.Pos('"') + 1, messages.Length());
	UnicodeString tmess = messages.SubString(0, messages.Pos('"') - 1);

	messages = messages.SubString(messages.Pos(':') + 1, messages.Length());
	UnicodeString tval = messages.SubString(0, messages.Pos(',') - 1);
	message.type = tval.ToInt();

	messages = messages.SubString(messages.Pos(',') + 1, messages.Length());

	messages = messages.SubString(messages.Pos('"') + 1, messages.Length());
	UnicodeString cmess = messages.SubString(0, messages.Pos('"') - 1);

	messages = messages.SubString(messages.Pos('[') + 1, messages.Length());
	UnicodeString cval = messages.SubString(0, messages.Pos(']') - 1);

	int i = 0;
	while((messages.Length() > 2) && (i++ < MAX_MESSAGES)){
		messages = messages.Trim().SubString(messages.Pos('"') + 1, messages.Length());
		UnicodeString t = messages.SubString(0, messages.Pos('"') - 1);

		if(t != ',' && t != "]"){
			message.messages[message.count_poles] = t;
			message.count_poles++;
		}

	}

	message.count_poles--;
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
	bool result = r->OpenKeyReadOnly("SYSTEM\\CurrentControlSet\\services\\reClientService");
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

	int a1 = p.Pos(":") + 1;
	int b1 = p.Pos(",");
	UnicodeString id = p.SubString(a1, b1 - a1);
//	UnicodeString id = p.SubString(a1, b1 - a1);
	contact->id = StrToInt(id);

	p = p.SubString(b1 + 1, p.Length());
	int a2 = p.Pos(":") + 1;
	int b2 = p.Pos(",");
	UnicodeString capt = p.SubString(a2 + 1, b2 - a2 - 2);
//	UnicodeString capt = p.SubString(a2, b2 - a2 - 1);
	contact->caption = capt;

	p = p.SubString(b2 + 1, p.Length());
	int a3 = p.Pos(":") + 1;
	int b3 = p.Pos(",");
	UnicodeString type = p.SubString(a3 + 1, b3 - a3 - 2);
//	UnicodeString type = p.SubString(a3, b3 - a3 - 1);
	contact->type = type;

	p = p.SubString(b3 + 1, p.Length());
	int a4 = p.Pos(":") + 1;
	int b4 = p.Pos(",");
	UnicodeString pid = p.SubString(a4 + 1, b4 - a4 - 2);
//	UnicodeString pid = p.SubString(a4, b4 - a4 - 1);
	contact->pid = pid;

//	p = p.SubString(b4 + 1, p.Length());
//	int a5 = p.Pos(":") + 1;
//	int b5 = p.Pos(",");
//	UnicodeString pas = p.SubString(a5, b5 - a5);
//	contact->pas = pas;

	p = p.SubString(b4 + 1, p.Length());
	int a6 = p.Pos(":") + 1;
	int b6 = p.Pos("null");
	if (a6 != b6) {
		p = p.SubString(a6, p.Length());
		contact->inner = parseContact(p);
	}
	else
	{
		contact->inner = NULL;
		b6 = p.Pos(",");
		p = p.SubString(b6 + 1, p.Length());
	}

	int a7 = p.Pos(":") + 1;
	int b7 = p.Pos("null");
	if (a7 != b7) {
		p = p.SubString(a7, p.Length());
		contact->next = parseContact(p);
	}
	else
	{
		b7 = p.Pos('}') + 2;
		if (b7 < p.Length()) {
			p = p.SubString(b7, p.Length());
		}
		contact->next = NULL;
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
