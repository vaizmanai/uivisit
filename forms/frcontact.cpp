//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frcontact.h"
#include "frmain.h"
#include "languages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfcontact *fcontact;
//---------------------------------------------------------------------------
__fastcall Tfcontact::Tfcontact(TComponent* Owner) : TForm(Owner)
{
    id = -1;
	parent = "";
	fold = false;
	applyLangUI();
}
//---------------------------------------------------------------------------
void __fastcall Tfcontact::ButtonAddClick(TObject *Sender)
{
	char capt[MAX_BUFF_CONVERT];
	UnicodeToUtf8(capt, EditCaption->Text.c_str(), MAX_BUFF_CONVERT);

	char pass[MAX_BUFF_CONVERT];
	UnicodeToUtf8(pass, EditPas->Text.c_str(), MAX_BUFF_CONVERT);

	char pid[MAX_BUFF_CONVERT];
	UnicodeToUtf8(pid, EditPid->Text.c_str(), MAX_BUFF_CONVERT);

	fmain->threadclient->Send(makeMessage(TMESS_LOCAL_CONTACT, 6,
		UnicodeString(id).c_str(),
		fold?L"fold":L"node",
		UnicodeString(capt),
		UnicodeString(pid),
		EditPas->Text == "*****"?L"":UnicodeString(pass).c_str(),
		parent));

	this->Close();
}
//---------------------------------------------------------------------------
void Tfcontact::prepAsFolder(bool n)
{
	if (n) {
		this->Caption = getText(L_CREATE_GROUP); //"Создание группы";
		this->ButtonAdd->Caption = getText(L_CREATE);
	}
	else
	{
		this->Caption = getText(L_EDIT_GROUP);
		this->ButtonAdd->Caption = getText(L_SAVE);
	}
	EditPid->Enabled = false;
	EditPas->Enabled = false;
	MemoDesc->Enabled = false;
	fold = true;
}
//---------------------------------------------------------------------------
void Tfcontact::prepAsNode(bool n)
{
	if (n) {
		this->Caption = getText(L_CREATE_ITEM); //"Создание контакта";
		this->ButtonAdd->Caption = getText(L_CREATE);
	}
	else
	{
		this->Caption = getText(L_EDIT_ITEM); //"Редактирование контакта";
		this->ButtonAdd->Caption = getText(L_SAVE);
	}
	EditPid->Enabled = true;
	EditPas->Enabled = true;
	MemoDesc->Enabled = false;
	fold = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfcontact::ApplicationEventsShortCut(TWMKey &Msg, bool &Handled)
{
	if (Msg.CharCode == 27) {
		this->Close();
	}
}
//---------------------------------------------------------------------------
void Tfcontact::applyLangUI()
{
	Caption = getText(L_CREATE_ITEM);

	Label1->Caption = getText(L_CAPTION_ITEM);
	Label2->Caption = getText(L_PASSWORD);
	Label3->Caption = getText(L_ID);
	Label4->Caption = getText(L_PARENT);

	ButtonAdd->Caption = getText(L_SAVE);
}
//---------------------------------------------------------------------------

