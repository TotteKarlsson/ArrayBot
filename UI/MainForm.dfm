object Main: TMain
  Left = 0
  Top = 0
  ActiveControl = mJoystickMessageRate
  Caption = 'Device Tester'
  ClientHeight = 531
  ClientWidth = 733
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
  object Label7: TLabel
    Left = 40
    Top = 369
    Width = 81
    Height = 13
    Caption = 'JoystickZPosition'
  end
  object Label8: TLabel
    Left = 40
    Top = 388
    Width = 101
    Height = 13
    Caption = 'JoystickAVGZPosition'
  end
  object Label11: TLabel
    Left = 48
    Top = 377
    Width = 81
    Height = 13
    Caption = 'JoystickZPosition'
  end
  object Label12: TLabel
    Left = 48
    Top = 396
    Width = 101
    Height = 13
    Caption = 'JoystickAVGZPosition'
  end
  object Splitter1: TSplitter
    Left = 0
    Top = 409
    Width = 733
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ExplicitLeft = 8
    ExplicitTop = 544
    ExplicitWidth = 952
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 733
    Height = 36
    ButtonHeight = 30
    ButtonWidth = 13
    Caption = 'ToolBar1'
    List = True
    AllowTextButtons = True
    TabOrder = 0
    ExplicitWidth = 952
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
  object BottomPanel: TPanel
    Left = 0
    Top = 412
    Width = 733
    Height = 119
    Align = alClient
    TabOrder = 1
    ExplicitTop = 504
    ExplicitWidth = 952
    ExplicitHeight = 193
    object infoMemo: TMemo
      Left = 1
      Top = 34
      Width = 731
      Height = 84
      Align = alClient
      ScrollBars = ssVertical
      TabOrder = 0
      WordWrap = False
      ExplicitWidth = 950
      ExplicitHeight = 158
    end
    object ToolBar2: TToolBar
      Left = 1
      Top = 1
      Width = 731
      Height = 33
      AutoSize = True
      ButtonHeight = 33
      Caption = 'ToolBar2'
      TabOrder = 1
      ExplicitWidth = 950
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
  object TopPanel: TPanel
    Left = 0
    Top = 36
    Width = 733
    Height = 373
    Align = alTop
    TabOrder = 2
    ExplicitWidth = 952
    object DevicesGB: TGroupBox
      Left = 1
      Top = 1
      Width = 153
      Height = 371
      Align = alLeft
      Caption = 'Devices'
      TabOrder = 0
      ExplicitHeight = 463
      object devicesLB: TListBox
        Left = 2
        Top = 15
        Width = 149
        Height = 354
        Align = alClient
        ItemHeight = 13
        TabOrder = 0
        OnClick = devicesLBClick
        ExplicitHeight = 446
      end
    end
    object DeviceGB: TGroupBox
      Left = 154
      Top = 1
      Width = 343
      Height = 371
      Align = alLeft
      Caption = 'Device'
      TabOrder = 1
      ExplicitHeight = 463
      object Button1: TButton
        Left = 145
        Top = 249
        Width = 80
        Height = 69
        Action = identifyCurrent
        TabOrder = 0
      end
      object Button7: TButton
        Left = 4
        Top = 249
        Width = 122
        Height = 69
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
        object Button3: TButton
          Left = 16
          Top = 23
          Width = 50
          Height = 25
          Caption = 'Fwd'
          TabOrder = 0
          OnMouseDown = DeviceBtnDown
        end
        object Button4: TButton
          Left = 72
          Top = 23
          Width = 50
          Height = 25
          Caption = 'Rev'
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
          OnKeyDown = DeviceValueEdit
        end
        object mJogVelocity: mtkFloatLabeledEdit
          Left = 21
          Top = 81
          Width = 66
          Height = 21
          EditLabel.Width = 60
          EditLabel.Height = 13
          EditLabel.Caption = 'Max Velocity'
          TabOrder = 4
          Text = '0.00'
          OnKeyDown = DeviceValueEdit
        end
        object mJogStopBtn: TButton
          Left = 128
          Top = 23
          Width = 41
          Height = 25
          Caption = 'Stop'
          TabOrder = 5
          OnMouseDown = DeviceBtnDown
        end
        object mJogStopModeCB: TCheckBox
          Left = 184
          Top = 50
          Width = 78
          Height = 17
          Caption = 'Profiled Stop'
          TabOrder = 6
          OnClick = mJogModeCBClick
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
        object Label1: TLabel
          Left = 17
          Top = 23
          Width = 49
          Height = 13
          Caption = 'Is Active: '
        end
        object Label2: TLabel
          Left = 166
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
          Left = 166
          Top = 36
          Width = 70
          Height = 13
          Caption = 'Is Forwarding:'
        end
        object Lbl2: TLabel
          Left = 166
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
          Left = 242
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
          Left = 242
          Top = 23
          Width = 18
          Height = 13
          Caption = 'N/A'
        end
        object mIsReversingLabel: TLabel
          Left = 242
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
      object Panel3: TPanel
        Left = 2
        Top = 15
        Width = 339
        Height = 34
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 4
        object Button2: TButton
          Left = 15
          Top = 3
          Width = 75
          Height = 28
          Action = homeDevice
          TabOrder = 0
        end
        object motorPositionE: mtkFloatLabeledEdit
          Left = 168
          Top = -3
          Width = 171
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
      Left = 497
      Top = 1
      Width = 235
      Height = 371
      Align = alClient
      Caption = 'JoyStick'
      TabOrder = 2
      ExplicitWidth = 454
      ExplicitHeight = 463
      object JoystickZPosition: TLabel
        Left = 16
        Top = 116
        Width = 81
        Height = 13
        Caption = 'JoystickZPosition'
      end
      object JoystickXPosition: TLabel
        Left = 16
        Top = 78
        Width = 81
        Height = 13
        Caption = 'JoystickXPosition'
      end
      object JoystickYPosition: TLabel
        Left = 16
        Top = 97
        Width = 81
        Height = 13
        Caption = 'JoystickYPosition'
      end
      object JoystickButton1: TLabel
        Left = 16
        Top = 139
        Width = 76
        Height = 13
        Caption = 'JoystickButton1'
      end
      object JoystickButton2: TLabel
        Left = 16
        Top = 158
        Width = 76
        Height = 13
        Caption = 'JoystickButton2'
      end
      object JoystickButton3: TLabel
        Left = 16
        Top = 177
        Width = 76
        Height = 13
        Caption = 'JoystickButton3'
      end
      object JoystickButton4: TLabel
        Left = 16
        Top = 196
        Width = 76
        Height = 13
        Caption = 'JoystickButton4'
      end
      object jsStateRG: TRadioGroup
        Left = 17
        Top = 18
        Width = 160
        Height = 54
        Caption = 'State'
        Columns = 2
        ItemIndex = 1
        Items.Strings = (
          'Enabled'
          'Disabled')
        TabOrder = 0
        OnClick = jsAxisRGClick
      end
      object mNrOfGearsLbl: TIntegerLabeledEdit
        Left = 16
        Top = 248
        Width = 41
        Height = 21
        EditLabel.Width = 55
        EditLabel.Height = 13
        EditLabel.Caption = 'Nr of Gears'
        TabOrder = 1
        Text = '0'
        OnKeyDown = JoyStickValueEdit
      end
      object mMaxXYJogVelocityJoystick: mtkFloatLabeledEdit
        Left = 17
        Top = 290
        Width = 66
        Height = 21
        EditLabel.Width = 75
        EditLabel.Height = 13
        EditLabel.Caption = 'Max XY Velocity'
        TabOrder = 2
        Text = '0.00'
        OnKeyDown = JoyStickValueEdit
      end
      object mXYJogAccelerationJoystick: mtkFloatLabeledEdit
        Left = 97
        Top = 290
        Width = 66
        Height = 21
        EditLabel.Width = 74
        EditLabel.Height = 13
        EditLabel.Caption = 'XY Acceleration'
        TabOrder = 3
        Text = '0.00'
        OnKeyDown = JoyStickValueEdit
      end
      object mMaxZJogVelocityJoystick: mtkFloatLabeledEdit
        Left = 17
        Top = 339
        Width = 66
        Height = 21
        EditLabel.Width = 69
        EditLabel.Height = 13
        EditLabel.Caption = 'Max Z Velocity'
        TabOrder = 4
        Text = '0.00'
        OnKeyDown = JoyStickValueEdit
      end
      object mZJogAccelerationJoystick: mtkFloatLabeledEdit
        Left = 97
        Top = 339
        Width = 66
        Height = 21
        EditLabel.Width = 68
        EditLabel.Height = 13
        EditLabel.Caption = 'Z Acceleration'
        TabOrder = 5
        Text = '0.00'
        OnKeyDown = JoyStickValueEdit
      end
      object mJoystickMessageRate: TIntegerLabeledEdit
        Left = 97
        Top = 248
        Width = 73
        Height = 21
        EditLabel.Width = 92
        EditLabel.Height = 13
        EditLabel.Caption = 'Message Rate (ms)'
        TabOrder = 6
        Text = '20'
        OnKeyDown = JoyStickValueEdit
        Value = 20
      end
    end
  end
  object ActionList1: TActionList
    Left = 656
    Top = 112
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
    end
    object moveBackward: TAction
      Caption = 'Backward'
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
