//---------------------------------------------------------------------------

#ifndef routinesH
#define routinesH
//---------------------------------------------------------------------------

#include <System.hpp>
#include "Registry.hpp"
#include "TlHelp32.h"

#define COMMUNICATORNAME L"communicator.exe"

#define MAX_MESSAGES 16
#define TIMEOUT_READING 250
#define TIME_IDLE 250
#define MAX_BUFFER 1024*1024


#define TYPE_LOG_ERROR 1
#define TYPE_LOG_INFO 2
#define TYPE_LOG_DETAIL 3
#define TYPE_LOG_FULL 4

UnicodeString type_log[] = {
							"BLANK",
							"ERROR",
							"INFO",
							"DETAIL",
							"FULL" };


#define WM_VISIT_EXIT	WM_USER + 1
#define WM_VISIT_LOGIN	WM_USER + 2
#define WM_VISIT_NOTIF	WM_USER + 3
#define WM_VISIT_LOG	WM_USER + 4
#define WM_VISIT_UPDATE WM_USER + 5
#define WM_VISIT_EXEC	WM_USER + 6
#define WM_VISIT_MESS	WM_USER + 7
#define WM_VISIT_DISCON	WM_USER + 8
#define WM_VISIT_CONT   WM_USER + 9
#define WM_VISIT_DCONT  WM_USER + 10
#define WM_VISIT_IVNC   WM_USER + 11
#define WM_VISIT_INCLNT WM_USER + 12
#define WM_VISIT_ALOGIN WM_USER + 13
#define WM_VISIT_RELOAD WM_USER + 14
#define WM_VISIT_MCONT  WM_USER + 15
#define WM_VISIT_SRLOAD WM_USER + 16

typedef struct Contact {
	int id;
	UnicodeString caption;
	UnicodeString pid;
	UnicodeString pas;
	UnicodeString type;

	Contact *next;
	Contact *inner;

    int status;
	void *data;
} Contact;

typedef struct {
	UnicodeString pid;
	UnicodeString pass;
	UnicodeString version;
	UnicodeString webpanel; //наша веб морда
//	UnicodeString client; //команда для запуска vnc клиента
//	UnicodeString manage; //команда для запуска панели настроек vnc сервера
    UnicodeString server;

	Contact *contact;

	void clean(){
		this->pid = "";
		this->pass = "";
//		this->client = "";
//		this->manage = "";
		this->contact = NULL;
//		this->mainForm = NULL;
		this->mainEnabling = true;
	}

	bool debug;

	UnicodeString profilelogin;
	UnicodeString profilepass;

	HWND mainForm;
	volatile bool mainEnabling;
} Client;

typedef struct {
	int type;
	int count_poles;
	UnicodeString messages[MAX_MESSAGES];
} Message;

typedef struct {
	int type;
	void (*process)(Message);
} Process;


HWND getMainHandle();

void addLog(int type, UnicodeString message);

Message makeMessage(int type, int count_poles, ...);

Message parseMessage(UnicodeString messages);

UnicodeString printMessage(Message message);

bool ExecProgram(UnicodeString cmd, UnicodeString arg, bool elevate, bool invisible);

bool ExistService();

int CountVisits();

void CloseCommunicator();

void CloseVisits();

bool SetCurrentUserThread();

Contact* parseContact(UnicodeString &text);

Contact* getContact(Contact *first, int id);

Contact* getContact(Contact *first, UnicodeString pid);

Contact* delContact(Contact *first, int id);

void swap(Contact *a, Contact *b);

void sortNodes(Contact *first);

UnicodeString cleanPid(UnicodeString pid);

#endif
