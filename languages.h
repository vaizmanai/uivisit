//---------------------------------------------------------------------------

#ifndef languagesH
#define languagesH
//---------------------------------------------------------------------------
#include "routines.h"

#define L_END                   	0
#define L_RESERVED		        	1
#define L_NAME              		2 //используем для отображения в меню
#define L_ALERT_EMPTY_MESSAGE		3
#define L_ALERT_NETWORK_MESSAGE 	4
#define L_ALERT_PROXY_MESSAGE		5
#define L_ALERT_AUTH_MESSAGE		6
#define L_ALERT_VNC_MESSAGE			7
#define L_ALERT_TIMEOUT_MESSAGE 	8
#define L_ALERT_PEER_MESSAGE		9
#define L_ALERT_TYPE_MESSAGE    	10
#define L_ALERT_AUTH_FAIL_MESSAGE	11
#define L_ALERT_REG_FAIL_MESSAGE    12
#define L_ALERT_REG_MAIL_MESSAGE	13
#define L_ALERT_REG_SUCC_MESSAGE    14
#define L_ERROR_MESSAGE         	15
#define L_APPLY_LANG            	16
#define L_ABSENT_VNC            	17
#define L_UNINSTALL_SERVICE     	18
#define L_INSTALL_SERVICE       	19
#define L_ABSENT_WEB		    	20
#define L_CAPTION               	21
#define L_EXIT                  	22
#define L_MANAGE                	23
#define L_WEB_PANEL             	24
#define L_NEW_GROUP             	25
#define L_NEW_CONT              	26
#define L_EDIT                  	27
#define L_REMOVE                	28
#define L_LOCAL_PC              	29
#define L_REMOTE_PC             	30
#define L_PASSWORD              	31
#define L_CONNECT               	32
#define L_LOGIN_PROFILE         	33
#define L_LOGIN                 	34
#define L_SIGNIN                	35
#define L_LOGOUT                	36
#define L_PROFILE               	37
#define L_REFRESH               	38
#define L_SAVE                  	39
#define L_COMMON_INFO				40
#define L_AUTH						41
#define L_PROXY						42
#define L_OS						43
#define L_NAME_PC					44
#define L_VERSION_VNC				45
#define L_LANG						46
#define L_REINSTALL					47
#define L_UPDATE					48
#define L_RELOAD					49
#define L_RESTART					50
#define L_ADD						51
#define L_EMAIL_PROFILE				52
#define L_PASS_PROFILE				53
#define L_VERSION					54
#define L_SERVER_PROXY				55
#define L_PORT_PROXY				56
#define L_APPLY						57
#define L_ALERT						58
#define L_CAPTION_ITEM              59
#define L_SAVE                      60
#define L_CREATE                    61
#define L_EDIT_GROUP                62
#define L_CREATE_GROUP              63
#define L_EDIT_ITEM                 64
#define L_CREATE_ITEM               65
#define L_ID                    	66
#define L_PARENT                    67
#define L_MAX_ITEMS                 68


wchar_t *languages_russian[L_MAX_ITEMS] = {
	L"",
	L"",
	L"русский",
	L"пустое сообщение",
	L"ошибка сети",
	L"ошибка прокси",
	L"ошибка авторизации",
	L"ошибка VNC",
	L"ошибка времени ожидания",
	L"отсутствует пир",
	L"неправильный тип подключения",  //10
	L"ошибка авторизации",
	L"учетная запись занята",
	L"не удалось отправить письмо",
	L"регистрация выполнена",
	L"Неудачное подключение: ",
	L"Для применения языка требуется перезапустить интерфейс",
	L"У нас нет доступных VNC клиентов!",
	L"Удалить службу",
	L"Установить службу",
	L"У нас нет информации о WEB!",   //20
	L"Менеджер удаленного доступа reVisit",
	L"Выйти",
	L"Управление",
	L"Web-панель",
	L"Новая группа",
	L"Новый контакт",
	L"Редактирование",
	L"Удалить",
	L"Локальный компьютер",
	L"Удаленный компьютер",           //30
	L"Пароль",
	L"Подключение",
	L"Вход в учетную запись",
	L"Вход",
	L"Регистрация",
	L"Выход",
	L"Профиль",
	L"Обновить",
	L"Сохранить",
	L"Общие данные",                   //40
	L"Авторизация",
	L"Прокси",
	L"Операционная система",
	L"Имя компьютера",
	L"Версия VNC",
	L"Язык интерфейса",
	L"Переустановить",
	L"Обновить",
	L"Перезапустить",
	L"Перезагрузить",                  //50
	L"Добавить",
	L"E-mail профиля",
	L"Пароль профиля",
	L"Версия reVisit",
	L"Адрес proxy сервера",
	L"Порт proxy сервера",
	L"Применить",
	L"Уведомление",
	L"Название",
	L"Сохранить",                      //60
	L"Создать",
	L"Редактирование группы",
	L"Создание группы",
	L"Редактирование контакта",
	L"Создание контакта",
	L"Идентификатор",
	L"Родительская группа" };

wchar_t *languages_english[L_MAX_ITEMS] = {
	L"",
	L"",
	L"english",
	L"empty message",
	L"network error",
	L"proxy error",
	L"auth error",
	L"VNC problem",
	L"timeout",
	L"peer is absent",
	L"unsupported type of connection",
	L"auth error",
	L"login isn't available",
	L"couldn't send email",
	L"reg is successful",
	L"Fail: ",
	L"For apply language it should reload UI",
	L"We don't have available VNC!",
	L"Uninstall service",
	L"Install service",
	L"We don't have info about WEB!",
	L"Manager of remote control reVisit",
	L"Exit",
	L"Management",
	L"Web-panel",
	L"New group",
	L"New item",
	L"Edit",
	L"Remove",
	L"Local PC",
	L"Remote PC",
	L"Password",
	L"Connect",
	L"Private profile",
	L"Login",
	L"Sign-in",
	L"Logout",
	L"Profile",
	L"Refresh",
	L"Save",
	L"Common info",
	L"Authorization",
	L"Proxy",
	L"OS",
	L"Name of PC",
	L"Version of VNC",
	L"Language",
	L"Reinstall",
	L"Update",
	L"Reload",
	L"Restart",
	L"Add",
	L"E-mail of profile",
	L"Password of profile",
	L"reVisit version",
	L"Proxy-server address",
	L"Proxy-server port",
	L"Apply",
	L"Message",
	L"Caption",
	L"Save",                      //60
	L"Create",
	L"Edit group",
	L"Create group",
	L"Edit item",
	L"Create item",
	L"ID",
	L"Parent" };

wchar_t *languages_farsi[L_MAX_ITEMS] = {
    L"",
	L"",
	L"فارسی",
	L"پیام خالی",
	L"خطای شبکه",
	L"خطای پروکسی",
	L"خطا احراز هویت",
	L"مسئله VNC",
	L"تعطیلات",
	L"همکار وجود ندارد",
	L"نوع اتصال نامعتبر است",
	L"auth error",
	L"ورود در دسترس نیست",
	L"ایمیل نمی تواند ارسال شود",
	L"ثبت نام موفق است",
	L"شکست: ",
	L"برای درخواست زبان باید UI را دوباره بارگیری",
	L"ما VNC موجود نداریم!",
	L"حذف سرویس",
	L"نصب سرویس",
	L"ما اطلاعاتی در مورد WEB نداریم!",
	L"مدیر کنترل از راه دور reVisit",
	L"خروج",
	L"مدیریت",
	L"وب پانل",
	L"گروه جدید",
	L"گزینه جدید",
	L"ویرایش",
	L"برداشتن",
	L"کامپیوتر محلی",
	L"کامپیوتر از راه دور",
	L"کلمه عبور",
	L"اتصال",
	L"مشخصات خصوصی",
	L"ورود",
	L"ثبت",
	L"خروج",
	L"مشخصات",
	L"تازه کردن",
	L"صرفه جویی",
	L"اطلاعات رایج",
	L"مجوز",
	L"پروکسی",
	L"سیستم عامل",
	L"نام کامپیوتر",
	L"نسخه VNC",
	L"زبان",
	L"نصب مجدد",
	L"به روز رسانی",
	L"بارگزاری مجدد",
	L"راه اندازی مجدد",
	L"اضافه کردن",
	L"ایمیل مشخصات",
	L"رمز عبور نمایه",
	L"نسخه reVisit",
	L"آدرس پروکسی سرور",
	L"پورت پروکسی سرور",
	L"درخواست دادن",
	L"پیام",
	L"عنوان",
	L"صرفه جویی",
	L"ايجاد كردن",
	L"ویرایش گروه",
	L"ایجاد گروه",
	L"ویرایش آیتم",
	L"ایجاد آیتم",
	L"شناسه",
	L"والدین" };

#define MY_LANG_RUSSIAN	0
#define MY_LANG_ENGLISH	1
#define MY_LANG_FARSI  	2

wchar_t **languages[L_MAX_ITEMS] = {languages_russian, languages_english, languages_farsi, NULL};

wchar_t *getLangText(int item);

UnicodeString getText(int item);
UnicodeString getFullText(int item, ...);

void applyLangBySystem();

#endif
