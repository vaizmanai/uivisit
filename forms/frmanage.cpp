//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmanage.h"
#include "frmain.h"
#include "fralert.h"
#include "frcontact.h"
#include "languages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfmanage *fmanage;
//---------------------------------------------------------------------------
__fastcall Tfmanage::Tfmanage(TComponent* Owner) : TForm(Owner)
{
	contact = NULL;
	Panel2->Left = Panel1->Left;
	Panel3->Left = Panel1->Left;
	Panel4->Left = Panel1->Left;
	ClientWidth = Panel1->Width + Panel1->Left + 8;
	Panel2->Hide();
	Panel3->Hide();
	Panel4->Hide();
	ListLanguages->Enabled = false;
	ListLanguages->Clear();
	ButtonProxyApply->Enabled = false;
    applyLangUI();
}
//---------------------------------------------------------------------------
void __fastcall Tfmanage::ButtonRefreshClick(TObject *Sender)
{
	if (contact != NULL) {
		fmain->threadclient->Send(makeMessage(TMESS_LOCAL_INFO_CONTACT, 1, IntToStr(contact->id)));
	}
	else
	{
		ListLanguages->Enabled = true;
		ButtonProxyApply->Enabled = true;
        int i = 0;
		while(languages[i] != NULL){
			ListLanguages->Items->Add(UnicodeString(languages[i][L_NAME]));
			i++;
		}

		if(myOptions.Lang < ListLanguages->Items->Count){
			ListLanguages->ItemIndex = myOptions.Lang;
		}
		fmain->threadclient->Send(makeMessage(TMESS_LOCAL_MYINFO, 0));
	}

   	fmain->threadclient->Send(makeMessage(TMESS_LOCAL_PROXY, 0));
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
    ButtonAddProfile->Enabled = false;
	EditHostname->Text = "";
	EditUptime->Text = "";
	EditVersion->Text = "";
	EditProxyServer->Text = "";
    EditProxyPort->Text = "";
	ListVNC->ItemIndex = -1;
	ListLanguages->Enabled = false;
	ListLanguages->Clear();
    ButtonProxyApply->Enabled = false;
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
void __fastcall Tfmanage::ComboBoxChange(TObject *Sender)
{
	Panel1->Hide();
	Panel2->Hide();
	Panel3->Hide();
	Panel4->Hide();

	switch (ComboBox->ItemIndex) {
		case 0:
			Panel1->Show();
			break;
		case 1:
			Panel2->Show();
			break;
		case 2:
			Panel3->Show();
			break;
		case 3:
			Panel4->Show();
			break;
	}

}
//---------------------------------------------------------------------------
void __fastcall Tfmanage::ButtonAddProfileClick(TObject *Sender)
{
	fmain->threadclient->Send(makeMessage(TMESS_LOCAL_CONT_REVERSE, 2, EditProfileEmail->Text, EditProfilePass->Text));
}
//---------------------------------------------------------------------------
void __fastcall Tfmanage::ButtonProxyApplyClick(TObject *Sender)
{
	fmain->threadclient->Send(makeMessage(TMESS_LOCAL_PROXY, 2, EditProxyServer->Text, EditProxyPort->Text));
}
//---------------------------------------------------------------------------
void __fastcall Tfmanage::ListLanguagesChange(TObject *Sender)
{
	myOptions.Lang = fmanage->ListLanguages->ItemIndex;
	applyLangUI();
	fmain->applyLangUI();
	fcontact->applyLangUI();
	falert->applyLangUI();
//	falert->ShowMessage(getFullText(L_APPLY_LANG, L_END));
}
//---------------------------------------------------------------------------
void Tfmanage::applyLangUI()
{
	Caption = getText(L_MANAGE);

	ComboBox->Clear();
	ComboBox->Items->Add(getText(L_COMMON_INFO));
	ComboBox->Items->Add(getText(L_MANAGE));
	ComboBox->Items->Add(getText(L_AUTH));
	ComboBox->Items->Add(getText(L_PROXY));

	Label3->Caption = getText(L_OS); //Операционная система
	Label2->Caption = getText(L_NAME_PC); //Имя компьютера
	Label1->Caption = getText(L_VERSION_VNC); //Версия VNC
	Label9->Caption = getText(L_LANG); //Язык интерфейса

	ButtonReVNC->Caption = getText(L_REINSTALL); //Переустановить
	ButtonUpdate->Caption = getText(L_UPDATE); //Обновить
	ButtonReload->Caption = getText(L_UPDATE); //Перезапустить
	ButtonRestart->Caption = getText(L_RESTART); //Перезагрузить
	ButtonAddProfile->Caption = getText(L_ADD); //Добавить
	Label4->Caption = getText(L_EMAIL_PROFILE); //E-mail профиля
	Label5->Caption = getText(L_PASS_PROFILE); //Пароль профиля

	Label6->Caption = getText(L_VERSION); //Версия reVisit
	Label7->Caption = getText(L_SERVER_PROXY); //Адрес proxy сервера
	Label8->Caption = getText(L_PORT_PROXY); //Порт proxy сервера
	ButtonProxyApply->Caption = getText(L_APPLY); //Применить

    ComboBox->ItemIndex = 0;
}

