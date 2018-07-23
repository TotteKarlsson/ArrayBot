object NavitarPresetFrame: TNavitarPresetFrame
  Left = 0
  Top = 0
  Width = 241
  Height = 88
  TabOrder = 0
  object MainGB: TGroupBox
    Left = 0
    Top = 0
    Width = 241
    Height = 88
    Align = alClient
    Caption = 'Preset Name'
    TabOrder = 0
    object ZoomPos: TIntegerLabeledEdit
      Left = 13
      Top = 44
      Width = 73
      Height = 21
      EditLabel.Width = 26
      EditLabel.Height = 13
      EditLabel.Caption = 'Zoom'
      NumbersOnly = True
      TabOrder = 0
      Text = '0'
      OnKeyDown = onKey
    end
    object FocusPos: TIntegerLabeledEdit
      Left = 95
      Top = 44
      Width = 73
      Height = 21
      EditLabel.Width = 28
      EditLabel.Height = 13
      EditLabel.Caption = 'Focus'
      NumbersOnly = True
      TabOrder = 1
      Text = '0'
      OnKeyDown = onKey
    end
    object GoButton: TButton
      Left = 176
      Top = 42
      Width = 48
      Height = 25
      Caption = '->'
      TabOrder = 2
      OnClick = GoButtonClick
    end
  end
end
