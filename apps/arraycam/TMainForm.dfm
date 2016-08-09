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
    Top = 621
    Width = 963
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 8
    ExplicitTop = 528
    ExplicitWidth = 967
  end
  object Splitter2: TSplitter
    Left = 845
    Top = 0
    Height = 621
    Align = alRight
    ExplicitLeft = 784
    ExplicitTop = 184
    ExplicitHeight = 100
  end
  object infoMemo: TMemo
    Left = 0
    Top = 624
    Width = 963
    Height = 111
    Align = alBottom
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Panel2: TPanel
    Left = 848
    Top = 0
    Width = 115
    Height = 621
    Align = alRight
    TabOrder = 1
    object mCameraStartLiveBtn: TButton
      Left = 1
      Top = 1
      Width = 113
      Height = 65
      Align = alTop
      Caption = 'Start'
      TabOrder = 0
      OnClick = mCameraStartLiveBtnClick
    end
    object Button2: TButton
      Left = 1
      Top = 66
      Width = 113
      Height = 73
      Align = alTop
      Caption = 'Info'
      TabOrder = 1
      OnClick = Button2Click
    end
    object GroupBox1: TGroupBox
      Left = 1
      Top = 139
      Width = 113
      Height = 70
      Align = alTop
      Caption = 'Settings'
      TabOrder = 2
      object mAutoGainCB: TCheckBox
        Left = 2
        Top = 15
        Width = 109
        Height = 17
        Align = alTop
        Caption = 'Auto Gain'
        TabOrder = 0
        OnClick = mAutoGainCBClick
      end
      object TrackBar1: TTrackBar
        Left = 2
        Top = 32
        Width = 109
        Height = 33
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
      Top = 209
      Width = 113
      Height = 80
      Align = alTop
      Caption = 'Mirror planes'
      TabOrder = 3
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
      Top = 409
      Width = 113
      Height = 60
      Align = alTop
      Caption = '1:2'
      TabOrder = 4
      OnClick = mOneToTwoBtnClick
    end
    object mOneToOneBtn: TButton
      Left = 1
      Top = 349
      Width = 113
      Height = 60
      Align = alTop
      Caption = '1:1'
      TabOrder = 5
      OnClick = mOneToOneBtnClick
    end
    object mFitToScreenButton: TButton
      Left = 1
      Top = 289
      Width = 113
      Height = 60
      Align = alTop
      Caption = 'Fit to screen'
      TabOrder = 6
      OnClick = mFitToScreenButtonClick
    end
    object mToggleLogPanelBtn: TButton
      Left = 1
      Top = 529
      Width = 113
      Height = 60
      Align = alTop
      Caption = 'Hide Logs'
      TabOrder = 7
      OnClick = mToggleLogPanelClick
    end
    object mRecordMovieBtn: TButton
      Left = 1
      Top = 589
      Width = 113
      Height = 60
      Align = alTop
      Caption = 'Record Movie'
      Enabled = False
      TabOrder = 8
      OnClick = mRecordMovieBtnClick
    end
    object mSnapShotBtn: TButton
      Left = 1
      Top = 469
      Width = 113
      Height = 60
      Align = alTop
      Caption = 'Snap Shot'
      TabOrder = 9
      OnClick = mSnapShotBtnClick
    end
  end
  object mMainPanel: TPanel
    Left = 0
    Top = 0
    Width = 845
    Height = 621
    Align = alClient
    TabOrder = 2
    OnResize = mMainPanelResize
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
