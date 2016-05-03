object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Device Tester'
  ClientHeight = 611
  ClientWidth = 927
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
    Width = 927
    Height = 36
    ButtonHeight = 30
    ButtonWidth = 13
    Caption = 'ToolBar1'
    List = True
    AllowTextButtons = True
    TabOrder = 0
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
    Top = 433
    Width = 927
    Height = 178
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 1
    object infoMemo: TMemo
      Left = 1
      Top = 34
      Width = 925
      Height = 143
      Align = alClient
      ScrollBars = ssVertical
      TabOrder = 0
      WordWrap = False
    end
    object ToolBar2: TToolBar
      Left = 1
      Top = 1
      Width = 925
      Height = 33
      AutoSize = True
      ButtonHeight = 33
      Caption = 'ToolBar2'
      TabOrder = 1
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
    Width = 927
    Height = 397
    Align = alTop
    TabOrder = 2
    object JoystickZPosition: TLabel
      Left = 600
      Top = 208
      Width = 81
      Height = 13
      Caption = 'JoystickZPosition'
    end
    object JoystickAvgZPos: TLabel
      Left = 600
      Top = 227
      Width = 81
      Height = 13
      Caption = 'JoystickZPosition'
    end
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 153
      Height = 395
      Align = alLeft
      Caption = 'Devices'
      TabOrder = 0
      object devicesLB: TListBox
        Left = 2
        Top = 15
        Width = 149
        Height = 378
        Align = alClient
        ItemHeight = 13
        TabOrder = 0
        OnClick = devicesLBClick
      end
    end
    object GroupBox2: TGroupBox
      Left = 154
      Top = 1
      Width = 335
      Height = 395
      Align = alLeft
      Caption = 'Device'
      TabOrder = 1
      object mIsActiveLabel: TLabel
        Left = 112
        Top = 175
        Width = 18
        Height = 13
        Caption = 'N/A'
      end
      object mIsHomingLabel: TLabel
        Left = 112
        Top = 194
        Width = 18
        Height = 13
        Caption = 'N/A'
      end
      object mIsHomedLabel: TLabel
        Left = 112
        Top = 213
        Width = 18
        Height = 13
        Caption = 'N/A'
      end
      object Label1: TLabel
        Left = 17
        Top = 175
        Width = 49
        Height = 13
        Caption = 'Is Active: '
      end
      object Label2: TLabel
        Left = 16
        Top = 194
        Width = 51
        Height = 13
        Caption = 'Is Homing:'
      end
      object Label3: TLabel
        Left = 17
        Top = 213
        Width = 52
        Height = 13
        Caption = 'Is Homed: '
      end
      object Lbl2: TLabel
        Left = 16
        Top = 251
        Width = 64
        Height = 13
        Caption = 'Is Reversing:'
      end
      object mVelocityLbl: TLabel
        Left = 111
        Top = 270
        Width = 52
        Height = 13
        Caption = 'Is Homed: '
      end
      object Lbl: TLabel
        Left = 16
        Top = 232
        Width = 70
        Height = 13
        Caption = 'Is Forwarding:'
      end
      object mIsReversingLabel: TLabel
        Left = 112
        Top = 251
        Width = 18
        Height = 13
        Caption = 'N/A'
      end
      object mIsForwardingLabel: TLabel
        Left = 112
        Top = 232
        Width = 18
        Height = 13
        Caption = 'N/A'
      end
      object Label5: TLabel
        Left = 17
        Top = 270
        Width = 41
        Height = 13
        Caption = 'Velocity:'
      end
      object Button1: TButton
        Left = 16
        Top = 24
        Width = 75
        Height = 25
        Action = identifyCurrent
        TabOrder = 0
      end
      object Button2: TButton
        Left = 97
        Top = 24
        Width = 75
        Height = 25
        Action = homeDevice
        TabOrder = 1
      end
      object Button3: TButton
        Left = 16
        Top = 55
        Width = 75
        Height = 25
        Action = jogForward
        TabOrder = 2
      end
      object Button4: TButton
        Left = 97
        Top = 55
        Width = 75
        Height = 25
        Action = jogBackwards
        TabOrder = 3
      end
      object motorPositionE: mtkFloatLabeledEdit
        Left = 16
        Top = 136
        Width = 75
        Height = 21
        EditLabel.Width = 37
        EditLabel.Height = 13
        EditLabel.Caption = 'Position'
        TabOrder = 4
        Text = '0.00'
      end
      object Button7: TButton
        Left = 178
        Top = 24
        Width = 65
        Height = 25
        Action = stopMotor
        TabOrder = 6
      end
      object fwdDriveBtn: TButton
        Left = 145
        Top = 208
        Width = 75
        Height = 25
        Caption = 'Forward'
        TabOrder = 7
        OnMouseDown = driveBtnDown
        OnMouseUp = driveBtnUp
      end
      object revDriveBtn: TButton
        Left = 226
        Top = 208
        Width = 75
        Height = 25
        Caption = 'Backward'
        TabOrder = 8
        OnMouseDown = driveBtnDown
        OnMouseUp = driveBtnUp
      end
      object mMaxVelocity: mtkFloatLabeledEdit
        Left = 97
        Top = 136
        Width = 66
        Height = 21
        EditLabel.Width = 56
        EditLabel.Height = 13
        EditLabel.Caption = 'Set Velocity'
        TabOrder = 5
        Text = '0.00'
        OnKeyDown = mMaxVelocityKeyDown
      end
      object mAcceleration: mtkFloatLabeledEdit
        Left = 177
        Top = 136
        Width = 66
        Height = 21
        EditLabel.Width = 59
        EditLabel.Height = 13
        EditLabel.Caption = 'Acceleration'
        TabOrder = 9
        Text = '0.00'
        OnKeyDown = mMaxVelocityKeyDown
      end
      object TrackBar1: TTrackBar
        Left = 6
        Top = 345
        Width = 150
        Height = 45
        Max = 1000
        Min = -1000
        Frequency = 50
        TabOrder = 10
      end
      object Button5: TButton
        Left = 249
        Top = 24
        Width = 75
        Height = 25
        Caption = 'Stop Profiled'
        TabOrder = 11
        OnClick = Button5Click
      end
      object DecreaseVelBtn: TButton
        Left = 256
        Top = 295
        Width = 50
        Height = 25
        Caption = '-'
        TabOrder = 12
        OnClick = DecreaseVelBtnClick
      end
      object IncreaseVelBtn: TButton
        Left = 201
        Top = 295
        Width = 49
        Height = 25
        Caption = '+'
        TabOrder = 13
        OnClick = IncreaseVelBtnClick
      end
      object ContinousMoveCB: TCheckBox
        Left = 145
        Top = 185
        Width = 78
        Height = 17
        Caption = 'Continous'
        TabOrder = 14
      end
      object mVelDeltaE: mtkFloatLabeledEdit
        Left = 200
        Top = 268
        Width = 121
        Height = 21
        EditLabel.Width = 84
        EditLabel.Height = 13
        EditLabel.Caption = 'Vel Increase Step'
        TabOrder = 15
        Text = '2.00'
      end
      object switchdirectionBtn: TButton
        Left = 216
        Top = 326
        Width = 89
        Height = 25
        Caption = 'Switch Direction'
        TabOrder = 16
        OnClick = switchdirectionBtnClick
      end
    end
  end
  object ActionList1: TActionList
    Left = 560
    Top = 144
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
      Caption = 'Jog Forward'
      OnExecute = jogForwardExecute
    end
    object jogBackwards: TAction
      Caption = 'Jog Backward'
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
      Caption = 'Stop Hard'
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
