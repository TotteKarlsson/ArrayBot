object MotorMoveProcessFrame: TMotorMoveProcessFrame
  Left = 0
  Top = 0
  Width = 385
  Height = 313
  AutoSize = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object MainGB: TGroupBox
    Left = 0
    Top = 0
    Width = 385
    Height = 313
    Caption = 'Motor'
    TabOrder = 0
    object mMovePosE: TFloatLabeledEdit
      Left = 16
      Top = 127
      Width = 49
      Height = 31
      EditLabel.Width = 160
      EditLabel.Height = 23
      EditLabel.Caption = 'Final Position (mm)'
      Enabled = False
      TabOrder = 0
      Text = '0.0'
      OnKeyDown = mMovePosEKeyDown
    end
    object mMaxVelE: TFloatLabeledEdit
      Left = 16
      Top = 195
      Width = 65
      Height = 31
      EditLabel.Width = 103
      EditLabel.Height = 23
      EditLabel.Caption = 'Max Velocity'
      Enabled = False
      TabOrder = 1
      Text = '0.0'
      OnKeyDown = mMovePosEKeyDown
    end
    object mAccE: TFloatLabeledEdit
      Left = 191
      Top = 195
      Width = 65
      Height = 31
      EditLabel.Width = 101
      EditLabel.Height = 23
      EditLabel.Caption = 'Acceleration'
      Enabled = False
      TabOrder = 2
      Text = '0.0'
      OnKeyDown = mMovePosEKeyDown
    end
    object mPostDwellTimeE: TFloatLabeledEdit
      Left = 191
      Top = 264
      Width = 65
      Height = 31
      EditLabel.Width = 176
      EditLabel.Height = 23
      EditLabel.Caption = 'Post Dwell Time (ms)'
      Enabled = False
      TabOrder = 3
      Text = '0.0'
      OnKeyDown = mMovePosEKeyDown
    end
    object MotorsCB: TComboBox
      Left = 16
      Top = 49
      Width = 240
      Height = 31
      Style = csDropDownList
      TabOrder = 4
      OnChange = MotorsCBChange
      OnClick = MotorsCBClick
    end
    object mPreDwellTimeE: TFloatLabeledEdit
      Left = 16
      Top = 264
      Width = 65
      Height = 31
      EditLabel.Width = 169
      EditLabel.Height = 23
      EditLabel.Caption = 'Pre Dwell Time (ms)'
      Enabled = False
      TabOrder = 5
      Text = '0.0'
      OnKeyDown = mMovePosEKeyDown
    end
  end
end
