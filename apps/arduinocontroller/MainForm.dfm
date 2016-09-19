object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Arduino Controller'
  ClientHeight = 707
  ClientWidth = 986
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
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 986
    Height = 89
    Align = alTop
    TabOrder = 0
    object GroupBox2: TGroupBox
      Left = 1
      Top = 1
      Width = 152
      Height = 87
      Align = alLeft
      Caption = 'Section Count'
      TabOrder = 0
      object mSectionCountLbl: TIntLabel
        Left = 40
        Top = 31
        Width = 10
        Height = 23
        Caption = '0'
        ValueString = '0'
        TheFont.Charset = DEFAULT_CHARSET
        TheFont.Color = clWindowText
        TheFont.Height = -19
        TheFont.Name = 'Tahoma'
        TheFont.Style = []
      end
    end
    object mResetCounterBtn: TArrayBotButton
      Left = 153
      Top = 1
      Width = 136
      Height = 87
      Align = alLeft
      Caption = 'Reset Counter'
      ParentDoubleBuffered = True
      TabOrder = 1
      OnClick = mResetCounterBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
    object Button1: TArrayBotButton
      Left = 818
      Top = 1
      Width = 88
      Height = 87
      Align = alRight
      Caption = 'About'
      ParentDoubleBuffered = True
      TabOrder = 2
      OnClick = mAboutBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
    object Button5: TArrayBotButton
      Left = 906
      Top = 1
      Width = 79
      Height = 87
      Action = FileExit1
      Align = alRight
      Caption = 'E&xit'
      ParentDoubleBuffered = True
      TabOrder = 3
      SoundID = 'BUTTON_CLICK_4'
    end
    object GroupBox1: TGroupBox
      Left = 519
      Top = 1
      Width = 299
      Height = 87
      Align = alRight
      Caption = 'Server'
      TabOrder = 4
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
  object CenterPanel: TPanel
    Left = 0
    Top = 89
    Width = 986
    Height = 618
    Align = alClient
    Caption = 'CenterPanel'
    TabOrder = 1
    ExplicitHeight = 568
    object Splitter1: TSplitter
      Left = 1
      Top = 419
      Width = 984
      Height = 3
      Cursor = crVSplit
      Align = alTop
      ExplicitLeft = 57
      ExplicitTop = 457
      ExplicitWidth = 821
    end
    object BottomPanel: TPanel
      Left = 1
      Top = 422
      Width = 984
      Height = 195
      Align = alClient
      TabOrder = 0
      ExplicitTop = 393
      ExplicitHeight = 224
      object Panel2: TPanel
        Left = 1
        Top = 1
        Width = 982
        Height = 193
        Align = alClient
        Caption = 'Panel2'
        TabOrder = 0
        ExplicitHeight = 172
        object infoMemo: TMemo
          Left = 1
          Top = 31
          Width = 980
          Height = 161
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
          ExplicitHeight = 140
        end
        object ToolBar1: TToolBar
          Left = 1
          Top = 1
          Width = 980
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
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 984
      Height = 418
      ActivePage = TabSheet1
      Align = alTop
      TabOrder = 1
      object TabSheet1: TTabSheet
        Caption = 'Controls'
        ExplicitHeight = 354
        object GroupBox3: TGroupBox
          Left = 3
          Top = 85
          Width = 303
          Height = 268
          Caption = 'Ribbon Separation'
          TabOrder = 0
          object mAutoPuffCB: TPropertyCheckBox
            Left = 16
            Top = 39
            Width = 169
            Height = 17
            Caption = 'Enable Auto Puff'
            TabOrder = 0
            OnClick = mAutoPuffCBClick
          end
          object mAutoZeroCutCB: TPropertyCheckBox
            Left = 16
            Top = 72
            Width = 169
            Height = 17
            Caption = 'Enable Zero Cut'
            TabOrder = 1
            OnClick = mAutoZeroCutCBClick
          end
          object mStartNewRibbonButton: TArrayBotButton
            Left = 16
            Top = 136
            Width = 257
            Height = 113
            Caption = 'Start new ribbon'
            TabOrder = 2
            OnClick = mStartNewRibbonButtonClick
            SoundID = 'BUTTON_CLICK_4'
          end
        end
        object GroupBox6: TGroupBox
          Left = 327
          Top = 14
          Width = 346
          Height = 136
          Caption = 'Puffer'
          TabOrder = 1
          object mPuffNowBtn: TArrayBotButton
            Left = 15
            Top = 37
            Width = 150
            Height = 80
            Caption = 'Puff'
            ParentDoubleBuffered = True
            TabOrder = 0
            OnClick = mPuffRelatedBtnClick
            SoundID = 'short_beep_3'
          end
          object mEnablePuffBtn: TArrayBotButton
            Left = 179
            Top = 37
            Width = 150
            Height = 80
            Caption = 'Enable Puffer'
            ParentDoubleBuffered = True
            TabOrder = 1
            OnClick = mPuffRelatedBtnClick
            SoundID = 'BUTTON_CLICK_4'
          end
        end
        object mDesiredRibbonLengthE: TIntegerLabeledEdit
          Left = 3
          Top = 42
          Width = 198
          Height = 31
          EditLabel.Width = 192
          EditLabel.Height = 23
          EditLabel.Caption = 'Desired Ribbon Length'
          TabOrder = 2
          Text = '-1'
          OnKeyDown = mDesiredRibbonLengthEKeyDown
          Value = -1
        end
        object GroupBox7: TGroupBox
          Left = 327
          Top = 152
          Width = 346
          Height = 201
          Caption = 'Leica UC7'
          TabOrder = 3
          object Label1: TLabel
            Left = 192
            Top = 27
            Width = 115
            Height = 23
            Caption = 'Cut Thickness'
          end
          object mSetZeroCutBtn: TArrayBotButton
            Left = 16
            Top = 102
            Width = 145
            Height = 80
            Caption = 'Set Zero Cut'
            TabOrder = 0
            OnClick = mSetZeroCutBtnClick
            SoundID = 'short_beep_3'
          end
          object mSetPresetCutBtn: TArrayBotButton
            Left = 190
            Top = 102
            Width = 145
            Height = 80
            Caption = 'Set Preset Cut'
            TabOrder = 1
            OnClick = mSetPresetCutBtnClick
            SoundID = 'short_beep_3'
          end
          object mLeicaCutThicknessLB: TComboBox
            Left = 192
            Top = 56
            Width = 137
            Height = 31
            ItemIndex = 0
            TabOrder = 2
            Text = '0'
            Items.Strings = (
              '0'
              '45'
              '100'
              '500'
              '1000')
          end
        end
        object GroupBox4: TGroupBox
          Left = 679
          Top = 14
          Width = 250
          Height = 339
          Caption = 'Lights'
          TabOrder = 4
          object mCoaxLightBtn: TArrayBotButton
            Left = 24
            Top = 138
            Width = 200
            Height = 79
            Caption = 'Flip Coax Light ON'
            ParentDoubleBuffered = True
            TabOrder = 0
            OnClick = LigthsBtnsClick
            SoundID = 'BUTTON_CLICK_4'
          end
          object mFrontBackLEDBtn: TArrayBotButton
            Left = 24
            Top = 37
            Width = 200
            Height = 80
            Caption = 'Flip LEDs ON'
            ParentDoubleBuffered = True
            TabOrder = 1
            OnClick = LigthsBtnsClick
            SoundID = 'BUTTON_CLICK_4'
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Board Settings'
        ImageIndex = 1
        ExplicitHeight = 351
        object mArduinoSB: TScrollBox
          Left = 0
          Top = 0
          Width = 976
          Height = 380
          Align = alClient
          TabOrder = 0
          ExplicitHeight = 351
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
    Left = 260
    Top = 400
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
    Left = 260
    Top = 464
  end
end
