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
      TabOrder = 2
      OnClick = ConnectBtnClick
    end
    object mSendMSGE: TSTDStringLabeledEdit
      Left = 24
      Top = 136
      Width = 81
      Height = 31
      EditLabel.Width = 43
      EditLabel.Height = 23
      EditLabel.Caption = 'Send'
      TabOrder = 3
      Text = 'i'
      OnKeyDown = mSendMSGEKeyDown
      Value = 'i'
    end
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 224
    Top = 112
  end
end
