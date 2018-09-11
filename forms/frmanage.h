//---------------------------------------------------------------------------

#ifndef frmanageH
#define frmanageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "routines.h"
#include <System.Notification.hpp>
#include <System.Win.TaskbarCore.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.JumpList.hpp>
#include <Vcl.ShellAnimations.hpp>
#include <Vcl.Taskbar.hpp>
//---------------------------------------------------------------------------
class Tfmanage : public TForm
{
__published:	// IDE-managed Components
	TButton *ButtonRefresh;
	TComboBox *ListVNC;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *EditHostname;
	TLabel *Label3;
	TEdit *EditUptime;
	TButton *ButtonReVNC;
	TButton *ButtonUpdate;
	TButton *ButtonReload;
	TButton *ButtonRestart;
	TApplicationEvents *ApplicationEvents;
	void __fastcall ButtonRefreshClick(TObject *Sender);
	void __fastcall ButtonReVNCClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ButtonUpdateClick(TObject *Sender);
	void __fastcall ButtonReloadClick(TObject *Sender);
	void __fastcall ButtonRestartClick(TObject *Sender);
	void __fastcall ApplicationEventsShortCut(TWMKey &Msg, bool &Handled);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfmanage(TComponent* Owner);

    Contact *contact;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfmanage *fmanage;
//---------------------------------------------------------------------------
#endif
