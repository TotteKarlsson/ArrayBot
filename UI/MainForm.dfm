object Main: TMain
  Left = 0
  Top = 0
  Caption = 'ArrayBot Version 0.5.3'
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
  Position = poDesktopCenter
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
    object Button7: TButton
      Left = 1
      Top = 574
      Width = 125
      Height = 60
      Action = stopAllA
      Align = alBottom
      BiDiMode = bdLeftToRight
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 0
    end
    object Button5: TButton
      Left = 1
      Top = 634
      Width = 125
      Height = 62
      Action = FileExit1
      Align = alBottom
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
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
      TabHeight = 60
      TabOrder = 0
      TabWidth = 100
      object TabSheet4: TTabSheet
        Caption = 'The Bot'
        object GroupBox2: TGroupBox
          Left = 387
          Top = 25
          Width = 366
          Height = 264
          Caption = 'Coverslip Operations'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          object LiftCSBtn: TButton
            Left = 20
            Top = 128
            Width = 133
            Height = 81
            Caption = 'Lift'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = LiftCSBtnClick
          end
          object mCSAngleE: TFloatLabeledEdit
            Left = 74
            Top = 57
            Width = 98
            Height = 31
            EditLabel.Width = 127
            EditLabel.Height = 23
            EditLabel.Caption = 'Coverslip Angle'
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
          Width = 345
          Height = 224
          Caption = 'Joystick'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          object mJSCSBtn: TSpeedButton
            Left = 23
            Top = 32
            Width = 100
            Height = 75
            GroupIndex = 10
            Caption = 'Enable'
            OnClick = JSControlClick
          end
          object mJSNoneBtn: TSpeedButton
            Left = 223
            Top = 32
            Width = 100
            Height = 75
            GroupIndex = 10
            Down = True
            Caption = 'None'
            OnClick = JSControlClick
          end
          object mJSSpeedFastBtn: TSpeedButton
            Left = 23
            Top = 128
            Width = 100
            Height = 75
            GroupIndex = 15
            Caption = 'Fast'
            OnClick = JSSpeedBtnClick
          end
          object mJSSpeedMediumBtn: TSpeedButton
            Left = 123
            Top = 128
            Width = 100
            Height = 75
            GroupIndex = 15
            Down = True
            Caption = 'Medium'
            OnClick = JSSpeedBtnClick
          end
          object mJSSpeedSlowBtn: TSpeedButton
            Left = 223
            Top = 128
            Width = 100
            Height = 75
            GroupIndex = 15
            Caption = 'Slow'
            OnClick = JSSpeedBtnClick
          end
        end
        object GroupBox3: TGroupBox
          Left = 24
          Top = 272
          Width = 223
          Height = 153
          Caption = 'Camera'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          object mCameraAngleEdit: TFloatLabeledEdit
            Left = 23
            Top = 65
            Width = 98
            Height = 31
            EditLabel.Width = 47
            EditLabel.Height = 23
            EditLabel.Caption = 'Angle'
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
        end
      end
      object TabSheet1: TTabSheet
        Caption = 'Motors'
        object ScrollBox1: TScrollBox
          Left = 0
          Top = 0
          Width = 1125
          Height = 625
          VertScrollBar.Position = 370
          Align = alClient
          TabOrder = 0
          inline TXYZUnitFrame1: TXYZUnitFrame
            Left = 0
            Top = -19
            Width = 1104
            Height = 348
            Align = alTop
            TabOrder = 0
            ExplicitTop = -19
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
            Top = -370
            Width = 1104
            Height = 351
            Align = alTop
            TabOrder = 1
            ExplicitTop = -370
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
          inline TMotorFrame1: TMotorFrame
            Left = 0
            Top = 621
            Width = 1104
            Height = 292
            Align = alBottom
            TabOrder = 2
            ExplicitTop = 621
            ExplicitWidth = 1104
          end
          inline TMotorFrame2: TMotorFrame
            Left = 0
            Top = 329
            Width = 1104
            Height = 292
            Align = alBottom
            TabOrder = 3
            ExplicitTop = 329
            ExplicitWidth = 1104
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Settings'
        ImageIndex = 2
        object JoyStickGB2: TGroupBox
          Left = 11
          Top = 16
          Width = 238
          Height = 169
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
            TabOrder = 0
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
            TabOrder = 3
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object JoyStickSettingsCB: TComboBox
            Left = 16
            Top = 24
            Width = 109
            Height = 21
            Style = csDropDownList
            TabOrder = 4
            OnChange = JoyStickSettingsCBChange
          end
          object AddJsSettingBtn: TButton
            Left = 137
            Top = 22
            Width = 21
            Height = 21
            Caption = '+'
            TabOrder = 5
            Visible = False
            OnClick = AddJsSettingBtnClick
          end
        end
        object GroupBox1: TGroupBox
          Left = 255
          Top = 16
          Width = 241
          Height = 169
          Caption = 'Lift Parameters'
          TabOrder = 1
          object mMoveAccelerationE: TFloatLabeledEdit
            Left = 105
            Top = 36
            Width = 73
            Height = 21
            EditLabel.Width = 59
            EditLabel.Height = 13
            EditLabel.Caption = 'Acceleration'
            TabOrder = 0
            Text = '0.00'
          end
          object mMoveVelocityVerticalE: TFloatLabeledEdit
            Left = 9
            Top = 36
            Width = 73
            Height = 21
            EditLabel.Width = 83
            EditLabel.Height = 13
            EditLabel.Caption = 'Velocity (vertical)'
            TabOrder = 1
            Text = '0.00'
            OnKeyDown = moveEdit
          end
          object mMoveVelHorizE: TFloatLabeledEdit
            Left = 9
            Top = 120
            Width = 73
            Height = 21
            EditLabel.Width = 94
            EditLabel.Height = 13
            EditLabel.Caption = 'Horiz distance (mm)'
            Enabled = False
            TabOrder = 2
            Text = '0.00'
          end
          object mVerticalMoveDistanceE: TFloatLabeledEdit
            Left = 9
            Top = 80
            Width = 73
            Height = 21
            EditLabel.Width = 86
            EditLabel.Height = 13
            EditLabel.Caption = 'Lift Distance (mm)'
            TabOrder = 3
            Text = '0.00'
          end
        end
        object Button2: TButton
          Left = 194
          Top = 421
          Width = 177
          Height = 116
          Caption = 'Home All'
          TabOrder = 2
          OnClick = Button3Click
        end
        object Button3: TButton
          Left = 11
          Top = 421
          Width = 177
          Height = 116
          Caption = 'Stow'
          TabOrder = 3
          OnClick = stowBtnClick
        end
        object BitBtn1: TBitBtn
          Left = 544
          Top = 97
          Width = 112
          Height = 60
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
          TabOrder = 4
        end
        object InitCloseBtn: TBitBtn
          Left = 544
          Top = 31
          Width = 112
          Height = 60
          Action = initBotA
          BiDiMode = bdLeftToRight
          Caption = 'Initialize'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 5
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
            Top = 51
            Width = 1123
            Height = 573
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
            Height = 50
            ButtonHeight = 44
            Caption = 'ToolBar1'
            TabOrder = 1
            object BitBtn2: TBitBtn
              Left = 0
              Top = 0
              Width = 75
              Height = 44
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
      Caption = 'Initialize'
      OnExecute = initBotAExecute
    end
    object ShutDownA: TAction
      Caption = 'ShutDown'
      OnExecute = ShutDownAExecute
    end
    object FileExit1: TFileExit
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
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
end
