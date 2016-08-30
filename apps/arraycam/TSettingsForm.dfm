object SettingsForm: TSettingsForm
  Left = 0
  Top = 0
  Caption = 'ArrayCam Settings'
  ClientHeight = 355
  ClientWidth = 549
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
    Left = 280
    Top = 8
    Width = 257
    Height = 193
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
  object GroupBox4: TGroupBox
    Left = 8
    Top = 8
    Width = 259
    Height = 193
    Caption = 'Camera'
    TabOrder = 1
    object GroupBox3: TGroupBox
      Left = 16
      Top = 26
      Width = 113
      Height = 64
      Caption = 'Settings'
      TabOrder = 0
      object mAutoExposureCB: TPropertyCheckBox
        Left = 10
        Top = 17
        Width = 109
        Height = 17
        Caption = 'Auto Exposure'
        TabOrder = 1
        OnClick = AutoParaCBClick
      end
      object mAutoGainCB: TPropertyCheckBox
        Left = 10
        Top = 40
        Width = 109
        Height = 17
        Caption = 'Auto Gain'
        TabOrder = 0
        OnClick = AutoParaCBClick
      end
    end
    object GroupBox2: TGroupBox
      Left = 16
      Top = 96
      Width = 113
      Height = 64
      Caption = 'Mirror planes'
      TabOrder = 1
      object mVerticalMirrorCB: TPropertyCheckBox
        Left = 10
        Top = 19
        Width = 65
        Height = 17
        Caption = 'Vertical'
        TabOrder = 0
        OnClick = mVerticalMirrorCBClick
      end
      object mHorizontalMirrorCB: TPropertyCheckBox
        Left = 10
        Top = 42
        Width = 65
        Height = 17
        Caption = 'Horizontal'
        TabOrder = 1
        OnClick = mHorizontalMirrorCBClick
      end
    end
  end
  object Button1: TButton
    Left = 440
    Top = 296
    Width = 99
    Height = 45
    Caption = 'Close'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 34
    Top = 224
    Width = 75
    Height = 25
    Caption = 'Button2'
    TabOrder = 3
  end
  object UIUpdateTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = UIUpdateTimerTimer
    Left = 344
    Top = 240
  end
end
