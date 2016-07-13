object TimeDelayFrame: TTimeDelayFrame
  Left = 0
  Top = 0
  Width = 137
  Height = 207
  AutoSize = True
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 137
    Height = 207
    Align = alLeft
    Caption = 'TimeDelay Process'
    TabOrder = 0
    object mTimeDelayE: TIntegerLabeledEdit
      Left = 13
      Top = 48
      Width = 60
      Height = 21
      EditLabel.Width = 76
      EditLabel.Height = 13
      EditLabel.Caption = 'Time Delay (ms)'
      TabOrder = 0
      Text = '0'
      OnKeyDown = mTimeDelayEKeyDown
    end
  end
end
