object AddJoyStickSettingForm: TAddJoyStickSettingForm
  Left = 0
  Top = 0
  Caption = 'Add Joystick Setting'
  ClientHeight = 224
  ClientWidth = 379
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object mSettingsNameE: TSTDStringLabeledEdit
    Left = 24
    Top = 32
    Width = 121
    Height = 21
    EditLabel.Width = 27
    EditLabel.Height = 13
    EditLabel.Caption = 'Name'
    TabOrder = 0
    Text = 'SettingsName'
    Value = 'SettingsName'
  end
  object mMaxXYVelocityE: TFloatLabeledEdit
    Left = 24
    Top = 80
    Width = 121
    Height = 21
    EditLabel.Width = 75
    EditLabel.Height = 13
    EditLabel.Caption = 'Max XY Velocity'
    TabOrder = 1
    Text = '0.0'
  end
  object mXYAcc: TFloatLabeledEdit
    Left = 168
    Top = 80
    Width = 121
    Height = 21
    EditLabel.Width = 74
    EditLabel.Height = 13
    EditLabel.Caption = 'XY Acceleration'
    TabOrder = 2
    Text = '0.0'
  end
  object mMaxZVelocityE: TFloatLabeledEdit
    Left = 24
    Top = 120
    Width = 121
    Height = 21
    EditLabel.Width = 69
    EditLabel.Height = 13
    EditLabel.Caption = 'Max Z Velocity'
    TabOrder = 3
    Text = '0.0'
  end
  object mZAccE: TFloatLabeledEdit
    Left = 168
    Top = 120
    Width = 121
    Height = 21
    EditLabel.Width = 68
    EditLabel.Height = 13
    EditLabel.Caption = 'Z Acceleration'
    TabOrder = 4
    Text = '0.0'
  end
  object CancelBtn: TButton
    Left = 153
    Top = 163
    Width = 100
    Height = 50
    Cancel = True
    Caption = 'CancelBtn'
    ModalResult = 2
    TabOrder = 5
  end
  object Button2: TButton
    Left = 271
    Top = 163
    Width = 100
    Height = 50
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 6
  end
end
