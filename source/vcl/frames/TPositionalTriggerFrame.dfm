object PositionalTriggerFrame: TPositionalTriggerFrame
  Left = 0
  Top = 0
  Width = 509
  Height = 329
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
    Width = 509
    Height = 329
    Align = alClient
    BiDiMode = bdLeftToRight
    Caption = 'Positional Trigger'
    ParentBiDiMode = False
    TabOrder = 0
    object GroupBox3: TGroupBox
      Left = 2
      Top = 123
      Width = 505
      Height = 204
      Align = alClient
      Caption = 'Device to Trigger'
      TabOrder = 0
      object GroupBox2: TGroupBox
        Left = 15
        Top = 64
        Width = 482
        Height = 129
        Caption = 'Trigger Parameters'
        TabOrder = 0
        object mNewVelE: TFloatLabeledEdit
          Left = 153
          Top = 56
          Width = 121
          Height = 31
          EditLabel.Width = 106
          EditLabel.Height = 23
          EditLabel.Caption = 'New Velocity'
          TabOrder = 0
          Text = '0.0'
          OnKeyDown = mNewVelEKeyDown
        end
        object mNewAccE: TFloatLabeledEdit
          Left = 305
          Top = 56
          Width = 121
          Height = 31
          EditLabel.Width = 144
          EditLabel.Height = 23
          EditLabel.Caption = 'New Acceleration'
          TabOrder = 1
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
          TabOrder = 2
          Text = '0.0'
          OnKeyDown = mNewVelEKeyDown
        end
      end
      object mDevicesCB: TComboBox
        Left = 15
        Top = 27
        Width = 313
        Height = 31
        TabOrder = 1
        Text = 'ComboBox1'
        OnChange = mDevicesCBChange
      end
    end
    object GroupBox4: TGroupBox
      Left = 2
      Top = 25
      Width = 505
      Height = 98
      Align = alTop
      BiDiMode = bdLeftToRight
      Caption = 'Condition'
      ParentBiDiMode = False
      TabOrder = 1
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
        Left = 144
        Top = 27
        Width = 342
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
end
