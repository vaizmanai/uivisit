//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fralert.h"
#include "frmain.h"
#include "languages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfalert *falert;
//---------------------------------------------------------------------------
__fastcall Tfalert::Tfalert(TComponent* Owner): TForm(Owner)
{
	applyLangUI();
}
//---------------------------------------------------------------------------
void __fastcall Tfalert::FormShow(TObject *Sender)
{
	this->Top = fmain->Top + fmain->Height/2 - this->Height/2;
	this->Left = fmain->Left + fmain->Width/2 - this->Width/2;
}
//---------------------------------------------------------------------------
void __fastcall Tfalert::TimerTimer(TObject *Sender)
{
	while(this->AlphaBlendValue < 255){
		this->AlphaBlendValue = this->AlphaBlendValue + 85;
		return;
	}
	while(this->counter < ALERT_TIMEOUT_SEC) {
		this->counter++;
		return;
	}
	this->Timer->Enabled = false;
    this->Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfalert::ShowMessage(String message)
{
    this->AlphaBlend = true;
	this->AlphaBlendValue = 0;
	this->Timer->Enabled = true;
	this->counter = 0;
    this->Label->Caption = message;
	this->Show();
}
//---------------------------------------------------------------------------
void Tfalert::applyLangUI()
{
	Caption = getText(L_MANAGE);
}
