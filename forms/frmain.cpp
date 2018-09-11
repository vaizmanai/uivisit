//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmain.h"
#include "frcontact.h"
#include "frmanage.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
Tfmain *fmain;
//---------------------------------------------------------------------------
__fastcall Tfmain::Tfmain(TComponent* Owner) : TForm(Owner)
{
	myClient.mainEnabling = true;

	if (!myClient.debug) {
		this->ClientWidth = this->LabelPid->Left + this->PanelContacts->Left + this->PanelContacts->Width;
	}

	threadclient = new ThreadClient(Client);

    TIcon* iconsh = new TIcon();
	iconsh->Handle = LoadIcon(0, IDI_SHIELD);
	if(iconsh->Handle) N2->ImageIndex = ImageList->AddIcon(iconsh);
	if (ExistService()) {
		N2->Caption = "Удалить службу";
	}
	else {
		N2->Caption = "Установить службу";
	}

	this->Constraints->MaxWidth = this->Width;
	this->Constraints->MaxHeight = this->Height;
	this->Constraints->MinWidth = this->Width;
	this->Constraints->MinHeight = this->Height;

	PanelLogin->Left = PanelContacts->Left;
	PanelLogin->Top = PanelContacts->Top;

    TrayIcon->BalloonTitle = "Менеджер удаленного доступа reVisit";
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::N1Click(TObject *Sender)
{
    this->Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::TrayIconDblClick(TObject *Sender)
{
	if (!this->Visible) {
		this->Show();
		Application->BringToFront();
	}
	else {
		this->Hide();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::UpdaterUITimer(TObject *Sender)
{
	LabelVersion->Caption = "reClient " + myClient.version;
	LabelPid->Text = myClient.pid;
	LabelPass->Text = myClient.pass;
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::ButtonConnectClick(TObject *Sender)
{
//	if(!myClient.client.Length()) {
//		ShowMessage("У нас нет доступных VNC клиентов!");
//		return;
//	}
	threadclient->Send(makeMessage(TMESS_LOCAL_CONNECT, 2, EditPid->Text.c_str(), EditPass->Text.c_str()));
//	if (!ExecProgram(myClient.client.SubString(0, myClient.client.LastDelimiter(' ')), myClient.client.SubString(myClient.client.LastDelimiter(' '), myClient.client.Length()), false, false) ) {
//		ShowMessage("Не удалось запустить VNC клиент!");
//	}
//	else {
//		addLog(TYPE_LOG_INFO, "пробуем подключиться");
//	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::Web1Click(TObject *Sender)
{
	if(!myClient.webpanel.Length()) {
		ShowMessage("У нас нет информации о WEB!");
		return;
	}
	ExecProgram(myClient.webpanel, "", false, false);
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::N2Click(TObject *Sender)
{
	if (!ExistService()) {
		UnicodeString attr = L"-service -install" + UnicodeString(myClient.debug==true?" -debug":"");
		if (myClient.server.Length()) {
			attr = attr + " -server " + myClient.server;
		}
		if (ExecProgram(Application->ExeName, attr, true, true)) {
			threadclient->Send(makeMessage(TMESS_LOCAL_TERMINATE, 1, L"1"));
			Application->Terminate();
		}
	}
	else
	{
		//удаление службы нужно делать от пользователя, а не от службы
		HANDLE ntoken = GetCurrentProcessToken();
//ShowMessage((int)ntoken);
		bool b = SetCurrentUserThread();
//ShowMessage((int)b);

		ExecProgram("net", "stop reClientService", true, true);
		if (ExecProgram(Application->ExeName, "-service -uninstall", true, true) ) {
			threadclient->Send(makeMessage(TMESS_LOCAL_TERMINATE, 1, L"1"));
			N2->Caption = "Установить службу";
		}

		if(ntoken){
			b = SetThreadToken(0, ntoken);
//ShowMessage((int)b);
			b = CloseHandle(ntoken);
//ShowMessage((int)b);
		}
	}
}
//---------------------------------------------------------------------------
void Tfmain::addNode(Contact *contact, TTreeNode *parent)
{
	TTreeNode *p = TreeView->Items->AddChild(parent, contact->caption);
	p->Data = contact;
	contact->data = (void *)p;
	if (contact->type == "fold") {
		p->ImageIndex = 0;
		p->SelectedIndex = 0;
	}
	else {
		if (contact->status) {
			p->ImageIndex = 2;
			p->SelectedIndex = 2;
		}
		else {
			p->ImageIndex = 1;
			p->SelectedIndex = 1;
		}
	}
}
//---------------------------------------------------------------------------
void Tfmain::addNodes(Contact *contact, TTreeNode *parent)
{
	while (contact != NULL) {
		if(contact->inner != NULL) {
			TTreeNode *p = TreeView->Items->AddChild(parent, contact->caption);
			p->Data = contact;
			contact->data = (void *)p;
			p->ImageIndex = 0;
			p->SelectedIndex = 0;
			addNodes(contact->inner, p); //наполним папку
		}
		else {
			addNode(contact, parent); //добавим контакт
		}
		contact = contact->next;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::TreeViewDblClick(TObject *Sender)
{
	TPoint p;
	GetCursorPos(&p);
	p = TreeView->ScreenToClient(p);

	THitTests MH = TreeView->GetHitTestInfoAt(p.x, p.y);
	if(MH.Contains(htOnItem)) {
		Contact *c = (Contact *)TreeView->Selected->Data;
		if (c->type == "node") {
//			if(!myClient.client.Length()){
//				ShowMessage("У нас нет доступных VNC клиентов!");
//				return;
//			}
			threadclient->Send(makeMessage(TMESS_LOCAL_CONN_CONTACT, 1, UnicodeString(c->id).w_str()));
//			if (!ExecProgram(myClient.client.SubString(0, myClient.client.LastDelimiter(' ')), myClient.client.SubString(myClient.client.LastDelimiter(' '), myClient.client.Length()), false, false) ) {
//				ShowMessage("Не удалось запустить VNC клиент!");
//			}
			addLog(TYPE_LOG_INFO, "пробуем подключиться");
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (!ExistService()) {
		threadclient->Send(makeMessage(TMESS_LOCAL_TERMINATE, 1, L"0"));
		if(myClient.debug) {
			MemoLog->Lines->SaveToFile("reclient.log");
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::ButtonRegisterClick(TObject *Sender)
{
	threadclient->Send(makeMessage(TMESS_LOCAL_REG, 1, EditProfileLogin->Text));
//	ShowMessage("Отправили запрос на регистрацию!");
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::ButtonLoginClick(TObject *Sender)
{
	threadclient->Send(makeMessage(TMESS_LOCAL_LOGIN, 3,
	EditProfileLogin->Text, EditProfilePass->Text, CheckProfileSave->Checked?L"1":L"0"));
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::ApplicationEventsMessage(tagMSG &Msg, bool &Handled)
{
	switch(Msg.message) {
		case 160:
		{
			myClient.mainEnabling = true;
			break;
		}
		case WM_NCLBUTTONDOWN:
		{
			myClient.mainEnabling = false;
			break;
		}
		case WM_VISIT_EXIT:
		{
			Close();
			break;
		}
		case WM_VISIT_LOGIN:
		{
			PanelLogin->Visible = false;
			PanelContacts->Visible = true;

			fmanage->ListVNC->Clear();
			fmain->threadclient->Send(makeMessage(TMESS_LOCAL_LISTVNC, 0)); //получим список доступных vnc
			break;
		}
		case WM_VISIT_NOTIF:
		{
			UnicodeString *buf = (UnicodeString *)Msg.lParam;
//			Application->MessageBoxW(buf->w_str(), L"Уведомление", 0);

			BalloonHint->Title = "Уведомление";
			BalloonHint->Description = *buf;
			BalloonHint->ShowHint(this);

			StatusBar->SimpleText = "Уведомление: " + *buf;
			delete buf;
			break;
		}
		case WM_VISIT_LOG:
		{
			UnicodeString *buf = (UnicodeString *)Msg.lParam;
			if(myClient.debug) {
				MemoLog->Lines->Add(*buf);
			}
            StatusBar->SimpleText = *buf;
			delete buf;
			break;
		}
		case WM_VISIT_UPDATE:
		{
			TreeView->Items->Clear();
			sortNodes(myClient.contact);
			addNodes(myClient.contact, NULL);
			break;
		}
		case WM_VISIT_EXEC:
		{
			UnicodeString *buf = (UnicodeString *)Msg.lParam;
			if (!ExecProgram(buf->SubString(0, buf->LastDelimiter(' ')), buf->SubString(buf->LastDelimiter(' '), buf->Length()), false, false) ) {
				ShowMessage("Не удалось запустить " + *buf + "!");
			}
			delete buf;
			break;
		}
		case WM_VISIT_DISCON:
		{
			PanelLogin->Show();
			PanelContacts->Hide();
			fmanage->Close();
			fcontact->Close();
			TreeView->Items->Clear();
			EditProfileLogin->Text = "";
			EditProfilePass->Text = "";
			myClient.pid = "";
			myClient.pass = "";
			myClient.contact = NULL; //todo поменять на нормальное удаление
            break;
		}
		case WM_VISIT_MCONT:
		{
			Contact *c = (Contact *)Msg.lParam;
			TTreeNode *p = (TTreeNode*)c->data;
			TTreeNode *n = NULL; //новый узел

			int idParent = Msg.wParam - 1;

			if (idParent == -1) { //в корень
				n = TreeView->Items->AddFirst(NULL, c->caption);
			}
			else{
				Contact *cParent = getContact(myClient.contact, idParent);
				n = TreeView->Items->AddChild((TTreeNode*)cParent->data, c->caption);
			}

            n->ImageIndex = p->ImageIndex;
            n->SelectedIndex = p->SelectedIndex;

			c->data = n;
			n->Data = c;
			MoveTreeViewBranch(p, n);

			TreeView->Items->Delete(p);
			break;
		}
		case WM_VISIT_CONT:
		{
			Contact *c = (Contact *)Msg.lParam;
			TTreeNode *p = (TTreeNode*)c->data;

			if (p) {
				p->Text = c->caption;
				if (c->type != "fold") {
					if (c->status) {
						p->ImageIndex = 2;
						p->SelectedIndex = 2;
					}
					else {
						p->ImageIndex = 1;
						p->SelectedIndex = 1;
					}
				}
			}
			else if (!p) { //новый контакт

				int idParent = Msg.wParam - 1;

				if (idParent == -1) {
					p = TreeView->Items->AddFirst(NULL, c->caption);
				}
				else {
					Contact *cParent = getContact(myClient.contact, idParent);
					if (cParent) {
						p = TreeView->Items->AddChild((TTreeNode*)cParent->data, c->caption);
					}
				}
                if (c->type == "fold") {
					p->ImageIndex = 0;
					p->SelectedIndex = 0;
				}
				else {
					p->ImageIndex = 1;
					p->SelectedIndex = 1;
				}
				c->data = p;
				p->Data = c;
			}
			break;
		}
		case WM_VISIT_DCONT:
		{
			Contact *c = (Contact *)Msg.lParam;
			TTreeNode *p = (TTreeNode*)c->data;
			if (p) {
				p->Delete();
				myClient.contact = delContact(myClient.contact, c->id);
			}
			break;
		}
		case WM_VISIT_IVNC:
		{
			UnicodeString *buf = (UnicodeString *)Msg.lParam;
			fmanage->ListVNC->Items->Add(*buf);
			delete buf;

			break;
		}
		case WM_VISIT_INCLNT:
		{

			UnicodeString **buf = (UnicodeString **)Msg.wParam;
			fmanage->EditHostname->Text = *buf[0];
			fmanage->EditUptime->Text = *buf[1];

			fmanage->ListVNC->ItemIndex = Msg.lParam;
			fmanage->ButtonReVNC->Enabled = true;
			fmanage->ButtonUpdate->Enabled = true;
			fmanage->ButtonReload->Enabled = true;
			fmanage->ButtonRestart->Enabled = true;

            delete buf;
			break;
		}
		case WM_VISIT_ALOGIN:
		{
			EditProfileLogin->Text = myClient.profilelogin;
			EditProfilePass->Text = myClient.profilepass;
			CheckProfileSave->Checked = true;
			ButtonLogin->Click();
			break;
		}
		case WM_VISIT_RELOAD:
		{
			ExecProgram(Application->ExeName, "", false, false);
			this->Close();
			break;
		}
		case WM_VISIT_SRLOAD:
		{
			if (ExecProgram("net", "stop reService", true, true)){
				if (ExecProgram("net", "start reService", true, true)){
					addLog(TYPE_LOG_INFO, "перезапустили сервис");
					this->Close();
				}
				addLog(TYPE_LOG_ERROR, "не получилось запустить сервис");
			}
            addLog(TYPE_LOG_ERROR, "не получилось остановить сервис");
			break;
		}
	}

}
//---------------------------------------------------------------------------
void Tfmain::MoveTreeViewBranch(TTreeNode *src, TTreeNode *dst)
{
	TTreeNode *n = src->getFirstChild();

	while(n){
		TTreeNode *p = TreeView->Items->AddChild(dst, n->Text);

		if (n->getFirstChild()) {
			MoveTreeViewBranch(n, p);
		}

		p->Data = n->Data;
		p->ImageIndex = n->ImageIndex;
		p->SelectedIndex = n->SelectedIndex;
		n = n->getNextSibling();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::ButtonLogoutClick(TObject *Sender)
{
	PanelLogin->Show();
	PanelContacts->Hide();
	TreeView->Items->Clear();
    CheckProfileSave->Checked = false;
	EditProfileLogin->Text = "";
	EditProfilePass->Text = "";
	myClient.profilelogin = "";
    myClient.profilepass = "";

	threadclient->Send(makeMessage(TMESS_LOCAL_LOGOUT, 0, ""));
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::TreeViewContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled)
{
	THitTests MH = TreeView->GetHitTestInfoAt(MousePos.x, MousePos.y);
	if(MH.Contains(htOnItem)) {
		TreeView->Select(TreeView->GetNodeAt(MousePos.x, MousePos.y));
		N4->Visible = true;
		N5->Visible = true;
		N7->Visible = true;
	}
	else {
        TreeView->Selected = NULL;
		N4->Visible = false;
		N5->Visible = false;
        N7->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::N5Click(TObject *Sender)
{
	Contact *c = (Contact *)TreeView->Selected->Data;
	if (c != NULL) {
		threadclient->Send(makeMessage(TMESS_LOCAL_CONTACT, 6, UnicodeString(c->id).w_str(), L"del", L"", L"", L"", L"", L""));
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::N3Click(TObject *Sender)
{
	fcontact->parent = -1;

	if (TreeView->Selected) {
		Contact *c = (Contact *)TreeView->Selected->Data;
		if (c != NULL) {
			if (c->type == "fold") {
				fcontact->parent = UnicodeString(c->id);
			}
		}
	}

	fcontact->id = -1;
	fcontact->EditCaption->Text = "";
	fcontact->EditPid->Text = "";
	fcontact->EditPas->Text = "";
	fcontact->MemoDesc->Text = "";
	fcontact->prepAsNode(true);
	fcontact->Show();
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::N4Click(TObject *Sender)
{
	Contact *c = (Contact *)TreeView->Selected->Data;
	fcontact->id = c->id;
	fcontact->parent = "";
	fcontact->EditCaption->Text = c->caption;
	fcontact->EditPid->Text = c->pid;
	fcontact->EditPas->Text = "*****";
	fcontact->MemoDesc->Text = "";
	if (c->type == "fold") {
		fcontact->prepAsFolder(false);
	}
	else {
		fcontact->prepAsNode(false);
	}

	fcontact->Show();
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::N6Click(TObject *Sender)
{
	fcontact->parent = -1;

	if (TreeView->Selected) {
		Contact *c = (Contact *)TreeView->Selected->Data;
		if (c != NULL){
			if (c->type == "fold") {
				fcontact->parent = UnicodeString(c->id);
			}
		}
	}

	fcontact->id = -1;
	fcontact->EditCaption->Text = "";
	fcontact->EditPid->Text = "";
	fcontact->EditPas->Text = "";
	fcontact->MemoDesc->Text = "";
	fcontact->prepAsFolder(true);
	fcontact->Show();
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::ButtonRefreshClick(TObject *Sender)
{
	threadclient->Send(makeMessage(TMESS_LOCAL_CONTACTS, 0));
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::ButtonLogClearClick(TObject *Sender)
{
	MemoLog->Clear();
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::N7Click(TObject *Sender)
{
	Contact *c = (Contact *)TreeView->Selected->Data;
	fmanage->contact = c;
	fmanage->Show();
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::ButtonOptionsSaveClick(TObject *Sender)
{
	threadclient->Send(makeMessage(TMESS_LOCAL_SAVE, 0));
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::EditPassKeyPress(TObject *Sender, System::WideChar &Key)
{
	if((int)Key == 13) {
		ButtonConnect->Click();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::EditPidKeyPress(TObject *Sender, System::WideChar &Key)
{
	if((int)Key == 13) {
		ButtonConnect->Click();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::EditProfileLoginKeyPress(TObject *Sender, System::WideChar &Key)
{
	if((int)Key == 13) {
		ButtonLogin->Click();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::EditProfilePassKeyPress(TObject *Sender, System::WideChar &Key)
{
	if((int)Key == 13) {
		ButtonLogin->Click();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::OptionClearClick(TObject *Sender)
{
	threadclient->Send(makeMessage(TMESS_LOCAL_OPTION_CLEAR, 0));
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::TreeViewDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
	Accept = true;
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::TreeViewEndDrag(TObject *Sender, TObject *Target, int X, int Y)
{
	UnicodeString parent = "-1";

	THitTests MH = TreeView->GetHitTestInfoAt(X, Y);
	if(MH.Contains(htOnItem)) {
		TTreeNode* dst = TreeView->GetNodeAt(X, Y);
		Contact *c = (Contact *)dst->Data;
		if (c && c->type == "fold") {
			parent = UnicodeString(c->id);
		}
		else{
            return;
		}
	}

	TTreeNode* src = TreeView->Selected;
	Contact *p = (Contact *)src->Data;
	if (p != NULL) {

		char capt[MAX_BUFF_CONVERT];
		UnicodeToUtf8(capt, p->caption.w_str(), MAX_BUFF_CONVERT);

		char pid[MAX_BUFF_CONVERT];
		UnicodeToUtf8(pid, p->pid.w_str(), MAX_BUFF_CONVERT);

		threadclient->Send(makeMessage(TMESS_LOCAL_CONTACT, 6,
			UnicodeString(p->id).w_str(),
			UnicodeString(p->type).w_str(),
			UnicodeString(capt).w_str(),
			UnicodeString(pid).w_str(),
			L"",
			UnicodeString(parent).w_str()) );
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::TreeViewEdited(TObject *Sender, TTreeNode *Node, UnicodeString &S)
{
	Contact *p = (Contact *)Node->Data;
	char capt[MAX_BUFF_CONVERT];
	UnicodeToUtf8(capt, S.w_str(), MAX_BUFF_CONVERT);

	char pid[MAX_BUFF_CONVERT];
	UnicodeToUtf8(pid, p->pid.w_str(), MAX_BUFF_CONVERT);

	threadclient->Send(makeMessage(TMESS_LOCAL_CONTACT, 6,
		UnicodeString(p->id).w_str(),
		UnicodeString(p->type).w_str(),
		UnicodeString(capt).w_str(),
		UnicodeString(pid).w_str(),
		L"",
		L"") );
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::TreeViewKeyPress(TObject *Sender, System::WideChar &Key)
{
	if (Key == 13) {
        TreeViewDblClick(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::ButtonProfileClick(TObject *Sender)
{
    ShowMessage("Не реализовано!");
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::N8Click(TObject *Sender)
{
	fmanage->contact = NULL;
	fmanage->Show();
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::FormCreate(TObject *Sender)
{
    myClient.mainForm = Handle;
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::StatusBarDblClick(TObject *Sender)
{
	this->Constraints->MaxWidth = Screen->Width;
	fmain->ClientWidth = MemoLog->Left + MemoLog->ClientWidth + OptionClear->Width + 20;

	this->Constraints->MaxWidth = this->Width;
	this->Constraints->MinWidth = this->Width;
    myClient.debug = true;
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::cleanallClick(TObject *Sender)
{
	ExecProgram(Application->ExeName, "-clean-all", true, true);
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::reloadcomClick(TObject *Sender)
{
	ExecProgram(Application->ExeName, "-reload", true, true);
}
//---------------------------------------------------------------------------

