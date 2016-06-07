object MotorFrame: TMotorFrame
  Left = 0
  Top = 0
  Width = 293
  Height = 292
  TabOrder = 0
  OnMouseUp = BtnUp
  object MotorGB: TGroupBox
    Left = 0
    Top = 0
    Width = 288
    Height = 272
    Caption = 'Motor'
    Constraints.MaxHeight = 272
    Constraints.MaxWidth = 288
    Constraints.MinHeight = 272
    Constraints.MinWidth = 288
    TabOrder = 0
    object Label4: TLabel
      Left = 141
      Top = 62
      Width = 97
      Height = 13
      Caption = 'Jog Velocity (mm/s):'
    end
    object Label5: TLabel
      Left = 157
      Top = 77
      Width = 81
      Height = 13
      Caption = 'Jog Acc. (mm/s):'
    end
    object mJogVelLbl: mtkFloatLabel
      Left = 244
      Top = 62
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
    object mJogAccLbl: mtkFloatLabel
      Left = 244
      Top = 77
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
    object StatusGB: TGroupBox
      Left = 2
      Top = 188
      Width = 284
      Height = 82
      Align = alBottom
      Caption = 'Status'
      TabOrder = 0
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
        Left = 17
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
    end
    object mMotorPositionE: TFloatLabeledEdit
      Left = 168
      Top = 29
      Width = 102
      Height = 27
      EditLabel.Width = 64
      EditLabel.Height = 13
      EditLabel.Caption = 'Position (mm)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Text = '0.00'
      OnKeyDown = mMotorPositionEKeyDown
      OnKeyUp = mMotorPositionEKeyUp
    end
    object Button1: TButton
      Left = 16
      Top = 18
      Width = 55
      Height = 28
      Action = identify
      TabOrder = 2
    end
    object JoggingGB: TGroupBox
      Left = 2
      Top = 96
      Width = 284
      Height = 92
      Align = alBottom
      Caption = 'Jogging'
      TabOrder = 3
      object mFwdBtn: TButton
        Left = 10
        Top = 59
        Width = 47
        Height = 25
        Caption = 'Fwd'
        TabOrder = 0
        OnMouseDown = BtnDown
        OnMouseUp = BtnUp
      end
      object mRewBtn: TButton
        Left = 70
        Top = 59
        Width = 44
        Height = 25
        Caption = 'Rev'
        TabOrder = 1
        OnMouseDown = BtnDown
        OnMouseUp = BtnUp
      end
      object mJogAcc: TFloatLabeledEdit
        Left = 98
        Top = 32
        Width = 66
        Height = 21
        EditLabel.Width = 114
        EditLabel.Height = 13
        EditLabel.Caption = 'Acceleration (mm/(s*s))'
        TabOrder = 2
        Text = '0.00'
        OnKeyDown = DevEdit
      end
      object mJogVelocity: TFloatLabeledEdit
        Left = 10
        Top = 32
        Width = 66
        Height = 21
        EditLabel.Width = 73
        EditLabel.Height = 13
        EditLabel.Caption = 'Velocity (mm/s)'
        TabOrder = 3
        Text = '0.00'
        OnKeyDown = DevEdit
      end
      object mPotentiometerSettingE: TFloatLabeledEdit
        Left = 170
        Top = 63
        Width = 66
        Height = 21
        EditLabel.Width = 96
        EditLabel.Height = 13
        EditLabel.Caption = 'Pot. Velocity (mm/s)'
        TabOrder = 4
        Text = '0.00'
        OnKeyDown = DevEdit
      end
    end
    object Button4: TButton
      Left = 77
      Top = 18
      Width = 55
      Height = 28
      Action = home
      TabOrder = 4
    end
    object EnableDisableBtn: TButton
      Left = 16
      Top = 52
      Width = 55
      Height = 28
      Caption = 'EnableBtn'
      TabOrder = 5
      OnClick = EnableDisableBtnClick
    end
    object StopBtn: TButton
      Left = 77
      Top = 52
      Width = 55
      Height = 28
      Caption = 'Stop'
      TabOrder = 6
      OnClick = StopBtnClick
    end
  end
  object mMotorStatusTimer: TTimer
    Enabled = False
    Interval = 250
    OnTimer = mMotorStatusTimerTimer
    Left = 240
    Top = 248
  end
  object ActionList1: TActionList
    Left = 24
    Top = 280
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
