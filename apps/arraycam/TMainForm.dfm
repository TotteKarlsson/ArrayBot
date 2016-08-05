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
  object Splitter1: TSplitter
    Left = 0
    Top = 485
    Width = 967
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 8
    ExplicitTop = 528
  end
  object Splitter2: TSplitter
    Left = 822
    Top = 0
    Height = 485
    Align = alRight
    ExplicitLeft = 784
    ExplicitTop = 184
    ExplicitHeight = 100
  end
  object infoMemo: TMemo
    Left = 0
    Top = 488
    Width = 967
    Height = 175
    Align = alBottom
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Panel2: TPanel
    Left = 825
    Top = 0
    Width = 142
    Height = 485
    Align = alRight
    TabOrder = 1
    object mCameraStartLiveBtn: TButton
      Left = 1
      Top = 1
      Width = 140
      Height = 65
      Align = alTop
      Caption = 'Start'
      TabOrder = 0
      OnClick = mCameraStartLiveBtnClick
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
    end
    object GroupBox1: TGroupBox
      Left = 1
      Top = 139
      Width = 140
      Height = 150
      Align = alTop
      Caption = 'Settings'
      TabOrder = 2
      object mAutoGainCB: TCheckBox
        Left = 2
        Top = 15
        Width = 136
        Height = 17
        Align = alTop
        Caption = 'Auto Gain'
        TabOrder = 0
        OnClick = mAutoGainCBClick
        ExplicitLeft = 1
        ExplicitTop = 139
        ExplicitWidth = 140
      end
      object TrackBar1: TTrackBar
        Left = 2
        Top = 32
        Width = 136
        Height = 69
        Align = alTop
        Max = 1000
        Min = 1
        Position = 1
        ShowSelRange = False
        TabOrder = 1
        ThumbLength = 50
        TickMarks = tmBoth
        TickStyle = tsNone
        OnChange = TrackBar1Change
        ExplicitLeft = 1
        ExplicitTop = 139
        ExplicitWidth = 140
      end
    end
    object RadioGroup1: TRadioGroup
      Left = 1
      Top = 289
      Width = 140
      Height = 105
      Align = alTop
      Caption = 'Sizing'
      Enabled = False
      ItemIndex = 1
      Items.Strings = (
        'Proportional'
        'Stretched')
      TabOrder = 3
      OnClick = RadioGroup1Click
      ExplicitLeft = 6
      ExplicitTop = 328
      ExplicitWidth = 185
    end
  end
  object mCameraBackPanel: TPanel
    Left = 0
    Top = 0
    Width = 822
    Height = 485
    Align = alClient
    TabOrder = 2
    ExplicitLeft = 280
    ExplicitTop = 128
    ExplicitWidth = 393
    ExplicitHeight = 249
    object mCameraStreamPanel: TPanel
      Left = 1
      Top = 1
      Width = 820
      Height = 483
      Align = alClient
      TabOrder = 0
      ExplicitLeft = 0
      ExplicitTop = -1
    end
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
    Left = 672
    Top = 152
  end
end
