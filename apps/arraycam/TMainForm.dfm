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
    Top = 573
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
    Height = 573
    Align = alRight
    ExplicitLeft = 784
    ExplicitTop = 184
    ExplicitHeight = 100
  end
  object Panel2: TPanel
    Left = 848
    Top = 0
    Width = 115
    Height = 573
    Align = alRight
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 113
      Height = 128
      Align = alTop
      Caption = 'Settings'
      TabOrder = 0
      object mAutoGainCB: TCheckBox
        Left = 2
        Top = 32
        Width = 109
        Height = 17
        Align = alTop
        Caption = 'Auto Gain'
        TabOrder = 0
        OnClick = AutoParaCBClick
        ExplicitLeft = 18
        ExplicitTop = 79
      end
      object mAutoExposureCB: TCheckBox
        Left = 2
        Top = 15
        Width = 109
        Height = 17
        Align = alTop
        Caption = 'Auto Exposure'
        TabOrder = 1
        OnClick = AutoParaCBClick
        ExplicitLeft = 5
        ExplicitTop = 95
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 129
      Width = 113
      Height = 64
      Align = alTop
      Caption = 'Mirror planes'
      TabOrder = 1
      ExplicitTop = 71
      object mVerticalMirrorCB: TPropertyCheckBox
        Left = 16
        Top = 19
        Width = 65
        Height = 17
        Caption = 'Vertical'
        TabOrder = 0
        OnClick = mVerticalMirrorCBClick
      end
      object mHorizontalMirrorCB: TPropertyCheckBox
        Left = 16
        Top = 42
        Width = 65
        Height = 17
        Caption = 'Horizontal'
        TabOrder = 1
        OnClick = mHorizontalMirrorCBClick
      end
    end
    object mOneToTwoBtn: TButton
      Left = 1
      Top = 273
      Width = 113
      Height = 40
      Align = alTop
      Caption = '1:2'
      TabOrder = 2
      OnClick = mOneToTwoBtnClick
      ExplicitTop = 215
    end
    object mOneToOneBtn: TButton
      Left = 1
      Top = 233
      Width = 113
      Height = 40
      Align = alTop
      Caption = '1:1'
      TabOrder = 3
      OnClick = mOneToOneBtnClick
      ExplicitTop = 175
    end
    object mFitToScreenButton: TButton
      Left = 1
      Top = 193
      Width = 113
      Height = 40
      Align = alTop
      Caption = 'Fit to screen'
      TabOrder = 4
      OnClick = mFitToScreenButtonClick
      ExplicitTop = 135
    end
    object mToggleLogPanelBtn: TButton
      Left = 1
      Top = 353
      Width = 113
      Height = 40
      Align = alTop
      Caption = 'Hide Bottom Panel'
      TabOrder = 5
      OnClick = mToggleLogPanelClick
      ExplicitTop = 295
    end
    object mRecordMovieBtn: TButton
      Left = 1
      Top = 393
      Width = 113
      Height = 40
      Align = alTop
      Caption = 'Record Movie'
      TabOrder = 6
      OnClick = mRecordMovieBtnClick
      ExplicitTop = 335
    end
    object mSnapShotBtn: TButton
      Left = 1
      Top = 313
      Width = 113
      Height = 40
      Align = alTop
      Caption = 'Snap Shot'
      TabOrder = 7
      OnClick = mSnapShotBtnClick
      ExplicitTop = 255
    end
  end
  object mMainPanel: TPanel
    Left = 0
    Top = 0
    Width = 845
    Height = 573
    Align = alClient
    TabOrder = 1
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
  object mBottomPanel: TPanel
    Left = 0
    Top = 576
    Width = 963
    Height = 159
    Align = alBottom
    TabOrder = 2
    object infoMemo: TMemo
      Left = 225
      Top = 42
      Width = 737
      Height = 116
      Align = alClient
      ScrollBars = ssVertical
      TabOrder = 0
      ExplicitLeft = 137
      ExplicitWidth = 825
    end
    object Panel1: TPanel
      Left = 1
      Top = 1
      Width = 961
      Height = 41
      Align = alTop
      TabOrder = 1
      ExplicitLeft = 2
      ExplicitTop = 3
      object Button1: TButton
        Left = 895
        Top = 1
        Width = 65
        Height = 39
        Align = alRight
        Caption = 'Clear'
        TabOrder = 0
        OnClick = Button1Click
      end
    end
    object GroupBox3: TGroupBox
      Left = 105
      Top = 42
      Width = 120
      Height = 116
      Align = alLeft
      Caption = 'Snap Shoots'
      TabOrder = 2
      object mShotsLB: TListBox
        Left = 2
        Top = 15
        Width = 116
        Height = 99
        Align = alClient
        ItemHeight = 13
        PopupMenu = mMediaPopup
        TabOrder = 0
        OnDblClick = mMoviesLBDblClick
        ExplicitLeft = 1
        ExplicitTop = 42
        ExplicitWidth = 88
        ExplicitHeight = 116
      end
    end
    object GroupBox4: TGroupBox
      Left = 1
      Top = 42
      Width = 104
      Height = 116
      Align = alLeft
      Caption = 'Movies'
      TabOrder = 3
      object mMoviesLB: TListBox
        Left = 2
        Top = 15
        Width = 100
        Height = 99
        Align = alClient
        ItemHeight = 13
        PopupMenu = mMediaPopup
        TabOrder = 0
        OnDblClick = mMoviesLBDblClick
        ExplicitLeft = 89
        ExplicitTop = 42
        ExplicitWidth = 88
        ExplicitHeight = 116
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
  object Timer1: TTimer
    Enabled = False
    Interval = 1
    OnTimer = Timer1Timer
    Left = 688
    Top = 80
  end
  object mMediaPopup: TPopupMenu
    Left = 64
    Top = 528
    object Delete1: TMenuItem
      Caption = 'Delete'
      OnClick = Delete1Click
    end
    object DeleteAll1: TMenuItem
      Caption = 'Delete All'
      OnClick = DeleteAll1Click
    end
  end
end
