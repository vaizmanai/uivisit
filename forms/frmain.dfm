object fmain: Tfmain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'reVisit'
  ClientHeight = 460
  ClientWidth = 1086
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object LabelVersion: TLabel
    Left = 8
    Top = 16
    Width = 241
    Height = 29
    Alignment = taCenter
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object Label4: TLabel
    Left = 48
    Top = 76
    Width = 17
    Height = 19
    Caption = 'ID'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 48
    Top = 137
    Width = 54
    Height = 19
    Caption = #1055#1072#1088#1086#1083#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 48
    Top = 243
    Width = 17
    Height = 19
    Caption = 'ID'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label7: TLabel
    Left = 48
    Top = 304
    Width = 54
    Height = 19
    Caption = #1055#1072#1088#1086#1083#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label8: TLabel
    Left = 8
    Top = 51
    Width = 241
    Height = 19
    Alignment = taCenter
    AutoSize = False
    Caption = #1051#1086#1082#1072#1083#1100#1085#1099#1081' '#1082#1086#1084#1087#1100#1102#1090#1077#1088
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label9: TLabel
    Left = 8
    Top = 218
    Width = 241
    Height = 19
    Alignment = taCenter
    AutoSize = False
    Caption = #1059#1076#1072#1083#1077#1085#1085#1099#1081' '#1082#1086#1084#1087#1100#1102#1090#1077#1088
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label10: TLabel
    Left = 8
    Top = 399
    Width = 241
    Height = 36
    Alignment = taCenter
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object PanelContacts: TPanel
    Left = 255
    Top = 8
    Width = 298
    Height = 425
    BevelKind = bkFlat
    BevelOuter = bvNone
    ShowCaption = False
    TabOrder = 7
    Visible = False
    object ButtonLogout: TButton
      Left = 198
      Top = 392
      Width = 89
      Height = 25
      Caption = #1042#1099#1093#1086#1076
      TabOrder = 0
      OnClick = ButtonLogoutClick
    end
    object ButtonProfile: TButton
      Left = 8
      Top = 392
      Width = 89
      Height = 25
      Caption = #1055#1088#1086#1092#1080#1083#1100
      TabOrder = 1
      OnClick = ButtonProfileClick
    end
    object TreeView: TTreeView
      Left = 8
      Top = 39
      Width = 281
      Height = 347
      DoubleBuffered = True
      DragMode = dmAutomatic
      Images = Images
      Indent = 20
      ParentDoubleBuffered = False
      PopupMenu = ContactPopup
      ReadOnly = True
      TabOrder = 2
      OnContextPopup = TreeViewContextPopup
      OnDblClick = TreeViewDblClick
      OnDragOver = TreeViewDragOver
      OnEdited = TreeViewEdited
      OnEndDrag = TreeViewEndDrag
      OnKeyPress = TreeViewKeyPress
    end
    object ButtonRefresh: TButton
      Left = 103
      Top = 392
      Width = 89
      Height = 25
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100
      TabOrder = 3
      Visible = False
      OnClick = ButtonRefreshClick
    end
    object EditFilter: TEdit
      AlignWithMargins = True
      Left = 8
      Top = 8
      Width = 281
      Height = 25
      Hint = #1057#1090#1088#1086#1082#1072' '#1087#1086#1080#1089#1082#1072
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
      OnChange = EditFilterChange
    end
  end
  object PanelLogin: TPanel
    Left = 519
    Top = 8
    Width = 298
    Height = 425
    BevelKind = bkTile
    BevelOuter = bvNone
    Ctl3D = True
    ParentCtl3D = False
    ShowCaption = False
    TabOrder = 6
    object PanelCredentials: TPanel
      Left = 8
      Top = 66
      Width = 273
      Height = 290
      BevelOuter = bvNone
      TabOrder = 0
      object Label2: TLabel
        Left = 16
        Top = 130
        Width = 54
        Height = 19
        Caption = #1055#1072#1088#1086#1083#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label1: TLabel
        Left = 16
        Top = 67
        Width = 45
        Height = 19
        Caption = 'E-mail'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel
        Left = -16
        Top = 27
        Width = 297
        Height = 19
        Alignment = taCenter
        AutoSize = False
        Caption = #1042#1093#1086#1076' '#1074' '#1091#1095#1077#1090#1085#1091#1102' '#1079#1072#1087#1080#1089#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object ButtonLogin: TButton
        Left = 16
        Top = 221
        Width = 97
        Height = 25
        Caption = #1042#1093#1086#1076
        TabOrder = 3
        OnClick = ButtonLoginClick
      end
      object CheckProfileSave: TCheckBox
        Left = 16
        Top = 198
        Width = 193
        Height = 17
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        TabOrder = 2
      end
      object ButtonRegister: TButton
        Left = 160
        Top = 221
        Width = 97
        Height = 25
        Caption = #1056#1077#1075#1080#1089#1090#1088#1072#1094#1080#1103
        TabOrder = 4
        OnClick = ButtonRegisterClick
      end
      object EditProfilePass: TMaskEdit
        Left = 16
        Top = 155
        Width = 241
        Height = 33
        AutoSize = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        PasswordChar = '*'
        TabOrder = 1
        Text = ''
        OnKeyPress = EditProfilePassKeyPress
      end
      object EditProfileLogin: TMaskEdit
        Left = 16
        Top = 91
        Width = 241
        Height = 33
        AutoSize = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        Text = ''
        OnKeyPress = EditProfileLoginKeyPress
      end
    end
  end
  object EditPass: TMaskEdit
    Left = 48
    Top = 326
    Width = 161
    Height = 33
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    Text = ''
    OnKeyPress = EditPassKeyPress
  end
  object EditPid: TMaskEdit
    Left = 48
    Top = 265
    Width = 161
    Height = 33
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    Text = ''
    OnKeyPress = EditPidKeyPress
  end
  object LabelPid: TMaskEdit
    Left = 48
    Top = 98
    Width = 161
    Height = 33
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    TabOrder = 0
    Text = ''
  end
  object LabelPass: TMaskEdit
    Left = 48
    Top = 159
    Width = 161
    Height = 33
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    Text = ''
    OnChange = LabelPassChange
    OnDblClick = LabelPassDblClick
    OnExit = LabelPassExit
    OnKeyPress = LabelPassKeyPress
  end
  object ButtonConnect: TButton
    Left = 81
    Top = 368
    Width = 97
    Height = 25
    Caption = #1055#1086#1076#1082#1083#1102#1095#1077#1085#1080#1077
    TabOrder = 4
    OnClick = ButtonConnectClick
  end
  object MemoLog: TMemo
    Left = 684
    Top = 8
    Width = 394
    Height = 425
    ReadOnly = True
    TabOrder = 5
  end
  object ButtonLogSave: TButton
    Left = 967
    Top = 8
    Width = 111
    Height = 25
    Caption = 'save log'
    TabOrder = 8
  end
  object ButtonLogClear: TButton
    Left = 967
    Top = 39
    Width = 111
    Height = 25
    Caption = 'clear log'
    TabOrder = 9
    OnClick = ButtonLogClearClick
  end
  object ButtonOptionsSave: TButton
    Left = 967
    Top = 379
    Width = 111
    Height = 25
    Caption = 'save options'
    TabOrder = 10
    OnClick = ButtonOptionsSaveClick
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 441
    Width = 1086
    Height = 19
    Panels = <>
    SimplePanel = True
    SizeGrip = False
    OnDblClick = StatusBarDblClick
  end
  object OptionClear: TButton
    Left = 967
    Top = 410
    Width = 111
    Height = 25
    Caption = 'clear options'
    TabOrder = 12
    OnClick = OptionClearClick
  end
  object cleanall: TButton
    Left = 967
    Top = 217
    Width = 111
    Height = 25
    Caption = 'clean-all'
    TabOrder = 13
    OnClick = cleanallClick
  end
  object reloadcom: TButton
    Left = 967
    Top = 248
    Width = 111
    Height = 25
    Caption = 'reload communicator'
    TabOrder = 14
    OnClick = reloadcomClick
  end
  object TrayIcon: TTrayIcon
    PopupMenu = PopupTrayMenu
    Visible = True
    OnDblClick = TrayIconDblClick
    Left = 808
    Top = 368
  end
  object PopupTrayMenu: TPopupMenu
    Images = ImageList
    Left = 808
    Top = 240
    object Web1: TMenuItem
      Caption = 'Web-'#1087#1072#1085#1077#1083#1100
      OnClick = Web1Click
    end
    object N2: TMenuItem
      Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1089#1083#1091#1078#1073#1091
      OnClick = N2Click
    end
    object N8: TMenuItem
      Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      OnClick = N8Click
    end
    object N1: TMenuItem
      Caption = #1042#1099#1081#1090#1080
      OnClick = N1Click
    end
  end
  object ApplicationEvents: TApplicationEvents
    OnMessage = ApplicationEventsMessage
    OnMinimize = ApplicationEventsMinimize
    Left = 736
    Top = 368
  end
  object Client: TIdTCPClient
    IOHandler = ClientHandler
    ConnectTimeout = 0
    Host = '127.0.0.1'
    IPVersion = Id_IPv4
    Port = 32781
    ReadTimeout = 500
    UseNagle = False
    Left = 664
    Top = 304
  end
  object ClientHandler: TIdIOHandlerStack
    Destination = '127.0.0.1:32781'
    Host = '127.0.0.1'
    MaxLineAction = maException
    Port = 32781
    DefaultPort = 0
    UseNagle = False
    ReadTimeout = 500
    Left = 736
    Top = 304
  end
  object UpdaterUI: TTimer
    Interval = 250
    OnTimer = UpdaterUITimer
    Left = 664
    Top = 368
  end
  object ImageList: TImageList
    BkColor = 10526880
    DrawingStyle = dsTransparent
    Left = 664
    Top = 240
  end
  object Images: TImageList
    DrawingStyle = dsTransparent
    Height = 20
    Width = 20
    Left = 736
    Top = 240
    Bitmap = {
      494C01010300B400AC0114001400FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000500000001400000001002000000000000019
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000E4DFDA00CDC3BA00CDC3BA00CDC3BA00CDC3BA00CDC3BA00CDC3BA00CDC3
      BA00CDC3BA00CAC0B70000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E4DFDA00CDC3BA00CDC3BA00CDC3
      BA00CDC3BA00CDC3BA00CDC3BA00CDC3BA00CDC3BA00CAC0B700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CFC5BC00E4DACF00E8E0D500E8E0D500E8E0D500E8E0D500E8E0D500E8E0
      D500E8E0D500B9AA9B0000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CFC5BC00E4DACF00E8E0D500E8E0
      D500E8E0D500E8E0D500E8E0D500E8E0D500E8E0D500B9AA9B00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000097B5C500609EBF0063A1C30063A1
      C30063A1C30063A1C30063A1C30063A1C30063A1C30063A1C30063A1C30063A1
      C30063A1C30063A1C30063A1C30063A1C30063A1C3005692B100EEF3F5000000
      0000D0C6BD00EDE5DB00F2EBE100F2EBE100F2EBE100F2EBE100F2EBE100F2EB
      E100F2EBE100BEAFA1008F7966008F7966008F7966008F7966008F796600A796
      870000000000000000000000000000000000D0C6BD00EDE5DB00F2EBE100F2EB
      E100F2EBE100F2EBE100F2EBE100F2EBE100F2EBE100BEAFA1008F7966008F79
      66008F7966008F7966008F796600A79687000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009DBAC90078BDE20085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50074B8DB00CFDDE4000000
      0000D0C6BD00EDE5DB00F2EBE100F2EBE100F2EBE100F2EBE100F2EBE100F2EB
      E100F2EBE100BEAFA100B09C8A00B09C8A00A9988A00C3B8AE00C9BFB700F2EF
      ED0000000000000000000000000000000000D0C6BD00EDE5DB00F2EBE100F2EB
      E100F2EBE100F2EBE100F2EBE100F2EBE100F2EBE100BEAFA100B09C8A00B09C
      8A00A9988A00C3B8AE00C9BFB700F2EFED000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A0BCCB006AACCE0085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF5007FC6EC00B1C7D3000000
      0000D0C6BD00EDE5DB00F2EBE100F2EBE100F1EADF00F0E7DC00F2EBE100F2EB
      E100F2EBE100BEAFA100CEBBAA00CEBBAA00C2B6AC00F6F4F300F6F4F300F6F4
      F300F6F4F300F6F4F300F6F4F300F9F9F900D0C6BD00EDE5DB00F2EBE100F2EB
      E100F1EADF00F0E7DC00F2EBE100F2EBE100F2EBE100BEAFA100CEBBAA00CEBB
      AA00C2B6AC00F6F4F300F6F4F300F6F4F300F6F4F300F6F4F300F6F4F300F9F9
      F900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A1BFCE005D9BBB0085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50097B7C8000000
      0000D0C6BD00EDE5DB00F2EBE100F2EBE100D3AB8C00D3A07900E5D2C000F2EB
      E100F2EBE100BEAFA100917B6800917B6800917B6800947F6D00947F6D00947F
      6D00958574009DB7B500999C9300C3B7AD00D0C6BD00EDE5DB00F2EBE100F2EB
      E100D3AB8C00D3A07900E5D2C000F2EBE100F2EBE100BEAFA100917B6800917B
      6800917B6800947F6D00947F6D00947F6D00958574009DB7B500999C9300C3B7
      AD00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A1C0CF005694B50085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50081AFC7000000
      0000D0C6BD00EDE5DB00F2EBE100F2EBE100D0996F00E8AF8300D8BBA200F2EB
      E100F2EBE100BEAFA100957F6B00957F6B00957F6B00957F6B00957F6B00957F
      6B00957F6B00957F6B00947E6A00C0B2A800D0C6BD00EDE5DB00F2EBE100F2EB
      E100D0996F00E8AF8300D8BBA200F2EBE100F2EBE100BEAFA100957F6B00957F
      6B00957F6B00957F6B00957F6B00957F6B00957F6B00957F6B00947E6A00C0B2
      A800000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A1C0CF005392B50083CCF20085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50079AECA00F9FA
      FB00D0C6BD00EDE5DB00F2EBE100F2EBE100E4D1BE00DCBFA600EFE6DA00F2EB
      E100F2EBE100BEAFA100F4DDB900F4DDB900F4DDB900F4DDB900F4DDB900F4DD
      B900F4DDB900F4DDB900EAD3B100CCC1B700D0C6BD00EDE5DB00F2EBE100F2EB
      E100E4D1BE00DCBFA600EFE6DA00F2EBE100F2EBE100BEAFA10028EF5A0028EF
      5A0028EF5A0028EF5A0028EF5A0028EF5A0028EF5A0028EF5A0047E26500CCC1
      B700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A1C0CF00599CC20079BFE30085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50073B1D100F1F5
      F700D0C6BD00EDE5DB00F2EBE100F2EBE100F2EBE100F2EBE100F2EBE100F2EB
      E100F2EBE100BEAFA100FFE8C200FFE8C200FFE8C200FFE8C200FFE8C200FFE8
      C200FFE8C200FFE8C200F4DDB900CEC3B800D0C6BD00EDE5DB00F2EBE100F2EB
      E100F2EBE100F2EBE100F2EBE100F2EBE100F2EBE100BEAFA10000FF4C0000FF
      4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0028EF5A00CEC3
      B800000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A1C0CF005FA6CE006DAFD20085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50073B7DC00DFE8
      ED00D0C6BD00EDE5DB00F2EBE100F2EBE100F2EBE100F2EBE100F2EBE100F2EB
      E100F2EBE100BEAFA100FFE8C200FFE8C200FFE8C200FFE8C200FFE8C200FFE8
      C200FFE8C200FFE8C200F4DDB900CEC3B800D0C6BD00EDE5DB00F2EBE100F2EB
      E100F2EBE100F2EBE100F2EBE100F2EBE100F2EBE100BEAFA10000FF4C0000FF
      4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0028EF5A00CEC3
      B800000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A1C0CF0063ADD70063A3C40085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF5007BC1E600BBD0
      DA00D0C6BD00EDE5DB00F2EBE100F2EBE100F2EBE100F2EBE100F2EBE100F2EB
      E100F2EBE100BEAFA100FFE8C200FFE8C200FFE8C200FFE8C200FFE8C200FFE8
      C200FFE8C200FFE8C200F4DDB900CEC3B800D0C6BD00EDE5DB00F2EBE100F2EB
      E100F2EBE100F2EBE100F2EBE100F2EBE100F2EBE100BEAFA10000FF4C0000FF
      4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0028EF5A00CEC3
      B800000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A1C0CF0063ADD8005D9CBF0085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50081C8EF0096B7
      C800D0C6BD00EDE5DB00F2EBE100F2EBE100F2EBE100F2EBE100F2EBE100F2EB
      E100F2EBE100BEAFA100FFE8C200FFE8C200FFE8C200FFE8C200FFE8C200FFE8
      C200FFE8C200FFE8C200F4DDB900CEC3B800D0C6BD00EDE5DB00F2EBE100F2EB
      E100F2EBE100F2EBE100F2EBE100F2EBE100F2EBE100BEAFA10000FF4C0000FF
      4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0028EF5A00CEC3
      B800000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A1C0CF0063ADD8005898BC0067A8
      CB0068A9CC0068A9CC0068A9CC0068A9CC0076BBE00085CEF50085CEF50085CE
      F50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF50085CEF5007DA8
      BE00D0C6BD00EDE5DB00C5B6A800C6B8A900C6B8A900C6B8A900C6B8A900C6B8
      A900DAD0C400BEAFA100FFE8C200FFE8C200FFE8C200FFE8C200FFE8C200FFE8
      C200FFE8C200FFE8C200F4DDB900CEC3B800D0C6BD00EDE5DB00C5B6A800C6B8
      A900C6B8A900C6B8A900C6B8A900C6B8A900DAD0C400BEAFA10000FF4C0000FF
      4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0028EF5A00CEC3
      B800000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A1C0CF0063ADD80063ADD70061AA
      D40061AAD40061AAD40061AAD40061AAD4005B9FC600609FC00066A6C70066A6
      C70066A6C70066A6C70066A6C70066A6C70066A6C70066A6C70066A6C7005D91
      AD00D0C6BD00EDE5DB009D877500AB968400AB968400AB968400AB968400AB96
      8400C0B2A400BEAFA100FFE8C200FFE8C200FFE8C200FFE8C200FFE8C200FFE8
      C200FFE8C200FFE8C200F4DDB900CEC3B800D0C6BD00EDE5DB009D877500AB96
      8400AB968400AB968400AB968400AB968400C0B2A400BEAFA10000FF4C0000FF
      4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0028EF5A00CEC3
      B800000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A1C0CF0063ADD80065B0DB0065B0
      DB0065B0DB0065B0DB0065B0DB0065B0DB0065B0DB0065B0DB0065B0DB0065B0
      DB0065B0DB0065B0DB0065B0DB0065B0DB0065B0DB005494B700000000000000
      0000D0C6BD00EDE5DB00EDE5DB00EDE5DB00EDE5DB00EDE5DB00EDE5DB00EDE5
      DB00F0E8DE00BEAFA100FFE8C200FFE8C200FFE8C200FFE8C200FFE8C200FFE8
      C200FFE8C200FFE8C200F4DDB900CEC3B800D0C6BD00EDE5DB00EDE5DB00EDE5
      DB00EDE5DB00EDE5DB00EDE5DB00EDE5DB00F0E8DE00BEAFA10000FF4C0000FF
      4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0028EF5A00CEC3
      B800000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A1C0CF0063ADD80065B0DB0065B0
      DB0065B0DB0065B0DB0065B0DB0065B0DB0065B0DB0065B0DB0065B0DB0065B0
      DB0065B0DB0065B0DB0065B0DB0065B0DB0065B0DB005494B700000000000000
      0000D0C6BD00EDE5DB00AB978500BCA99800BCA99800BCA99800BCA99800BCA9
      9800C5B8AA00BEAFA100FFE8C200FFE8C200FFE8C200FFE8C200FFE8C200FFE8
      C200FFE8C200FFE8C200F4DDB900CEC3B800D0C6BD00EDE5DB00AB978500BCA9
      9800BCA99800BCA99800BCA99800BCA99800C5B8AA00BEAFA10000FF4C0000FF
      4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0000FF4C0028EF5A00CEC3
      B800000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A1C0CF0063ADD80065B0DB0065B0
      DB0065B0DB0065B0DB005EA3CA0088ABBD009AB7C7009AB7C7009AB7C7009AB7
      C7009AB7C7009AB7C7009AB7C7009AB7C7009AB7C7009AB7C700000000000000
      0000D0C6BD00EDE5DB00A6928000B9A59400B9A59400B9A59400B9A59400B9A5
      9400C3B5A700BEAFA100C3B7AE00C3B7AE00C3B7AE00C3B7AE00C3B7AE00C3B7
      AE00C3B7AE00C3B7AE00C3B7AE00E2DCD700D0C6BD00EDE5DB00A6928000B9A5
      9400B9A59400B9A59400B9A59400B9A59400C3B5A700BEAFA100C3B7AE00C3B7
      AE00C3B7AE00C3B7AE00C3B7AE00C3B7AE00C3B7AE00C3B7AE00C3B7AE00E2DC
      D700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A1BDCD005595B8005596BA005596
      BA005596BA005495B800A5C1CF00FDFDFE000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D0C6BD00EDE5DB00E8E0D500E8E0D500E8E0D500E8E0D500E8E0D500E8E0
      D500EDE5DB00BEAFA10000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D0C6BD00EDE5DB00E8E0D500E8E0
      D500E8E0D500E8E0D500E8E0D500E8E0D500EDE5DB00BEAFA100000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CFC5BD00E8E0D500EDE5DB00EDE5DB00EDE5DB00EDE5DB00EDE5DB00EDE5
      DB00EDE5DB00BCAC9E0000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CFC5BD00E8E0D500EDE5DB00EDE5
      DB00EDE5DB00EDE5DB00EDE5DB00EDE5DB00EDE5DB00BCAC9E00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000E2DDD800CFC5BD00D0C6BD00D0C6BD00D0C6BD00D0C6BD00D0C6BD00D0C6
      BD00D0C6BD00CBC0B70000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E2DDD800CFC5BD00D0C6BD00D0C6
      BD00D0C6BD00D0C6BD00D0C6BD00D0C6BD00D0C6BD00CBC0B700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000050000000140000000100010000000000F00000000000000000000000
      000000000000000000000000FFFFFF00FFFFF003FF003FF000000000FFFFF003
      FF003FF000000000000010000F0000F000000000000010000F0000F000000000
      0000100000000000000000000000100000000000000000000000100000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000300000000000
      0000000000003000000000000000000000003000000000000000000000FFF003
      FF003FF000000000FFFFF003FF003FF000000000FFFFF003FF003FF000000000
      00000000000000000000000000000000000000000000}
  end
  object ContactPopup: TPopupMenu
    Left = 808
    Top = 304
    object N6: TMenuItem
      Caption = #1053#1086#1074#1072#1103' '#1075#1088#1091#1087#1087#1072
      OnClick = N6Click
    end
    object N3: TMenuItem
      Caption = #1053#1086#1074#1099#1081' '#1082#1086#1085#1090#1072#1082#1090
      OnClick = N3Click
    end
    object N4: TMenuItem
      Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
      OnClick = N4Click
    end
    object N7: TMenuItem
      Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      OnClick = N7Click
    end
    object N5: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100
      OnClick = N5Click
    end
  end
end
