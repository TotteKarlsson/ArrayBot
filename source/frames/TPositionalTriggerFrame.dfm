object PositionalTriggerFrame: TPositionalTriggerFrame
  Left = 0
  Top = 0
  Width = 424
  Height = 267
  Constraints.MinHeight = 267
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object GroupBox3: TGroupBox
    Left = 0
    Top = 104
    Width = 424
    Height = 163
    Align = alClient
    Caption = 'Child Action Properties'
    TabOrder = 1
    ExplicitWidth = 591
    ExplicitHeight = 330
    object mDevicesCB: TComboBox
      Left = 15
      Top = 44
      Width = 300
      Height = 31
      Constraints.MaxWidth = 300
      TabOrder = 0
      Text = 'ComboBox1'
      OnChange = mDevicesCBChange
    end
    object mFinalPositionE: TFloatLabeledEdit
      Left = 15
      Top = 120
      Width = 121
      Height = 31
      EditLabel.Width = 108
      EditLabel.Height = 23
      EditLabel.Caption = 'Final Position'
      TabOrder = 1
      Text = '0.0'
      OnKeyDown = mNewVelEKeyDown
    end
    object mNewAccE: TFloatLabeledEdit
      Left = 280
      Top = 120
      Width = 121
      Height = 31
      EditLabel.Width = 101
      EditLabel.Height = 23
      EditLabel.Caption = 'Acceleration'
      TabOrder = 3
      Text = '0.0'
      OnKeyDown = mNewVelEKeyDown
    end
    object mNewVelE: TFloatLabeledEdit
      Left = 147
      Top = 120
      Width = 121
      Height = 31
      EditLabel.Width = 63
      EditLabel.Height = 23
      EditLabel.Caption = 'Velocity'
      TabOrder = 2
      Text = '0.0'
      OnKeyDown = mNewVelEKeyDown
    end
  end
  object GroupBox4: TGroupBox
    Left = 0
    Top = 0
    Width = 424
    Height = 104
    Align = alTop
    BiDiMode = bdLeftToRight
    Caption = 'Trigger Condition'
    ParentBiDiMode = False
    TabOrder = 0
    ExplicitWidth = 591
    object mPositionE: TFloatLabeledEdit
      Left = 22
      Top = 59
      Width = 99
      Height = 31
      EditLabel.Width = 63
      EditLabel.Height = 23
      EditLabel.Caption = 'Position'
      TabOrder = 0
      Text = '0.0'
      OnKeyDown = mPositionEKeyDown
    end
    object mOpRG: TRadioGroup
      Left = 147
      Top = 25
      Width = 266
      Height = 65
      Caption = 'Operator'
      Columns = 4
      ItemIndex = 0
      Items.Strings = (
        '>'
        '<'
        '>='
        '<=')
      TabOrder = 1
      OnClick = mOpRGClick
    end
  end
end
