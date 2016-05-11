object XYZUnitFrame: TXYZUnitFrame
  Left = 0
  Top = 0
  Width = 632
  Height = 351
  TabOrder = 0
  object mainGB: TGroupBox
    Left = 0
    Top = 0
    Width = 632
    Height = 351
    Align = alClient
    Caption = 'XYZ Unit'
    TabOrder = 0
    ExplicitWidth = 720
    ExplicitHeight = 402
    object TopPanel: TPanel
      Left = 2
      Top = 15
      Width = 628
      Height = 26
      Align = alTop
      BevelOuter = bvLowered
      TabOrder = 0
      ExplicitWidth = 716
    end
    object ScrollBox1: TScrollBox
      Left = 2
      Top = 41
      Width = 628
      Height = 308
      Align = alClient
      TabOrder = 1
      ExplicitWidth = 716
      ExplicitHeight = 344
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
