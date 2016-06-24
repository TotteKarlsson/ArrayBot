object XYZPositionsFrame: TXYZPositionsFrame
  Left = 0
  Top = 0
  Width = 273
  Height = 161
  AutoSize = True
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 273
    Height = 161
    Caption = 'XYZUnit Positions'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 47
      Top = 33
      Width = 19
      Height = 24
      Caption = 'X:'
    end
    object Label2: TLabel
      Left = 47
      Top = 62
      Width = 19
      Height = 24
      Caption = 'Y:'
    end
    object Label3: TLabel
      Left = 48
      Top = 91
      Width = 18
      Height = 24
      Caption = 'Z:'
    end
    object Label4: TLabel
      Left = 9
      Top = 120
      Width = 57
      Height = 24
      Caption = 'Angle:'
    end
    object mXPosL: TLabel
      Left = 88
      Top = 33
      Width = 70
      Height = 24
      Caption = 'mXPosL'
    end
    object mYPosL: TLabel
      Left = 88
      Top = 62
      Width = 59
      Height = 24
      Caption = 'Label5'
    end
    object mZPosL: TLabel
      Left = 88
      Top = 91
      Width = 59
      Height = 24
      Caption = 'Label5'
    end
    object mAnglePosL: TLabel
      Left = 88
      Top = 120
      Width = 59
      Height = 24
      Caption = 'Label5'
    end
  end
  object PullPosTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = PullPosTimerTimer
    Left = 216
    Top = 64
  end
end
