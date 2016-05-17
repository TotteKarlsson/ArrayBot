object Main: TMain
  Left = 0
  Top = 0
  Caption = 'ArrayBot Version 0.1'
  ClientHeight = 549
  ClientWidth = 667
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
  object Splitter1: TSplitter
    Left = 0
    Top = 384
    Width = 667
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
    Width = 667
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
      Action = initBotA
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
    Top = 387
    Width = 667
    Height = 162
    Align = alBottom
    TabOrder = 1
    ExplicitTop = 404
    object infoMemo: TMemo
      Left = 1
      Top = 34
      Width = 665
      Height = 127
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
    object ToolBar2: TToolBar
      Left = 1
      Top = 1
      Width = 665
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
    Width = 667
    Height = 348
    Align = alClient
    Constraints.MinHeight = 348
    TabOrder = 2
    ExplicitHeight = 365
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 665
      Height = 346
      ActivePage = TabSheet4
      Align = alClient
      TabOrder = 0
      ExplicitHeight = 363
      object TabSheet4: TTabSheet
        Caption = 'The Bot'
        ExplicitHeight = 335
        object GroupBox6: TGroupBox
          Left = 365
          Top = 19
          Width = 284
          Height = 154
          Caption = 'Coordinated Move'
          TabOrder = 0
          object MoveBtn: TButton
            Left = 138
            Top = 22
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
          object mMoveAngleE: mtkFloatLabeledEdit
            Left = 19
            Top = 44
            Width = 98
            Height = 53
            EditLabel.Width = 85
            EditLabel.Height = 13
            EditLabel.Caption = 'Move Angle (deg)'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -37
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            Text = '0.00'
            OnKeyDown = moveEdit
          end
        end
        object Button1: TButton
          Left = 520
          Top = 191
          Width = 129
          Height = 98
          Action = stopAllA
          Caption = 'Abort'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -27
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
        end
        object JoyControlRG: TRadioGroup
          Left = 3
          Top = 11
          Width = 342
          Height = 76
          Caption = 'JoyStick Control'
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
          TabOrder = 2
          OnClick = JoyControlRGClick
        end
        object JSSpeedsRG: TRadioGroup
          Left = 3
          Top = 95
          Width = 342
          Height = 78
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
          TabOrder = 3
          OnClick = JSSpeedsRGClick
        end
        object csaGB: TGroupBox
          Left = 3
          Top = 206
          Width = 193
          Height = 104
          Caption = 'CoverSlip Angle'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
          object mCSAngleE: mtkFloatLabeledEdit
            Left = 20
            Top = 63
            Width = 68
            Height = 33
            EditLabel.Width = 111
            EditLabel.Height = 25
            EditLabel.Caption = 'Angle (deg)'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -21
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
        Caption = 'XYZ Units'
        ExplicitHeight = 335
        object ScrollBox1: TScrollBox
          Left = 0
          Top = 0
          Width = 657
          Height = 318
          Align = alClient
          TabOrder = 0
          ExplicitHeight = 335
          inline TXYZUnitFrame1: TXYZUnitFrame
            Left = 0
            Top = 351
            Width = 636
            Height = 348
            Align = alTop
            TabOrder = 0
            ExplicitTop = 351
            ExplicitWidth = 636
            ExplicitHeight = 348
            inherited mainGB: TGroupBox
              Width = 636
              Height = 348
              ExplicitWidth = 636
              ExplicitHeight = 348
              inherited TopPanel: TPanel
                Width = 632
                ExplicitWidth = 632
              end
              inherited ScrollBox1: TScrollBox
                Width = 632
                Height = 305
                ExplicitWidth = 632
                ExplicitHeight = 305
              end
            end
          end
          inline TXYZUnitFrame2: TXYZUnitFrame
            Left = 0
            Top = 0
            Width = 636
            Height = 351
            Align = alTop
            TabOrder = 1
            ExplicitWidth = 636
            inherited mainGB: TGroupBox
              Width = 636
              ExplicitWidth = 636
              ExplicitHeight = 351
              inherited TopPanel: TPanel
                Width = 632
                ExplicitWidth = 632
              end
              inherited ScrollBox1: TScrollBox
                Width = 632
                ExplicitWidth = 632
                ExplicitHeight = 308
              end
            end
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Settings'
        ImageIndex = 2
        ExplicitHeight = 335
        object JoyStickGB2: TGroupBox
          Left = 11
          Top = 16
          Width = 238
          Height = 169
          Caption = 'JoyStick Velocities'
          TabOrder = 0
          object mZJogAccelerationJoystick: mtkFloatLabeledEdit
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
          object mXYJogAccelerationJoystick: mtkFloatLabeledEdit
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
          object mMaxZJogVelocityJoystick: mtkFloatLabeledEdit
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
          object mMaxXYJogVelocityJoystick: mtkFloatLabeledEdit
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
          object mMoveAccelerationE: mtkFloatLabeledEdit
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
          object mMoveVelocityVerticalE: mtkFloatLabeledEdit
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
          object mMoveVelHorizE: mtkFloatLabeledEdit
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
          object mVerticalMoveDistanceE: mtkFloatLabeledEdit
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
        object Button3: TButton
          Left = 194
          Top = 205
          Width = 177
          Height = 116
          Caption = 'Home All'
          TabOrder = 2
          OnClick = Button3Click
        end
        object Button4: TButton
          Left = 11
          Top = 205
          Width = 177
          Height = 116
          Caption = 'Stow'
          TabOrder = 3
          OnClick = stowBtnClick
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'TabSheet3'
        ImageIndex = 3
        ExplicitHeight = 335
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
            inherited Button4: TButton [4]
            end
            inherited JoggingGB: TGroupBox [5]
              Top = 116
              Width = 289
              ExplicitTop = 116
              ExplicitWidth = 289
            end
            inherited mMotorPositionE: mtkFloatLabeledEdit [6]
              Left = 173
              EditLabel.ExplicitLeft = 173
              EditLabel.ExplicitTop = 13
              EditLabel.ExplicitWidth = 64
              ExplicitLeft = 173
            end
            inherited StatusGB: TGroupBox [7]
              Top = 208
              Width = 289
              ExplicitTop = 208
              ExplicitWidth = 289
            end
            inherited Button1: TButton [8]
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
    object initBotA: TAction
      Caption = 'Initialize'
      OnExecute = initBotAExecute
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
