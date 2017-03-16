object Main: TMain
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'ArrayBot Version 0.5.8'
  ClientHeight = 900
  ClientWidth = 1103
  Color = clBtnFace
  Constraints.MinHeight = 900
  Constraints.MinWidth = 1100
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
  object mRightPanel: TPanel
    Left = 920
    Top = 0
    Width = 183
    Height = 900
    Align = alRight
    TabOrder = 0
    OnDblClick = mRightPanelDblClick
    object mJSCSBtn: TSpeedButton
      Left = 1
      Top = 1
      Width = 181
      Height = 138
      Align = alTop
      AllowAllUp = True
      Caption = 'Enable JS'
      OnClick = JSControlClick
      ExplicitLeft = 6
      ExplicitTop = 347
    end
    object mJSStatusL: TLabel
      Left = 1
      Top = 225
      Width = 181
      Height = 23
      Align = alTop
      Caption = 'mJSStatusL'
      WordWrap = True
      ExplicitWidth = 96
    end
    object BottomBtnPanel: TPanel
      Left = 1
      Top = 647
      Width = 181
      Height = 252
      Align = alBottom
      AutoSize = True
      TabOrder = 0
      object Button5: TArrayBotButton
        Left = 1
        Top = 126
        Width = 179
        Height = 125
        Action = FileExit1
        Align = alBottom
        Caption = 'E&xit'
        TabOrder = 0
        SoundID = 'BUTTON_CLICK_4'
      end
      object Button7: TArrayBotButton
        Left = 1
        Top = 1
        Width = 179
        Height = 125
        Action = stopAllA
        Align = alBottom
        BiDiMode = bdLeftToRight
        Caption = 'Stop All'
        ParentBiDiMode = False
        TabOrder = 1
        SoundID = 'BUTTON_CLICK_4'
      end
    end
    object mJoyStickRG: TRadioGroup
      Left = 1
      Top = 139
      Width = 181
      Height = 86
      Align = alTop
      Caption = 'JoyStick'
      ItemIndex = 0
      Items.Strings = (
        'Blue'
        'White')
      TabOrder = 1
      OnClick = mJoyStickRGClick
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 920
    Height = 900
    ActivePage = mFrontPage
    Align = alClient
    TabHeight = 60
    TabOrder = 1
    TabWidth = 150
    OnChange = PageControl1Change
    object mFrontPage: TTabSheet
      Caption = 'The Bot'
      object mMiddlePanel: TPanel
        Left = 0
        Top = 97
        Width = 912
        Height = 588
        Align = alClient
        AutoSize = True
        TabOrder = 0
        object mRibbonCreationGB: TGroupBox
          Left = 1
          Top = 1
          Width = 910
          Height = 586
          Align = alClient
          Caption = 'Ribbon Creation'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          object mLiftGB: TGroupBox
            Left = 537
            Top = 43
            Width = 304
            Height = 288
            Caption = 'Simple Lift'
            TabOrder = 0
            object LiftBtn: TArrayBotButton
              Left = 18
              Top = 129
              Width = 264
              Height = 136
              Action = liftA
              Caption = 'Lift'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 3
              SoundID = 'BUTTON_CLICK_4'
            end
            object mLiftCB: TComboBox
              Left = 15
              Top = 32
              Width = 267
              Height = 31
              TabOrder = 0
              Text = '<none>'
              OnChange = mLiftCBChange
            end
            object mMoveAccelerationE: TFloatLabeledEdit
              Left = 178
              Top = 92
              Width = 104
              Height = 31
              EditLabel.Width = 101
              EditLabel.Height = 23
              EditLabel.Caption = 'Acceleration'
              TabOrder = 2
              Text = '0.00'
            end
            object mMoveVelocityVerticalE: TFloatLabeledEdit
              Left = 18
              Top = 92
              Width = 73
              Height = 31
              EditLabel.Width = 63
              EditLabel.Height = 23
              EditLabel.Caption = 'Velocity'
              TabOrder = 1
              Text = '0.00'
            end
          end
          object GroupBox3: TGroupBox
            Left = 26
            Top = 43
            Width = 471
            Height = 512
            Caption = 'Wiggler'
            TabOrder = 1
            object Label1: TLabel
              Left = 72
              Top = 165
              Width = 158
              Height = 23
              Caption = 'Pull Distance (mm)'
            end
            object mWigglerAmplitudeE: TFloatLabeledEdit
              Left = 24
              Top = 307
              Width = 105
              Height = 31
              EditLabel.Width = 84
              EditLabel.Height = 23
              EditLabel.Caption = 'Amplitude'
              TabOrder = 0
              Text = '1.00'
              Value = 1.000000000000000000
            end
            object mWigglerAccelerationE: TFloatLabeledEdit
              Left = 151
              Top = 239
              Width = 105
              Height = 31
              EditLabel.Width = 101
              EditLabel.Height = 23
              EditLabel.Caption = 'Acceleration'
              TabOrder = 1
              Text = '5.00'
              Value = 5.000000000000000000
            end
            object mWiggleBtn: TArrayBotButton
              Left = 171
              Top = 320
              Width = 278
              Height = 171
              Caption = 'Wiggle'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 2
              OnClick = mWiggleBtnClick
              SoundID = 'BUTTON_CLICK_4'
            end
            object mWigglerVelocityE: TFloatLabeledEdit
              Left = 24
              Top = 239
              Width = 105
              Height = 31
              EditLabel.Width = 63
              EditLabel.Height = 23
              EditLabel.Caption = 'Velocity'
              TabOrder = 3
              Text = '3.00'
              Value = 3.000000000000000000
            end
            object mWiggleSpinButton: TCSpinButton
              Left = 24
              Top = 354
              Width = 105
              Height = 137
              Margins.Left = 0
              Margins.Top = 0
              Margins.Right = 0
              Margins.Bottom = 0
              DownGlyph.Data = {
                0E010000424D0E01000000000000360000002800000009000000060000000100
                200000000000D800000000000000000000000000000000000000008080000080
                8000008080000080800000808000008080000080800000808000008080000080
                8000008080000080800000808000000000000080800000808000008080000080
                8000008080000080800000808000000000000000000000000000008080000080
                8000008080000080800000808000000000000000000000000000000000000000
                0000008080000080800000808000000000000000000000000000000000000000
                0000000000000000000000808000008080000080800000808000008080000080
                800000808000008080000080800000808000}
              TabOrder = 4
              UpGlyph.Data = {
                0E010000424D0E01000000000000360000002800000009000000060000000100
                200000000000D800000000000000000000000000000000000000008080000080
                8000008080000080800000808000008080000080800000808000008080000080
                8000000000000000000000000000000000000000000000000000000000000080
                8000008080000080800000000000000000000000000000000000000000000080
                8000008080000080800000808000008080000000000000000000000000000080
                8000008080000080800000808000008080000080800000808000000000000080
                8000008080000080800000808000008080000080800000808000008080000080
                800000808000008080000080800000808000}
              OnDownClick = mWiggleSpinButtonDownClick
              OnUpClick = mWiggleSpinButtonUpClick
            end
            object mPullRibbonBtn: TArrayBotButton
              Left = 240
              Top = 42
              Width = 209
              Height = 112
              Caption = 'Pull'
              TabOrder = 5
              OnClick = mPullRibbonBtnClick
              SoundID = 'SHORT_BEEP_1'
            end
            object mPullCB: TComboBox
              Left = 304
              Top = 165
              Width = 145
              Height = 33
              Style = csDropDownList
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -21
              Font.Name = 'Tahoma'
              Font.Style = []
              ItemIndex = 3
              ParentFont = False
              TabOrder = 6
              Text = '0.5'
              Items.Strings = (
                '0.01'
                '0.05'
                '0.1'
                '0.5'
                '1'
                '1.5'
                '2')
            end
            object mRelaxBtn: TArrayBotButton
              Left = 24
              Top = 42
              Width = 153
              Height = 73
              Caption = 'Relax'
              TabOrder = 7
              OnClick = mPullRibbonBtnClick
              SoundID = 'SHORT_BEEP_1'
            end
          end
        end
      end
      object mSequencesPanel: TPanel
        Left = 0
        Top = 685
        Width = 912
        Height = 145
        Align = alBottom
        AutoSize = True
        TabOrder = 1
        OnResize = mSequencesPanelResize
      end
      object TopPanel: TPanel
        Left = 0
        Top = 0
        Width = 912
        Height = 97
        Align = alTop
        TabOrder = 2
        object mUnitControlRG: TRadioGroup
          Left = 462
          Top = 1
          Width = 240
          Height = 95
          Align = alLeft
          Caption = 'Unit Control'
          Columns = 2
          DoubleBuffered = False
          ItemIndex = 0
          Items.Strings = (
            'Both'
            'Coverslip'
            'Whisker'
            'None')
          ParentDoubleBuffered = False
          TabOrder = 0
          OnClick = mUnitControlRGClick
        end
        object mXYCtrlRG: TRadioGroup
          Left = 702
          Top = 1
          Width = 224
          Height = 95
          Align = alLeft
          Caption = 'XY Control'
          Columns = 2
          ItemIndex = 0
          Items.Strings = (
            'X && Y'
            'X'
            'Y'
            'None')
          TabOrder = 1
          OnClick = mXYCtrlRGClick
        end
        object JSGB: TGroupBox
          Left = 1
          Top = 1
          Width = 461
          Height = 95
          Align = alLeft
          Caption = 'Motor Speed'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          object Panel2: TPanel
            Left = 2
            Top = 27
            Width = 457
            Height = 50
            Align = alTop
            TabOrder = 0
            object mJSSpeedFastBtn: TSpeedButton
              Left = 301
              Top = 1
              Width = 150
              Height = 48
              Align = alLeft
              GroupIndex = 15
              Caption = 'Fast'
              OnClick = JSSpeedBtnClick
              ExplicitHeight = 50
            end
            object mJSSpeedMediumBtn: TSpeedButton
              Left = 151
              Top = 1
              Width = 150
              Height = 48
              Align = alLeft
              GroupIndex = 15
              Down = True
              Caption = 'Medium'
              OnClick = JSSpeedBtnClick
              ExplicitHeight = 50
            end
            object mJSSpeedSlowBtn: TSpeedButton
              Left = 1
              Top = 1
              Width = 150
              Height = 48
              Align = alLeft
              GroupIndex = 15
              Caption = 'Slow'
              OnClick = JSSpeedBtnClick
              ExplicitHeight = 50
            end
          end
        end
      end
    end
    object RibbonLifterTabSheet: TTabSheet
      Caption = 'The Pickup'
      ImageIndex = 5
      TabVisible = False
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
    end
    object mMoveSequencesPage: TTabSheet
      Caption = 'Sequences'
      ImageIndex = 4
    end
    object TabSheet1: TTabSheet
      Caption = 'Motors'
      object ScrollBox1: TScrollBox
        Left = 0
        Top = 0
        Width = 912
        Height = 725
        HorzScrollBar.Smooth = True
        VertScrollBar.Tracking = True
        Align = alClient
        BorderStyle = bsNone
        Padding.Left = 5
        Padding.Top = 5
        Padding.Right = 5
        Padding.Bottom = 5
        TabOrder = 0
      end
      object Panel1: TPanel
        Left = 0
        Top = 725
        Width = 912
        Height = 105
        Align = alBottom
        TabOrder = 1
        object mCheckDevicesBtn: TBitBtn
          Left = 178
          Top = 1
          Width = 176
          Height = 103
          Action = checkForDevices
          Align = alLeft
          BiDiMode = bdLeftToRight
          Caption = 'Devices Check'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 0
        end
        object ReInitBotBtn: TBitBtn
          Left = 1
          Top = 1
          Width = 177
          Height = 103
          Action = reInitBotA
          Align = alLeft
          BiDiMode = bdLeftToRight
          Caption = 'Reinitialize Devices'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 1
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Settings'
      ImageIndex = 2
      object JoyStickGB2: TGroupBox
        Left = 43
        Top = 416
        Width = 422
        Height = 345
        Caption = 'JoyStick Velocities'
        TabOrder = 0
        object mZJogAccelerationJoystick: TFloatLabeledEdit
          Left = 247
          Top = 198
          Width = 66
          Height = 31
          EditLabel.Width = 118
          EditLabel.Height = 23
          EditLabel.Caption = 'Z Acceleration'
          TabOrder = 3
          Text = '0.00'
          OnKeyDown = JoyStickValueEdit
        end
        object mXYJogAccelerationJoystick: TFloatLabeledEdit
          Left = 247
          Top = 108
          Width = 66
          Height = 31
          EditLabel.Width = 129
          EditLabel.Height = 23
          EditLabel.Caption = 'XY Acceleration'
          TabOrder = 1
          Text = '0.00'
          OnKeyDown = JoyStickValueEdit
        end
        object mMaxZJogVelocityJoystick: TFloatLabeledEdit
          Left = 16
          Top = 198
          Width = 66
          Height = 31
          EditLabel.Width = 120
          EditLabel.Height = 23
          EditLabel.Caption = 'Max Z Velocity'
          TabOrder = 2
          Text = '0.00'
          OnKeyDown = JoyStickValueEdit
        end
        object mMaxXYJogVelocityJoystick: TFloatLabeledEdit
          Left = 16
          Top = 108
          Width = 66
          Height = 31
          EditLabel.Width = 131
          EditLabel.Height = 23
          EditLabel.Caption = 'Max XY Velocity'
          TabOrder = 0
          Text = '0.00'
          OnKeyDown = JoyStickValueEdit
        end
        object JoyStickSettingsCB: TComboBox
          Left = 16
          Top = 24
          Width = 291
          Height = 31
          Style = csDropDownList
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
          OnChange = JoyStickSettingsCBChange
        end
        object AddJsSettingBtn: TButton
          Left = 313
          Top = 23
          Width = 32
          Height = 33
          Caption = '+'
          TabOrder = 7
          Visible = False
          OnClick = AddJsSettingBtnClick
        end
        object mAngleControlVelE: TFloatLabeledEdit
          Left = 16
          Top = 286
          Width = 66
          Height = 31
          EditLabel.Width = 156
          EditLabel.Height = 23
          EditLabel.Caption = 'Angle Ctrl. Velocity'
          TabOrder = 4
          Text = '0.00'
          OnKeyDown = JoyStickValueEdit
        end
        object mAngleControllerAccE: TFloatLabeledEdit
          Left = 247
          Top = 286
          Width = 66
          Height = 31
          EditLabel.Width = 122
          EditLabel.Height = 23
          EditLabel.Caption = 'Angle Ctrl Acc.'
          TabOrder = 5
          Text = '0.00'
          OnKeyDown = JoyStickValueEdit
        end
      end
      object GroupBox1: TGroupBox
        Left = 466
        Top = 27
        Width = 257
        Height = 155
        Caption = 'Arduino Client'
        TabOrder = 1
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
          Left = 143
          Top = 40
          Width = 104
          Height = 97
          Caption = 'Start'
          TabOrder = 1
          OnClick = mASStartBtnClick
        end
      end
      object GroupBox2: TGroupBox
        Left = 466
        Top = 208
        Width = 383
        Height = 329
        Caption = 'Wiggler'
        TabOrder = 2
        object mWigglerAmplitudeStepE: TFloatLabeledEdit
          Left = 32
          Top = 64
          Width = 129
          Height = 31
          EditLabel.Width = 128
          EditLabel.Height = 23
          EditLabel.Caption = 'Amplitude Step'
          TabOrder = 0
          Text = '0.50'
          Value = 0.500000000000000000
        end
        object GroupBox4: TGroupBox
          Left = 29
          Top = 120
          Width = 249
          Height = 153
          Caption = 'Pull/Relax Parameterss'
          TabOrder = 1
          object mPullRelaxAccE: TFloatLabeledEdit
            Left = 133
            Top = 82
            Width = 105
            Height = 31
            EditLabel.Width = 101
            EditLabel.Height = 23
            EditLabel.Caption = 'Acceleration'
            TabOrder = 0
            Text = '5.00'
            Value = 5.000000000000000000
          end
          object mPullRelaxVelocityE: TFloatLabeledEdit
            Left = 16
            Top = 82
            Width = 105
            Height = 31
            EditLabel.Width = 63
            EditLabel.Height = 23
            EditLabel.Caption = 'Velocity'
            TabOrder = 1
            Text = '3.00'
            Value = 3.000000000000000000
          end
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Logging'
      ImageIndex = 4
      object BottomPanel: TPanel
        Left = 0
        Top = 0
        Width = 912
        Height = 830
        Align = alClient
        TabOrder = 0
        object infoMemo: TMemo
          Left = 1
          Top = 31
          Width = 910
          Height = 798
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
          Width = 910
          Height = 30
          AutoSize = True
          ButtonHeight = 30
          Caption = 'ToolBar1'
          TabOrder = 1
          object mClearLogWindowBtn: TBitBtn
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
            OnClick = BitBtn3Click
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
    object TabSheet3: TTabSheet
      Caption = 'About'
      ImageIndex = 6
      inline TAboutArrayBotFrame_21: TAboutArrayBotFrame_2
        Left = 0
        Top = 0
        Width = 912
        Height = 830
        Align = alClient
        TabOrder = 0
        ExplicitWidth = 912
        ExplicitHeight = 830
        inherited GroupBox1: TGroupBox
          Width = 912
          Height = 644
          ExplicitWidth = 912
          ExplicitHeight = 644
          inherited Memo1: TMemo
            Top = 25
            Width = 908
            Height = 617
            ExplicitTop = 25
            ExplicitWidth = 908
            ExplicitHeight = 617
          end
        end
        inherited Panel1: TPanel
          Width = 912
          ExplicitWidth = 912
          inherited Image1: TImage
            Left = 726
            ExplicitLeft = 708
          end
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 764
    Top = 792
    object checkForDevices: TAction
      Caption = 'Devices Check'
      OnExecute = checkForDevicesExecute
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
      OnExecute = stopAllAExecute
    end
    object reInitBotA: TAction
      Caption = 'Reinitialize Devices'
      OnExecute = reInitBotAExecute
    end
    object ShutDownA: TAction
      Caption = 'Disconnect Devices'
      OnExecute = ShutDownAExecute
    end
    object FileExit1: TFileExit
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
    object abortLiftA: TAction
      Caption = 'Abort Lift'
      OnExecute = abortLiftAExecute
    end
    object liftA: TAction
      Caption = 'Lift'
      OnExecute = liftAExecute
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = ShutDownTimerTimer
    Left = 764
    Top = 616
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 664
    Top = 784
  end
  object UIUpdateTimer: TTimer
    Enabled = False
    Interval = 250
    OnTimer = UIUpdateTimerTimer
    Left = 636
    Top = 560
  end
  object mLiftTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = mLiftTimerTimer
    Left = 760
    Top = 680
  end
  object WaitForDeviceInitTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = WaitForDeviceInitTimerTimer
    Left = 760
    Top = 552
  end
end
