object ArduinoBoardFrame: TArduinoBoardFrame
  Left = 0
  Top = 0
  Width = 281
  Height = 273
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
    Width = 281
    Height = 273
    Align = alClient
    Caption = 'Arduino Board 1'
    TabOrder = 0
    object mCommPortE: TIntegerLabeledEdit
      Left = 24
      Top = 72
      Width = 81
      Height = 31
      EditLabel.Width = 78
      EditLabel.Height = 23
      EditLabel.Caption = 'COM Port'
      TabOrder = 0
      Text = '4'
      Value = 4
    end
    object mBaudRateE: TIntegerLabeledEdit
      Left = 151
      Top = 72
      Width = 89
      Height = 31
      EditLabel.Width = 87
      EditLabel.Height = 23
      EditLabel.Caption = 'Baud Rate'
      TabOrder = 1
      Text = '9600'
      Value = 9600
    end
    object mConnectBtn: TButton
      Left = 24
      Top = 184
      Width = 216
      Height = 65
      Caption = 'Connect/Disconnect'
      TabOrder = 3
      OnClick = ConnectBtnClick
    end
    object mSendMSGE: TSTDStringLabeledEdit
      Left = 24
      Top = 136
      Width = 129
      Height = 31
      EditLabel.Width = 102
      EditLabel.Height = 23
      EditLabel.Caption = 'Custom Msg'
      TabOrder = 2
      Text = 'i'
      Value = 'i'
    end
    object mSendBtn: TButton
      Left = 165
      Top = 132
      Width = 75
      Height = 39
      Caption = 'Send'
      TabOrder = 4
    end
  end
  object mCheckConnectionTimer: TTimer
    OnTimer = mCheckConnectionTimerTimer
    Left = 224
    Top = 56
  end
end
