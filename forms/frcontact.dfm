object fcontact: Tfcontact
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1082#1086#1085#1090#1072#1082#1090#1072
  ClientHeight = 288
  ClientWidth = 290
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 21
    Width = 48
    Height = 13
    Caption = #1053#1072#1079#1074#1072#1085#1080#1077
  end
  object Label2: TLabel
    Left = 16
    Top = 72
    Width = 37
    Height = 13
    Caption = #1055#1072#1088#1086#1083#1100
  end
  object Label3: TLabel
    Left = 151
    Top = 21
    Width = 82
    Height = 13
    Caption = #1048#1076#1077#1085#1090#1080#1092#1080#1082#1072#1090#1086#1088
  end
  object Label4: TLabel
    Left = 151
    Top = 72
    Width = 105
    Height = 13
    Caption = #1056#1086#1076#1080#1090#1077#1083#1100#1089#1082#1072#1103' '#1087#1072#1087#1082#1072
  end
  object Label5: TLabel
    Left = 16
    Top = 123
    Width = 49
    Height = 13
    Caption = #1054#1087#1080#1089#1072#1085#1080#1077
  end
  object EditPid: TEdit
    Left = 151
    Top = 40
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'EditPid'
  end
  object EditPas: TEdit
    Left = 16
    Top = 91
    Width = 121
    Height = 21
    TabOrder = 2
    Text = 'EditPas'
  end
  object EditCaption: TEdit
    Left = 16
    Top = 40
    Width = 121
    Height = 21
    TabOrder = 0
    Text = 'EditCaption'
  end
  object MemoDesc: TMemo
    Left = 16
    Top = 142
    Width = 256
    Height = 89
    Enabled = False
    TabOrder = 4
  end
  object Parent: TComboBox
    Left = 151
    Top = 91
    Width = 121
    Height = 21
    Enabled = False
    TabOrder = 3
    Text = 'Parent'
  end
  object ButtonAdd: TButton
    Left = 175
    Top = 255
    Width = 97
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 5
    OnClick = ButtonAddClick
  end
  object ApplicationEvents: TApplicationEvents
    OnShortCut = ApplicationEventsShortCut
    Left = 120
    Top = 184
  end
end
