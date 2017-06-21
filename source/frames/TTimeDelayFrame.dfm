object TimeDelayFrame: TTimeDelayFrame
  Left = 0
  Top = 0
  Width = 313
  Height = 207
  AutoSize = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 313
    Height = 207
    Align = alLeft
    Caption = 'TimeDelay Process'
    TabOrder = 0
    object mTimeDelayE: TIntegerLabeledEdit
      Left = 21
      Top = 128
      Width = 121
      Height = 31
      EditLabel.Width = 90
      EditLabel.Height = 23
      EditLabel.Caption = 'Delay (ms)'
      TabOrder = 0
      Text = '0'
      OnKeyDown = mEditKeyDown
    end
    object mNameEdit: TSTDStringLabeledEdit
      Left = 21
      Top = 64
      Width = 260
      Height = 31
      EditLabel.Width = 49
      EditLabel.Height = 23
      EditLabel.Caption = 'Name'
      Enabled = False
      ReadOnly = True
      TabOrder = 1
      OnKeyDown = mEditKeyDown
    end
  end
end
