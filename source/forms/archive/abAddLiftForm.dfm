object AddLiftSettingForm: TAddLiftSettingForm
  Left = 0
  Top = 0
  Caption = 'Add Lift Setting'
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
  object mVelocityE: TFloatLabeledEdit
    Left = 121
    Top = 80
    Width = 80
    Height = 21
    EditLabel.Width = 37
    EditLabel.Height = 13
    EditLabel.Caption = 'Velocity'
    TabOrder = 1
    Text = '0.0'
  end
  object mAcc: TFloatLabeledEdit
    Left = 232
    Top = 80
    Width = 73
    Height = 21
    EditLabel.Width = 59
    EditLabel.Height = 13
    EditLabel.Caption = 'Acceleration'
    TabOrder = 2
    Text = '0.0'
  end
  object mDistanceE: TFloatLabeledEdit
    Left = 24
    Top = 80
    Width = 71
    Height = 21
    EditLabel.Width = 41
    EditLabel.Height = 13
    EditLabel.Caption = 'Distance'
    TabOrder = 3
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
    TabOrder = 4
  end
  object Button2: TButton
    Left = 271
    Top = 163
    Width = 100
    Height = 50
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 5
  end
end
