//---------------------------------------------------------------------------

#ifndef processingH
#define processingH
//---------------------------------------------------------------------------

#include "routines.h"
#include "threadclient.h"

extern Client myClient;
extern Options myOptions;

#define TMESS_BLANK 0 				//

#define TMESS_LOCAL_TEST		 20 //
#define TMESS_LOCAL_INFO 		 21 //запрос на идентификатор и пароль, версию и т.п.
#define TMESS_LOCAL_CONNECT		 22 //
#define TMESS_LOCAL_NOTIFICATION 23 //
#define TMESS_LOCAL_INFO_CLIENT  24 //
#define TMESS_LOCAL_TERMINATE    25 //закрытие коммуникатора и службы VNC
#define TMESS_LOCAL_REG          26 //регистрация учетки
#define TMESS_LOCAL_LOGIN        27 //вход в учетку
#define TMESS_LOCAL_CONTACT	 	 28 //
#define TMESS_LOCAL_CONTACTS     29 //
#define TMESS_LOCAL_LOGOUT       30 //
#define TMESS_LOCAL_CONN_CONTACT 31	//подключение к контакту из профиля
#define TMESS_LOCAL_MESSAGE 	 32 //система сообщений
#define TMESS_LOCAL_EXEC 		 33 //запуск приложения, например, внс клиента
#define TMESS_LOCAL_STATUS       34 //
#define TMESS_LOCAL_LISTVNC      35 //
#define TMESS_LOCAL_INFO_CONTACT 36 //
#define TMESS_LOCAL_INFO_ANSWER  37 //
#define TMESS_LOCAL_MANAGE       38 //
#define TMESS_LOCAL_SAVE         39 //
#define TMESS_LOCAL_OPTION_CLEAR 40 //
#define TMESS_LOCAL_RELOAD       41 //
#define TMESS_LOCAL_LOG          42 //
#define TMESS_LOCAL_MYMANAGE	 43 //
#define TMESS_LOCAL_MYINFO		 44	//
#define TMESS_LOCAL_INFO_HIDE    45 //
#define TMESS_LOCAL_CONT_REVERSE 46 //
#define TMESS_LOCAL_OPTIONS_UI 	 47 //
#define TMESS_LOCAL_PROXY	 	 48 //
#define TMESS_LOCAL_STANDART_ALR 49 //
#define TMESS_LOCAL_STANDART_LOG 50 //
#define TMESS_LOCAL_MAX		   	 51 //


void processBlank(Message message);
void processInfo(Message message);
void processNotification(Message message);
void processInfoClient(Message message);
void processTerminate(Message message);
void processLogin(Message message);
void processContact(Message message);
void processContacts(Message message);
void processLogout(Message message);
void processExec(Message message);
void processStatus(Message message);
void processListVNC(Message message);
void processInfoAnswer(Message message);
void processReload(Message message);
void processLog(Message message);
void processHide(Message message);
void processOptionsUI(Message message);
void processProxy(Message message);
void processStandartAlert(Message message);
void processStandartLog(Message message);

Process processing[] = {
	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},	{TMESS_BLANK, processBlank},
	{TMESS_LOCAL_TEST, processBlank},	//20
	{TMESS_LOCAL_INFO, processInfo},
	{TMESS_LOCAL_CONNECT, processBlank},
	{TMESS_LOCAL_NOTIFICATION, processNotification},
	{TMESS_LOCAL_INFO_CLIENT, processInfoClient},
	{TMESS_LOCAL_TERMINATE, processTerminate},
	{TMESS_LOCAL_REG, processBlank},
	{TMESS_LOCAL_LOGIN, processLogin},
	{TMESS_LOCAL_CONTACT, processContact},
	{TMESS_LOCAL_CONTACTS, processContacts},
	{TMESS_LOCAL_LOGOUT, processLogout},
	{TMESS_LOCAL_CONN_CONTACT, processBlank},
	{TMESS_LOCAL_MESSAGE, processBlank},
	{TMESS_LOCAL_EXEC, processExec},
	{TMESS_LOCAL_STATUS, processStatus},
	{TMESS_LOCAL_LISTVNC, processListVNC},
	{TMESS_LOCAL_INFO_CONTACT, processBlank},
	{TMESS_LOCAL_INFO_ANSWER, processInfoAnswer},
	{TMESS_LOCAL_MANAGE, processBlank},
	{TMESS_LOCAL_SAVE, processBlank},
	{TMESS_LOCAL_OPTION_CLEAR, processBlank},
	{TMESS_LOCAL_RELOAD, processReload},
	{TMESS_LOCAL_LOG, processLog},
	{TMESS_LOCAL_MYMANAGE, processBlank},
	{TMESS_LOCAL_MYINFO, processBlank},
	{TMESS_LOCAL_INFO_HIDE, processHide},
	{TMESS_LOCAL_CONT_REVERSE, processBlank},
	{TMESS_LOCAL_OPTIONS_UI, processOptionsUI},
	{TMESS_LOCAL_PROXY, processProxy},
	{TMESS_LOCAL_STANDART_ALR, processStandartAlert},
	{TMESS_LOCAL_STANDART_LOG, processStandartLog}

};



#endif
