object PositionalTriggerFrame: TPositionalTriggerFrame
  Left = 0
  Top = 0
  Width = 600
  Height = 481
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 16
    Top = 32
    Width = 561
    Height = 401
    Caption = 'Positional Trigger'
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 302
      Width = 134
      Height = 23
      Caption = 'Observed motor'
    end
    object Label2: TLabel
      Left = 16
      Top = 38
      Width = 55
      Height = 23
      Caption = 'Device'
    end
    object Label3: TLabel
      Left = 192
      Top = 38
      Width = 72
      Height = 23
      Caption = 'Function'
    end
    object ComboBox1: TComboBox
      Left = 16
      Top = 331
      Width = 145
      Height = 31
      TabOrder = 0
      Text = 'ComboBox1'
    end
    object FloatLabeledEdit1: TFloatLabeledEdit
      Left = 192
      Top = 331
      Width = 129
      Height = 31
      EditLabel.Width = 130
      EditLabel.Height = 23
      EditLabel.Caption = 'Trigger Position'
      TabOrder = 1
      Text = '0.0'
    end
    object RadioGroup1: TRadioGroup
      Left = 352
      Top = 302
      Width = 129
      Height = 60
      Caption = 'Condition'
      Items.Strings = (
        '>='
        '<=')
      TabOrder = 2
    end
    object ComboBox2: TComboBox
      Left = 16
      Top = 67
      Width = 145
      Height = 31
      TabOrder = 3
      Text = 'ComboBox1'
    end
    object ComboBox3: TComboBox
      Left = 192
      Top = 67
      Width = 129
      Height = 31
      TabOrder = 4
      Text = 'ComboBox3'
    end
    object GroupBox2: TGroupBox
      Left = 352
      Top = 32
      Width = 185
      Height = 185
      Caption = 'Velocity Parameters'
      TabOrder = 5
      object mNewVelE: TFloatLabeledEdit
        Left = 24
        Top = 64
        Width = 121
        Height = 31
        EditLabel.Width = 89
        EditLabel.Height = 23
        EditLabel.Caption = 'mNewVelE'
        TabOrder = 0
        Text = '0.0'
      end
      object mNewAccE: TFloatLabeledEdit
        Left = 24
        Top = 136
        Width = 121
        Height = 31
        EditLabel.Width = 147
        EditLabel.Height = 23
        EditLabel.Caption = 'FloatLabeledEdit2'
        TabOrder = 1
        Text = '0.0'
      end
    end
  end
end
