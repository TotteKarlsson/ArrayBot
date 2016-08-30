object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
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
  object SpeedButton1: TSpeedButton
    Left = 32
    Top = 40
    Width = 97
    Height = 81
  end
  object BitBtn1: TBitBtn
    Left = 248
    Top = 152
    Width = 105
    Height = 81
    Caption = 'BitBtn1'
    TabOrder = 0
  end
  object Button1: TButton
    Left = 32
    Top = 152
    Width = 121
    Height = 81
    Caption = 'Button1'
    TabOrder = 1
  end
  object ButtonedEdit1: TButtonedEdit
    Left = 176
    Top = 40
    Width = 177
    Height = 21
    TabOrder = 2
    Text = 'ButtonedEdit1'
  end
  object ArrayBotButton1: TArrayBotButton
    Left = 520
    Top = 256
    Width = 217
    Height = 113
    Caption = 'ArrayBotButton1'
    TabOrder = 3
    OnClick = ArrayBotButton1Click
    SoundID = 'BUTTON_CLICK_4'
  end
  object mInfoMemo: TMemo
    Left = 0
    Top = 488
    Width = 902
    Height = 118
    Align = alBottom
    Lines.Strings = (
      'Memo1')
    TabOrder = 4
  end
  object mShutDownTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = mShutDownTimerTimer
    Left = 488
    Top = 104
  end
end
