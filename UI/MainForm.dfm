object Main: TMain
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'ArrayBot Version 0.1'
  ClientHeight = 852
  ClientWidth = 1278
  Color = clBtnFace
  Constraints.MaxHeight = 852
  Constraints.MaxWidth = 1278
  Constraints.MinHeight = 852
  Constraints.MinWidth = 1278
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
    Left = 1151
    Top = 0
    Width = 127
    Height = 852
    Align = alRight
    TabOrder = 0
    ExplicitLeft = 1145
    ExplicitHeight = 821
    object Button7: TButton
      Left = 1
      Top = 729
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
      ExplicitTop = 698
    end
    object Button5: TButton
      Left = 1
      Top = 789
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
      ExplicitTop = 758
    end
  end
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 1151
    Height = 852
    Align = alClient
    Constraints.MinHeight = 348
    Constraints.MinWidth = 670
    TabOrder = 1
    ExplicitWidth = 1145
    ExplicitHeight = 821
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 1149
      Height = 850
      ActivePage = TabSheet4
      Align = alClient
      TabHeight = 60
      TabOrder = 0
      TabWidth = 100
      ExplicitWidth = 1143
      ExplicitHeight = 819
      object TabSheet4: TTabSheet
        Caption = 'The Bot'
        ExplicitHeight = 777
        DesignSize = (
          1141
          780)
        object GroupBox2: TGroupBox
          Left = 19
          Top = 17
          Width = 366
          Height = 312
          Caption = 'Coverslip Operations'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          object LiftCSBtn: TButton
            Left = 212
            Top = 136
            Width = 127
            Height = 50
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
          object mMoveAngleE: TFloatLabeledEdit
            Left = 74
            Top = 172
            Width = 98
            Height = 31
            EditLabel.Width = 77
            EditLabel.Height = 23
            EditLabel.Caption = 'Lift angle'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            Text = '0.00'
            OnKeyDown = moveEdit
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
            TabOrder = 2
            Text = '0.00'
            OnKeyDown = mCSAngleEKeyDown
          end
          object InsertCSBtn: TButton
            Left = 212
            Top = 192
            Width = 127
            Height = 50
            Caption = 'Insert'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 3
            OnClick = LiftCSBtnClick
          end
        end
        object Button1: TButton
          Left = 843
          Top = 662
          Width = 284
          Height = 104
          Action = stopAllA
          Anchors = [akRight, akBottom]
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -43
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          ExplicitTop = 659
        end
        object JSGB: TGroupBox
          Left = 760
          Top = 17
          Width = 345
          Height = 224
          Caption = 'Joystick'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          object mJSCSBtn: TSpeedButton
            Left = 23
            Top = 32
            Width = 100
            Height = 75
            GroupIndex = 10
            Caption = 'Coverslip'
            OnClick = JSControlClick
          end
          object mJSWhiskerBtn: TSpeedButton
            Left = 123
            Top = 32
            Width = 100
            Height = 75
            GroupIndex = 10
            Caption = 'Whisker'
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
      end
      object TabSheet1: TTabSheet
        Caption = 'XYZ Units'
        ExplicitHeight = 777
        object ScrollBox1: TScrollBox
          Left = 0
          Top = 0
          Width = 1141
          Height = 780
          Align = alClient
          TabOrder = 0
          ExplicitHeight = 777
          inline TXYZUnitFrame1: TXYZUnitFrame
            Left = 0
            Top = 351
            Width = 1137
            Height = 348
            Align = alTop
            TabOrder = 0
            ExplicitTop = 351
            ExplicitWidth = 1137
            ExplicitHeight = 348
            inherited mainGB: TGroupBox
              Width = 1137
              Height = 348
              ExplicitWidth = 1137
              ExplicitHeight = 348
              inherited TopPanel: TPanel
                Width = 1133
                ExplicitWidth = 1133
              end
              inherited ScrollBox1: TScrollBox
                Width = 1133
                Height = 305
                ExplicitWidth = 1133
                ExplicitHeight = 305
              end
            end
          end
          inline TXYZUnitFrame2: TXYZUnitFrame
            Left = 0
            Top = 0
            Width = 1137
            Height = 351
            Align = alTop
            TabOrder = 1
            ExplicitWidth = 1137
            inherited mainGB: TGroupBox
              Width = 1137
              ExplicitWidth = 1137
              ExplicitHeight = 351
              inherited TopPanel: TPanel
                Width = 1133
                ExplicitWidth = 1133
              end
              inherited ScrollBox1: TScrollBox
                Width = 1133
                ExplicitWidth = 1133
                ExplicitHeight = 308
              end
            end
          end
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'CS Angle Motor'
        ImageIndex = 3
        ExplicitHeight = 777
        inline TMotorFrame1: TMotorFrame
          Left = 0
          Top = 0
          Width = 293
          Height = 292
          TabOrder = 0
          inherited MotorGB: TGroupBox
            Width = 293
            Height = 292
            Align = alClient
            Constraints.MaxHeight = 292
            Constraints.MaxWidth = 293
            ExplicitWidth = 293
            ExplicitHeight = 292
            inherited JoggingGB: TGroupBox [4]
              Top = 116
              Width = 289
              ExplicitTop = 116
              ExplicitWidth = 289
            end
            inherited mMotorPositionE: TFloatLabeledEdit
              Left = 173
              EditLabel.ExplicitLeft = 173
              EditLabel.ExplicitTop = 13
              EditLabel.ExplicitWidth = 64
              ExplicitLeft = 173
            end
            inherited StatusGB: TGroupBox [6]
              Top = 208
              Width = 289
              ExplicitTop = 208
              ExplicitWidth = 289
            end
            inherited Button1: TButton [7]
            end
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Settings'
        ImageIndex = 2
        ExplicitHeight = 777
        object JoyStickGB2: TGroupBox
          Left = 11
          Top = 16
          Width = 238
          Height = 169
          Caption = 'JoyStick Velocities'
          TabOrder = 0
          object mZJogAccelerationJoystick: TFloatLabeledEdit
            Left = 119
            Top = 117
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
            Left = 16
            Top = 117
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
            Left = 119
            Top = 66
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
            Top = 66
            Width = 66
            Height = 21
            EditLabel.Width = 75
            EditLabel.Height = 13
            EditLabel.Caption = 'Max XY Velocity'
            TabOrder = 3
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object ComboBox1: TComboBox
            Left = 16
            Top = 24
            Width = 109
            Height = 21
            TabOrder = 4
            Text = 'ComboBox1'
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
          Top = 205
          Width = 177
          Height = 116
          Caption = 'Home All'
          TabOrder = 2
          OnClick = Button3Click
        end
        object Button3: TButton
          Left = 11
          Top = 205
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
        ExplicitHeight = 777
        object BottomPanel: TPanel
          Left = 0
          Top = 0
          Width = 1141
          Height = 780
          Align = alClient
          TabOrder = 0
          ExplicitHeight = 777
          object infoMemo: TMemo
            Left = 1
            Top = 51
            Width = 1139
            Height = 728
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
            ExplicitHeight = 725
          end
          object ToolBar1: TToolBar
            Left = 1
            Top = 1
            Width = 1139
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
    Top = 488
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
    Top = 488
  end
  object StatusTimer: TTimer
    Enabled = False
    Interval = 500
    Left = 120
    Top = 488
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 200
    Top = 488
  end
end
