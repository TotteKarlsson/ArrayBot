object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'MainForm'
  ClientHeight = 663
  ClientWidth = 967
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 104
    Top = 32
    Width = 457
    Height = 329
    TabOrder = 0
  end
  object Button1: TButton
    Left = 600
    Top = 40
    Width = 105
    Height = 65
    Caption = 'Start'
    TabOrder = 1
    OnClick = Button1Click
  end
  object infoMemo: TMemo
    Left = 0
    Top = 488
    Width = 967
    Height = 175
    Align = alBottom
    Lines.Strings = (
      'infoMemo')
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object TrackBar1: TTrackBar
    Left = 536
    Top = 400
    Width = 150
    Height = 45
    Max = 1000
    TabOrder = 3
    OnChange = TrackBar1Change
  end
  object Button2: TButton
    Left = 603
    Top = 184
    Width = 102
    Height = 73
    Caption = 'Info'
    TabOrder = 4
    OnClick = Button2Click
  end
  object CheckBox1: TCheckBox
    Left = 632
    Top = 344
    Width = 97
    Height = 17
    Caption = 'CheckBox1'
    TabOrder = 5
    OnClick = CheckBox1Click
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 1
    OnTimer = Timer1Timer
    Left = 736
    Top = 232
  end
  object mShutDownTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = mShutDownTimerTimer
    Left = 808
    Top = 232
  end
end
