//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmain.h"
#include "frcontact.h"
#include "frmanage.h"
#include "fralert.h"
#include "languages.h"
#include "System.NetEncoding.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
Tfmain *fmain;
//---------------------------------------------------------------------------
__fastcall Tfmain::Tfmain(TComponent* Owner) : TForm(Owner)
{
	myClient.mainEnabling = true;

	applyLangBySystem();

	if (!myClient.debug) {
		this->ClientWidth = this->PanelContacts->Left + this->PanelContacts->Width + EditFilter->Left;
	}

	threadclient = new ThreadClient(Client);

    TIcon* iconsh = new TIcon();
	iconsh->Handle = LoadIcon(0, IDI_SHIELD);
	if(iconsh->Handle) N2->ImageIndex = ImageList->AddIcon(iconsh);
	applyLangUI();

	this->Constraints->MinWidth = this->Width;
	this->Constraints->MinHeight = this->Height;

	PanelLogin->Left = PanelContacts->Left;
	PanelLogin->Top = PanelContacts->Top;

	TrayIcon->BalloonTitle = getFullText(L_CAPTION, L_END);

	try{
		if(ExistService()){
			while(!WTSRegisterSessionNotification(this->Handle, 0) && !Application->Terminated){
				::Sleep(100);
			}
		}
	}
	catch(...){
		addLog(TYPE_LOG_ERROR, "не получилось зарегистрировать WTSRegisterSessionNotification");
	}
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
		Application->Restore();
		Application->BringToFront();
	}
	else {
        //Application->Minimize();
		this->Hide();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::UpdaterUITimer(TObject *Sender)
{
	if(myClient.version != "" && myClient.version != "0"){
		Caption = "reVisit " + myClient.version;
	}
	else{
		Caption = "reVisit";
	}
	LabelVersion->Caption = Caption;

	if (myClient.hide == "1") {
		LabelPid->Text = "XX:XX:XX:XX";
		LabelPass->Text = "*****";
	}
	else {
		if( myClient.pid.Length() && myClient.pass.Length() ){
			if(myClient.autoreg) {
				threadclient->Send(makeMessage(TMESS_LOCAL_CONT_REVERSE, 2, myClient.autologin, myClient.autopass));
				myClient.autoreg = 0;
			}
			LabelPid->Text = myClient.pid;
			LabelPass->Text = myClient.pass;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::ButtonConnectClick(TObject *Sender)
{
	if(!myClient.client.Length()) {
		falert->ShowMessage(getFullText(L_ABSENT_VNC, L_END));
		return;
	}
	threadclient->Send(makeMessage(TMESS_LOCAL_CONNECT, 2, EditPid->Text.c_str(), EditPass->Text.c_str()));
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::Web1Click(TObject *Sender)
{
	if(!myClient.webpanel.Length()) {
		falert->ShowMessage(getFullText(L_ABSENT_WEB, L_END));
		return;
	}
	ExecProgram(myClient.webpanel, "", false, false);
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::N2Click(TObject *Sender)
{
	if (!ExistService()) {
		UnicodeString attr = "-service -install";
		if (myClient.debug) {
			attr = attr + UnicodeString(" -debug");
		}
		if (myClient.server.Length()) {
			attr = attr + UnicodeString(" -server ") + myClient.server;
		}
		if (myClient.pass.Length()) {
			attr = attr + UnicodeString(" -password ") + myClient.pass;
		}
		if (myClient.autoreg){
            attr = attr + UnicodeString(" -autoreg ") + myClient.autologin + UnicodeString(" ") + myClient.autopass;
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
		bool b = SetCurrentUserThread();

		ExecProgram("net", "stop reService", true, true);
		Sleep(SERVICE_PAUSE_RESTART_UI + SERVICE_WAIT_CYCLE + SERVICE_WAIT_AFTER_CYCLE);
		if (ExecProgram(Application->ExeName, "-service -uninstall", true, true) ) {
			threadclient->Send(makeMessage(TMESS_LOCAL_TERMINATE, 1, L"1"));
			N2->Caption = getFullText(L_INSTALL_SERVICE, L_END);
		}

		if(ntoken){
			SetThreadToken(0, ntoken);
			CloseHandle(ntoken);
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
void Tfmain::addNodes(Contact *contact, TTreeNode *parent, UnicodeString filter)
{
	while (contact != NULL) {
		if(contact->inner != NULL) {
			TTreeNode *p = TreeView->Items->AddChild(parent, contact->caption);
			p->Data = contact;
			contact->data = (void *)p;
			p->ImageIndex = 0;
			p->SelectedIndex = 0;
			addNodes(contact->inner, p, filter); //наполним папку
		}
		else {
			if( filter.Length() == 0 || contact->caption.LowerCase().Pos(filter.LowerCase()) || cleanPid(contact->pid).Pos(cleanPid(filter)) ) {
				addNode(contact, parent); //добавим контакт
			}
		}
		contact = contact->next;
	}
}
//---------------------------------------------------------------------------
void Tfmain::updateTreeView()
{
	unbindNodes(myClient.contact);
	TreeView->Items->Clear();
	sortNodes(myClient.contact);
	addNodes(myClient.contact, NULL, EditFilter->Text);
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
			if(!myClient.client.Length()){
				falert->ShowMessage(getFullText(L_ABSENT_VNC, L_END));
				return;
			}
			threadclient->Send(makeMessage(TMESS_LOCAL_CONN_CONTACT, 1, UnicodeString(c->id).w_str()));
			addLog(TYPE_LOG_INFO, "пробуем подключиться");
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::FormClose(TObject *Sender, TCloseAction &Action)
{
	myOptions.Width = this->Width;
	myOptions.Height = this->Height;
	myOptions.Left = this->Left;
	myOptions.Top = this->Top;

	TURLEncoding *coder = new TURLEncoding;
	threadclient->Send(makeMessage(TMESS_LOCAL_OPTIONS_UI, 1, coder->Encode(getJsonStringOptions())));
	coder->Free();

	Sleep(TIME_IDLE);

	if (!ExistService()) {
		threadclient->Send(makeMessage(TMESS_LOCAL_TERMINATE, 1, L"0"));
		if(myClient.debug) {
			try {
				MemoLog->Lines->SaveToFile("revisit.log");
			}catch(...){ }
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
		case WM_WTSSESSION_CHANGE:
		{
            if(Msg.wParam == WTS_SESSION_LOGON || Msg.wParam == WTS_SESSION_LOGOFF || Msg.wParam == WTS_CONSOLE_CONNECT || Msg.wParam == WTS_CONSOLE_DISCONNECT){
				this->Close();
			}
			break;
		}
		case WM_NCMOUSEMOVE:
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

			if(Msg.wParam) {
				falert->ShowMessage(*buf);
			}

			StatusBar->SimpleText = *buf;
			delete buf;
			break;
		}
		case WM_VISIT_ST_LOG:
		{
			UnicodeString *buf = (UnicodeString *)Msg.lParam;
            StatusBar->SimpleText = *buf;
			delete buf;
			break;
		}
		case WM_VISIT_STATUS:
		{
			UnicodeString *buf = (UnicodeString *)Msg.lParam;
			StatusBar->SimpleText = *buf;
			delete buf;
			break;
		}
		case WM_VISIT_LOG:
		{
			UnicodeString *buf = (UnicodeString *)Msg.lParam;
			if(myClient.debug) {
				MemoLog->Lines->Add(*buf);
			}
			delete buf;
			break;
		}
		case WM_VISIT_UPDATE:
		{
			updateTreeView();
			break;
		}
		case WM_VISIT_EXEC:
		{
			UnicodeString *buf = (UnicodeString *)Msg.lParam;
			StartProgram(*buf);
			delete buf;
			break;
		}
		case WM_VISIT_DISCON:
		{
			PanelLogin->Show();
			PanelContacts->Hide();
			fmanage->Close();
			fcontact->Close();
            unbindNodes(myClient.contact);
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
		case WM_VISIT_SCONT:
		{
			Contact *c = getContact(myClient.contact, (int)Msg.lParam);
			if (c) {
				c->status = Msg.wParam;
				TTreeNode *p = (TTreeNode*)c->data;
				if (p) {
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
		case WM_VISIT_PROXY:
		{
			UnicodeString **buf = (UnicodeString **)Msg.wParam;
			fmanage->EditProxyServer->Text = *buf[0];
			fmanage->EditProxyPort->Text = *buf[1];
			delete buf;
			break;
		}
		case WM_VISIT_INCLNT:
		{
			UnicodeString **buf = (UnicodeString **)Msg.wParam;
			fmanage->EditHostname->Text = *buf[0];
			fmanage->EditUptime->Text = *buf[1];
			fmanage->EditVersion->Text = *buf[2];

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
			ExecProgram("net", "stop reService", true, true);
			Sleep(SERVICE_PAUSE_RESTART_UI + SERVICE_WAIT_CYCLE + SERVICE_WAIT_AFTER_CYCLE);
			if (ExecProgram("net", "start reService", true, true)){
				addLog(TYPE_LOG_INFO, "Перезапустили сервис");
				this->Close();
			}
			addLog(TYPE_LOG_ERROR, "Не получилось перезапустить сервис");
			break;
		}
		case WM_VISIT_APPLY:
		{
			if (myOptions.Width && myOptions.Height) {
                this->Width = myOptions.Width;
				this->Height = myOptions.Height;
				this->Left = myOptions.Left;
				this->Top = myOptions.Top;

				applyLangUI();
				fmanage->applyLangUI();
				fcontact->applyLangUI();
                falert->applyLangUI();

				addLog(TYPE_LOG_INFO, "Применили опции ui");
				break;
			}
			addLog(TYPE_LOG_INFO, "Не стали применять опции ui");
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
	unbindNodes(myClient.contact);
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
	if(!myClient.webprofile.Length()) {
		ShowMessage("У нас нет информации о WEB!");
		return;
	}
	ExecProgram(myClient.webprofile, "", false, false);
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::N8Click(TObject *Sender)
{
	fmanage->contact = NULL;
	fmanage->ButtonAddProfile->Enabled = true;
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
	if(!myClient.debug) {
		myClient.debug = true;
		this->Width = this->Width + 550;
	}
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
void __fastcall Tfmain::EditFilterChange(TObject *Sender)
{
	updateTreeView();
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::ApplicationEventsMinimize(TObject *Sender)
{
    this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::LabelPassExit(TObject *Sender)
{
	if(!UpdaterUI->Enabled) {
		UpdaterUI->Enabled = true;
		if(this->Tag) threadclient->Send(makeMessage(TMESS_LOCAL_INFO, 1, LabelPass->Text.c_str()));
	}
	this->Tag = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::LabelPassDblClick(TObject *Sender)
{
	UpdaterUI->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::LabelPassKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == 13) {
		ButtonConnect->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::FormResize(TObject *Sender)
{
	int padding = EditFilter->Left;

	PanelLogin->Width = this->ClientWidth - PanelLogin->Left - padding - (myClient.debug?520:0);
	PanelContacts->Width = PanelLogin->Width;

	TreeView->Width = PanelContacts->ClientWidth - TreeView->Left - padding;
	EditFilter->Width = TreeView->Width;
	ButtonLogout->Left = EditFilter->Width - ButtonLogout->Width + padding;

	MemoLog->Left = PanelLogin->Left + PanelLogin->Width + padding;
	ButtonLogSave->Left = MemoLog->Left + MemoLog->Width + padding;
	ButtonLogClear->Left = MemoLog->Left + MemoLog->Width + padding;
	cleanall->Left = MemoLog->Left + MemoLog->Width + padding;
	reloadcom->Left = MemoLog->Left + MemoLog->Width + padding;
	ButtonOptionsSave->Left = MemoLog->Left + MemoLog->Width + padding;
	OptionClear->Left = MemoLog->Left + MemoLog->Width + padding;


	PanelLogin->Height = this->ClientHeight - PanelLogin->Top - StatusBar->Height - padding;
	PanelContacts->Height = PanelLogin->Height;
	MemoLog->Height = PanelContacts->Height;

	ButtonProfile->Top = PanelLogin->ClientHeight - ButtonProfile->Height - padding;
	ButtonLogout->Top = ButtonProfile->Top;
	TreeView->Height = ButtonLogout->Top - TreeView->Top - padding;

	PanelCredentials->Left = (PanelLogin->Width - PanelCredentials->Width) / 2;
    PanelCredentials->Top = (PanelLogin->Height - PanelCredentials->Height) / 2;
}
//---------------------------------------------------------------------------
void __fastcall Tfmain::LabelPassChange(TObject *Sender)
{
    this->Tag = 1;
}
//---------------------------------------------------------------------------
void Tfmain::applyLangUI()
{
	if (ExistService()) {
		N2->Caption = getText(L_UNINSTALL_SERVICE);
	}
	else {
		N2->Caption = getText(L_INSTALL_SERVICE);
	}

	N1->Caption = getText(L_EXIT);
	N8->Caption = getText(L_MANAGE);
	Web1->Caption = getText(L_WEB_PANEL);

	N6->Caption = getText(L_NEW_GROUP);
	N3->Caption = getText(L_NEW_CONT);
	N4->Caption = getText(L_EDIT);
	N7->Caption = getText(L_MANAGE);
	N5->Caption = getText(L_REMOVE);

	Label6->Caption = getText(L_ID);
    Label4->Caption = getText(L_ID);
	Label8->Caption = getText(L_LOCAL_PC);
	Label9->Caption = getText(L_REMOTE_PC);
	Label7->Caption = getText(L_PASSWORD);
	Label2->Caption = getText(L_PASSWORD);
	Label5->Caption = getText(L_PASSWORD);

	Label3->Caption = getText(L_LOGIN_PROFILE);
	CheckProfileSave->Caption = getText(L_SAVE);
	ButtonLogin->Caption = getText(L_LOGIN);
	ButtonConnect->Caption = getText(L_CONNECT);
	ButtonRegister->Caption = getText(L_SIGNIN);

	ButtonProfile->Caption = getText(L_PROFILE);
	ButtonRefresh->Caption = getText(L_REFRESH);
	ButtonLogout->Caption = getText(L_LOGOUT);
}
