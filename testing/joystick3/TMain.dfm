object Main: TMain
  Left = 0
  Top = 0
  AlphaBlend = True
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
    Left = 370
    Top = 76
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 1
  end
  object Button2: TButton
    Left = 431
    Top = 136
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 2
  end
  object Button3: TButton
    Left = 496
    Top = 76
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 3
  end
  object Button4: TButton
    Left = 431
    Top = 16
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 4
  end
  object Button5: TButton
    Left = 115
    Top = 264
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 5
  end
  object Button6: TButton
    Left = 162
    Top = 264
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 6
  end
  object Button7: TButton
    Left = 209
    Top = 264
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 7
  end
  object Button8: TButton
    Left = 256
    Top = 264
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 8
  end
  object Button9: TButton
    Left = 304
    Top = 264
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 9
  end
  object Button10: TButton
    Left = 351
    Top = 264
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 10
  end
  object Button11: TButton
    Left = 398
    Top = 264
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 11
  end
  object Button12: TButton
    Left = 445
    Top = 264
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 12
  end
  object Button13: TButton
    Left = 493
    Top = 264
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 13
  end
  object Button14: TButton
    Left = 539
    Top = 264
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 14
  end
  object POVButton1: TButton
    Left = 130
    Top = 76
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 15
  end
  object POVButton4: TButton
    Left = 191
    Top = 16
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 16
  end
  object POVButton3: TButton
    Left = 256
    Top = 76
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 17
  end
  object POVButton2: TButton
    Left = 191
    Top = 136
    Width = 40
    Height = 40
    Caption = 'Up'
    TabOrder = 18
  end
  object Button15: TButton
    Left = 585
    Top = 240
    Width = 113
    Height = 64
    Caption = 'SwitchJoyStick'
    TabOrder = 19
    OnClick = Button15Click
  end
  object Timer1: TTimer
    Interval = 50
    OnTimer = Timer1Timer
    Left = 272
    Top = 160
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = ShutDownTimerTimer
    Left = 608
    Top = 56
  end
end
