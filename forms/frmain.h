//---------------------------------------------------------------------------

#ifndef frmainH
#define frmainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "trayicon.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.AppEvnts.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>

#include "threadclient.h"
#include "routines.h"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <direct.h>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tfmain : public TForm
{
__published:	// IDE-managed Components
	TTrayIcon *TrayIcon;
	TPopupMenu *PopupTrayMenu;
	TMenuItem *N1;
	TMaskEdit *EditPass;
	TMaskEdit *EditPid;
	TApplicationEvents *ApplicationEvents;
	TIdTCPClient *Client;
	TIdIOHandlerStack *ClientHandler;
	TMaskEdit *LabelPid;
	TMaskEdit *LabelPass;
	TButton *ButtonConnect;
	TMemo *MemoLog;
	TTimer *UpdaterUI;
	TLabel *LabelVersion;
	TMenuItem *Web1;
	TMenuItem *N2;
	TImageList *ImageList;
	TPanel *PanelLogin;
	TPanel *PanelContacts;
	TButton *ButtonLogout;
	TButton *ButtonProfile;
	TTreeView *TreeView;
	TImageList *Images;
	TPopupMenu *ContactPopup;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TButton *ButtonRefresh;
	TButton *ButtonLogSave;
	TButton *ButtonLogClear;
	TMenuItem *N7;
	TButton *ButtonOptionsSave;
	TStatusBar *StatusBar;
	TButton *OptionClear;
	TBalloonHint *BalloonHint;
	TMenuItem *N8;
	TButton *cleanall;
	TButton *reloadcom;
	TEdit *EditFilter;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TPanel *PanelCredentials;
	TButton *ButtonLogin;
	TCheckBox *CheckProfileSave;
	TButton *ButtonRegister;
	TMaskEdit *EditProfilePass;
	TLabel *Label2;
	TMaskEdit *EditProfileLogin;
	TLabel *Label1;
	TLabel *Label3;
	void __fastcall TrayIconDblClick(TObject *Sender);
	void __fastcall UpdaterUITimer(TObject *Sender);
	void __fastcall ButtonConnectClick(TObject *Sender);
	void __fastcall Web1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ButtonRegisterClick(TObject *Sender);
	void __fastcall ButtonLoginClick(TObject *Sender);
	void __fastcall ApplicationEventsMessage(tagMSG &Msg, bool &Handled);
	void __fastcall ButtonLogoutClick(TObject *Sender);
	void __fastcall TreeViewDblClick(TObject *Sender);
	void __fastcall TreeViewContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall ButtonRefreshClick(TObject *Sender);
	void __fastcall ButtonLogClearClick(TObject *Sender);
	void __fastcall ButtonOptionsSaveClick(TObject *Sender);
	void __fastcall EditPassKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EditPidKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EditProfileLoginKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EditProfilePassKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall OptionClearClick(TObject *Sender);
	void __fastcall TreeViewDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept);
	void __fastcall TreeViewEndDrag(TObject *Sender, TObject *Target, int X, int Y);
	void __fastcall TreeViewEdited(TObject *Sender, TTreeNode *Node, UnicodeString &S);
	void __fastcall TreeViewKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ButtonProfileClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall StatusBarDblClick(TObject *Sender);
	void __fastcall cleanallClick(TObject *Sender);
	void __fastcall reloadcomClick(TObject *Sender);
	void __fastcall EditFilterChange(TObject *Sender);
	void __fastcall ApplicationEventsMinimize(TObject *Sender);
	void __fastcall LabelPassExit(TObject *Sender);
	void __fastcall LabelPassDblClick(TObject *Sender);
	void __fastcall LabelPassKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall LabelPassChange(TObject *Sender);


private:	// User declarations
	void MoveTreeViewBranch(TTreeNode *src, TTreeNode *dst);

public:		// User declarations
	__fastcall Tfmain(TComponent* Owner);

	void updateTreeView();
	void addNode(Contact *node, TTreeNode *parent);
	void addNodes(Contact *node, TTreeNode *parent, UnicodeString filter);

	ThreadClient *threadclient;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfmain *fmain;
extern Client myClient;
extern Options myOptions;
//---------------------------------------------------------------------------
#endif
