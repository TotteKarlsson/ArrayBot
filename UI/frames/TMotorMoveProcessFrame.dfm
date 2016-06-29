object MotorMoveProcessFrame: TMotorMoveProcessFrame
  Left = 0
  Top = 0
  Width = 225
  Height = 207
  AutoSize = True
  TabOrder = 0
  object MainGB: TGroupBox
    Left = 0
    Top = 0
    Width = 225
    Height = 207
    Caption = 'Motor Move Process'
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 20
      Width = 28
      Height = 13
      Caption = 'Motor'
    end
    object mMovePosE: TFloatLabeledEdit
      Left = 16
      Top = 79
      Width = 49
      Height = 21
      EditLabel.Width = 89
      EditLabel.Height = 13
      EditLabel.Caption = 'Final Position (mm)'
      TabOrder = 0
      Text = '0.0'
    end
    object mMaxVelE: TFloatLabeledEdit
      Left = 16
      Top = 127
      Width = 65
      Height = 21
      EditLabel.Width = 60
      EditLabel.Height = 13
      EditLabel.Caption = 'Max Velocity'
      TabOrder = 1
      Text = '0.0'
    end
    object mAccE: TFloatLabeledEdit
      Left = 119
      Top = 127
      Width = 65
      Height = 21
      EditLabel.Width = 59
      EditLabel.Height = 13
      EditLabel.Caption = 'Acceleration'
      TabOrder = 2
      Text = '0.0'
    end
    object mPostDwellTimeE: TFloatLabeledEdit
      Left = 119
      Top = 167
      Width = 65
      Height = 21
      EditLabel.Width = 98
      EditLabel.Height = 13
      EditLabel.Caption = 'Post Dwell Time (ms)'
      TabOrder = 3
      Text = '0.0'
    end
    object MotorsCB: TComboBox
      Left = 16
      Top = 39
      Width = 169
      Height = 21
      TabOrder = 4
      Text = 'Select Motor'
    end
    object mPreDwellTimeE: TFloatLabeledEdit
      Left = 16
      Top = 167
      Width = 65
      Height = 21
      EditLabel.Width = 93
      EditLabel.Height = 13
      EditLabel.Caption = 'Pre Dwell Time (ms)'
      TabOrder = 5
      Text = '0.0'
    end
  end
end
