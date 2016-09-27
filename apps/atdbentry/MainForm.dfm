object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Main'
  ClientHeight = 558
  ClientWidth = 854
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object infoMemo: TMemo
    Left = 0
    Top = 469
    Width = 854
    Height = 89
    Align = alBottom
    Lines.Strings = (
      'infoMemo')
    TabOrder = 0
    ExplicitTop = 193
    ExplicitWidth = 418
  end
  object ArrayBotButton1: TArrayBotButton
    Left = 16
    Top = 56
    Width = 137
    Height = 65
    Caption = 'ArrayBotButton1'
    TabOrder = 1
    OnClick = ArrayBotButton1Click
    SoundID = 'BUTTON_CLICK_4'
  end
  object ArrayBotButton2: TArrayBotButton
    Left = 200
    Top = 56
    Width = 161
    Height = 65
    Caption = 'ArrayBotButton2'
    TabOrder = 2
    OnClick = ArrayBotButton2Click
    SoundID = 'BUTTON_CLICK_4'
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = ShutDownTimerTimer
    Left = 352
    Top = 48
  end
end
