object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Main'
  ClientHeight = 451
  ClientWidth = 712
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object infoMemo: TMemo
    Left = 0
    Top = 320
    Width = 712
    Height = 131
    Align = alBottom
    Lines.Strings = (
      'infoMemo')
    TabOrder = 0
  end
  object Button1: TButton
    Left = 24
    Top = 200
    Width = 65
    Height = 65
    Caption = 'Up'
    TabOrder = 1
  end
  object Timer1: TTimer
    Interval = 50
    OnTimer = Timer1Timer
    Left = 184
    Top = 64
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = ShutDownTimerTimer
    Left = 440
    Top = 80
  end
end
