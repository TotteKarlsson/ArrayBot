object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Arduino Client'
  ClientHeight = 585
  ClientWidth = 855
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
    Left = 672
    Top = 0
    Width = 183
    Height = 585
    Align = alRight
    TabOrder = 0
    ExplicitLeft = 904
    ExplicitHeight = 791
    object BottomBtnPanel: TPanel
      Left = 1
      Top = 457
      Width = 181
      Height = 127
      Align = alBottom
      AutoSize = True
      TabOrder = 0
      ExplicitTop = 663
      object Button5: TSpeedButton
        Left = 1
        Top = 1
        Width = 179
        Height = 125
        Action = FileExit1
        Align = alBottom
      end
    end
  end
  object MainPanel: TPanel
    Left = 0
    Top = 0
    Width = 672
    Height = 585
    Align = alClient
    TabOrder = 1
    ExplicitWidth = 904
    ExplicitHeight = 791
    object Splitter1: TSplitter
      Left = 1
      Top = 361
      Width = 670
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
      Width = 670
      Height = 360
      Align = alTop
      Constraints.MinHeight = 348
      Constraints.MinWidth = 670
      TabOrder = 0
      ExplicitWidth = 902
      object GroupBox1: TGroupBox
        Left = 16
        Top = 13
        Width = 257
        Height = 268
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
        object mASStartBtn: TButton
          Left = 16
          Top = 160
          Width = 200
          Height = 65
          Caption = 'Start/Stop'
          TabOrder = 1
          OnClick = mASStartBtnClick
        end
      end
    end
    object BottomPanel: TPanel
      Left = 1
      Top = 364
      Width = 670
      Height = 220
      Align = alClient
      TabOrder = 1
      ExplicitWidth = 902
      ExplicitHeight = 426
      object infoMemo: TMemo
        Left = 1
        Top = 31
        Width = 668
        Height = 188
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
        ExplicitWidth = 900
        ExplicitHeight = 394
      end
      object ToolBar1: TToolBar
        Left = 1
        Top = 1
        Width = 668
        Height = 30
        AutoSize = True
        ButtonHeight = 30
        Caption = 'ToolBar1'
        TabOrder = 1
        ExplicitWidth = 900
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
