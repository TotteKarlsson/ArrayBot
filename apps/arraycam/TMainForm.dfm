object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Array Cam 0.5'
  ClientHeight = 735
  ClientWidth = 963
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
    Top = 557
    Width = 963
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 8
    ExplicitTop = 528
    ExplicitWidth = 967
  end
  object Splitter2: TSplitter
    Left = 818
    Top = 0
    Height = 557
    Align = alRight
    ExplicitLeft = 784
    ExplicitTop = 184
    ExplicitHeight = 100
  end
  object infoMemo: TMemo
    Left = 0
    Top = 560
    Width = 963
    Height = 175
    Align = alBottom
    ScrollBars = ssVertical
    TabOrder = 0
    ExplicitTop = 488
    ExplicitWidth = 967
  end
  object Panel2: TPanel
    Left = 821
    Top = 0
    Width = 142
    Height = 557
    Align = alRight
    TabOrder = 1
    ExplicitLeft = 825
    ExplicitHeight = 485
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
      Height = 102
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
        TickMarks = tmBoth
        TickStyle = tsNone
        Visible = False
        OnChange = TrackBar1Change
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 241
      Width = 140
      Height = 80
      Align = alTop
      Caption = 'Mirror planes'
      TabOrder = 3
      ExplicitTop = 361
      object mVerticalMirrorCB: TPropertyCheckBox
        Left = 16
        Top = 24
        Width = 65
        Height = 17
        Caption = 'Vertical'
        TabOrder = 0
        OnClick = mVerticalMirrorCBClick
      end
      object mHorizontalMirrorCB: TPropertyCheckBox
        Left = 16
        Top = 47
        Width = 65
        Height = 17
        Caption = 'Horizontal'
        TabOrder = 1
        OnClick = mHorizontalMirrorCBClick
      end
    end
    object mOneToTwoBtn: TButton
      Left = 1
      Top = 433
      Width = 140
      Height = 56
      Align = alTop
      Caption = '1:2'
      TabOrder = 4
      OnClick = mOneToTwoBtnClick
      ExplicitTop = 321
    end
    object mOneToOneBtn: TButton
      Left = 1
      Top = 377
      Width = 140
      Height = 56
      Align = alTop
      Caption = '1:1'
      TabOrder = 5
      OnClick = mOneToOneBtnClick
      ExplicitTop = 321
    end
    object mFitToScreenButton: TButton
      Left = 1
      Top = 321
      Width = 140
      Height = 56
      Align = alTop
      Caption = 'Fit to screen'
      TabOrder = 6
      OnClick = mFitToScreenButtonClick
    end
    object mToggleLogPanel: TButton
      Left = 1
      Top = 489
      Width = 140
      Height = 62
      Align = alTop
      Caption = 'Hide Logs'
      TabOrder = 7
      OnClick = mToggleLogPanelClick
    end
  end
  object mMainPanel: TPanel
    Left = 0
    Top = 0
    Width = 818
    Height = 557
    Align = alClient
    TabOrder = 2
    OnResize = mMainPanelResize
    ExplicitLeft = 120
    ExplicitTop = 96
    ExplicitWidth = 185
    ExplicitHeight = 41
    object mCameraBackPanel: TPanel
      Left = 0
      Top = 0
      Width = 320
      Height = 256
      BorderStyle = bsSingle
      Caption = 'mCameraBackPanel'
      TabOrder = 0
      object mCameraStreamPanel: TPanel
        Left = 1
        Top = 1
        Width = 314
        Height = 250
        Align = alClient
        AutoSize = True
        Color = clTeal
        ParentBackground = False
        TabOrder = 0
        ExplicitWidth = 742
        ExplicitHeight = 441
      end
    end
  end
  object mShutDownTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = mShutDownTimerTimer
    Left = 672
    Top = 152
  end
end
