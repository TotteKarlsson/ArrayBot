object MainForm: TMainForm
  Left = 0
  Top = 0
  ActiveControl = TPGConnectionFrame1.mServerIPE
  Caption = 'Arduino Controller'
  ClientHeight = 947
  ClientWidth = 1488
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
  object Splitter1: TSplitter
    Left = 0
    Top = 735
    Width = 1488
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 32
    ExplicitTop = 657
    ExplicitWidth = 990
  end
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 1488
    Height = 89
    Align = alTop
    TabOrder = 0
    object Button1: TArrayBotButton
      Left = 1320
      Top = 1
      Width = 88
      Height = 87
      Align = alRight
      Caption = 'About'
      ParentDoubleBuffered = True
      TabOrder = 0
      OnClick = mAboutBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
    object Button5: TArrayBotButton
      Left = 1408
      Top = 1
      Width = 79
      Height = 87
      Action = FileExit1
      Align = alRight
      Caption = 'E&xit'
      ParentDoubleBuffered = True
      TabOrder = 1
      SoundID = 'BUTTON_CLICK_4'
    end
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 528
      Height = 87
      Align = alLeft
      Caption = 'Arduino Server'
      TabOrder = 2
      object NrOfServerClients: TIntLabel
        Left = 411
        Top = 31
        Width = 10
        Height = 23
        Caption = '1'
        Value = 1
        TheFont.Charset = DEFAULT_CHARSET
        TheFont.Color = clWindowText
        TheFont.Height = -19
        TheFont.Name = 'Tahoma'
        TheFont.Style = []
      end
      object Label1: TLabel
        Left = 296
        Top = 31
        Width = 109
        Height = 23
        Caption = 'Nr of Clients:'
      end
      object mArduinoServerPortE: TIntegerLabeledEdit
        Left = 184
        Top = 28
        Width = 96
        Height = 31
        EditLabel.Width = 33
        EditLabel.Height = 23
        EditLabel.Caption = 'Port'
        LabelPosition = lpLeft
        TabOrder = 0
        Text = '50000'
        Value = 50000
      end
      object mArduinoServerStartBtn: TButton
        Left = 11
        Top = 27
        Width = 126
        Height = 55
        Caption = 'Start/Stop'
        TabOrder = 1
        OnClick = mArduinoServerStartBtnClick
      end
    end
  end
  object mShowBottomPanelBtn: TButton
    Left = 0
    Top = 928
    Width = 1488
    Height = 19
    Align = alBottom
    Caption = '^'
    TabOrder = 1
    Visible = False
    OnClick = mShowBottomPanelBtnClick
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 738
    Width = 1488
    Height = 190
    Align = alBottom
    TabOrder = 2
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 1486
      Height = 188
      Align = alClient
      Caption = 'Panel2'
      TabOrder = 0
      object infoMemo: TMemo
        Left = 1
        Top = 34
        Width = 1484
        Height = 153
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
      object Panel1: TPanel
        Left = 1
        Top = 1
        Width = 1484
        Height = 33
        Align = alTop
        TabOrder = 1
        object ToolBar1: TToolBar
          Left = 1
          Top = 1
          Width = 1447
          Height = 31
          Align = alClient
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
            Font.Height = -16
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = MiscBtnClick
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
              'DEBUG'
              'DEBUG1'
              'DEBUG2'
              'DEBUG3'
              'DEBUG4'
              'DEBUG5')
          end
        end
        object ToolBar2: TToolBar
          Left = 1448
          Top = 1
          Width = 35
          Height = 31
          Align = alRight
          AutoSize = True
          ButtonHeight = 30
          Caption = 'ToolBar1'
          List = True
          AllowTextButtons = True
          TabOrder = 1
          Wrapable = False
          object mHideBottomPanelBtn: TBitBtn
            Left = 0
            Top = 0
            Width = 35
            Height = 30
            Align = alRight
            Caption = 'x'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = MiscBtnClick
          end
        end
      end
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 89
    Width = 1488
    Height = 646
    ActivePage = TabSheet3
    Align = alClient
    TabOrder = 3
    object TabSheet1: TTabSheet
      Caption = 'Controls'
      object GroupBox4: TGroupBox
        Left = 0
        Top = 0
        Width = 463
        Height = 608
        Align = alLeft
        Caption = 'Lights'
        TabOrder = 0
        object LEDBtn: TArrayBotButton
          Left = 19
          Top = 144
          Width = 200
          Height = 80
          Caption = 'Flip LEDs ON'
          ParentDoubleBuffered = True
          TabOrder = 0
          OnClick = LigthsBtnsClick
          SoundID = 'BUTTON_CLICK_4'
        end
        object RequestInfoBtn: TArrayBotButton
          Left = 19
          Top = 38
          Width = 200
          Height = 80
          Caption = 'Request Info'
          ParentDoubleBuffered = True
          TabOrder = 1
          OnClick = LigthsBtnsClick
          SoundID = 'BUTTON_CLICK_4'
        end
        object LEDDriveE: TIntegerLabeledEdit
          Left = 256
          Top = 168
          Width = 162
          Height = 31
          EditLabel.Width = 149
          EditLabel.Height = 23
          EditLabel.Caption = 'LED Drive (0-255)'
          TabOrder = 2
          Text = '0'
          OnKeyDown = LEDDriveEKeyDown
        end
        object DriveTB: TTrackBar
          Left = 252
          Top = 216
          Width = 166
          Height = 45
          Max = 255
          ShowSelRange = False
          TabOrder = 3
          TickStyle = tsNone
          OnChange = DriveTBChange
        end
      end
      object Button2: TButton
        Left = 1184
        Top = 293
        Width = 185
        Height = 97
        Caption = 'Query Sensors'
        TabOrder = 1
      end
      inline TWatchDogServerFrame1: TWatchDogServerFrame
        Left = 463
        Top = 0
        Width = 1017
        Height = 608
        Align = alClient
        TabOrder = 2
        ExplicitLeft = 463
        ExplicitWidth = 1017
        ExplicitHeight = 608
        inherited GroupBox1: TGroupBox
          Width = 313
          Height = 608
          ExplicitWidth = 313
          ExplicitHeight = 608
          inherited ServerIPE: TSTDStringLabeledEdit
            Height = 31
            EditLabel.Width = 77
            EditLabel.Height = 23
            EditLabel.ExplicitLeft = 17
            EditLabel.ExplicitTop = 22
            EditLabel.ExplicitWidth = 77
            EditLabel.ExplicitHeight = 23
            ExplicitHeight = 31
          end
          inherited WalkBtn: TArrayBotButton
            Height = 33
            ExplicitHeight = 33
          end
          inherited PeriodicReadE: TIntegerLabeledEdit
            Height = 31
            EditLabel.Width = 129
            EditLabel.Height = 23
            EditLabel.ExplicitLeft = 17
            EditLabel.ExplicitTop = 219
            EditLabel.ExplicitWidth = 129
            EditLabel.ExplicitHeight = 23
            ExplicitHeight = 31
          end
        end
        inherited SensorPanel: TScrollBox
          Left = 313
          Width = 704
          Height = 608
          ExplicitLeft = 313
          ExplicitWidth = 704
          ExplicitHeight = 608
        end
        inherited EnvSensorsReadsTimer: TTimer
          Left = 96
          Top = 376
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Board Settings'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object mArduinoSB: TScrollBox
        Left = 0
        Top = 0
        Width = 1480
        Height = 608
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'ATDB'
      ImageIndex = 2
      inline TPGConnectionFrame1: TPGConnectionFrame
        Left = 0
        Top = 0
        Width = 513
        Height = 608
        Align = alLeft
        TabOrder = 0
        ExplicitWidth = 513
        ExplicitHeight = 608
        inherited GBox1: TGroupBox
          Width = 513
          Height = 608
          Align = alClient
          ExplicitWidth = 513
          ExplicitHeight = 608
          inherited mServerIPE: TSTDStringLabeledEdit
            Top = 56
            Height = 31
            EditLabel.Width = 126
            EditLabel.Height = 23
            EditLabel.ExplicitLeft = 16
            EditLabel.ExplicitTop = 30
            EditLabel.ExplicitWidth = 126
            EditLabel.ExplicitHeight = 23
            ExplicitTop = 56
            ExplicitHeight = 31
          end
          inherited mDBUserE: TSTDStringLabeledEdit
            Top = 121
            Height = 31
            EditLabel.Width = 37
            EditLabel.Height = 23
            EditLabel.ExplicitLeft = 16
            EditLabel.ExplicitTop = 95
            EditLabel.ExplicitWidth = 37
            EditLabel.ExplicitHeight = 23
            ExplicitTop = 121
            ExplicitHeight = 31
          end
          inherited mPasswordE: TSTDStringLabeledEdit
            Left = 181
            Top = 121
            Height = 31
            EditLabel.Width = 78
            EditLabel.Height = 23
            EditLabel.ExplicitLeft = 181
            EditLabel.ExplicitTop = 95
            EditLabel.ExplicitWidth = 78
            EditLabel.ExplicitHeight = 23
            ExplicitLeft = 181
            ExplicitTop = 121
            ExplicitHeight = 31
          end
          inherited mDatabaseE: TSTDStringLabeledEdit
            Left = 181
            Top = 56
            Height = 31
            EditLabel.Width = 78
            EditLabel.Height = 23
            EditLabel.ExplicitLeft = 181
            EditLabel.ExplicitTop = 30
            EditLabel.ExplicitWidth = 78
            EditLabel.ExplicitHeight = 23
            ExplicitLeft = 181
            ExplicitTop = 56
            ExplicitHeight = 31
          end
          inherited ArrayBotButton1: TArrayBotButton
            Left = 16
            Top = 184
            Width = 145
            Height = 65
            ExplicitLeft = 16
            ExplicitTop = 184
            ExplicitWidth = 145
            ExplicitHeight = 65
          end
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 164
    Top = 464
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
      ImageIndex = 0
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
    Left = 436
    Top = 376
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 32
    Top = 464
  end
  object UIUpdateTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = UIUpdateTimerTimer
    Left = 436
    Top = 304
  end
  object BindingsList1: TBindingsList
    Methods = <>
    OutputConverters = <>
    Left = 20
    Top = 5
  end
  object GetEnvironmentNumbersTimer: TTimer
    Left = 544
    Top = 560
  end
end
