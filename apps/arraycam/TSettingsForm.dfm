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
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnKeyDown = FormKeyDown
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
    Width = 266
    Height = 234
    Caption = 'Camera'
    TabOrder = 1
    object mGamma: TLabel
      Left = 187
      Top = 104
      Width = 6
      Height = 13
      Caption = '1'
    end
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
      Left = 143
      Top = 26
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
    object mPhotoOutputBaseFolder: TSTDStringLabeledEdit
      Left = 14
      Top = 161
      Width = 219
      Height = 21
      EditLabel.AlignWithMargins = True
      EditLabel.Width = 61
      EditLabel.Height = 13
      EditLabel.Caption = 'Photo Folder'
      TabOrder = 2
    end
    object mMoviesFolderE: TSTDStringLabeledEdit
      Left = 14
      Top = 206
      Width = 219
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = 'Movies Folder'
      TabOrder = 3
    end
    object mBrowseForImagesFolderBtn: TButton
      Left = 236
      Top = 159
      Width = 27
      Height = 25
      Caption = '...'
      TabOrder = 4
      OnClick = BrowseForFolder
    end
    object mBrowseForMoviesFolderBtn: TButton
      Left = 236
      Top = 204
      Width = 27
      Height = 25
      Caption = '...'
      TabOrder = 5
      OnClick = BrowseForFolder
    end
    object mGammaSB: TTrackBar
      Left = 14
      Top = 96
      Width = 150
      Height = 35
      Max = 1000
      Position = 100
      ShowSelRange = False
      TabOrder = 6
      ThumbLength = 35
      TickStyle = tsNone
      OnChange = mGammaSBChange
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
  object GroupBox5: TGroupBox
    Left = 8
    Top = 248
    Width = 185
    Height = 73
    Caption = 'Miscellaneous'
    TabOrder = 3
    object mPairLEDsCB: TPropertyCheckBox
      Left = 16
      Top = 32
      Width = 97
      Height = 17
      Caption = 'Pair F/B LEDs'
      TabOrder = 0
      OnClick = mPairLEDsCBClick
    end
  end
  object UIUpdateTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = UIUpdateTimerTimer
    Left = 344
    Top = 240
  end
end
