object WatchDogSensorFrame: TWatchDogSensorFrame
  Left = 0
  Top = 0
  Width = 317
  Height = 317
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 317
    Height = 317
    Align = alClient
    Caption = 'Sensor Info'
    TabOrder = 0
    object IsConnectedLbl: TLabel
      Left = 138
      Top = 281
      Width = 23
      Height = 13
      Caption = 'false'
    end
    object Lbl: TLabel
      Left = 16
      Top = 281
      Width = 68
      Height = 13
      Caption = 'Is Connected:'
    end
    object DeviceID: TSTDStringLabeledEdit
      Left = 16
      Top = 60
      Width = 281
      Height = 21
      EditLabel.Width = 46
      EditLabel.Height = 13
      EditLabel.Caption = 'Device ID'
      Enabled = False
      TabOrder = 0
    end
    object DeviceAlias: TSTDStringLabeledEdit
      Left = 16
      Top = 120
      Width = 281
      Height = 21
      EditLabel.Width = 57
      EditLabel.Height = 13
      EditLabel.Caption = 'Device Alias'
      Enabled = False
      TabOrder = 1
    end
    object TemperatureE: TFloatLabeledEdit
      Left = 16
      Top = 181
      Width = 183
      Height = 21
      EditLabel.Width = 80
      EditLabel.Height = 13
      EditLabel.Caption = 'Temperature (C)'
      Enabled = False
      TabOrder = 2
      Text = '-1.0000'
      Value = -1.000000000000000000
    end
    object HumidityE: TFloatLabeledEdit
      Left = 157
      Top = 242
      Width = 140
      Height = 21
      EditLabel.Width = 85
      EditLabel.Height = 13
      EditLabel.Caption = 'Rel. Humidity (%)'
      Enabled = False
      TabOrder = 3
      Text = '-1.0000'
      Value = -1.000000000000000000
    end
    object DewPointE: TFloatLabeledEdit
      Left = 16
      Top = 242
      Width = 105
      Height = 21
      EditLabel.Width = 45
      EditLabel.Height = 13
      EditLabel.Caption = 'Dewpoint'
      Enabled = False
      TabOrder = 4
      Text = '-1.0000'
      Value = -1.000000000000000000
    end
  end
end
