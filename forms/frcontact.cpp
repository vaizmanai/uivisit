//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frcontact.h"
#include "frmain.h"
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
		this->Caption = "Create group";
		this->ButtonAdd->Caption = "Create";
	}
	else
	{
		this->Caption = "Edit group";
		this->ButtonAdd->Caption = "Save";
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
		this->Caption = "Create contact";
		this->ButtonAdd->Caption = "Create";
	}
	else
	{
		this->Caption = "Edit contact";
		this->ButtonAdd->Caption = "Save";
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


