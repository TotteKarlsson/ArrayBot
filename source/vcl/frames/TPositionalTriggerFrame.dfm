object PositionalTriggerFrame: TPositionalTriggerFrame
  Left = 0
  Top = 0
  Width = 789
  Height = 624
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
    Width = 789
    Height = 520
    Align = alClient
    Caption = 'Child Device'
    TabOrder = 0
    ExplicitLeft = 2
    ExplicitTop = 129
    ExplicitWidth = 785
    ExplicitHeight = 493
    object GroupBox2: TGroupBox
      Left = 2
      Top = 56
      Width = 785
      Height = 169
      Align = alTop
      Caption = 'Move Parameters'
      TabOrder = 1
      ExplicitWidth = 781
      object mNewVelE: TFloatLabeledEdit
        Left = 7
        Top = 120
        Width = 121
        Height = 31
        EditLabel.Width = 106
        EditLabel.Height = 23
        EditLabel.Caption = 'New Velocity'
        TabOrder = 1
        Text = '0.0'
        OnKeyDown = mNewVelEKeyDown
      end
      object mNewAccE: TFloatLabeledEdit
        Left = 145
        Top = 120
        Width = 121
        Height = 31
        EditLabel.Width = 144
        EditLabel.Height = 23
        EditLabel.Caption = 'New Acceleration'
        TabOrder = 2
        Text = '0.0'
        OnKeyDown = mNewVelEKeyDown
      end
      object mFinalPositionE: TFloatLabeledEdit
        Left = 7
        Top = 56
        Width = 121
        Height = 31
        EditLabel.Width = 108
        EditLabel.Height = 23
        EditLabel.Caption = 'Final Position'
        TabOrder = 0
        Text = '0.0'
        OnKeyDown = mNewVelEKeyDown
      end
    end
    object mDevicesCB: TComboBox
      Left = 2
      Top = 25
      Width = 785
      Height = 31
      Align = alTop
      TabOrder = 0
      Text = 'ComboBox1'
      OnChange = mDevicesCBChange
      ExplicitWidth = 781
    end
  end
  object GroupBox4: TGroupBox
    Left = 0
    Top = 0
    Width = 789
    Height = 104
    Align = alTop
    BiDiMode = bdLeftToRight
    Caption = 'Trigger Condition'
    ParentBiDiMode = False
    TabOrder = 1
    ExplicitLeft = 2
    ExplicitTop = 25
    ExplicitWidth = 785
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
