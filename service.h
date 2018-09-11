//---------------------------------------------------------------------------
#ifndef serviceH
#define serviceH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <SvcMgr.hpp>
#include <vcl.h>
#include "routines.h"
//---------------------------------------------------------------------------
class TreClientService : public TService
{
__published:    // IDE-managed Components
	void __fastcall ServiceAfterInstall(TService *Sender);
	void __fastcall ServiceExecute(TService *Sender);
	void __fastcall ServiceBeforeUninstall(TService *Sender);
private:        // User declarations
public:         // User declarations
	__fastcall TreClientService(TComponent* Owner);
	TServiceController __fastcall GetServiceController(void);

	friend void __stdcall ServiceController(unsigned CtrlCode);
};
//---------------------------------------------------------------------------
extern PACKAGE TreClientService *reClientService;
extern Client myClient;
//---------------------------------------------------------------------------
#endif
