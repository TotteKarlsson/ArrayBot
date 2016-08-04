object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Arduino Controller'
  ClientHeight = 646
  ClientWidth = 983
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 23
  object mButtonPanel: TPanel
    Left = 800
    Top = 71
    Width = 183
    Height = 575
    Align = alRight
    TabOrder = 0
    object BottomBtnPanel: TPanel
      Left = 1
      Top = 447
      Width = 181
      Height = 127
      Align = alBottom
      AutoSize = True
      TabOrder = 0
      object Button5: TSpeedButton
        Left = 1
        Top = 1
        Width = 179
        Height = 125
        Action = FileExit1
        Align = alBottom
      end
    end
    object mFrontBackLEDBtn: TButton
      Left = 1
      Top = 1
      Width = 181
      Height = 100
      Align = alTop
      Caption = 'FrontBack LEDs ON'
      TabOrder = 1
      OnClick = LEDBtnClick
      ExplicitLeft = 4
      ExplicitTop = 5
    end
    object Button1: TButton
      Left = 1
      Top = 336
      Width = 181
      Height = 111
      Align = alBottom
      Caption = 'About'
      TabOrder = 2
      OnClick = mAboutBtnClick
    end
  end
  object MainPanel: TPanel
    Left = 0
    Top = 71
    Width = 800
    Height = 575
    Align = alClient
    TabOrder = 1
    object Splitter1: TSplitter
      Left = 1
      Top = 361
      Width = 798
      Height = 3
      Cursor = crVSplit
      Align = alTop
      ExplicitLeft = 25
      ExplicitTop = 586
      ExplicitWidth = 902
    end
    object TopPanel: TPanel
      Left = 1
      Top = 1
      Width = 798
      Height = 360
      Align = alTop
      Constraints.MinHeight = 348
      Constraints.MinWidth = 670
      TabOrder = 0
      object PageControl1: TPageControl
        Left = 1
        Top = 1
        Width = 796
        Height = 358
        ActivePage = TabSheet1
        Align = alClient
        TabOrder = 0
        object TabSheet1: TTabSheet
          Caption = 'Ribbon Controller'
          object GroupBox3: TGroupBox
            Left = 18
            Top = 20
            Width = 303
            Height = 157
            Caption = 'Auto Puff Control'
            TabOrder = 0
            object mPuffAfterSectionCountE: TIntegerLabeledEdit
              Left = 152
              Top = 50
              Width = 129
              Height = 31
              EditLabel.Width = 131
              EditLabel.Height = 23
              EditLabel.Caption = 'Puff after count'
              TabOrder = 0
              Text = '-1'
              OnKeyDown = mPuffAfterSectionCountEKeyDown
              Value = -1
            end
            object mAutoPuffCB: TPropertyCheckBox
              Left = 16
              Top = 57
              Width = 97
              Height = 17
              Caption = 'Enabled'
              TabOrder = 1
              OnClick = mAutoPuffCBClick
            end
          end
          object GroupBox6: TGroupBox
            Left = 327
            Top = 20
            Width = 258
            Height = 157
            Caption = 'Manual Puff'
            TabOrder = 1
            object PuffNowBtn: TButton
              Left = 19
              Top = 32
              Width = 214
              Height = 104
              Caption = 'Puff'
              TabOrder = 0
              OnClick = PuffNowBtnClick
            end
          end
        end
        object TabSheet2: TTabSheet
          Caption = 'Settings'
          ImageIndex = 1
          object GroupBox1: TGroupBox
            Left = 0
            Top = 0
            Width = 257
            Height = 320
            Align = alLeft
            Caption = 'Arduino Server'
            TabOrder = 0
            object mArduinoServerPortE: TIntegerLabeledEdit
              Left = 16
              Top = 56
              Width = 121
              Height = 31
              EditLabel.Width = 108
              EditLabel.Height = 23
              EditLabel.Caption = 'Network Port'
              TabOrder = 0
              Text = '50000'
              Value = 50000
            end
            object mArduinoServerStartBtn: TButton
              Left = 16
              Top = 160
              Width = 200
              Height = 65
              Caption = 'Start/Stop'
              TabOrder = 1
              OnClick = mArduinoServerStartBtnClick
            end
          end
          object mArduinoSB: TScrollBox
            Left = 257
            Top = 0
            Width = 531
            Height = 320
            Align = alClient
            TabOrder = 1
          end
        end
      end
    end
    object BottomPanel: TPanel
      Left = 1
      Top = 364
      Width = 798
      Height = 210
      Align = alClient
      TabOrder = 1
      object infoMemo: TMemo
        Left = 1
        Top = 31
        Width = 796
        Height = 178
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
      end
      object ToolBar1: TToolBar
        Left = 1
        Top = 1
        Width = 796
        Height = 30
        AutoSize = True
        ButtonHeight = 30
        Caption = 'ToolBar1'
        TabOrder = 1
        object mClearLogMemoBtn: TBitBtn
          Left = 0
          Top = 0
          Width = 75
          Height = 30
          Caption = 'Clear'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          OnClick = mClearLogMemoBtnClick
        end
        object LogLevelCB: TComboBox
          Left = 75
          Top = 0
          Width = 145
          Height = 31
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          Text = 'INFO'
          OnChange = LogLevelCBChange
          Items.Strings = (
            'INFO'
            'Everything')
        end
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 983
    Height = 71
    Align = alTop
    TabOrder = 2
    object GroupBox4: TGroupBox
      Left = 726
      Top = 1
      Width = 139
      Height = 69
      Align = alRight
      Caption = 'Temperature'
      TabOrder = 0
      object mTemperatureLbl: mtkFloatLabel
        Left = 40
        Top = 31
        Width = 43
        Height = 23
        Caption = '-1.00'
        ValueString = '-1.00'
        Value = -1.000000000000000000
        TheFont.Charset = DEFAULT_CHARSET
        TheFont.Color = clWindowText
        TheFont.Height = -19
        TheFont.Name = 'Tahoma'
        TheFont.Style = []
      end
    end
    object GroupBox5: TGroupBox
      Left = 865
      Top = 1
      Width = 117
      Height = 69
      Align = alRight
      Caption = 'Humidity'
      TabOrder = 1
      object mHumidityE: mtkFloatLabel
        Left = 30
        Top = 31
        Width = 43
        Height = 23
        Caption = '-1.00'
        ValueString = '-1.00'
        Value = -1.000000000000000000
        TheFont.Charset = DEFAULT_CHARSET
        TheFont.Color = clWindowText
        TheFont.Height = -19
        TheFont.Name = 'Tahoma'
        TheFont.Style = []
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 1
      Width = 152
      Height = 69
      Align = alLeft
      Caption = 'Section Count'
      TabOrder = 2
      object mSectionCount: TIntLabel
        Left = 40
        Top = 31
        Width = 17
        Height = 23
        Caption = '-1'
        ValueString = '-1'
        Value = -1
        TheFont.Charset = DEFAULT_CHARSET
        TheFont.Color = clWindowText
        TheFont.Height = -19
        TheFont.Name = 'Tahoma'
        TheFont.Style = []
      end
    end
    object mResetCounterBtn: TButton
      Left = 153
      Top = 1
      Width = 160
      Height = 69
      Align = alLeft
      Caption = 'Reset Counter'
      TabOrder = 3
      OnClick = mResetCounterBtnClick
    end
  end
  object ActionList1: TActionList
    Left = 260
    Top = 360
    object checkForDevices: TAction
      Caption = 'Devices Check'
    end
    object addDevicesToListBox: TAction
      Caption = 'Connect All'
    end
    object identifyCurrent: TAction
      Caption = 'Identify'
    end
    object homeDevice: TAction
      Caption = 'Home'
    end
    object jogForward: TAction
      Caption = 'Fwd'
    end
    object jogBackwards: TAction
      Caption = 'Rev'
    end
    object moveForward: TAction
      Caption = 'Forward'
    end
    object moveBackward: TAction
      Caption = 'Backward'
    end
    object stopAllA: TAction
      Caption = 'Stop All'
    end
    object reInitBotA: TAction
      Caption = 'Reinitialize Devices'
    end
    object ShutDownA: TAction
      Caption = 'Disconnect Devices'
    end
    object FileExit1: TFileExit
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
    object abortLiftA: TAction
      Caption = 'Abort Lift'
    end
    object liftA: TAction
      Caption = 'Lift'
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = ShutDownTimerTimer
    Left = 476
    Top = 360
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 152
    Top = 360
  end
  object UIUpdateTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = UIUpdateTimerTimer
    Left = 180
    Top = 416
  end
end
