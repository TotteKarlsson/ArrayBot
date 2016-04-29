object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Device Tester'
  ClientHeight = 645
  ClientWidth = 771
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
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 771
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
    Top = 337
    Width = 771
    Height = 308
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 1
    object infoMemo: TMemo
      Left = 1
      Top = 34
      Width = 769
      Height = 273
      Align = alClient
      ScrollBars = ssVertical
      TabOrder = 0
      WordWrap = False
    end
    object ToolBar2: TToolBar
      Left = 1
      Top = 1
      Width = 769
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
    Width = 771
    Height = 301
    Align = alTop
    TabOrder = 2
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 153
      Height = 299
      Align = alLeft
      Caption = 'Devices'
      TabOrder = 0
      object devicesLB: TListBox
        Left = 2
        Top = 15
        Width = 149
        Height = 282
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
      Height = 299
      Align = alLeft
      Caption = 'Device'
      TabOrder = 1
      object mIsActiveLabel: TLabel
        Left = 17
        Top = 215
        Width = 18
        Height = 13
        Caption = 'N/A'
      end
      object mIsHomingLabel: TLabel
        Left = 80
        Top = 215
        Width = 18
        Height = 13
        Caption = 'N/A'
      end
      object mIsHomedLabel: TLabel
        Left = 153
        Top = 215
        Width = 18
        Height = 13
        Caption = 'N/A'
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
        Left = 250
        Top = 257
        Width = 71
        Height = 37
        Action = stopMotor
        TabOrder = 6
      end
      object fwdDriveBtn: TButton
        Left = 17
        Top = 87
        Width = 75
        Height = 25
        Caption = 'Forward'
        TabOrder = 7
        OnClick = moveForwardExecute
        OnMouseDown = driveBtnDown
        OnMouseUp = driveBtnUp
      end
      object revDriveBtn: TButton
        Left = 98
        Top = 87
        Width = 75
        Height = 25
        Caption = 'Backward'
        TabOrder = 8
        OnClick = moveBackwardExecute
        OnMouseDown = driveBtnDown
        OnMouseUp = driveBtnUp
      end
      object Button5: TButton
        Left = 192
        Top = 24
        Width = 75
        Height = 25
        Caption = 'Button5'
        TabOrder = 9
        OnClick = Button5Click
      end
      object mMaxVelocity: mtkFloatLabeledEdit
        Left = 97
        Top = 136
        Width = 66
        Height = 21
        EditLabel.Width = 60
        EditLabel.Height = 13
        EditLabel.Caption = 'Max Velocity'
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
        TabOrder = 10
        Text = '0.00'
        OnKeyDown = mMaxVelocityKeyDown
      end
      object Button8: TButton
        Left = 120
        Top = 176
        Width = 75
        Height = 25
        Caption = 'Button8'
        TabOrder = 11
      end
      object TrackBar1: TTrackBar
        Left = 23
        Top = 249
        Width = 150
        Height = 45
        Min = -10
        TabOrder = 12
        OnChange = TrackBar1Change
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
      Caption = 'Stop'
      OnExecute = stopMotorExecute
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = ShutDownTimerTimer
    Left = 512
    Top = 64
  end
  object StatusTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = StatusTimerTimer
    Left = 424
    Top = 96
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 480
    Top = 200
  end
end
