object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'MainForm'
  ClientHeight = 606
  ClientWidth = 902
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
  PixelsPerInch = 96
  TextHeight = 13
  object mInfoMemo: TMemo
    Left = 0
    Top = 488
    Width = 902
    Height = 118
    Align = alBottom
    Lines.Strings = (
      'Memo1')
    TabOrder = 0
  end
  object mShutDownTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = mShutDownTimerTimer
    Left = 128
    Top = 352
  end
end
