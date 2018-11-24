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
#include <Vcl.DockTabSet.hpp>
#include <Vcl.Tabs.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfmanage : public TForm
{
__published:	// IDE-managed Components
	TButton *ButtonRefresh;
	TApplicationEvents *ApplicationEvents;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TEdit *EditUptime;
	TLabel *Label3;
	TEdit *EditHostname;
	TLabel *Label2;
	TLabel *Label1;
	TComboBox *ListVNC;
	TButton *ButtonReVNC;
	TButton *ButtonUpdate;
	TButton *ButtonReload;
	TButton *ButtonRestart;
	TButton *ButtonAddProfile;
	TEdit *EditProfileEmail;
	TEdit *EditProfilePass;
	TLabel *Label4;
	TLabel *Label5;
	TComboBox *ComboBox;
	TLabel *Label6;
	TEdit *EditVersion;
	TPanel *Panel4;
	TLabel *Label7;
	TLabel *Label8;
	TButton *ButtonProxyApply;
	TEdit *EditProxyServer;
	TEdit *EditProxyPort;
	void __fastcall ButtonRefreshClick(TObject *Sender);
	void __fastcall ButtonReVNCClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ButtonUpdateClick(TObject *Sender);
	void __fastcall ButtonReloadClick(TObject *Sender);
	void __fastcall ButtonRestartClick(TObject *Sender);
	void __fastcall ApplicationEventsShortCut(TWMKey &Msg, bool &Handled);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ComboBoxChange(TObject *Sender);
	void __fastcall ButtonAddProfileClick(TObject *Sender);
	void __fastcall ButtonProxyApplyClick(TObject *Sender);



private:	// User declarations
public:		// User declarations
	__fastcall Tfmanage(TComponent* Owner);

    Contact *contact;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfmanage *fmanage;
//---------------------------------------------------------------------------
#endif
