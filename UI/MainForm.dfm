object Main: TMain
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'ArrayBot Version 0.5.8'
  ClientHeight = 919
  ClientWidth = 1103
  Color = clBtnFace
  Constraints.MinHeight = 900
  Constraints.MinWidth = 1100
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
    Left = 920
    Top = 0
    Width = 183
    Height = 919
    Align = alRight
    TabOrder = 0
    OnDblClick = mButtonPanelDblClick
    object mJSCSBtn: TSpeedButton
      Left = 1
      Top = 1
      Width = 181
      Height = 138
      Align = alTop
      AllowAllUp = True
      Caption = 'Enable JS'
      OnClick = JSControlClick
      ExplicitLeft = 6
      ExplicitTop = 347
    end
    object BottomBtnPanel: TPanel
      Left = 1
      Top = 666
      Width = 181
      Height = 252
      Align = alBottom
      AutoSize = True
      TabOrder = 0
      object Button5: TArrayBotButton
        Left = 1
        Top = 126
        Width = 179
        Height = 125
        Action = FileExit1
        Align = alBottom
        Caption = 'E&xit'
        TabOrder = 0
        SoundID = 'BUTTON_CLICK_4'
      end
      object Button7: TArrayBotButton
        Left = 1
        Top = 1
        Width = 179
        Height = 125
        Action = stopAllA
        Align = alBottom
        BiDiMode = bdLeftToRight
        Caption = 'Stop All'
        ParentBiDiMode = False
        TabOrder = 1
        SoundID = 'BUTTON_CLICK_4'
      end
    end
  end
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 920
    Height = 919
    Align = alClient
    Constraints.MinHeight = 348
    Constraints.MinWidth = 670
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 918
      Height = 917
      ActivePage = mFrontPage
      Align = alClient
      TabHeight = 60
      TabOrder = 0
      TabWidth = 150
      OnChange = PageControl1Change
      object mFrontPage: TTabSheet
        Caption = 'The Bot'
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object mBottomPanel: TPanel
          Left = 0
          Top = 680
          Width = 910
          Height = 167
          Align = alBottom
          TabOrder = 0
          object GroupBox2: TGroupBox
            Left = 1
            Top = 1
            Width = 269
            Height = 165
            Align = alLeft
            Caption = 'Section Count'
            TabOrder = 0
            object mSectionCountLbl: TIntLabel
              Left = 32
              Top = 40
              Width = 17
              Height = 23
              Caption = '-1'
              ValueString = '-1'
              Value = -1
              TheFont.Charset = DEFAULT_CHARSET
              TheFont.Color = clWindowText
              TheFont.Height = -19
              TheFont.Name = 'Tahoma'
              TheFont.Style = []
            end
            object mResetCountBtn: TArrayBotButton
              Left = 104
              Top = 35
              Width = 153
              Height = 100
              Caption = 'Reset'
              ParentDoubleBuffered = True
              TabOrder = 0
              OnClick = mResetCountBtnClick
              SoundID = 'BUTTON_CLICK_4'
            end
          end
          object GroupBox4: TGroupBox
            Left = 270
            Top = 1
            Width = 303
            Height = 165
            Align = alLeft
            Caption = 'Ribbon Length Control'
            TabOrder = 1
            object mRibbonLengthE: TIntegerLabeledEdit
              Left = 152
              Top = 50
              Width = 129
              Height = 31
              EditLabel.Width = 123
              EditLabel.Height = 23
              EditLabel.Caption = 'Ribbon Length'
              TabOrder = 0
              Text = '-1'
              OnKeyDown = mRibbonLengthEKeyDown
              Value = -1
            end
            object mAutoPuffCB: TPropertyCheckBox
              Left = 16
              Top = 57
              Width = 97
              Height = 17
              Caption = 'Enabled'
              TabOrder = 1
              OnClick = mAutoPuffCBClick
            end
          end
          object GroupBox5: TGroupBox
            Left = 573
            Top = 1
            Width = 314
            Height = 165
            Align = alLeft
            Caption = 'Misc. Puffer'
            TabOrder = 2
            object mPuffBtn: TArrayBotButton
              Left = 24
              Top = 43
              Width = 100
              Height = 75
              Caption = 'Puff'
              ParentDoubleBuffered = True
              TabOrder = 0
              OnClick = mResetCountBtnClick
              SoundID = 'BUTTON_CLICK_4'
            end
            object mEnablePuffBtn: TArrayBotButton
              Left = 151
              Top = 43
              Width = 150
              Height = 75
              Caption = 'Enable Puffer'
              ParentDoubleBuffered = True
              TabOrder = 1
              OnClick = mResetCountBtnClick
              SoundID = 'BUTTON_CLICK_4'
            end
          end
        end
        object mTopPanel: TPanel
          Left = 0
          Top = 0
          Width = 910
          Height = 91
          Align = alTop
          AutoSize = True
          TabOrder = 1
        end
        object mMiddlePanel: TPanel
          Left = 0
          Top = 91
          Width = 910
          Height = 589
          Align = alClient
          AutoSize = True
          TabOrder = 2
          object JSGB: TGroupBox
            Left = 1
            Top = 1
            Width = 461
            Height = 587
            Align = alLeft
            Caption = 'Joystick'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -21
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            object mXYCtrlRG: TRadioGroup
              Left = 2
              Top = 137
              Width = 457
              Height = 112
              Align = alTop
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
            object mUnitControlRG: TRadioGroup
              Left = 2
              Top = 27
              Width = 457
              Height = 110
              Align = alTop
              Caption = 'Unit Control'
              Columns = 4
              DoubleBuffered = False
              ItemIndex = 0
              Items.Strings = (
                'Both'
                'Coverslip'
                'Whisker'
                'None')
              ParentDoubleBuffered = False
              TabOrder = 1
              OnClick = mUnitControlRGClick
            end
            object Panel2: TPanel
              Left = 2
              Top = 249
              Width = 457
              Height = 100
              Align = alTop
              TabOrder = 2
              object mJSSpeedFastBtn: TSpeedButton
                Left = 301
                Top = 1
                Width = 150
                Height = 98
                Align = alLeft
                GroupIndex = 15
                Caption = 'Fast'
                OnClick = JSSpeedBtnClick
                ExplicitTop = 6
              end
              object mJSSpeedMediumBtn: TSpeedButton
                Left = 151
                Top = 1
                Width = 150
                Height = 98
                Align = alLeft
                GroupIndex = 15
                Down = True
                Caption = 'Medium'
                OnClick = JSSpeedBtnClick
                ExplicitLeft = 1
                ExplicitTop = 6
              end
              object mJSSpeedSlowBtn: TSpeedButton
                Left = 1
                Top = 1
                Width = 150
                Height = 98
                Align = alLeft
                GroupIndex = 15
                Caption = 'Slow'
                OnClick = JSSpeedBtnClick
                ExplicitLeft = -65
                ExplicitTop = 6
              end
            end
          end
          object LiftGB: TGroupBox
            Left = 462
            Top = 1
            Width = 447
            Height = 587
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
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
      end
      object TabSheet1: TTabSheet
        Caption = 'Motors'
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object ScrollBox1: TScrollBox
          Left = 0
          Top = 0
          Width = 910
          Height = 742
          HorzScrollBar.Smooth = True
          VertScrollBar.Tracking = True
          Align = alClient
          BorderStyle = bsNone
          Padding.Left = 5
          Padding.Top = 5
          Padding.Right = 5
          Padding.Bottom = 5
          TabOrder = 0
        end
        object Panel1: TPanel
          Left = 0
          Top = 742
          Width = 910
          Height = 105
          Align = alBottom
          TabOrder = 1
          object mCheckDevicesBtn: TBitBtn
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
        Caption = 'Sequences'
        ImageIndex = 4
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
      end
      object TabSheet2: TTabSheet
        Caption = 'Settings'
        ImageIndex = 2
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object mJSStatusL: TLabel
          Left = 455
          Top = 192
          Width = 96
          Height = 23
          Caption = 'mJSStatusL'
        end
        object JoyStickGB2: TGroupBox
          Left = 11
          Top = 24
          Width = 422
          Height = 345
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
          Top = 24
          Width = 186
          Height = 153
          Caption = 'JoyStick'
          ItemIndex = 0
          Items.Strings = (
            'Blue'
            'White')
          TabOrder = 1
          OnClick = mJoyStickRGClick
        end
        object GroupBox1: TGroupBox
          Left = 11
          Top = 390
          Width = 257
          Height = 155
          Caption = 'Arduino Client'
          TabOrder = 2
          object mArduinoServerPortE: TIntegerLabeledEdit
            Left = 16
            Top = 56
            Width = 121
            Height = 31
            EditLabel.Width = 108
            EditLabel.Height = 23
            EditLabel.Caption = 'Network Port'
            TabOrder = 0
            Text = '50000'
            Value = 50000
          end
          object mASStartBtn: TButton
            Left = 143
            Top = 40
            Width = 104
            Height = 97
            Caption = 'Start'
            TabOrder = 1
            OnClick = mASStartBtnClick
          end
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'Logging'
        ImageIndex = 4
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object BottomPanel: TPanel
          Left = 0
          Top = 0
          Width = 910
          Height = 847
          Align = alClient
          TabOrder = 0
          object infoMemo: TMemo
            Left = 1
            Top = 31
            Width = 908
            Height = 815
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
            Width = 908
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
      object TabSheet3: TTabSheet
        Caption = 'About'
        ImageIndex = 6
        inline TAboutArrayBotFrame_21: TAboutArrayBotFrame_2
          Left = 0
          Top = 0
          Width = 910
          Height = 847
          Align = alClient
          TabOrder = 0
          ExplicitWidth = 910
          ExplicitHeight = 847
          inherited GroupBox1: TGroupBox
            Width = 910
            Height = 661
            ExplicitWidth = 910
            ExplicitHeight = 661
            inherited Memo1: TMemo
              Top = 25
              Width = 906
              Height = 634
              ExplicitTop = 25
              ExplicitWidth = 906
              ExplicitHeight = 634
            end
          end
          inherited Panel1: TPanel
            Width = 910
            ExplicitWidth = 910
            inherited Image1: TImage
              Left = 724
              ExplicitLeft = 708
            end
          end
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 140
    Top = 664
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
    Left = 660
    Top = 632
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 32
    Top = 664
  end
  object UIUpdateTimer: TTimer
    Enabled = False
    Interval = 250
    OnTimer = UIUpdateTimerTimer
    Left = 364
    Top = 664
  end
  object mLiftTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = mLiftTimerTimer
    Left = 752
    Top = 632
  end
  object WaitForDeviceInitTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = WaitForDeviceInitTimerTimer
    Left = 248
    Top = 664
  end
end
