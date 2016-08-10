object SettingsForm: TSettingsForm
  Left = 0
  Top = 0
  Caption = 'ArrayCam Settings'
  ClientHeight = 349
  ClientWidth = 545
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 25
    Top = 15
    Width = 257
    Height = 155
    Caption = 'Arduino Client'
    TabOrder = 0
    object mArduinoServerPortE: TIntegerLabeledEdit
      Left = 16
      Top = 56
      Width = 121
      Height = 21
      EditLabel.Width = 63
      EditLabel.Height = 13
      EditLabel.Caption = 'Network Port'
      TabOrder = 0
      Text = '50000'
      Value = 50000
    end
    object mASStartBtn: TButton
      Left = 143
      Top = 40
      Width = 104
      Height = 97
      Caption = 'Start'
      TabOrder = 1
      OnClick = mASStartBtnClick
    end
  end
  object UIUpdateTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = UIUpdateTimerTimer
    Left = 56
    Top = 256
  end
end
