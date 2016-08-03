object Main: TMain
  Left = 0
  Top = 0
  Caption = 'ArrayBot Version 0.5.8'
  ClientHeight = 791
  ClientWidth = 1087
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 23
  object mButtonPanel: TPanel
    Left = 904
    Top = 0
    Width = 183
    Height = 791
    Align = alRight
    TabOrder = 0
    object mAboutBtn: TSpeedButton
      Left = 1
      Top = 1
      Width = 181
      Height = 134
      Align = alTop
      AllowAllUp = True
      Caption = 'About'
      OnClick = mAboutBtnClick
      ExplicitTop = -57
      ExplicitWidth = 125
    end
    object mJSCSBtn: TSpeedButton
      Left = 1
      Top = 135
      Width = 181
      Height = 138
      Align = alTop
      AllowAllUp = True
      Caption = 'Enable JS'
      OnClick = JSControlClick
      ExplicitWidth = 125
    end
    object BottomBtnPanel: TPanel
      Left = 1
      Top = 538
      Width = 181
      Height = 252
      Align = alBottom
      AutoSize = True
      TabOrder = 0
      object Button5: TSpeedButton
        Left = 1
        Top = 126
        Width = 179
        Height = 125
        Action = FileExit1
        Align = alBottom
        ExplicitWidth = 123
      end
      object Button7: TSpeedButton
        Left = 1
        Top = 1
        Width = 179
        Height = 125
        Action = stopAllA
        Align = alBottom
        BiDiMode = bdLeftToRight
        ParentBiDiMode = False
        ExplicitWidth = 123
      end
    end
  end
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 904
    Height = 791
    Align = alClient
    Constraints.MinHeight = 348
    Constraints.MinWidth = 670
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 902
      Height = 789
      ActivePage = TabSheet2
      Align = alClient
      TabHeight = 60
      TabOrder = 0
      TabWidth = 150
      object TabSheet4: TTabSheet
        Caption = 'The Bot'
        object mBottomPanel: TPanel
          Left = 0
          Top = 552
          Width = 894
          Height = 167
          Align = alBottom
          TabOrder = 0
        end
        object mTopPanel: TPanel
          Left = 0
          Top = 0
          Width = 894
          Height = 187
          Align = alTop
          AutoSize = True
          TabOrder = 1
        end
        object mMiddlePanel: TPanel
          Left = 0
          Top = 187
          Width = 894
          Height = 365
          Align = alClient
          AutoSize = True
          TabOrder = 2
          object JSGB: TGroupBox
            Left = 1
            Top = 1
            Width = 461
            Height = 363
            Align = alLeft
            Caption = 'Joystick'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -21
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            object mJSSpeedFastBtn: TSpeedButton
              Left = 307
              Top = 44
              Width = 140
              Height = 100
              GroupIndex = 15
              Caption = 'Fast'
              OnClick = JSSpeedBtnClick
            end
            object mJSSpeedMediumBtn: TSpeedButton
              Left = 161
              Top = 44
              Width = 140
              Height = 100
              GroupIndex = 15
              Down = True
              Caption = 'Medium'
              OnClick = JSSpeedBtnClick
            end
            object mJSSpeedSlowBtn: TSpeedButton
              Left = 15
              Top = 44
              Width = 140
              Height = 100
              GroupIndex = 15
              Caption = 'Slow'
              OnClick = JSSpeedBtnClick
            end
            object mXYCtrlRG: TRadioGroup
              Left = 15
              Top = 161
              Width = 426
              Height = 105
              Caption = 'XY Control'
              Columns = 4
              ItemIndex = 0
              Items.Strings = (
                'X && Y'
                'X'
                'Y'
                'None')
              TabOrder = 0
              OnClick = mXYCtrlRGClick
            end
          end
          object LiftGB: TGroupBox
            Left = 462
            Top = 1
            Width = 431
            Height = 363
            Align = alClient
            Caption = 'Lift'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            object LiftBtn: TSpeedButton
              Left = 16
              Top = 129
              Width = 409
              Height = 136
              Action = liftA
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
            end
            object mMoveAccelerationE: TFloatLabeledEdit
              Left = 105
              Top = 92
              Width = 73
              Height = 31
              EditLabel.Width = 101
              EditLabel.Height = 23
              EditLabel.Caption = 'Acceleration'
              TabOrder = 1
              Text = '0.00'
              OnKeyDown = moveEdit
            end
            object mMoveVelocityVerticalE: TFloatLabeledEdit
              Left = 18
              Top = 92
              Width = 73
              Height = 31
              EditLabel.Width = 63
              EditLabel.Height = 23
              EditLabel.Caption = 'Velocity'
              TabOrder = 0
              Text = '0.00'
              OnKeyDown = moveEdit
            end
            object mLiftCB: TComboBox
              Left = 16
              Top = 32
              Width = 409
              Height = 31
              TabOrder = 2
              Text = '<none>'
              OnChange = mLiftCBChange
            end
          end
        end
      end
      object RibbonLifterTabSheet: TTabSheet
        Caption = 'The Pickup'
        ImageIndex = 5
        TabVisible = False
      end
      object TabSheet1: TTabSheet
        Caption = 'Motors'
        object ScrollBox1: TScrollBox
          Left = 0
          Top = 0
          Width = 894
          Height = 614
          Align = alClient
          TabOrder = 0
        end
        object Panel1: TPanel
          Left = 0
          Top = 614
          Width = 894
          Height = 105
          Align = alBottom
          TabOrder = 1
          object BitBtn1: TBitBtn
            Left = 178
            Top = 1
            Width = 176
            Height = 103
            Action = checkForDevices
            Align = alLeft
            BiDiMode = bdLeftToRight
            Caption = 'Devices Check'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 0
          end
          object ReInitBotBtn: TBitBtn
            Left = 1
            Top = 1
            Width = 177
            Height = 103
            Action = reInitBotA
            Align = alLeft
            BiDiMode = bdLeftToRight
            Caption = 'Reinitialize Devices'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 1
          end
        end
      end
      object mMoveSequencesPage: TTabSheet
        Caption = 'Move Sequences'
        ImageIndex = 4
      end
      object TabSheet2: TTabSheet
        Caption = 'Settings'
        ImageIndex = 2
        object JoyStickGB2: TGroupBox
          Left = 11
          Top = 24
          Width = 422
          Height = 417
          Caption = 'JoyStick Velocities'
          TabOrder = 0
          object mZJogAccelerationJoystick: TFloatLabeledEdit
            Left = 247
            Top = 198
            Width = 66
            Height = 31
            EditLabel.Width = 118
            EditLabel.Height = 23
            EditLabel.Caption = 'Z Acceleration'
            TabOrder = 3
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object mXYJogAccelerationJoystick: TFloatLabeledEdit
            Left = 247
            Top = 108
            Width = 66
            Height = 31
            EditLabel.Width = 129
            EditLabel.Height = 23
            EditLabel.Caption = 'XY Acceleration'
            TabOrder = 1
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object mMaxZJogVelocityJoystick: TFloatLabeledEdit
            Left = 16
            Top = 198
            Width = 66
            Height = 31
            EditLabel.Width = 120
            EditLabel.Height = 23
            EditLabel.Caption = 'Max Z Velocity'
            TabOrder = 2
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object mMaxXYJogVelocityJoystick: TFloatLabeledEdit
            Left = 16
            Top = 108
            Width = 66
            Height = 31
            EditLabel.Width = 131
            EditLabel.Height = 23
            EditLabel.Caption = 'Max XY Velocity'
            TabOrder = 0
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object JoyStickSettingsCB: TComboBox
            Left = 16
            Top = 24
            Width = 291
            Height = 31
            Style = csDropDownList
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
            OnChange = JoyStickSettingsCBChange
          end
          object AddJsSettingBtn: TButton
            Left = 313
            Top = 23
            Width = 32
            Height = 33
            Caption = '+'
            TabOrder = 7
            Visible = False
            OnClick = AddJsSettingBtnClick
          end
          object mAngleControlVelE: TFloatLabeledEdit
            Left = 16
            Top = 286
            Width = 66
            Height = 31
            EditLabel.Width = 156
            EditLabel.Height = 23
            EditLabel.Caption = 'Angle Ctrl. Velocity'
            TabOrder = 4
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
          object mAngleControllerAccE: TFloatLabeledEdit
            Left = 247
            Top = 286
            Width = 66
            Height = 31
            EditLabel.Width = 122
            EditLabel.Height = 23
            EditLabel.Caption = 'Angle Ctrl Acc.'
            TabOrder = 5
            Text = '0.00'
            OnKeyDown = JoyStickValueEdit
          end
        end
        object mJoyStickRG: TRadioGroup
          Left = 455
          Top = 32
          Width = 146
          Height = 145
          Caption = 'JoyStick'
          ItemIndex = 0
          Items.Strings = (
            'White'
            'Blue')
          TabOrder = 1
          OnClick = mJoyStickRGClick
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'Logging'
        ImageIndex = 4
        object BottomPanel: TPanel
          Left = 0
          Top = 0
          Width = 894
          Height = 719
          Align = alClient
          TabOrder = 0
          object infoMemo: TMemo
            Left = 1
            Top = 31
            Width = 892
            Height = 687
            Align = alClient
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            ScrollBars = ssBoth
            TabOrder = 0
            WordWrap = False
          end
          object ToolBar1: TToolBar
            Left = 1
            Top = 1
            Width = 892
            Height = 30
            AutoSize = True
            ButtonHeight = 30
            Caption = 'ToolBar1'
            TabOrder = 1
            object BitBtn2: TBitBtn
              Left = 0
              Top = 0
              Width = 75
              Height = 30
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
            object LogLevelCB: TComboBox
              Left = 75
              Top = 0
              Width = 145
              Height = 31
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -19
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 1
              Text = 'INFO'
              OnChange = LogLevelCBChange
              Items.Strings = (
                'INFO'
                'Everything')
            end
          end
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 436
    Top = 680
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
    object reInitBotA: TAction
      Caption = 'Reinitialize Devices'
      OnExecute = reInitBotAExecute
    end
    object ShutDownA: TAction
      Caption = 'Disconnect Devices'
      OnExecute = ShutDownAExecute
    end
    object FileExit1: TFileExit
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
    object abortLiftA: TAction
      Caption = 'Abort Lift'
      OnExecute = abortLiftAExecute
    end
    object liftA: TAction
      Caption = 'Lift'
      OnExecute = liftAExecute
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = ShutDownTimerTimer
    Left = 652
    Top = 680
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 328
    Top = 680
  end
  object UIUpdateTimer: TTimer
    Enabled = False
    Interval = 150
    Left = 220
    Top = 680
  end
  object mLiftTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = mLiftTimerTimer
    Left = 760
    Top = 680
  end
  object WaitForDeviceInitTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = WaitForDeviceInitTimerTimer
    Left = 112
    Top = 680
  end
end
