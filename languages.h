//---------------------------------------------------------------------------

#ifndef languagesH
#define languagesH
//---------------------------------------------------------------------------
#include "routines.h"


#define L_NAME              	0 //используем для отображения в меню
#define L_ALERT_EMPTY_MESSAGE	1
#define L_ALERT_NETWORK_MESSAGE 2
#define L_ALERT_PROXY_MESSAGE	3
#define L_ALERT_AUTH_MESSAGE	4
#define L_ALERT_VNC_MESSAGE		5
#define L_ALERT_TIMEOUT_MESSAGE 6
#define L_ALERT_PEER_MESSAGE	7
#define L_ALERT_TYPE_MESSAGE	8
#define L_ERROR_MESSAGE         9
#define L_MAX_ITEMS             10


UnicodeString languages_russian[L_MAX_ITEMS] = {
	"русский",
	"пустое сообщение",
	"ошибка сети",
	"ошибка прокси",
	"ошибка авторизации",
	"ошибка VNC",
	"ошибка времени ожидания",
	"отсутствует пир",
	"неправильный тип подключения",
	"Неудачное подключение: " };

UnicodeString languages_english[L_MAX_ITEMS] = {
	"english",
	"empty message",
	"network error",
	"proxy error",
	"auth error",
	"VNC problem",
	"timeout",
	"peer is absent",
	"unsupported type of connection",
	"Fail: " };

UnicodeString *languages[L_MAX_ITEMS] = {languages_russian, languages_english, NULL};


#endif
