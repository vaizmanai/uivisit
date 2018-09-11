//---------------------------------------------------------------------------

#ifndef frcontactH
#define frcontactH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>

#define MAX_BUFF_CONVERT 256
//---------------------------------------------------------------------------
class Tfcontact : public TForm
{
__published:	// IDE-managed Components
	TEdit *EditPid;
	TEdit *EditPas;
	TEdit *EditCaption;
	TMemo *MemoDesc;
	TComboBox *Parent;
	TButton *ButtonAdd;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TApplicationEvents *ApplicationEvents;
	void __fastcall ButtonAddClick(TObject *Sender);
	void __fastcall ApplicationEventsShortCut(TWMKey &Msg, bool &Handled);

private:	// User declarations
	bool fold;
public:		// User declarations
	__fastcall Tfcontact(TComponent* Owner);

	void prepAsFolder(bool n);
	void prepAsNode(bool n);

	int id;
    UnicodeString parent;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfcontact *fcontact;
//---------------------------------------------------------------------------
#endif
