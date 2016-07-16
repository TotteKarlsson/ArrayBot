object PositionalTriggerFrame: TPositionalTriggerFrame
  Left = 0
  Top = 0
  Width = 544
  Height = 369
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
    Width = 544
    Height = 369
    Align = alClient
    BiDiMode = bdLeftToRight
    Caption = 'Positional Trigger'
    ParentBiDiMode = False
    TabOrder = 0
    object GroupBox3: TGroupBox
      Left = 2
      Top = 147
      Width = 540
      Height = 220
      Align = alClient
      Caption = 'Device to Trigger'
      TabOrder = 0
      object Label2: TLabel
        Left = 24
        Top = 46
        Width = 55
        Height = 23
        Caption = 'Device'
      end
      object Label3: TLabel
        Left = 22
        Top = 134
        Width = 72
        Height = 23
        Caption = 'Function'
      end
      object GroupBox2: TGroupBox
        Left = 301
        Top = 22
        Width = 185
        Height = 185
        Caption = 'Velocity Parameters'
        TabOrder = 0
        object mNewVelE: TFloatLabeledEdit
          Left = 24
          Top = 64
          Width = 121
          Height = 31
          EditLabel.Width = 106
          EditLabel.Height = 23
          EditLabel.Caption = 'New Velocity'
          TabOrder = 0
          Text = '0.0'
        end
        object mNewAccE: TFloatLabeledEdit
          Left = 24
          Top = 136
          Width = 121
          Height = 31
          EditLabel.Width = 144
          EditLabel.Height = 23
          EditLabel.Caption = 'New Acceleration'
          TabOrder = 1
          Text = '0.0'
        end
      end
      object mDevicesCB: TComboBox
        Left = 22
        Top = 75
        Width = 259
        Height = 31
        TabOrder = 1
        Text = 'ComboBox1'
        OnChange = mDevicesCBChange
      end
      object ComboBox3: TComboBox
        Left = 22
        Top = 163
        Width = 259
        Height = 31
        ItemIndex = 0
        TabOrder = 2
        Text = 'Move Absolute'
        Items.Strings = (
          'Move Absolute'
          'Stop')
      end
    end
    object GroupBox4: TGroupBox
      Left = 2
      Top = 25
      Width = 540
      Height = 122
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
        Left = 168
        Top = 16
        Width = 161
        Height = 100
        Caption = 'Operator'
        Columns = 2
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
