object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Arduino Client'
  ClientHeight = 697
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
    Height = 697
    Align = alRight
    TabOrder = 0
    object BottomBtnPanel: TPanel
      Left = 1
      Top = 569
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
    object GroupBox3: TGroupBox
      Left = 1
      Top = 1
      Width = 181
      Height = 64
      Align = alTop
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
    object GroupBox4: TGroupBox
      Left = 1
      Top = 65
      Width = 181
      Height = 73
      Align = alTop
      Caption = 'Temperature'
      TabOrder = 2
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
  end
  object MainPanel: TPanel
    Left = 0
    Top = 0
    Width = 672
    Height = 697
    Align = alClient
    TabOrder = 1
    object Splitter1: TSplitter
      Left = 1
      Top = 563
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
      Height = 562
      Align = alTop
      Constraints.MinHeight = 348
      Constraints.MinWidth = 670
      TabOrder = 0
      object GroupBox1: TGroupBox
        Left = 16
        Top = 13
        Width = 257
        Height = 204
        Caption = 'Arduino Client'
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
          Top = 112
          Width = 200
          Height = 65
          Caption = 'Start'
          TabOrder = 1
          OnClick = mASStartBtnClick
        end
      end
      object GroupBox2: TGroupBox
        Left = 312
        Top = 13
        Width = 273
        Height = 124
        Caption = 'Section Count'
        TabOrder = 1
        object mSectionCountLbl: TIntLabel
          Left = 32
          Top = 40
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
        object mResetCountBtn: TButton
          Left = 104
          Top = 35
          Width = 153
          Height = 73
          Caption = 'Reset'
          TabOrder = 0
          OnClick = mResetCountBtnClick
        end
      end
      object GroupBox6: TGroupBox
        Left = 15
        Top = 231
        Width = 258
        Height = 157
        Caption = 'Manual Puff'
        TabOrder = 2
        object PuffNowBtn: TButton
          Left = 19
          Top = 32
          Width = 214
          Height = 104
          Caption = 'Puff'
          TabOrder = 0
        end
      end
      object GroupBox5: TGroupBox
        Left = 312
        Top = 151
        Width = 303
        Height = 106
        Caption = 'Auto Puff Control'
        TabOrder = 3
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
    end
    object BottomPanel: TPanel
      Left = 1
      Top = 566
      Width = 670
      Height = 130
      Align = alClient
      TabOrder = 1
      object infoMemo: TMemo
        Left = 1
        Top = 31
        Width = 668
        Height = 98
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
        Width = 668
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
    Left = 272
    Top = 288
  end
  object UIUpdateTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = UIUpdateTimerTimer
    Left = 548
    Top = 328
  end
end
