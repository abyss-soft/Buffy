object AboutBox: TAboutBox
  Left = 163
  Top = 168
  BorderStyle = bsToolWindow
  Caption = 'Buffy Created by Flame.'
  ClientHeight = 358
  ClientWidth = 791
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = True
  Position = poScreenCenter
  Scaled = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object LMDDockLabel3: TLMDDockLabel
    Left = 95
    Top = 6
    Width = 486
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Caption = #1053#1077#1084#1085#1086#1075#1086' '#1080#1089#1090#1086#1088#1080#1080' '#1080#1083#1080' '#1082#1072#1082' '#1087#1086#1103#1074#1080#1083#1072#1089#1100' '#1076#1072#1085#1085#1072#1103' '#1087#1088#1086#1075#1088#1072#1084#1084#1072':'
  end
  object LMDDockLabel4: TLMDDockLabel
    Left = 208
    Top = 232
    Width = 273
    Height = 25
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Caption = #1047#1072#1095#1077#1084' '#1086#1085#1072', '#1089#1086#1073#1089#1090#1074#1077#1085#1085#1086', '#1085#1091#1078#1085#1072':'
  end
  object NLicense: TLMDGlyphLabel
    Left = 40
    Top = 40
    Width = 10
    Height = 22
    Alignment.Alignment = agTopLeft
    Bevel.Mode = bmCustom
    Caption = ' '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object MHistory: TLMDGlyphLabel
    Left = 24
    Top = 24
    Width = 10
    Height = 22
    Alignment.Alignment = agTopLeft
    Bevel.Mode = bmCustom
    Caption = ' '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object MUsed: TLMDGlyphLabel
    Left = 24
    Top = 248
    Width = 10
    Height = 22
    Alignment.Alignment = agTopLeft
    Bevel.Mode = bmCustom
    Caption = ' '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LMDFormFill1: TLMDFormFill
    FillObject.Style = sfGradient
    FillObject.Gradient.Color = 16744576
    FillObject.Gradient.ColorCount = 100
    FillObject.Gradient.Style = gstElliptic
    FillObject.Gradient.EndColor = clGray
    Left = 696
    Top = 520
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 30
    OnTimer = Timer1Timer
    Left = 744
    Top = 312
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 30
    OnTimer = Timer2Timer
    Left = 712
    Top = 312
  end
  object Timer3: TTimer
    Enabled = False
    Interval = 30
    OnTimer = Timer3Timer
    Left = 680
    Top = 312
  end
end
