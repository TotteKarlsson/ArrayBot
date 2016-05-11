object Main: TMain
  Left = 0
  Top = 0
  Caption = 'ArrayBot Version 0.1'
  ClientHeight = 685
  ClientWidth = 950
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
    Top = 520
    Width = 950
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
    Width = 950
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
      Action = stopAllA
      TabOrder = 2
    end
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 523
    Width = 950
    Height = 162
    Align = alBottom
    TabOrder = 1
    object infoMemo: TMemo
      Left = 1
      Top = 34
      Width = 948
      Height = 127
      Align = alClient
      ScrollBars = ssVertical
      TabOrder = 0
      WordWrap = False
    end
    object ToolBar2: TToolBar
      Left = 1
      Top = 1
      Width = 948
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
    Width = 950
    Height = 484
    Align = alClient
    TabOrder = 2
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 948
      Height = 482
      ActivePage = TabSheet4
      Align = alClient
      TabOrder = 0
      object TabSheet4: TTabSheet
        Caption = 'The Bot'
        ExplicitLeft = 0
        ExplicitTop = 23
        object CoverSlipGB: TGroupBox
          Left = 16
          Top = 14
          Width = 385
          Height = 159
          Caption = 'Cover Slip'
          TabOrder = 0
          object Panel1: TPanel
            Left = 2
            Top = 15
            Width = 381
            Height = 19
            Align = alTop
            BevelOuter = bvNone
            TabOrder = 0
          end
          object GroupBox1: TGroupBox
            Left = 2
            Top = 34
            Width = 381
            Height = 114
            Align = alTop
            Caption = 'Positions'
            TabOrder = 1
            object PositionsCB: TComboBox
              Left = 11
              Top = 40
              Width = 104
              Height = 21
              ItemIndex = 0
              TabOrder = 0
              Text = 'Edit...'
              OnChange = PositionsCBChange
              Items.Strings = (
                'Edit...')
            end
            object GotoPosBtn: TButton
              Left = 121
              Top = 38
              Width = 27
              Height = 25
              Caption = '->'
              TabOrder = 1
              OnClick = GotoBtnClick
            end
            object mXPosE: mtkFloatLabeledEdit
              Left = 192
              Top = 40
              Width = 33
              Height = 21
              EditLabel.Width = 6
              EditLabel.Height = 13
              EditLabel.Caption = 'X'
              TabOrder = 2
              Text = '0.00'
            end
            object mYPosE: mtkFloatLabeledEdit
              Left = 235
              Top = 40
              Width = 37
              Height = 21
              EditLabel.Width = 6
              EditLabel.Height = 13
              EditLabel.Caption = 'Y'
              TabOrder = 3
              Text = '0.00'
            end
            object mZPosE: mtkFloatLabeledEdit
              Left = 278
              Top = 40
              Width = 35
              Height = 21
              EditLabel.Width = 6
              EditLabel.Height = 13
              EditLabel.Caption = 'Z'
              TabOrder = 4
              Text = '0.00'
            end
            object Button5: TButton
              Left = 319
              Top = 78
              Width = 31
              Height = 25
              Caption = '+'
              TabOrder = 5
              OnClick = Button5Click
            end
            object mPositionLabelE: TSTDStringLabeledEdit
              Left = 192
              Top = 80
              Width = 121
              Height = 21
              EditLabel.Width = 67
              EditLabel.Height = 13
              EditLabel.Caption = 'Position Name'
              TabOrder = 6
            end
          end
        end
        object GroupBox3: TGroupBox
          Left = 445
          Top = 14
          Width = 425
          Height = 159
          Caption = 'Whisker'
          TabOrder = 1
          object Panel2: TPanel
            Left = 2
            Top = 15
            Width = 421
            Height = 19
            Align = alTop
            BevelOuter = bvNone
            TabOrder = 0
          end
          object GroupBox5: TGroupBox
            Left = 2
            Top = 34
            Width = 421
            Height = 114
            Align = alTop
            Caption = 'Positions'
            TabOrder = 1
            object ComboBox1: TComboBox
              Left = 11
              Top = 32
              Width = 104
              Height = 21
              ItemIndex = 0
              TabOrder = 0
              Text = 'Edit...'
              OnChange = PositionsCBChange
              Items.Strings = (
                'Edit...')
            end
            object Button6: TButton
              Left = 121
              Top = 30
              Width = 27
              Height = 25
              Caption = '->'
              TabOrder = 1
              OnClick = GotoBtnClick
            end
            object tkFloatLabeledEdit1: mtkFloatLabeledEdit
              Left = 192
              Top = 32
              Width = 33
              Height = 21
              EditLabel.Width = 6
              EditLabel.Height = 13
              EditLabel.Caption = 'X'
              TabOrder = 2
              Text = '0.00'
            end
            object tkFloatLabeledEdit2: mtkFloatLabeledEdit
              Left = 235
              Top = 32
              Width = 37
              Height = 21
              EditLabel.Width = 6
              EditLabel.Height = 13
              EditLabel.Caption = 'Y'
              TabOrder = 3
              Text = '0.00'
            end
            object tkFloatLabeledEdit3: mtkFloatLabeledEdit
              Left = 278
              Top = 32
              Width = 35
              Height = 21
              EditLabel.Width = 6
              EditLabel.Height = 13
              EditLabel.Caption = 'Z'
              TabOrder = 4
              Text = '0.00'
            end
            object STDStringLabeledEdit1: TSTDStringLabeledEdit
              Left = 192
              Top = 72
              Width = 121
              Height = 21
              EditLabel.Width = 67
              EditLabel.Height = 13
              EditLabel.Caption = 'Position Name'
              TabOrder = 5
            end
            object Button8: TButton
              Left = 319
              Top = 70
              Width = 31
              Height = 25
              Caption = '+'
              TabOrder = 6
              OnClick = Button5Click
            end
          end
        end
        object GroupBox6: TGroupBox
          Left = 16
          Top = 195
          Width = 383
          Height = 190
          Caption = 'Coordinated Move'
          TabOrder = 2
          object MoveBtn: TButton
            Left = 194
            Top = 32
            Width = 88
            Height = 57
            Caption = 'Start Move'
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
          Left = 424
          Top = 179
          Width = 409
          Height = 209
          Caption = 'JoyStick'
          TabOrder = 3
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
            Top = 148
            Width = 144
            Height = 45
            Caption = 'State'
            Columns = 2
            ItemIndex = 1
            Items.Strings = (
              'Enabled'
              'Disabled')
            TabOrder = 5
            OnClick = jsAxisRGClick
          end
          object JoyControlRG: TRadioGroup
            Left = 200
            Top = 24
            Width = 153
            Height = 105
            Caption = 'JoyStick Control'
            ItemIndex = 2
            Items.Strings = (
              'CoverSlip'
              'Whisker'
              'None')
            TabOrder = 6
            OnClick = JoyControlRGClick
          end
        end
      end
      object TabSheet1: TTabSheet
        Caption = 'XYZ Units'
        object ScrollBox1: TScrollBox
          Left = 0
          Top = 0
          Width = 940
          Height = 454
          Align = alClient
          TabOrder = 0
          ExplicitTop = 351
          ExplicitHeight = 103
          inline TXYZUnitFrame1: TXYZUnitFrame
            Left = 0
            Top = 351
            Width = 936
            Height = 348
            Align = alTop
            TabOrder = 0
            ExplicitTop = -249
            ExplicitWidth = 919
            ExplicitHeight = 348
            inherited mainGB: TGroupBox
              Width = 936
              Height = 348
              ExplicitWidth = 940
              ExplicitHeight = 348
              inherited TopPanel: TPanel
                Width = 932
                ExplicitWidth = 936
              end
              inherited ScrollBox1: TScrollBox
                Width = 932
                Height = 305
                ExplicitWidth = 936
                ExplicitHeight = 305
              end
            end
          end
          inline TXYZUnitFrame2: TXYZUnitFrame
            Left = 0
            Top = 0
            Width = 936
            Height = 351
            Align = alTop
            TabOrder = 1
            ExplicitWidth = 940
            inherited mainGB: TGroupBox
              Width = 936
              ExplicitWidth = 940
              inherited TopPanel: TPanel
                Width = 932
                ExplicitWidth = 936
              end
              inherited ScrollBox1: TScrollBox
                Width = 932
                ExplicitWidth = 936
              end
            end
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Devices'
        ImageIndex = 1
        object DevicesGB: TGroupBox
          Left = 0
          Top = 0
          Width = 153
          Height = 454
          Align = alLeft
          Caption = 'Devices'
          TabOrder = 0
          object devicesLB: TListBox
            Left = 2
            Top = 15
            Width = 149
            Height = 437
            Align = alClient
            ItemHeight = 13
            TabOrder = 0
            OnClick = devicesLBClick
          end
        end
        inline TMotorFrame1: TMotorFrame
          Left = 153
          Top = 0
          Width = 293
          Height = 454
          Align = alLeft
          TabOrder = 1
          ExplicitLeft = 153
          ExplicitHeight = 454
          inherited MotorGB: TGroupBox
            Height = 454
            Align = alLeft
            Constraints.MaxHeight = 454
            ExplicitHeight = 454
            inherited StatusGB: TGroupBox
              Top = 370
              ExplicitTop = 370
            end
            inherited JoggingGB: TGroupBox
              Top = 278
              ExplicitTop = 278
              inherited mFwdBtn: TButton
                OnMouseDown = nil
              end
              inherited mRewBtn: TButton
                OnMouseDown = nil
              end
              inherited mJogVelocity: mtkFloatLabeledEdit
                OnKeyDown = nil
              end
            end
          end
          inherited mMotorStatusTimer: TTimer
            Left = 184
            Top = 120
          end
          inherited ActionList1: TActionList
            Left = 216
            Top = 216
          end
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'JoyStick'
        ImageIndex = 2
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
      OnExecute = addDevicesToListBoxExecute
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
    OnTimer = StatusTimerTimer
    Left = 112
    Top = 592
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 192
    Top = 592
  end
end
