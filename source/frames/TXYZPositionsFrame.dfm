object XYZPositionsFrame: TXYZPositionsFrame
  Left = 0
  Top = 0
  Width = 177
  Height = 161
  AutoSize = True
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 177
    Height = 161
    Caption = 'XYZUnit Positions'
    TabOrder = 0
    object Label1: TLabel
      Left = 36
      Top = 33
      Width = 6
      Height = 13
      Caption = 'X'
    end
    object Label2: TLabel
      Left = 36
      Top = 62
      Width = 6
      Height = 13
      Caption = 'Y'
    end
    object Label3: TLabel
      Left = 36
      Top = 91
      Width = 6
      Height = 13
      Caption = 'Z'
    end
    object Label4: TLabel
      Left = 26
      Top = 120
      Width = 27
      Height = 13
      Caption = 'Angle'
    end
    object mXPosL: TLabel
      Left = 88
      Top = 33
      Width = 36
      Height = 13
      Caption = 'mXPosL'
    end
    object mYPosL: TLabel
      Left = 88
      Top = 62
      Width = 31
      Height = 13
      Caption = 'Label5'
    end
    object mZPosL: TLabel
      Left = 88
      Top = 91
      Width = 31
      Height = 13
      Caption = 'Label5'
    end
    object mAnglePosL: TLabel
      Left = 88
      Top = 120
      Width = 31
      Height = 13
      Caption = 'Label5'
    end
  end
  object PullPosTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = PullPosTimerTimer
    Left = 8
    Top = 72
  end
end
