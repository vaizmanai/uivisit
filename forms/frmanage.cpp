//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmanage.h"
#include "frmain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfmanage *fmanage;
//---------------------------------------------------------------------------
__fastcall Tfmanage::Tfmanage(TComponent* Owner) : TForm(Owner)
{
	contact = NULL;
}
//---------------------------------------------------------------------------
void __fastcall Tfmanage::ButtonRefreshClick(TObject *Sender)
{
	if (contact != NULL) {
		fmain->threadclient->Send(makeMessage(TMESS_LOCAL_INFO_CONTACT, 1, IntToStr(contact->id)));
	}
	else
	{
		fmain->threadclient->Send(makeMessage(TMESS_LOCAL_MYINFO, 0));
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmanage::ButtonReVNCClick(TObject *Sender)
{
	if (contact != NULL) {
		fmain->threadclient->Send(makeMessage(TMESS_LOCAL_MANAGE, 3, IntToStr(contact->id), L"revnc", IntToStr(this->ListVNC->ItemIndex)));
	}
	else
	{
		fmain->threadclient->Send(makeMessage(TMESS_LOCAL_MYMANAGE, 2, L"revnc", IntToStr(this->ListVNC->ItemIndex)));
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmanage::FormClose(TObject *Sender, TCloseAction &Action)
{
	ButtonReVNC->Enabled = false;
	ButtonUpdate->Enabled = false;
	ButtonReload->Enabled = false;
	ButtonRestart->Enabled = false;
	EditHostname->Text = "";
    EditUptime->Text = "";
	ListVNC->ItemIndex = -1;
	contact = NULL;
}
//---------------------------------------------------------------------------
void __fastcall Tfmanage::ButtonUpdateClick(TObject *Sender)
{
	if (contact != NULL) {
		fmain->threadclient->Send(makeMessage(TMESS_LOCAL_MANAGE, 2, IntToStr(contact->id), L"update"));
	}
	else
	{
		fmain->threadclient->Send(makeMessage(TMESS_LOCAL_MYMANAGE, 1, L"update"));
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmanage::ButtonReloadClick(TObject *Sender)
{
	if (contact != NULL) {
		fmain->threadclient->Send(makeMessage(TMESS_LOCAL_MANAGE, 2, IntToStr(contact->id), L"reload"));
	}
	else
	{
		fmain->threadclient->Send(makeMessage(TMESS_LOCAL_MYMANAGE, 1, L"update"));
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmanage::ButtonRestartClick(TObject *Sender)
{
	if (contact != NULL) {
		fmain->threadclient->Send(makeMessage(TMESS_LOCAL_MANAGE, 2, IntToStr(contact->id), L"restart"));
	}
	else
	{
		fmain->threadclient->Send(makeMessage(TMESS_LOCAL_MYMANAGE, 1, L"restart"));
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmanage::ApplicationEventsShortCut(TWMKey &Msg, bool &Handled)
{
	if (Msg.CharCode == 27) {
		this->Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmanage::FormShow(TObject *Sender)
{
	ButtonRefresh->Click();
}
//---------------------------------------------------------------------------

