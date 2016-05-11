object XYZUnitFrame: TXYZUnitFrame
  Left = 0
  Top = 0
  Width = 720
  Height = 402
  TabOrder = 0
  object mainGB: TGroupBox
    Left = 0
    Top = 0
    Width = 720
    Height = 402
    Align = alClient
    Caption = 'XYZ Unit'
    TabOrder = 0
    object TopPanel: TPanel
      Left = 2
      Top = 15
      Width = 716
      Height = 26
      Align = alTop
      BevelOuter = bvLowered
      TabOrder = 0
    end
    object ScrollBox1: TScrollBox
      Left = 2
      Top = 41
      Width = 716
      Height = 344
      Align = alTop
      TabOrder = 1
    end
  end
  object mMotorStatusTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = mMotorStatusTimerTimer
    Left = 112
    Top = 80
  end
end
