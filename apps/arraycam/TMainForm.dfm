object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Array Cam 0.5'
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
    Left = 0
    Top = 0
    Width = 967
    Height = 488
    Align = alClient
    TabOrder = 0
    object Panel2: TPanel
      Left = 824
      Top = 1
      Width = 142
      Height = 486
      Align = alRight
      TabOrder = 0
      object Button1: TButton
        Left = 1
        Top = 1
        Width = 140
        Height = 65
        Align = alTop
        Caption = 'Start'
        TabOrder = 0
        OnClick = Button1Click
        ExplicitLeft = 80
        ExplicitTop = 40
        ExplicitWidth = 105
      end
      object Button2: TButton
        Left = 1
        Top = 66
        Width = 140
        Height = 73
        Align = alTop
        Caption = 'Info'
        TabOrder = 1
        OnClick = Button2Click
        ExplicitLeft = 83
        ExplicitTop = 184
        ExplicitWidth = 102
      end
      object CheckBox1: TCheckBox
        Left = 1
        Top = 139
        Width = 140
        Height = 17
        Align = alTop
        Caption = 'CheckBox1'
        TabOrder = 2
        OnClick = CheckBox1Click
        ExplicitLeft = 88
        ExplicitTop = 344
        ExplicitWidth = 97
      end
      object TrackBar1: TTrackBar
        Left = 1
        Top = 156
        Width = 140
        Height = 45
        Align = alTop
        Max = 1000
        TabOrder = 3
        OnChange = TrackBar1Change
        ExplicitLeft = 35
        ExplicitTop = 400
        ExplicitWidth = 150
      end
    end
  end
  object infoMemo: TMemo
    Left = 0
    Top = 488
    Width = 967
    Height = 175
    Align = alBottom
    ScrollBars = ssVertical
    TabOrder = 1
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
