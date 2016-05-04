object Main: TMain
  Left = 0
  Top = 0
  ActiveControl = JoySteps
  Caption = 'Device Tester'
  ClientHeight = 702
  ClientWidth = 952
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 120
    Top = 221
    Width = 18
    Height = 13
    Caption = 'N/A'
  end
  object Label6: TLabel
    Left = 120
    Top = 202
    Width = 18
    Height = 13
    Caption = 'N/A'
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 952
    Height = 36
    ButtonHeight = 30
    ButtonWidth = 13
    Caption = 'ToolBar1'
    List = True
    AllowTextButtons = True
    TabOrder = 0
    ExplicitWidth = 927
    object BitBtn1: TBitBtn
      Left = 0
      Top = 0
      Width = 96
      Height = 30
      Action = connectAllDevices
      Caption = 'Connect All'
      TabOrder = 0
    end
    object BitBtn2: TBitBtn
      Left = 96
      Top = 0
      Width = 105
      Height = 30
      Action = checkForDevices
      Caption = 'Devices Check'
      TabOrder = 1
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 504
    Width = 952
    Height = 198
    Align = alBottom
    Caption = 'Panel1'
    TabOrder = 1
    object infoMemo: TMemo
      Left = 1
      Top = 34
      Width = 950
      Height = 163
      Align = alClient
      ScrollBars = ssVertical
      TabOrder = 0
      WordWrap = False
      ExplicitWidth = 925
      ExplicitHeight = 143
    end
    object ToolBar2: TToolBar
      Left = 1
      Top = 1
      Width = 950
      Height = 33
      AutoSize = True
      ButtonHeight = 33
      Caption = 'ToolBar2'
      TabOrder = 1
      ExplicitWidth = 925
      object BitBtn3: TBitBtn
        Left = 0
        Top = 0
        Width = 75
        Height = 33
        Caption = 'Clear'
        TabOrder = 0
        OnClick = BitBtn3Click
      end
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 36
    Width = 952
    Height = 468
    Align = alClient
    TabOrder = 2
    ExplicitWidth = 927
    ExplicitHeight = 397
    object DevicesGB: TGroupBox
      Left = 1
      Top = 1
      Width = 153
      Height = 466
      Align = alLeft
      Caption = 'Devices'
      TabOrder = 0
      ExplicitHeight = 395
      object devicesLB: TListBox
        Left = 2
        Top = 15
        Width = 149
        Height = 449
        Align = alClient
        ItemHeight = 13
        TabOrder = 0
        OnClick = devicesLBClick
      end
    end
    object DeviceGB: TGroupBox
      Left = 154
      Top = 1
      Width = 343
      Height = 466
      Align = alLeft
      Caption = 'Device'
      TabOrder = 1
      object Button1: TButton
        Left = 6
        Top = 345
        Width = 75
        Height = 28
        Action = identifyCurrent
        TabOrder = 0
      end
      object Button7: TButton
        Left = 17
        Top = 295
        Width = 74
        Height = 43
        Action = stopMotor
        TabOrder = 1
      end
      object JoggingGB: TGroupBox
        Left = 2
        Top = 131
        Width = 339
        Height = 112
        Align = alTop
        Caption = 'Jogging'
        TabOrder = 2
        ExplicitTop = 97
        ExplicitWidth = 451
        object Button3: TButton
          Left = 16
          Top = 23
          Width = 50
          Height = 25
          Action = jogForward
          TabOrder = 0
          OnMouseDown = DeviceBtnDown
        end
        object Button4: TButton
          Left = 72
          Top = 23
          Width = 50
          Height = 25
          Action = jogBackwards
          TabOrder = 1
          OnMouseDown = DeviceBtnDown
        end
        object mJogModeCB: TCheckBox
          Left = 184
          Top = 27
          Width = 78
          Height = 17
          Caption = 'Continous'
          TabOrder = 2
          OnClick = mJogModeCBClick
        end
        object mJogAcc: mtkFloatLabeledEdit
          Left = 97
          Top = 81
          Width = 66
          Height = 21
          EditLabel.Width = 59
          EditLabel.Height = 13
          EditLabel.Caption = 'Acceleration'
          TabOrder = 3
          Text = '0.00'
          OnKeyDown = mDeviceValueEdit
        end
        object mJogVelocity: mtkFloatLabeledEdit
          Left = 21
          Top = 81
          Width = 66
          Height = 21
          EditLabel.Width = 37
          EditLabel.Height = 13
          EditLabel.Caption = 'Velocity'
          TabOrder = 4
          Text = '0.00'
          OnKeyDown = mDeviceValueEdit
        end
        object Button8: TButton
          Left = 128
          Top = 23
          Width = 41
          Height = 25
          Action = stopMotor
          TabOrder = 5
          OnMouseDown = DeviceBtnDown
        end
      end
      object GroupBox4: TGroupBox
        Left = 2
        Top = 49
        Width = 339
        Height = 82
        Align = alTop
        Caption = 'Status'
        TabOrder = 3
        ExplicitLeft = 3
        ExplicitTop = 9
        ExplicitWidth = 563
        object Label1: TLabel
          Left = 17
          Top = 23
          Width = 49
          Height = 13
          Caption = 'Is Active: '
        end
        object Label2: TLabel
          Left = 144
          Top = 23
          Width = 51
          Height = 13
          Caption = 'Is Homing:'
        end
        object Label3: TLabel
          Left = 17
          Top = 36
          Width = 52
          Height = 13
          Caption = 'Is Homed: '
        end
        object Label5: TLabel
          Left = 17
          Top = 49
          Width = 77
          Height = 13
          Caption = 'Velocity (mm/s):'
        end
        object Lbl: TLabel
          Left = 144
          Top = 36
          Width = 70
          Height = 13
          Caption = 'Is Forwarding:'
        end
        object Lbl2: TLabel
          Left = 144
          Top = 49
          Width = 64
          Height = 13
          Caption = 'Is Reversing:'
        end
        object mIsActiveLabel: TLabel
          Left = 107
          Top = 23
          Width = 18
          Height = 13
          Caption = 'N/A'
        end
        object mIsForwardingLabel: TLabel
          Left = 220
          Top = 36
          Width = 18
          Height = 13
          Caption = 'N/A'
        end
        object mIsHomedLabel: TLabel
          Left = 107
          Top = 36
          Width = 18
          Height = 13
          Caption = 'N/A'
        end
        object mIsHomingLabel: TLabel
          Left = 220
          Top = 23
          Width = 18
          Height = 13
          Caption = 'N/A'
        end
        object mIsReversingLabel: TLabel
          Left = 220
          Top = 49
          Width = 18
          Height = 13
          Caption = 'N/A'
        end
        object mVelocityLbl: TLabel
          Left = 107
          Top = 49
          Width = 19
          Height = 13
          Caption = '0.0 '
        end
      end
      object MovingGB: TGroupBox
        Left = 2
        Top = 243
        Width = 339
        Height = 130
        Align = alTop
        Caption = 'Moving'
        TabOrder = 4
        ExplicitLeft = 17
        ExplicitTop = 169
        ExplicitWidth = 330
        object ContinousMoveCB: TCheckBox
          Left = 169
          Top = 54
          Width = 78
          Height = 17
          Caption = 'Continous'
          TabOrder = 0
        end
        object IncreaseVelBtn: TButton
          Left = 17
          Top = 55
          Width = 49
          Height = 25
          Caption = '+'
          TabOrder = 1
          OnClick = IncreaseVelBtnClick
        end
        object mAcceleration: mtkFloatLabeledEdit
          Left = 231
          Top = 27
          Width = 50
          Height = 21
          EditLabel.Width = 59
          EditLabel.Height = 13
          EditLabel.Caption = 'Acceleration'
          TabOrder = 2
          Text = '0.00'
          OnKeyDown = mDeviceValueEdit
        end
        object mMaxVelocity: mtkFloatLabeledEdit
          Left = 169
          Top = 27
          Width = 56
          Height = 21
          EditLabel.Width = 37
          EditLabel.Height = 13
          EditLabel.Caption = 'Velocity'
          TabOrder = 3
          Text = '0.00'
          OnKeyDown = mDeviceValueEdit
        end
        object mVelDeltaE: mtkFloatLabeledEdit
          Left = 169
          Top = 90
          Width = 76
          Height = 21
          EditLabel.Width = 84
          EditLabel.Height = 13
          EditLabel.Caption = 'Vel Increase Step'
          TabOrder = 4
          Text = '0.00'
        end
        object switchdirectionBtn: TButton
          Left = 17
          Top = 86
          Width = 89
          Height = 25
          Caption = 'Switch Direction'
          TabOrder = 5
          OnClick = switchdirectionBtnClick
        end
        object DecreaseVelBtn: TButton
          Left = 72
          Top = 55
          Width = 50
          Height = 25
          Caption = '-'
          TabOrder = 6
          OnClick = DecreaseVelBtnClick
        end
        object fwdDriveBtn: TButton
          Left = 16
          Top = 23
          Width = 39
          Height = 25
          Caption = 'Fwd'
          TabOrder = 7
          OnMouseDown = DeviceBtnDown
          OnMouseUp = driveBtnUp
        end
        object revDriveBtn: TButton
          Left = 61
          Top = 23
          Width = 40
          Height = 25
          Caption = 'Rev'
          TabOrder = 8
          OnMouseDown = DeviceBtnDown
          OnMouseUp = driveBtnUp
        end
        object Button6: TButton
          Left = 107
          Top = 23
          Width = 41
          Height = 25
          Action = stopMotor
          TabOrder = 9
          OnMouseDown = DeviceBtnDown
        end
      end
      object Panel3: TPanel
        Left = 2
        Top = 15
        Width = 339
        Height = 34
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 5
        ExplicitWidth = 563
        object Button2: TButton
          Left = 15
          Top = 3
          Width = 75
          Height = 28
          Action = homeDevice
          TabOrder = 0
        end
        object motorPositionE: mtkFloatLabeledEdit
          Left = 150
          Top = 1
          Width = 95
          Height = 37
          EditLabel.Width = 37
          EditLabel.Height = 13
          EditLabel.Caption = 'Position'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlue
          Font.Height = -24
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentFont = False
          TabOrder = 1
          Text = '0.00'
        end
      end
    end
    object JoyStickGB: TGroupBox
      Left = 501
      Top = 0
      Width = 185
      Height = 425
      Caption = 'JoyStick'
      TabOrder = 2
      object JoystickAvgZPos: TLabel
        Left = 32
        Top = 380
        Width = 101
        Height = 13
        Caption = 'JoystickAVGZPosition'
      end
      object JoystickZPosition: TLabel
        Left = 32
        Top = 361
        Width = 81
        Height = 13
        Caption = 'JoystickZPosition'
      end
      object GroupBox1: TGroupBox
        Left = 3
        Top = 16
        Width = 179
        Height = 201
        Caption = 'Velocity Settings'
        TabOrder = 0
        object RadioGroup1: TRadioGroup
          Left = 3
          Top = 24
          Width = 185
          Height = 59
          Caption = 'Presets'
          Columns = 4
          ItemIndex = 0
          Items.Strings = (
            '1'
            '2'
            '3'
            '4')
          TabOrder = 0
        end
        object maxJoyVel: mtkFloatLabeledEdit
          Left = 16
          Top = 112
          Width = 65
          Height = 21
          EditLabel.Width = 60
          EditLabel.Height = 13
          EditLabel.Caption = 'Max Velocity'
          TabOrder = 1
          Text = '0.00'
        end
        object JoySteps: TIntegerLabeledEdit
          Left = 96
          Top = 112
          Width = 49
          Height = 21
          EditLabel.Width = 28
          EditLabel.Height = 13
          EditLabel.Caption = 'Gears'
          TabOrder = 2
          Text = '4'
          Value = 4
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 648
    Top = 296
    object checkForDevices: TAction
      Caption = 'Devices Check'
      OnExecute = checkForDevicesExecute
    end
    object connectAllDevices: TAction
      Caption = 'Connect All'
      OnExecute = connectAllDevicesExecute
    end
    object identifyCurrent: TAction
      Caption = 'Identify'
      OnExecute = identifyCurrentExecute
    end
    object homeDevice: TAction
      Caption = 'Home'
      OnExecute = homeDeviceExecute
    end
    object jogForward: TAction
      Caption = 'Fwd'
      OnExecute = jogForwardExecute
    end
    object jogBackwards: TAction
      Caption = 'Rev'
      OnExecute = jogBackwardsExecute
    end
    object moveForward: TAction
      Caption = 'Forward'
      OnExecute = moveForwardExecute
    end
    object moveBackward: TAction
      Caption = 'Backward'
      OnExecute = moveBackwardExecute
    end
    object stopMotor: TAction
      Caption = 'Stop'
      OnExecute = stopMotorExecute
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = ShutDownTimerTimer
    Left = 32
    Top = 208
  end
  object StatusTimer: TTimer
    Enabled = False
    Interval = 500
    OnTimer = StatusTimerTimer
    Left = 40
    Top = 136
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 48
    Top = 80
  end
end
