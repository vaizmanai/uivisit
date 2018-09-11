//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "threadclient.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ThreadClient::ThreadClient(TIdTCPClient *TCPClient) : TThread(false)
{
	this->FreeOnTerminate = true;
	this->TCPClient = TCPClient;

	if(TCPClient->Connected()) {
		addLog(TYPE_LOG_ERROR, "Уже подключен");
		this->Terminate();
	}
}
//---------------------------------------------------------------------------
void __fastcall ThreadClient::Execute()
{
	addLog(TYPE_LOG_ERROR, "thread запустился");

	if (!this->Terminated) {
		//если это не сервис, то нам нужен коммуникатор
		if (!ExistService()) {
			addLog(TYPE_LOG_INFO, "Распакуем и запустим коммуникатор");

			wchar_t shellPath[MAX_PATH] = {0};

			//получим информацию о program files
			if(GetTempPath(MAX_PATH, shellPath)) {
				wcscat(shellPath, L"\\reClient\\");

				//создаем папку
				if(CreateDirectory(shellPath, 0)) {
					//игнорируем, папка уже может быть создана
					addLog(TYPE_LOG_ERROR, "Не удалось создать папку");
				}

				//распакуем комумникатор
				TResourceStream* ptCommunicator = new TResourceStream((int)HInstance, UnicodeString("COMMUNICATOR"), L"EXEFILE");
				try {
					ptCommunicator->SaveToFile(UnicodeString(shellPath) + COMMUNICATORNAME);
				}
				catch(...) {
					addLog(TYPE_LOG_ERROR, "Не получилось распаковать коммуникатор");
				}

				delete ptCommunicator;
				//запустим его
				UnicodeString attr;
				if (myClient.server.Length()) {
                    attr = "server " + myClient.server;
				}
				ExecProgram(UnicodeString(shellPath) + COMMUNICATORNAME, attr, false, !myClient.debug);
			}
			else {
				addLog(TYPE_LOG_ERROR, "Не удалось получить имя временной папки");
			}
		}
		else {
			addLog(TYPE_LOG_INFO, "Существует сервис, никаких манипуляций с коммуникатором не требуется");
		}
	}


	while(!this->Terminated) {
		try {
			if(!TCPClient->Connected()) {
				TCPClient->Connect();
			}
		}
		catch(...) {
			TCPClient->Disconnect();
			addLog(TYPE_LOG_ERROR, "Ошибка подключения");
			Sleep(TIME_IDLE);
			continue;
		}

		addLog(TYPE_LOG_INFO, "Подключились");
		
		while(true) {
			try {
				UnicodeString data = TCPClient->IOHandler->ReadLn("}", TIMEOUT_READING, MAX_BUFFER, IndyTextEncoding_OSDefault());

				if(data.Length()) {
					//вот так вот с этим госдеповским утф....
					data = UTF8ToUnicodeString(data);

					Message message = parseMessage(data);

					addLog(TYPE_LOG_INFO, "Новое сообщение");

					if(message.type < TMESS_LOCAL_MAX) {
						addLog(TYPE_LOG_DETAIL, printMessage(message));

						while(!myClient.mainEnabling) { //не обрабатываем сообщения если форма перемещается
							Sleep(TIME_IDLE);
						}
						processing[message.type].process(message);
					}
					else {
						addLog(TYPE_LOG_ERROR, "Не правильный тип сообщения");
					}
				}

			}
			catch(...) {
				PostMessage(getMainHandle(), WM_VISIT_DISCON, 0, 0);
				TCPClient->Disconnect();
				addLog(TYPE_LOG_ERROR, "Ошибка чтения");
				myClient.clean();
				Sleep(TIME_IDLE);
				break;
			}
		}
	}

	addLog(TYPE_LOG_ERROR, "thread завершился");
}
//---------------------------------------------------------------------------
void ThreadClient::Send(Message message)
{
	try{
		if(TCPClient->Connected()){
			addLog(TYPE_LOG_INFO, "Отправляем коннектору сообщение");
			TCPClient->IOHandler->Write(printMessage(message), IndyTextEncoding_OSDefault());
		}
		else
		{
			addLog(TYPE_LOG_ERROR, "Нет соединения до коннектора");
		}
	}
	catch(...)
	{
		addLog(TYPE_LOG_ERROR, "Не получилось отправить команду коннектору");
	}
}
//---------------------------------------------------------------------------

