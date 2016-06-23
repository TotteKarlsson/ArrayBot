object Main: TMain
  Left = 0
  Top = 0
  Caption = 'ArrayBot Version 0.5.8'
  ClientHeight = 697
  ClientWidth = 1262
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
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
  TextHeight = 13
  object Btnpanel: TPanel
    Left = 1135
    Top = 0
    Width = 127
    Height = 697
    Align = alRight
    TabOrder = 0
    object mJSCSBtn: TSpeedButton
      Left = 1
      Top = 126
      Width = 125
      Height = 134
      Align = alTop
      AllowAllUp = True
      Caption = 'Enable JoyStick'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      OnClick = JSControlClick
      ExplicitTop = 251
    end
    object Button7: TSpeedButton
      Left = 1
      Top = 1
      Width = 125
      Height = 125
      Action = stopAllA
      Align = alTop
      BiDiMode = bdLeftToRight
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentBiDiMode = False
      ExplicitTop = 126
    end
    object mAboutBtn: TSpeedButton
      Left = 1
      Top = 260
      Width = 125
      Height = 134
      Align = alTop
      AllowAllUp = True
      Caption = 'About'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      OnClick = mAboutBtnClick
      ExplicitLeft = 25
      ExplicitTop = 382
    end
    object BottomBtnPanel: TPanel
      Left = 1
      Top = 569
      Width = 125
      Height = 127
      Align = alBottom
      AutoSize = True
      TabOrder = 0
      ExplicitTop = 552
      object Button5: TSpeedButton
        Left = 1
        Top = 1
        Width = 123
        Height = 125
        Action = FileExit1
        Align = alBottom
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
    end
  end
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 1135
    Height = 697
    Align = alClient
    Constraints.MinHeight = 348
    Constraints.MinWidth = 670
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 1133
      Height = 695
      ActivePage = TabSheet4
      Align = alClient
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabHeight = 60
      TabOrder = 0
      TabWidth = 100
      object TabSheet4: TTabSheet
        Caption = 'The Bot'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        object AnglesGB: TGroupBox
          Left = 491
          Top = 25
          Width = 366
          Height = 104
          Caption = 'Angles'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          object mCSAngleE: TFloatLabeledEdit
            Left = 18
            Top = 57
            Width = 98
            Height = 31
            EditLabel.Width = 74
            EditLabel.Height = 23
            EditLabel.Caption = 'Coverslip'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -19
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            Text = '0.00'
            OnKeyDown = mCSAngleEKeyDown
          end
          object mCameraAngleEdit: TFloatLabeledEdit
            Left = 151
            Top = 57
            Width = 98
            Height = 31
            EditLabel.Width = 64
            EditLabel.Height = 23
            EditLabel.Caption = 'Camera'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -19
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            Text = '0.00'
            OnKeyDown = mCSAngleEKeyDown
          end
        end
        object JSGB: TGroupBox
          Left = 24
          Top = 25
          Width = 461
          Height = 312
          Caption = 'Joystick'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          object mJSSpeedFastBtn: TSpeedButton
            Left = 307
            Top = 44
            Width = 140
            Height = 100
            GroupIndex = 15
            Caption = 'Fast'
            OnClick = JSSpeedBtnClick
          end
          object mJSSpeedMediumBtn: TSpeedButton
            Left = 161
            Top = 44
            Width = 140
            Height = 100
            GroupIndex = 15
            Down = True
            Caption = 'Medium'
            OnClick = JSSpeedBtnClick
          end
          object mJSSpeedSlowBtn: TSpeedButton
            Left = 15
            Top = 44
            Width = 140
            Height = 100
            GroupIndex = 15
            Caption = 'Slow'
            OnClick = JSSpeedBtnClick
          end
          object mXYCtrlRG: TRadioGroup
            Left = 15
            Top = 184
            Width = 426
            Height = 105
            Caption = 'XY Control'
            Columns = 4
            ItemIndex = 0
            Items.Strings = (
              'X && Y'
              'X'
              'Y'
              'None')
            TabOrder = 0
            OnClick = mXYCtrlRGClick
          end
        end
        object LiftGB: TGroupBox
          Left = 491
          Top = 144
          Width = 446
          Height = 321
          Caption = 'Lift'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          object LiftBtn: TSpeedButton
            Left = 16
            Top = 161
            Width = 409
            Height = 136
            Action = liftA
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
          end
          object mMoveAccelerationE: TFloatLabeledEdit
            Left = 305
            Top = 100
            Width = 73
            Height = 31
            EditLabel.Width = 101
            EditLabel.Height = 23
            EditLabel.Caption = 'Acceleration'
            TabOrder = 1
            Text = '0.00'
            OnKeyDown = moveEdit
          end
          object mMoveVelocityVerticalE: TFloatLabeledEdit
            Left = 202
            Top = 100
            Width = 73
            Height = 31
            EditLabel.Width = 63
            EditLabel.Height = 23
            EditLabel.Caption = 'Velocity'
            TabOrder = 0
            Text = '0.00'
            OnKeyDown = moveEdit
          end
          object mVerticalMoveDistanceE: TFloatLabeledEdit
            Left = 27
            Top = 100
            Width = 86
            Height = 31
            EditLabel.Width = 154
            EditLabel.Height = 23
            EditLabel.Caption = 'Lift Distance (mm)'
            TabOrder = 2
            Text = '0.00'
            OnKeyDown = moveEdit
          end
          object mLiftCB: TComboBox
            Left = 16
            Top = 32
            Width = 409
            Height = 31
            TabOrder = 3
            Text = '<none>'
            OnChange = mLiftCBChange
          end
        end
      end
      object TabSheet1: TTabSheet
        Caption = 'Motors'
        object ScrollBox1: TScrollBox
          Left = 0
          Top = 0
          Width = 1125
          Height = 625
          VertScrollBar.Position = 78
          Align = alClient
          TabOrder = 0
          inline TXYZUnitFrame1: TXYZUnitFrame
            Left = 0
            Top = 273
            Width = 1104
            Height = 348
            Align = alTop
            TabOrder = 0
            ExplicitTop = 273
            ExplicitWidth = 1104
            ExplicitHeight = 348
            inherited mainGB: TGroupBox
              Width = 1104
              Height = 348
              ExplicitWidth = 1104
              ExplicitHeight = 348
              inherited TopPanel: TPanel
                Width = 1100
                ExplicitWidth = 1100
              end
              inherited ScrollBox1: TScrollBox
                Width = 1100
                Height = 305
                ExplicitWidth = 1100
                ExplicitHeight = 305
              end
            end
          end
          inline TXYZUnitFrame2: TXYZUnitFrame
            Left = 0
            Top = -78
            Width = 1104
            Height = 351
            Align = alTop
            TabOrder = 1
            ExplicitTop = -78
            ExplicitWidth = 1104
            inherited mainGB: TGroupBox
              Width = 1104
              ExplicitWidth = 1104
              inherited TopPanel: TPanel
                Width = 1100
                ExplicitWidth = 1100
              end
              inherited ScrollBox1: TScrollBox
                Width = 1100
                ExplicitWidth = 1100
              end
            end
          end
        end
      end
      object mMoveSequencesPage: TTabSheet
        Caption = 'Move Sequences'
        ImageIndex = 4
      end
      object TabSheet2: TTabSheet
        Caption = 'Settings'
        ImageIndex = 2
        object JoyStickGB2: TGroupBox
          Left = 11
          Top = 16
          Width = 238
          Height = 241
          Caption = 'JoyStick Velocities'
          TabOrder = 0
          object mZJogAccelerationJoystick: TFloatLabeledEdit
            Left = 119
            Top = 130
            Width = 66
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'Z Acceleration'
            TabOrder = 3
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object mXYJogAccelerationJoystick: TFloatLabeledEdit
            Left = 119
            Top = 82
            Width = 66
            Height = 21
            EditLabel.Width = 74
            EditLabel.Height = 13
            EditLabel.Caption = 'XY Acceleration'
            TabOrder = 1
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object mMaxZJogVelocityJoystick: TFloatLabeledEdit
            Left = 16
            Top = 130
            Width = 66
            Height = 21
            EditLabel.Width = 69
            EditLabel.Height = 13
            EditLabel.Caption = 'Max Z Velocity'
            TabOrder = 2
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object mMaxXYJogVelocityJoystick: TFloatLabeledEdit
            Left = 16
            Top = 82
            Width = 66
            Height = 21
            EditLabel.Width = 75
            EditLabel.Height = 13
            EditLabel.Caption = 'Max XY Velocity'
            TabOrder = 0
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object JoyStickSettingsCB: TComboBox
            Left = 16
            Top = 24
            Width = 109
            Height = 21
            Style = csDropDownList
            TabOrder = 6
            OnChange = JoyStickSettingsCBChange
          end
          object AddJsSettingBtn: TButton
            Left = 137
            Top = 22
            Width = 21
            Height = 21
            Caption = '+'
            TabOrder = 7
            Visible = False
            OnClick = AddJsSettingBtnClick
          end
          object mAngleControlVelE: TFloatLabeledEdit
            Left = 16
            Top = 178
            Width = 66
            Height = 21
            EditLabel.Width = 91
            EditLabel.Height = 13
            EditLabel.Caption = 'Angle Ctrl. Velocity'
            TabOrder = 4
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object mAngleControllerAccE: TFloatLabeledEdit
            Left = 119
            Top = 178
            Width = 66
            Height = 21
            EditLabel.Width = 71
            EditLabel.Height = 13
            EditLabel.Caption = 'Angle Ctrl Acc.'
            TabOrder = 5
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
        end
        object Button2: TButton
          Left = 194
          Top = 421
          Width = 177
          Height = 116
          Caption = 'Home All'
          TabOrder = 1
          OnClick = Button3Click
        end
        object Button3: TButton
          Left = 11
          Top = 421
          Width = 177
          Height = 116
          Caption = 'Stow'
          TabOrder = 2
          OnClick = stowBtnClick
        end
        object BitBtn1: TBitBtn
          Left = 304
          Top = 32
          Width = 160
          Height = 87
          Action = checkForDevices
          BiDiMode = bdLeftToRight
          Caption = 'Devices Check'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 3
        end
        object InitCloseBtn: TBitBtn
          Left = 488
          Top = 32
          Width = 160
          Height = 88
          Action = initBotA
          BiDiMode = bdLeftToRight
          Caption = 'Initialize Devices'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 4
        end
        object Button1: TButton
          Left = 11
          Top = 270
          Width = 118
          Height = 83
          Caption = 'Save Parameters'
          TabOrder = 5
          OnClick = Button1Click
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'Logging'
        ImageIndex = 4
        object BottomPanel: TPanel
          Left = 0
          Top = 0
          Width = 1125
          Height = 625
          Align = alClient
          TabOrder = 0
          object infoMemo: TMemo
            Left = 1
            Top = 31
            Width = 1123
            Height = 593
            Align = alClient
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ScrollBars = ssVertical
            TabOrder = 0
            WordWrap = False
          end
          object ToolBar1: TToolBar
            Left = 1
            Top = 1
            Width = 1123
            Height = 30
            AutoSize = True
            ButtonHeight = 30
            Caption = 'ToolBar1'
            TabOrder = 1
            object BitBtn2: TBitBtn
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
    end
  end
  object ActionList1: TActionList
    Left = 304
    Top = 648
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
    object initBotA: TAction
      Caption = 'Initialize Devices'
      OnExecute = initBotAExecute
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
    Left = 32
    Top = 648
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 200
    Top = 648
  end
  object UIUpdateTimer: TTimer
    Enabled = False
    Interval = 150
    OnTimer = UIUpdateTimerTimer
    Left = 392
    Top = 648
  end
  object mLiftTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = mLiftTimerTimer
    Left = 544
    Top = 648
  end
  object WaitForDeviceInitTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = WaitForDeviceInitTimerTimer
    Left = 640
    Top = 648
  end
end
