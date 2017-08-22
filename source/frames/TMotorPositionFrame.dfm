object MotorPositionFrame: TMotorPositionFrame
  Left = 0
  Top = 0
  Width = 161
  Height = 81
  AutoSize = True
  TabOrder = 0
  object MotorPositionGB: TGroupBox
    Left = 0
    Top = 0
    Width = 161
    Height = 81
    Caption = 'Motor Position'
    TabOrder = 0
    object mPosL: TLabel
      Left = 2
      Top = 15
      Width = 30
      Height = 13
      Align = alClient
      Alignment = taCenter
      Caption = 'mPosL'
      Layout = tlCenter
    end
  end
  object PullPosTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = PullPosTimerTimer
    Left = 80
    Top = 80
  end
end
