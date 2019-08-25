object fmanage: Tfmanage
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
  ClientHeight = 269
  ClientWidth = 1335
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ButtonRefresh: TButton
    Left = 1079
    Top = 8
    Width = 97
    Height = 25
    Caption = #1047#1072#1087#1088#1086#1089#1080#1090#1100
    TabOrder = 1
    Visible = False
    OnClick = ButtonRefreshClick
  end
  object Panel1: TPanel
    Left = 159
    Top = 8
    Width = 178
    Height = 252
    BevelKind = bkFlat
    BevelOuter = bvNone
    Ctl3D = True
    ParentCtl3D = False
    ShowCaption = False
    TabOrder = 2
    object Label3: TLabel
      Left = 16
      Top = 70
      Width = 143
      Height = 13
      AutoSize = False
      Caption = #1054#1087#1077#1088#1072#1094#1080#1086#1085#1085#1072#1103' '#1089#1080#1089#1090#1077#1084#1072
    end
    object Label2: TLabel
      Left = 16
      Top = 22
      Width = 143
      Height = 13
      AutoSize = False
      Caption = #1048#1084#1103' '#1082#1086#1084#1087#1100#1102#1090#1077#1088#1072
    end
    object Label6: TLabel
      Left = 16
      Top = 117
      Width = 143
      Height = 13
      AutoSize = False
      Caption = #1042#1077#1088#1089#1080#1103' reVisit'
    end
    object Label9: TLabel
      Left = 16
      Top = 166
      Width = 143
      Height = 13
      AutoSize = False
      Caption = #1071#1079#1099#1082' '#1080#1085#1090#1077#1088#1092#1077#1081#1089#1072
    end
    object EditUptime: TEdit
      Left = 16
      Top = 89
      Width = 143
      Height = 21
      ReadOnly = True
      TabOrder = 0
    end
    object EditHostname: TEdit
      Left = 16
      Top = 41
      Width = 143
      Height = 21
      ReadOnly = True
      TabOrder = 1
    end
    object EditVersion: TEdit
      Left = 16
      Top = 136
      Width = 143
      Height = 21
      ReadOnly = True
      TabOrder = 2
    end
    object ListLanguages: TComboBox
      Left = 16
      Top = 185
      Width = 143
      Height = 21
      TabOrder = 3
      Text = 'ListVNC'
      OnChange = ListLanguagesChange
    end
  end
  object Panel2: TPanel
    Left = 343
    Top = 8
    Width = 178
    Height = 252
    BevelKind = bkFlat
    BevelOuter = bvNone
    Ctl3D = True
    ParentCtl3D = False
    ShowCaption = False
    TabOrder = 3
    object Label1: TLabel
      Left = 14
      Top = 22
      Width = 143
      Height = 13
      AutoSize = False
      Caption = #1042#1077#1088#1089#1080#1103' VNC'
    end
    object ListVNC: TComboBox
      Left = 14
      Top = 41
      Width = 143
      Height = 21
      TabOrder = 0
    end
    object ButtonReVNC: TButton
      Left = 64
      Top = 68
      Width = 97
      Height = 25
      Caption = #1055#1077#1088#1077#1091#1089#1090#1072#1085#1086#1074#1080#1090#1100
      Enabled = False
      TabOrder = 1
      OnClick = ButtonReVNCClick
    end
    object ButtonUpdate: TButton
      Left = 64
      Top = 99
      Width = 97
      Height = 25
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100
      Enabled = False
      TabOrder = 2
      OnClick = ButtonUpdateClick
    end
    object ButtonReload: TButton
      Left = 64
      Top = 130
      Width = 97
      Height = 25
      Caption = #1055#1077#1088#1077#1079#1072#1087#1091#1089#1090#1080#1090#1100
      Enabled = False
      TabOrder = 3
      OnClick = ButtonReloadClick
    end
    object ButtonRestart: TButton
      Left = 64
      Top = 161
      Width = 97
      Height = 25
      Caption = #1055#1077#1088#1077#1079#1072#1075#1088#1091#1079#1080#1090#1100
      Enabled = False
      TabOrder = 4
      OnClick = ButtonRestartClick
    end
  end
  object Panel3: TPanel
    Left = 527
    Top = 8
    Width = 178
    Height = 252
    BevelKind = bkFlat
    BevelOuter = bvNone
    Ctl3D = True
    ParentCtl3D = False
    ShowCaption = False
    TabOrder = 4
    object Label4: TLabel
      Left = 16
      Top = 22
      Width = 143
      Height = 13
      AutoSize = False
      Caption = 'E-mail '#1087#1088#1086#1092#1080#1083#1103
    end
    object Label5: TLabel
      Left = 16
      Top = 72
      Width = 143
      Height = 13
      AutoSize = False
      Caption = #1055#1072#1088#1086#1083#1100' '#1087#1088#1086#1092#1080#1083#1103
    end
    object ButtonAddProfile: TButton
      Left = 60
      Top = 122
      Width = 97
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      Enabled = False
      TabOrder = 0
      OnClick = ButtonAddProfileClick
    end
    object EditProfileEmail: TEdit
      Left = 16
      Top = 41
      Width = 143
      Height = 21
      TabOrder = 1
    end
    object EditProfilePass: TEdit
      Left = 14
      Top = 91
      Width = 145
      Height = 21
      PasswordChar = '*'
      TabOrder = 2
    end
  end
  object ComboBox: TComboBox
    Left = 7
    Top = 8
    Width = 146
    Height = 252
    AutoComplete = False
    Style = csSimple
    DoubleBuffered = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 20
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentDoubleBuffered = False
    ParentFont = False
    TabOrder = 0
    Text = #1054#1073#1097#1080#1077' '#1076#1072#1085#1085#1099#1077
    OnChange = ComboBoxChange
    Items.Strings = (
      #1054#1073#1097#1080#1077' '#1076#1072#1085#1085#1099#1077
      #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      #1040#1074#1090#1086#1088#1080#1079#1072#1094#1080#1103
      #1055#1088#1086#1082#1089#1080
      #1041#1077#1079#1086#1087#1072#1089#1085#1086#1089#1090#1100)
  end
  object Panel4: TPanel
    Left = 711
    Top = 8
    Width = 178
    Height = 252
    BevelKind = bkFlat
    BevelOuter = bvNone
    Ctl3D = True
    ParentCtl3D = False
    ShowCaption = False
    TabOrder = 5
    object Label7: TLabel
      Left = 16
      Top = 22
      Width = 143
      Height = 13
      AutoSize = False
      Caption = #1040#1076#1088#1077#1089' proxy '#1089#1077#1088#1074#1077#1088#1072
    end
    object Label8: TLabel
      Left = 16
      Top = 72
      Width = 143
      Height = 13
      AutoSize = False
      Caption = #1055#1086#1088#1090' proxy '#1089#1077#1088#1074#1077#1088#1072
    end
    object ButtonProxyApply: TButton
      Left = 60
      Top = 122
      Width = 97
      Height = 25
      Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
      TabOrder = 0
      OnClick = ButtonProxyApplyClick
    end
    object EditProxyServer: TEdit
      Left = 16
      Top = 41
      Width = 143
      Height = 21
      TabOrder = 1
    end
    object EditProxyPort: TEdit
      Left = 14
      Top = 91
      Width = 145
      Height = 21
      TabOrder = 2
    end
  end
  object Panel5: TPanel
    Left = 895
    Top = 8
    Width = 178
    Height = 252
    BevelKind = bkFlat
    BevelOuter = bvNone
    Ctl3D = True
    ParentCtl3D = False
    ShowCaption = False
    TabOrder = 6
    object RandomPassword: TCheckBox
      Left = 16
      Top = 21
      Width = 137
      Height = 17
      Caption = #1053#1077' '#1089#1086#1093#1088#1072#1085#1103#1090#1100' '#1087#1072#1088#1086#1083#1100
      TabOrder = 0
    end
  end
  object ApplicationEvents: TApplicationEvents
    OnIdle = ApplicationEventsIdle
    OnShortCut = ApplicationEventsShortCut
    Left = 64
    Top = 160
  end
end
