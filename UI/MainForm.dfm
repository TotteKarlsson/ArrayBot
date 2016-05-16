object Main: TMain
  Left = 0
  Top = 0
  Caption = 'ArrayBot Version 0.1'
  ClientHeight = 668
  ClientWidth = 766
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
    Top = 503
    Width = 766
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 8
    ExplicitTop = 437
    ExplicitWidth = 740
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 766
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
      Width = 80
      Height = 30
      Action = stopAllA
      TabOrder = 2
    end
    object Button2: TButton
      Left = 281
      Top = 0
      Width = 75
      Height = 30
      Caption = 'Toggle Log'
      TabOrder = 3
      OnClick = Button2Click
    end
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 506
    Width = 766
    Height = 162
    Align = alBottom
    TabOrder = 1
    ExplicitTop = 430
    object infoMemo: TMemo
      Left = 1
      Top = 34
      Width = 764
      Height = 127
      Align = alClient
      ScrollBars = ssVertical
      TabOrder = 0
      WordWrap = False
    end
    object ToolBar2: TToolBar
      Left = 1
      Top = 1
      Width = 764
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
    Width = 766
    Height = 467
    Align = alClient
    TabOrder = 2
    ExplicitHeight = 391
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 764
      Height = 465
      ActivePage = TabSheet4
      Align = alClient
      Constraints.MinHeight = 389
      Constraints.MinWidth = 753
      TabOrder = 0
      ExplicitHeight = 389
      object TabSheet4: TTabSheet
        Caption = 'The Bot'
        ExplicitHeight = 361
        object GroupBox6: TGroupBox
          Left = 16
          Top = 19
          Width = 329
          Height = 166
          Caption = 'Coordinated Move'
          TabOrder = 0
          object MoveBtn: TButton
            Left = 194
            Top = 36
            Width = 127
            Height = 109
            Caption = 'Start Move'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -21
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = MoveBtnClick
          end
          object mMoveAccelerationE: mtkFloatLabeledEdit
            Left = 97
            Top = 36
            Width = 73
            Height = 21
            EditLabel.Width = 59
            EditLabel.Height = 13
            EditLabel.Caption = 'Acceleration'
            TabOrder = 1
            Text = '0.00'
          end
          object mMoveAngleE: mtkFloatLabeledEdit
            Left = 9
            Top = 84
            Width = 73
            Height = 21
            EditLabel.Width = 85
            EditLabel.Height = 13
            EditLabel.Caption = 'Move Angle (deg)'
            TabOrder = 2
            Text = '0.00'
            OnKeyDown = moveEdit
          end
          object mMoveVelHorizE: mtkFloatLabeledEdit
            Left = 97
            Top = 84
            Width = 73
            Height = 21
            EditLabel.Width = 71
            EditLabel.Height = 13
            EditLabel.Caption = 'Velocity (horiz)'
            Enabled = False
            TabOrder = 3
            Text = '0.00'
          end
          object mMoveVelocityVerticalE: mtkFloatLabeledEdit
            Left = 9
            Top = 36
            Width = 73
            Height = 21
            EditLabel.Width = 83
            EditLabel.Height = 13
            EditLabel.Caption = 'Velocity (vertical)'
            TabOrder = 4
            Text = '0.00'
            OnKeyDown = moveEdit
          end
          object mVerticalMoveDistanceE: mtkFloatLabeledEdit
            Left = 9
            Top = 127
            Width = 73
            Height = 21
            EditLabel.Width = 107
            EditLabel.Height = 13
            EditLabel.Caption = 'Vertical move distance'
            TabOrder = 5
            Text = '0.00'
          end
        end
        object JoyStickGB: TGroupBox
          Left = 351
          Top = 19
          Width = 383
          Height = 329
          Caption = 'JoyStick'
          TabOrder = 1
          object mNrOfGearsLbl: TIntegerLabeledEdit
            Left = 192
            Top = 286
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
            Left = 24
            Top = 247
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
            Left = 104
            Top = 247
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
            Left = 24
            Top = 286
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
            Left = 104
            Top = 286
            Width = 66
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'Z Acceleration'
            TabOrder = 4
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object JoyControlRG: TRadioGroup
            Left = 16
            Top = 141
            Width = 342
            Height = 76
            Caption = 'Control'
            Columns = 3
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -21
            Font.Name = 'Tahoma'
            Font.Style = []
            ItemIndex = 2
            Items.Strings = (
              'CoverSlip'
              'Whisker'
              'None')
            ParentFont = False
            TabOrder = 5
            OnClick = JoyControlRGClick
          end
          object JSSpeedsRG: TRadioGroup
            Left = 16
            Top = 30
            Width = 344
            Height = 105
            Caption = 'Speed'
            Columns = 3
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -21
            Font.Name = 'Tahoma'
            Font.Style = []
            ItemIndex = 1
            Items.Strings = (
              'Fast '
              'Medium'
              'Slow')
            ParentFont = False
            TabOrder = 6
            OnClick = JSSpeedsRGClick
          end
        end
        object Button1: TButton
          Left = 16
          Top = 206
          Width = 161
          Height = 123
          Action = stopAllA
          Caption = 'Abort'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -27
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
      end
      object TabSheet1: TTabSheet
        Caption = 'XYZ Units'
        ExplicitHeight = 361
        object ScrollBox1: TScrollBox
          Left = 0
          Top = 0
          Width = 756
          Height = 437
          Align = alClient
          TabOrder = 0
          ExplicitHeight = 361
          inline TXYZUnitFrame1: TXYZUnitFrame
            Left = 0
            Top = 351
            Width = 735
            Height = 348
            Align = alTop
            TabOrder = 0
            ExplicitTop = 351
            ExplicitWidth = 735
            ExplicitHeight = 348
            inherited mainGB: TGroupBox
              Width = 735
              Height = 348
              ExplicitWidth = 735
              ExplicitHeight = 348
              inherited TopPanel: TPanel
                Width = 731
                ExplicitWidth = 731
              end
              inherited ScrollBox1: TScrollBox
                Width = 731
                Height = 305
                ExplicitWidth = 731
                ExplicitHeight = 305
              end
            end
          end
          inline TXYZUnitFrame2: TXYZUnitFrame
            Left = 0
            Top = 0
            Width = 735
            Height = 351
            Align = alTop
            TabOrder = 1
            ExplicitWidth = 735
            inherited mainGB: TGroupBox
              Width = 735
              ExplicitWidth = 735
              ExplicitHeight = 351
              inherited TopPanel: TPanel
                Width = 731
                ExplicitWidth = 731
              end
              inherited ScrollBox1: TScrollBox
                Width = 731
                ExplicitWidth = 731
                ExplicitHeight = 308
              end
            end
          end
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 296
    Top = 592
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
    Left = 24
    Top = 592
  end
  object StatusTimer: TTimer
    Enabled = False
    Interval = 500
    Left = 112
    Top = 592
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 192
    Top = 592
  end
end
