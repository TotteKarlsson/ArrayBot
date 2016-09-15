object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Array Cam 0.5'
  ClientHeight = 693
  ClientWidth = 968
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 19
  object Splitter1: TSplitter
    Left = 0
    Top = 531
    Width = 968
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 8
    ExplicitTop = 528
    ExplicitWidth = 967
  end
  object Splitter2: TSplitter
    Left = 786
    Top = 0
    Height = 531
    Align = alRight
    ExplicitLeft = 784
    ExplicitTop = 184
    ExplicitHeight = 100
  end
  object Panel2: TPanel
    Left = 789
    Top = 0
    Width = 179
    Height = 531
    Align = alRight
    TabOrder = 0
    ExplicitHeight = 740
    object ScrollBox1: TScrollBox
      Left = 1
      Top = 1
      Width = 177
      Height = 529
      VertScrollBar.Position = 174
      Align = alClient
      TabOrder = 0
      ExplicitHeight = 738
      object GroupBox5: TGroupBox
        Left = 0
        Top = -174
        Width = 156
        Height = 60
        Align = alTop
        Caption = 'Temperature'
        TabOrder = 1
        Visible = False
        object mTemperatureLbl: mtkFloatLabel
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
      object GroupBox6: TGroupBox
        Left = 0
        Top = -114
        Width = 156
        Height = 60
        Align = alTop
        Caption = 'Humidity'
        TabOrder = 2
        Visible = False
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
      object Button2: TArrayBotButton
        Left = 0
        Top = 486
        Width = 156
        Height = 60
        Align = alBottom
        Caption = 'Exit'
        ParentDoubleBuffered = True
        TabOrder = 0
        OnClick = Button2Click
        SoundID = 'BUTTON_CLICK_4'
      end
      object mFitToScreenButton: TArrayBotButton
        Left = 0
        Top = -54
        Width = 156
        Height = 60
        Align = alTop
        Caption = 'Fit to screen'
        ParentDoubleBuffered = True
        TabOrder = 3
        OnClick = mFitToScreenButtonClick
        SoundID = 'BUTTON_CLICK_4'
      end
      object mFrontBackLEDBtn: TArrayBotButton
        Left = 0
        Top = 426
        Width = 156
        Height = 60
        Align = alBottom
        Caption = 'Toggle LED Light'
        ParentDoubleBuffered = True
        TabOrder = 4
        WordWrap = True
        OnClick = mFrontBackLEDBtnClick
        SoundID = 'BUTTON_CLICK_4'
      end
      object mOneToOneBtn: TArrayBotButton
        Left = 0
        Top = 186
        Width = 156
        Height = 60
        Align = alTop
        Caption = '1:1'
        ParentDoubleBuffered = True
        TabOrder = 5
        OnClick = mOneToOneBtnClick
        SoundID = 'BUTTON_CLICK_4'
      end
      object mOneToTwoBtn: TArrayBotButton
        Left = 0
        Top = 246
        Width = 156
        Height = 60
        Align = alTop
        Caption = '1:2'
        ParentDoubleBuffered = True
        TabOrder = 6
        OnClick = mOneToTwoBtnClick
        SoundID = 'BUTTON_CLICK_4'
      end
      object mRecordMovieBtn: TArrayBotButton
        Left = 0
        Top = 306
        Width = 156
        Height = 60
        Align = alTop
        Caption = 'Record Movie'
        ParentDoubleBuffered = True
        TabOrder = 7
        OnClick = mRecordMovieBtnClick
        SoundID = 'BUTTON_CLICK_4'
      end
      object mSettingsBtn: TArrayBotButton
        Left = 0
        Top = 66
        Width = 156
        Height = 60
        Align = alTop
        Caption = 'Settings'
        ParentDoubleBuffered = True
        TabOrder = 8
        OnClick = mSettingsBtnClick
        SoundID = 'BUTTON_CLICK_4'
      end
      object mSnapShotBtn: TArrayBotButton
        Left = 0
        Top = 126
        Width = 156
        Height = 60
        Align = alTop
        Caption = 'Snap Shot'
        ParentDoubleBuffered = True
        TabOrder = 9
        OnClick = mSnapShotBtnClick
        SoundID = 'CAMERA_SHUTTER_1'
      end
      object mToggleCoaxBtn: TArrayBotButton
        Left = 0
        Top = 366
        Width = 156
        Height = 60
        Align = alBottom
        Caption = 'Toggle Coax Light'
        ParentDoubleBuffered = True
        TabOrder = 10
        WordWrap = True
        OnClick = mFrontBackLEDBtnClick
        SoundID = 'BUTTON_CLICK_4'
      end
      object mToggleLogPanelBtn: TArrayBotButton
        Left = 0
        Top = 6
        Width = 156
        Height = 60
        Align = alTop
        Caption = 'Hide Bottom Panel'
        ParentDoubleBuffered = True
        TabOrder = 11
        OnClick = mToggleLogPanelClick
        SoundID = 'BUTTON_CLICK_4'
      end
    end
  end
  object mMainPanel: TPanel
    Left = 0
    Top = 0
    Width = 786
    Height = 531
    Align = alClient
    TabOrder = 1
    OnResize = mMainPanelResize
    ExplicitHeight = 740
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
    Top = 534
    Width = 968
    Height = 159
    Align = alBottom
    TabOrder = 2
    ExplicitTop = 743
    object GroupBox3: TGroupBox
      Left = 105
      Top = 1
      Width = 120
      Height = 157
      Align = alLeft
      Caption = 'Snap Shots'
      TabOrder = 0
      object mShotsLB: TListBox
        Left = 2
        Top = 21
        Width = 116
        Height = 134
        Align = alClient
        ItemHeight = 19
        PopupMenu = mMediaPopup
        TabOrder = 0
        OnDblClick = mMoviesLBDblClick
      end
    end
    object GroupBox4: TGroupBox
      Left = 1
      Top = 1
      Width = 104
      Height = 157
      Align = alLeft
      Caption = 'Movies'
      TabOrder = 1
      object mMoviesLB: TListBox
        Left = 2
        Top = 21
        Width = 100
        Height = 134
        Align = alClient
        ItemHeight = 19
        PopupMenu = mMediaPopup
        TabOrder = 0
        OnDblClick = mMoviesLBDblClick
      end
    end
    object GroupBox8: TGroupBox
      Left = 513
      Top = 1
      Width = 454
      Height = 157
      Align = alClient
      Caption = 'Logs'
      TabOrder = 2
      object infoMemo: TMemo
        Left = 2
        Top = 62
        Width = 450
        Height = 93
        Align = alClient
        ScrollBars = ssVertical
        TabOrder = 0
      end
      object Panel1: TPanel
        Left = 2
        Top = 21
        Width = 450
        Height = 41
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 1
        object ToolBar1: TToolBar
          Left = 0
          Top = 0
          Width = 450
          Height = 40
          AutoSize = True
          ButtonHeight = 40
          Caption = 'ToolBar1'
          TabOrder = 0
          object mClearLogMemoBtn: TBitBtn
            Left = 0
            Top = 0
            Width = 113
            Height = 40
            Align = alLeft
            Caption = 'Clear'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = ClearLogMemo
          end
          object LogLevelCB: TComboBox
            Left = 113
            Top = 0
            Width = 145
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            Text = 'INFO'
            OnChange = LogLevelCBChange
            Items.Strings = (
              'INFO'
              'DEBUG'
              'DEBUG1'
              'DEBUG2'
              'DEBUG3'
              'DEBUG4'
              'DEBUG5')
          end
        end
      end
    end
    object LightIntensitiesGB: TGroupBox
      Left = 225
      Top = 1
      Width = 288
      Height = 157
      Align = alLeft
      Caption = 'Light Intensities'
      TabOrder = 3
      object mCoaxLbl: TLabel
        Left = 151
        Top = 112
        Width = 85
        Height = 19
        Caption = 'Coax: (122)'
      end
      object mBackLEDLbl: TLabel
        Left = 151
        Top = 69
        Width = 85
        Height = 19
        Caption = 'Coax: (122)'
      end
      object mFrontLEDLbl: TLabel
        Left = 151
        Top = 26
        Width = 85
        Height = 19
        Caption = 'Coax: (122)'
      end
      object Panel3: TPanel
        Left = 2
        Top = 21
        Width = 143
        Height = 134
        Align = alLeft
        TabOrder = 0
        object mBackLEDTB: TTrackBar
          Left = 1
          Top = 46
          Width = 141
          Height = 45
          Align = alTop
          Max = 255
          TabOrder = 0
          TickStyle = tsNone
          OnChange = IntensityChange
        end
        object mCoaxTB: TTrackBar
          Left = 1
          Top = 91
          Width = 141
          Height = 45
          Align = alTop
          Max = 255
          TabOrder = 1
          TickStyle = tsNone
          OnChange = IntensityChange
        end
        object mFrontLEDTB: TTrackBar
          Left = 1
          Top = 1
          Width = 141
          Height = 45
          Align = alTop
          Max = 255
          TabOrder = 2
          TickStyle = tsNone
          OnChange = IntensityChange
        end
      end
    end
  end
  object mShutDownTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = mShutDownTimerTimer
    Left = 304
    Top = 640
  end
  object mCaptureVideoTimer: TTimer
    Enabled = False
    Interval = 1
    OnTimer = mCaptureVideoTimerTimer
    Left = 208
    Top = 680
  end
  object mMediaPopup: TPopupMenu
    Left = 72
    Top = 640
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
