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
    object mOneToTwoBtn: TButton
      Left = 1
      Top = 129
      Width = 113
      Height = 40
      Align = alTop
      Caption = '1:2'
      TabOrder = 0
      OnClick = mOneToTwoBtnClick
    end
    object mOneToOneBtn: TButton
      Left = 1
      Top = 89
      Width = 113
      Height = 40
      Align = alTop
      Caption = '1:1'
      TabOrder = 1
      OnClick = mOneToOneBtnClick
    end
    object mFitToScreenButton: TButton
      Left = 1
      Top = 49
      Width = 113
      Height = 40
      Align = alTop
      Caption = 'Fit to screen'
      TabOrder = 2
      OnClick = mFitToScreenButtonClick
    end
    object mToggleLogPanelBtn: TButton
      Left = 1
      Top = 169
      Width = 113
      Height = 40
      Align = alTop
      Caption = 'Hide Bottom Panel'
      TabOrder = 3
      OnClick = mToggleLogPanelClick
    end
    object mRecordMovieBtn: TButton
      Left = 1
      Top = 209
      Width = 113
      Height = 40
      Align = alTop
      Caption = 'Record Movie'
      TabOrder = 4
      OnClick = mRecordMovieBtnClick
    end
    object mSnapShotBtn: TButton
      Left = 1
      Top = 249
      Width = 113
      Height = 40
      Align = alTop
      Caption = 'Snap Shot'
      TabOrder = 5
      OnClick = mSnapShotBtnClick
    end
    object Button2: TButton
      Left = 1
      Top = 821
      Width = 113
      Height = 40
      Align = alBottom
      Caption = 'Exit'
      TabOrder = 6
      OnClick = Button2Click
    end
    object mSettingsBtn: TButton
      Left = 1
      Top = 1
      Width = 113
      Height = 48
      Align = alTop
      Caption = 'Settings'
      TabOrder = 7
      OnClick = mSettingsBtnClick
    end
    object GroupBox5: TGroupBox
      Left = 1
      Top = 456
      Width = 113
      Height = 60
      Align = alBottom
      Caption = 'Temperature'
      TabOrder = 8
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
      Left = 1
      Top = 516
      Width = 113
      Height = 60
      Align = alBottom
      Caption = 'Humidity'
      TabOrder = 9
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
      TabOrder = 10
      WordWrap = True
      OnClick = mFrontBackLEDBtnClick
    end
    object mToggleCoaxBtn: TButton
      Left = 1
      Top = 771
      Width = 113
      Height = 50
      Align = alBottom
      Caption = 'Toggle Coax Light'
      TabOrder = 11
      WordWrap = True
      OnClick = mFrontBackLEDBtnClick
    end
    object GroupBox7: TGroupBox
      Left = 1
      Top = 576
      Width = 113
      Height = 145
      Align = alBottom
      Caption = 'Light Intensities'
      TabOrder = 12
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
        Top = 15
        Width = 116
        Height = 140
        Align = alClient
        ItemHeight = 13
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
        Top = 15
        Width = 100
        Height = 140
        Align = alClient
        ItemHeight = 13
        PopupMenu = mMediaPopup
        TabOrder = 0
        OnDblClick = mMoviesLBDblClick
      end
    end
    object GroupBox8: TGroupBox
      Left = 225
      Top = 1
      Width = 753
      Height = 157
      Align = alClient
      Caption = 'Logs'
      TabOrder = 2
      object infoMemo: TMemo
        Left = 2
        Top = 56
        Width = 749
        Height = 99
        Align = alClient
        ScrollBars = ssVertical
        TabOrder = 0
      end
      object Panel1: TPanel
        Left = 2
        Top = 15
        Width = 749
        Height = 41
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 1
        object ToolBar1: TToolBar
          Left = 0
          Top = 0
          Width = 749
          Height = 30
          AutoSize = True
          ButtonHeight = 30
          Caption = 'ToolBar1'
          TabOrder = 0
          object mClearLogMemoBtn: TBitBtn
            Left = 0
            Top = 0
            Width = 75
            Height = 30
            Caption = 'Clear'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = Button1Click
          end
          object LogLevelCB: TComboBox
            Left = 75
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
