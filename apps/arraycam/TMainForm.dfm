object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'Array Cam 0.5'
  ClientHeight = 1024
  ClientWidth = 979
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 862
    Width = 979
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 8
    ExplicitTop = 528
    ExplicitWidth = 967
  end
  object Splitter2: TSplitter
    Left = 861
    Top = 0
    Height = 862
    Align = alRight
    ExplicitLeft = 784
    ExplicitTop = 184
    ExplicitHeight = 100
  end
  object Panel2: TPanel
    Left = 864
    Top = 0
    Width = 115
    Height = 862
    Align = alRight
    TabOrder = 0
    ExplicitHeight = 1118
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 113
      Height = 64
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
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 65
      Width = 113
      Height = 64
      Align = alTop
      Caption = 'Mirror planes'
      TabOrder = 1
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
      Top = 209
      Width = 113
      Height = 40
      Align = alTop
      Caption = '1:2'
      TabOrder = 2
      OnClick = mOneToTwoBtnClick
    end
    object mOneToOneBtn: TButton
      Left = 1
      Top = 169
      Width = 113
      Height = 40
      Align = alTop
      Caption = '1:1'
      TabOrder = 3
      OnClick = mOneToOneBtnClick
    end
    object mFitToScreenButton: TButton
      Left = 1
      Top = 129
      Width = 113
      Height = 40
      Align = alTop
      Caption = 'Fit to screen'
      TabOrder = 4
      OnClick = mFitToScreenButtonClick
    end
    object mToggleLogPanelBtn: TButton
      Left = 1
      Top = 289
      Width = 113
      Height = 40
      Align = alTop
      Caption = 'Hide Bottom Panel'
      TabOrder = 5
      OnClick = mToggleLogPanelClick
    end
    object mRecordMovieBtn: TButton
      Left = 1
      Top = 329
      Width = 113
      Height = 40
      Align = alTop
      Caption = 'Record Movie'
      TabOrder = 6
      OnClick = mRecordMovieBtnClick
    end
    object mSnapShotBtn: TButton
      Left = 1
      Top = 249
      Width = 113
      Height = 40
      Align = alTop
      Caption = 'Snap Shot'
      TabOrder = 7
      OnClick = mSnapShotBtnClick
    end
    object Button2: TButton
      Left = 1
      Top = 821
      Width = 113
      Height = 40
      Align = alBottom
      Caption = 'Exit'
      TabOrder = 8
      OnClick = Button2Click
      ExplicitTop = 1077
    end
    object mSettingsBtn: TButton
      Left = 1
      Top = 369
      Width = 113
      Height = 48
      Align = alTop
      Caption = 'Settings'
      TabOrder = 9
      OnClick = mSettingsBtnClick
    end
    object GroupBox5: TGroupBox
      Left = 1
      Top = 601
      Width = 113
      Height = 60
      Align = alBottom
      Caption = 'Temperature'
      TabOrder = 10
      ExplicitTop = 857
      object mTemperatureLbl: mtkFloatLabel
        Left = 32
        Top = 26
        Width = 43
        Height = 23
        Caption = '-1.00'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ValueString = '-1.00'
        Value = -1.000000000000000000
        TheFont.Charset = DEFAULT_CHARSET
        TheFont.Color = clWindowText
        TheFont.Height = -19
        TheFont.Name = 'Tahoma'
        TheFont.Style = []
      end
    end
    object GroupBox6: TGroupBox
      Left = 1
      Top = 661
      Width = 113
      Height = 60
      Align = alBottom
      Caption = 'Humidity'
      TabOrder = 11
      ExplicitTop = 917
      object mHumidityE: mtkFloatLabel
        Left = 32
        Top = 23
        Width = 43
        Height = 23
        Caption = '-1.00'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ValueString = '-1.00'
        Value = -1.000000000000000000
        TheFont.Charset = DEFAULT_CHARSET
        TheFont.Color = clWindowText
        TheFont.Height = -19
        TheFont.Name = 'Tahoma'
        TheFont.Style = []
      end
    end
    object mFrontBackLEDBtn: TButton
      Left = 1
      Top = 721
      Width = 113
      Height = 50
      Align = alBottom
      Caption = 'Toggle LED Light'
      TabOrder = 12
      WordWrap = True
      OnClick = mFrontBackLEDBtnClick
      ExplicitTop = 977
    end
    object mToggleCoaxBtn: TButton
      Left = 1
      Top = 771
      Width = 113
      Height = 50
      Align = alBottom
      Caption = 'Toggle Coax Light'
      TabOrder = 13
      WordWrap = True
      OnClick = mFrontBackLEDBtnClick
      ExplicitTop = 1027
    end
    object GroupBox7: TGroupBox
      Left = 1
      Top = 456
      Width = 113
      Height = 145
      Align = alBottom
      Caption = 'Light Intensities'
      TabOrder = 14
      ExplicitTop = 696
      object mCoaxTB: TTrackBar
        Left = 2
        Top = 105
        Width = 109
        Height = 45
        Align = alTop
        Max = 255
        TabOrder = 0
        OnChange = LightTBChange
      end
      object mBackLEDTB: TTrackBar
        Left = 2
        Top = 60
        Width = 109
        Height = 45
        Align = alTop
        Max = 255
        TabOrder = 1
        OnChange = LightTBChange
      end
      object mFrontLEDTB: TTrackBar
        Left = 2
        Top = 15
        Width = 109
        Height = 45
        Align = alTop
        Max = 255
        TabOrder = 2
        OnChange = LightTBChange
      end
    end
  end
  object mMainPanel: TPanel
    Left = 0
    Top = 0
    Width = 861
    Height = 862
    Align = alClient
    TabOrder = 1
    OnResize = mMainPanelResize
    ExplicitTop = -2
    ExplicitHeight = 1118
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
        OnDblClick = mCameraStreamPanelDblClick
      end
    end
  end
  object mBottomPanel: TPanel
    Left = 0
    Top = 865
    Width = 979
    Height = 159
    Align = alBottom
    TabOrder = 2
    ExplicitTop = 1121
    object infoMemo: TMemo
      Left = 225
      Top = 42
      Width = 753
      Height = 116
      Align = alClient
      ScrollBars = ssVertical
      TabOrder = 0
    end
    object Panel1: TPanel
      Left = 1
      Top = 1
      Width = 977
      Height = 41
      Align = alTop
      TabOrder = 1
      object Button1: TButton
        Left = 911
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
