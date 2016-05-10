object Main: TMain
  Left = 0
  Top = 0
  Caption = 'ArrayBot Version 0.1'
  ClientHeight = 574
  ClientWidth = 740
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
    Width = 740
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 8
    ExplicitTop = 437
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 740
    Height = 36
    ButtonHeight = 30
    ButtonWidth = 13
    Caption = 'ToolBar1'
    List = True
    AllowTextButtons = True
    TabOrder = 0
    object InitCloseBtn: TBitBtn
      Left = 0
      Top = 0
      Width = 96
      Height = 30
      Action = InitializeUnitsA
      Caption = 'Initialize'
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
    object Button7: TButton
      Left = 201
      Top = 0
      Width = 122
      Height = 30
      Action = stopMotor
      TabOrder = 2
    end
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 412
    Width = 740
    Height = 162
    Align = alBottom
    TabOrder = 1
    object infoMemo: TMemo
      Left = 1
      Top = 34
      Width = 738
      Height = 127
      Align = alClient
      ScrollBars = ssVertical
      TabOrder = 0
      WordWrap = False
    end
    object ToolBar2: TToolBar
      Left = 1
      Top = 1
      Width = 738
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
  object TopPanel: TPanel
    Left = 0
    Top = 36
    Width = 740
    Height = 373
    Align = alClient
    TabOrder = 2
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 738
      Height = 371
      ActivePage = TabSheet1
      Align = alClient
      TabOrder = 0
      object TabSheet4: TTabSheet
        Caption = 'The Bot'
      end
      object TabSheet1: TTabSheet
        Caption = 'XYZ Units'
        inline TXYZUnitFrame1: TXYZUnitFrame
          Left = 0
          Top = 0
          Width = 730
          Height = 343
          Align = alClient
          TabOrder = 0
          ExplicitWidth = 730
          ExplicitHeight = 343
          inherited mainGB: TGroupBox
            Width = 730
            Height = 343
            ExplicitWidth = 730
            ExplicitHeight = 343
            inherited Panel1: TPanel
              Width = 726
              ExplicitWidth = 726
            end
            inherited ScrollBox1: TScrollBox
              Width = 726
              Height = 285
              ExplicitWidth = 726
              ExplicitHeight = 285
            end
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Devices'
        ImageIndex = 1
        object DeviceGB: TGroupBox
          Left = 153
          Top = 0
          Width = 343
          Height = 343
          Align = alLeft
          Caption = 'Device'
          TabOrder = 0
          object Button1: TButton
            Left = 6
            Top = 249
            Width = 80
            Height = 56
            Action = identifyCurrent
            TabOrder = 0
          end
          object JoggingGB: TGroupBox
            Left = 2
            Top = 131
            Width = 339
            Height = 112
            Align = alTop
            Caption = 'Jogging'
            TabOrder = 1
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
            TabOrder = 2
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
            TabOrder = 3
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
        object DevicesGB: TGroupBox
          Left = 0
          Top = 0
          Width = 153
          Height = 343
          Align = alLeft
          Caption = 'Devices'
          TabOrder = 1
          object devicesLB: TListBox
            Left = 2
            Top = 15
            Width = 149
            Height = 326
            Align = alClient
            ItemHeight = 13
            TabOrder = 0
            OnClick = devicesLBClick
          end
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'JoyStick'
        ImageIndex = 2
        object JoyStickGB: TGroupBox
          Left = 0
          Top = 0
          Width = 730
          Height = 343
          Align = alClient
          Caption = 'JoyStick'
          TabOrder = 0
          object mNrOfGearsLbl: TIntegerLabeledEdit
            Left = 17
            Top = 30
            Width = 41
            Height = 21
            EditLabel.Width = 55
            EditLabel.Height = 13
            EditLabel.Caption = 'Nr of Gears'
            TabOrder = 0
            Text = '0'
            OnKeyDown = JoyStickValueEdit
          end
          object mMaxXYJogVelocityJoystick: mtkFloatLabeledEdit
            Left = 17
            Top = 72
            Width = 66
            Height = 21
            EditLabel.Width = 75
            EditLabel.Height = 13
            EditLabel.Caption = 'Max XY Velocity'
            TabOrder = 1
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object mXYJogAccelerationJoystick: mtkFloatLabeledEdit
            Left = 97
            Top = 72
            Width = 66
            Height = 21
            EditLabel.Width = 74
            EditLabel.Height = 13
            EditLabel.Caption = 'XY Acceleration'
            TabOrder = 2
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object mMaxZJogVelocityJoystick: mtkFloatLabeledEdit
            Left = 17
            Top = 121
            Width = 66
            Height = 21
            EditLabel.Width = 69
            EditLabel.Height = 13
            EditLabel.Caption = 'Max Z Velocity'
            TabOrder = 3
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object mZJogAccelerationJoystick: mtkFloatLabeledEdit
            Left = 97
            Top = 121
            Width = 66
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'Z Acceleration'
            TabOrder = 4
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object jsStateRG: TRadioGroup
            Left = 17
            Top = 160
            Width = 160
            Height = 54
            Caption = 'State'
            Columns = 2
            ItemIndex = 1
            Items.Strings = (
              'Enabled'
              'Disabled')
            TabOrder = 5
            OnClick = jsAxisRGClick
          end
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 280
    Top = 176
    object checkForDevices: TAction
      Caption = 'Devices Check'
      OnExecute = checkForDevicesExecute
    end
    object addDevicesToListBox: TAction
      Caption = 'Connect All'
      OnExecute = addDevicesToListBoxExecute
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
      Caption = 'Stop All'
      OnExecute = stopMotorExecute
    end
    object InitializeUnitsA: TAction
      Caption = 'Initialize'
      OnExecute = InitializeUnitsAExecute
    end
    object ShutDownA: TAction
      Caption = 'ShutDown'
      OnExecute = ShutDownAExecute
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = ShutDownTimerTimer
    Left = 40
    Top = 464
  end
  object StatusTimer: TTimer
    Enabled = False
    Interval = 500
    OnTimer = StatusTimerTimer
    Left = 128
    Top = 464
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 208
    Top = 464
  end
end
