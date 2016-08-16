object RibbonLifterFrame: TRibbonLifterFrame
  Left = 0
  Top = 0
  Width = 608
  Height = 421
  TabOrder = 0
  object GroupBox2: TGroupBox
    Left = 16
    Top = 183
    Width = 321
    Height = 210
    Caption = 'Lift Parameters'
    TabOrder = 0
    object mInitialLiftSpeedZE: TFloatLabeledEdit
      Left = 16
      Top = 40
      Width = 57
      Height = 21
      EditLabel.Width = 86
      EditLabel.Height = 13
      EditLabel.Caption = 'Initial Lift Speed Z'
      TabOrder = 0
      Text = '0.0'
    end
    object mInitialLiftAccZE: TFloatLabeledEdit
      Left = 111
      Top = 40
      Width = 57
      Height = 21
      EditLabel.Width = 115
      EditLabel.Height = 13
      EditLabel.Caption = 'Initial Lift Acceleration Z'
      TabOrder = 1
      Text = '0.0'
    end
    object mWhiskerLiftOffZPositionE: TFloatLabeledEdit
      Left = 16
      Top = 120
      Width = 152
      Height = 21
      EditLabel.Width = 124
      EditLabel.Height = 13
      EditLabel.Caption = 'Whisker Lift Off Z Position'
      TabOrder = 2
      Text = '0.0'
    end
    object mMove2Btn: TButton
      Left = 224
      Top = 155
      Width = 75
      Height = 38
      Caption = 'Test'
      TabOrder = 3
      OnClick = mMove2BtnClick
    end
    object mWhiskerXLiftStowPosW: TFloatLabeledEdit
      Left = 16
      Top = 168
      Width = 152
      Height = 21
      EditLabel.Width = 114
      EditLabel.Height = 13
      EditLabel.Caption = 'Whisker X Stow Position'
      TabOrder = 4
      Text = '0.0'
    end
    object mInitialLiftSpeedYE: TFloatLabeledEdit
      Left = 16
      Top = 80
      Width = 57
      Height = 21
      EditLabel.Width = 86
      EditLabel.Height = 13
      EditLabel.Caption = 'Initial Lift Speed Y'
      TabOrder = 5
      Text = '0.0'
    end
    object mInitialLiftAccYE: TFloatLabeledEdit
      Left = 111
      Top = 80
      Width = 57
      Height = 21
      EditLabel.Width = 115
      EditLabel.Height = 13
      EditLabel.Caption = 'Initial Lift Acceleration Y'
      TabOrder = 6
      Text = '0.0'
    end
    object mLiftDistanceCSE: TFloatLabeledEdit
      Left = 242
      Top = 88
      Width = 57
      Height = 21
      EditLabel.Width = 75
      EditLabel.Height = 13
      EditLabel.Caption = 'CS Lift Distance'
      TabOrder = 7
      Text = '0.0'
    end
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 24
    Width = 321
    Height = 137
    Caption = 'Move Ribbon to Pickup Location'
    TabOrder = 1
    object mRunningLbl: TLabel
      Left = 224
      Top = 114
      Width = 3
      Height = 13
    end
    object mLiftLocationXE: TFloatLabeledEdit
      Left = 16
      Top = 48
      Width = 57
      Height = 21
      EditLabel.Width = 67
      EditLabel.Height = 13
      EditLabel.Caption = 'Lift Location X'
      TabOrder = 0
      Text = '0.0'
    end
    object mLiftLocationYE: TFloatLabeledEdit
      Left = 111
      Top = 48
      Width = 57
      Height = 21
      EditLabel.Width = 67
      EditLabel.Height = 13
      EditLabel.Caption = 'Lift Location Y'
      TabOrder = 1
      Text = '0.0'
    end
    object mMoveToPickupLocationSpeedE: TFloatLabeledEdit
      Left = 16
      Top = 96
      Width = 57
      Height = 21
      EditLabel.Width = 74
      EditLabel.Height = 13
      EditLabel.Caption = 'Move To Speed'
      TabOrder = 2
      Text = '0.0'
    end
    object mMoveToPickupLocationAccE: TFloatLabeledEdit
      Left = 111
      Top = 96
      Width = 57
      Height = 21
      EditLabel.Width = 95
      EditLabel.Height = 13
      EditLabel.Caption = 'Move To Acc/DeAcc'
      TabOrder = 3
      Text = '0.0'
    end
    object mMove1Btn: TButton
      Left = 224
      Top = 88
      Width = 75
      Height = 38
      Caption = 'Test'
      TabOrder = 4
      OnClick = mMove1BtnClick
    end
  end
  object mMoveTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = mMoveTimerTimer
    Left = 264
    Top = 56
  end
end
