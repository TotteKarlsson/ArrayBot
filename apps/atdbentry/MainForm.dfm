object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Main'
  ClientHeight = 282
  ClientWidth = 418
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
    Top = 193
    Width = 418
    Height = 89
    Align = alBottom
    Lines.Strings = (
      'infoMemo')
    TabOrder = 0
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = ShutDownTimerTimer
    Left = 352
    Top = 48
  end
end
