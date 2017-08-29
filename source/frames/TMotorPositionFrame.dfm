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
      Width = 157
      Height = 64
      Align = alClient
      Alignment = taCenter
      Caption = 'N/A'
      Layout = tlCenter
      ExplicitWidth = 18
      ExplicitHeight = 13
    end
  end
  object PullPosTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = PullPosTimerTimer
    Left = 26
    Top = 18
  end
end
