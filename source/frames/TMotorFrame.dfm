object MotorFrame: TMotorFrame
  Left = 0
  Top = 0
  Width = 297
  Height = 417
  AutoSize = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  OnMouseUp = BtnUp
  object MotorGB: TGroupBox
    Left = 0
    Top = 0
    Width = 297
    Height = 417
    Caption = 'Motor'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object StatusGB: TGroupBox
      Left = 2
      Top = 330
      Width = 293
      Height = 85
      Align = alBottom
      Caption = 'Status'
      TabOrder = 2
      object Label1: TLabel
        Left = 10
        Top = 23
        Width = 49
        Height = 13
        Caption = 'Is Active: '
      end
      object Label2: TLabel
        Left = 162
        Top = 23
        Width = 51
        Height = 13
        Caption = 'Is Homing:'
      end
      object Label3: TLabel
        Left = 10
        Top = 36
        Width = 52
        Height = 13
        Caption = 'Is Homed: '
      end
      object Lbl: TLabel
        Left = 162
        Top = 36
        Width = 70
        Height = 13
        Caption = 'Is Forwarding:'
      end
      object Lbl2: TLabel
        Left = 162
        Top = 49
        Width = 64
        Height = 13
        Caption = 'Is Reversing:'
      end
      object mIsActiveLabel: TLabel
        Left = 72
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
        Left = 72
        Top = 36
        Width = 18
        Height = 13
        Caption = 'N/A'
        Color = clBtnFace
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentColor = False
        ParentFont = False
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
      object Label6: TLabel
        Left = 10
        Top = 49
        Width = 57
        Height = 13
        Caption = 'Is Enabled: '
      end
      object mIsEnabledLbl: TLabel
        Left = 72
        Top = 49
        Width = 18
        Height = 13
        Caption = 'N/A'
      end
      object Label4: TLabel
        Left = 7
        Top = 61
        Width = 61
        Height = 13
        Caption = 'Jog Velocity:'
      end
      object Label5: TLabel
        Left = 162
        Top = 61
        Width = 45
        Height = 13
        Caption = 'Jog Acc.:'
      end
      object mJogAccLbl: mtkFloatLabel
        Left = 236
        Top = 61
        Width = 26
        Height = 13
        Caption = '-1.00'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ValueString = '-1.00'
        Value = -1.000000000000000000
        TheFont.Charset = DEFAULT_CHARSET
        TheFont.Color = clWindowText
        TheFont.Height = -11
        TheFont.Name = 'Tahoma'
        TheFont.Style = []
      end
      object mJogVelLbl: mtkFloatLabel
        Left = 72
        Top = 61
        Width = 26
        Height = 13
        Caption = '-1.00'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ValueString = '-1.00'
        Value = -1.000000000000000000
        TheFont.Charset = DEFAULT_CHARSET
        TheFont.Color = clWindowText
        TheFont.Height = -11
        TheFont.Name = 'Tahoma'
        TheFont.Style = []
      end
    end
    object mMotorPositionE: TFloatLabeledEdit
      Left = 154
      Top = 37
      Width = 136
      Height = 36
      EditLabel.Width = 77
      EditLabel.Height = 13
      EditLabel.Caption = 'Current Position'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -20
      Font.Name = 'Segoe UI'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      Text = '0.00'
      OnKeyDown = mMotorPositionEKeyDown
      OnKeyUp = mMotorPositionEKeyUp
    end
    object Button1: TButton
      Left = 13
      Top = 18
      Width = 60
      Height = 40
      Action = identify
      TabOrder = 0
    end
    object JoggingGB: TGroupBox
      Left = 2
      Top = 256
      Width = 293
      Height = 74
      Align = alBottom
      Caption = 'Jogging'
      TabOrder = 3
      object mFwdBtn: TButton
        Left = 162
        Top = 19
        Width = 60
        Height = 40
        Caption = 'Fwd'
        TabOrder = 2
        OnMouseDown = BtnDown
        OnMouseUp = BtnUp
      end
      object mRewBtn: TButton
        Left = 228
        Top = 19
        Width = 60
        Height = 40
        Caption = 'Rev'
        TabOrder = 3
        OnMouseDown = BtnDown
        OnMouseUp = BtnUp
      end
      object mJogAcc: TFloatLabeledEdit
        Left = 80
        Top = 35
        Width = 55
        Height = 21
        EditLabel.Width = 59
        EditLabel.Height = 13
        EditLabel.Caption = 'Acceleration'
        TabOrder = 1
        Text = '0.00'
        OnKeyDown = DevEdit
      end
      object mJogVelocity: TFloatLabeledEdit
        Left = 10
        Top = 35
        Width = 56
        Height = 21
        EditLabel.Width = 37
        EditLabel.Height = 13
        EditLabel.Caption = 'Velocity'
        TabOrder = 0
        Text = '0.00'
        OnKeyDown = DevEdit
      end
    end
    object GroupBox1: TGroupBox
      Left = 2
      Top = 192
      Width = 293
      Height = 64
      Align = alBottom
      Caption = 'Range && Limits (mm)'
      TabOrder = 4
      object mPositionRangeMaxE: TFloatLabeledEdit
        Left = 10
        Top = 34
        Width = 52
        Height = 21
        EditLabel.Width = 60
        EditLabel.Height = 13
        EditLabel.Caption = 'Max Position'
        TabOrder = 0
        Text = '-1.00'
        Value = -1.000000000000000000
      end
      object mMinPositionLimitE: TFloatLabeledEdit
        Left = 113
        Top = 34
        Width = 59
        Height = 21
        EditLabel.Width = 80
        EditLabel.Height = 13
        EditLabel.Caption = 'Min Position Limit'
        TabOrder = 1
        Text = '-1.00'
        Value = -1.000000000000000000
      end
      object mMaxPositionLimitE: TFloatLabeledEdit
        Left = 201
        Top = 34
        Width = 76
        Height = 21
        EditLabel.Width = 84
        EditLabel.Height = 13
        EditLabel.Caption = 'Max Position Limit'
        TabOrder = 2
        Text = '-1.00'
        Value = -1.000000000000000000
      end
    end
    object MiscGB: TGroupBox
      Left = 2
      Top = 120
      Width = 293
      Height = 72
      Align = alBottom
      Caption = 'Misc.'
      TabOrder = 5
      object mPotentiometerSettingE: TFloatLabeledEdit
        Left = 10
        Top = 34
        Width = 61
        Height = 21
        EditLabel.Width = 60
        EditLabel.Height = 13
        EditLabel.Caption = 'Pot. Velocity'
        TabOrder = 0
        Text = '0.00'
        OnKeyDown = DevEdit
      end
      object Button4: TButton
        Left = 86
        Top = 20
        Width = 60
        Height = 40
        Action = home
        TabOrder = 1
      end
      object StopBtn: TButton
        Left = 152
        Top = 20
        Width = 136
        Height = 40
        Caption = 'Stop'
        TabOrder = 2
        OnClick = StopBtnClick
      end
    end
    object EnableDisableBtn: TButton
      Left = 13
      Top = 74
      Width = 60
      Height = 40
      Caption = 'EnableBtn'
      TabOrder = 6
      OnClick = EnableDisableBtnClick
    end
    object mEnableDisableLimits: TPropertyCheckBox
      Left = 154
      Top = 79
      Width = 110
      Height = 41
      Caption = 'Enable or Disable Position Limits'
      TabOrder = 7
      WordWrap = True
      OnClick = mEnableDisableLimitsClick
    end
  end
  object mMotorStatusTimer: TTimer
    Enabled = False
    Interval = 250
    OnTimer = mMotorStatusTimerTimer
    Left = 120
    Top = 328
  end
  object ActionList1: TActionList
    Left = 120
    Top = 288
    object identify: TAction
      Caption = 'Identify'
      OnExecute = identifyExecute
    end
    object home: TAction
      Caption = 'Home'
      OnExecute = homeExecute
    end
  end
end
