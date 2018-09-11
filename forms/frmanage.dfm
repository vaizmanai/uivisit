object fmanage: Tfmanage
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
  ClientHeight = 253
  ClientWidth = 344
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
  object Label1: TLabel
    Left = 184
    Top = 45
    Width = 143
    Height = 13
    AutoSize = False
    Caption = #1042#1077#1088#1089#1080#1103' VNC'
  end
  object Label2: TLabel
    Left = 24
    Top = 45
    Width = 143
    Height = 13
    AutoSize = False
    Caption = #1048#1084#1103' '#1082#1086#1084#1087#1100#1102#1090#1077#1088#1072
  end
  object Label3: TLabel
    Left = 24
    Top = 93
    Width = 143
    Height = 13
    AutoSize = False
    Caption = #1054#1087#1077#1088#1072#1094#1080#1086#1085#1085#1072#1103' '#1089#1080#1089#1090#1077#1084#1072
  end
  object ButtonRefresh: TButton
    Left = 124
    Top = 8
    Width = 97
    Height = 25
    Caption = #1047#1072#1087#1088#1086#1089#1080#1090#1100
    TabOrder = 0
    Visible = False
    OnClick = ButtonRefreshClick
  end
  object ListVNC: TComboBox
    Left = 184
    Top = 64
    Width = 143
    Height = 21
    TabOrder = 1
    Text = 'ListVNC'
  end
  object EditHostname: TEdit
    Left = 24
    Top = 64
    Width = 143
    Height = 21
    ReadOnly = True
    TabOrder = 2
  end
  object EditUptime: TEdit
    Left = 24
    Top = 112
    Width = 143
    Height = 21
    ReadOnly = True
    TabOrder = 3
  end
  object ButtonReVNC: TButton
    Left = 208
    Top = 91
    Width = 97
    Height = 25
    Caption = #1055#1077#1088#1077#1091#1089#1090#1072#1085#1086#1074#1080#1090#1100
    Enabled = False
    TabOrder = 4
    OnClick = ButtonReVNCClick
  end
  object ButtonUpdate: TButton
    Left = 208
    Top = 122
    Width = 97
    Height = 25
    Caption = #1054#1073#1085#1086#1074#1080#1090#1100
    Enabled = False
    TabOrder = 5
    OnClick = ButtonUpdateClick
  end
  object ButtonReload: TButton
    Left = 208
    Top = 153
    Width = 97
    Height = 25
    Caption = #1055#1077#1088#1077#1079#1072#1087#1091#1089#1090#1080#1090#1100
    Enabled = False
    TabOrder = 6
    OnClick = ButtonReloadClick
  end
  object ButtonRestart: TButton
    Left = 208
    Top = 184
    Width = 97
    Height = 25
    Caption = #1055#1077#1088#1077#1079#1072#1075#1088#1091#1079#1080#1090#1100
    Enabled = False
    TabOrder = 7
    OnClick = ButtonRestartClick
  end
  object ApplicationEvents: TApplicationEvents
    OnShortCut = ApplicationEventsShortCut
    Left = 80
    Top = 176
  end
end
