//---------------------------------------------------------------------------

#ifndef threadclientH
#define threadclientH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <IdTCPClient.hpp>

#include "routines.h"
#include "processing.h"

//---------------------------------------------------------------------------
class ThreadClient : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall ThreadClient(TIdTCPClient *TCPClient);
	 TIdTCPClient *TCPClient;

     void Send(Message message);
};
//---------------------------------------------------------------------------
#endif
