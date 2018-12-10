//---------------------------------------------------------------------------

#ifndef fralertH
#define fralertH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#define ALERT_TIMEOUT_SEC 7
//---------------------------------------------------------------------------
class Tfalert : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer;
	TLabel *Label;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall TimerTimer(TObject *Sender);
private:	// User declarations
    short counter;
public:		// User declarations
	__fastcall Tfalert(TComponent* Owner);
    void applyLangUI();
	void __fastcall ShowMessage(String message);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfalert *falert;
//---------------------------------------------------------------------------
#endif
