object SettingsForm: TSettingsForm
  Left = 0
  Top = 0
  Caption = 'ArrayCam Settings'
  ClientHeight = 435
  ClientWidth = 578
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
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 578
    Height = 380
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Camera'
      object Label1: TLabel
        Left = 26
        Top = 117
        Width = 35
        Height = 13
        Caption = 'Gamma'
      end
      object mGamma: TLabel
        Left = 187
        Top = 136
        Width = 6
        Height = 13
        Caption = '1'
      end
      object GroupBox4: TGroupBox
        Left = 3
        Top = 3
        Width = 329
        Height = 97
        Caption = 'Gain'
        TabOrder = 0
        object mGainLbl: TLabel
          Left = 204
          Top = 51
          Width = 6
          Height = 13
          Caption = '1'
        end
        object mAutoGainCB: TPropertyCheckBox
          Left = 18
          Top = 19
          Width = 109
          Height = 17
          Caption = 'Auto Gain'
          TabOrder = 0
          OnClick = AutoParaCBClick
        end
        object mGainTB: TTrackBar
          Left = 18
          Top = 42
          Width = 167
          Height = 35
          Enabled = False
          Max = 1000
          Position = 100
          ShowSelRange = False
          TabOrder = 1
          ThumbLength = 35
          TickStyle = tsNone
          OnChange = mGainTBChange
        end
      end
      object mGammaSB: TTrackBar
        Left = 14
        Top = 128
        Width = 150
        Height = 35
        Max = 300
        Min = 10
        Position = 100
        ShowSelRange = False
        TabOrder = 1
        ThumbLength = 35
        TickStyle = tsNone
        OnChange = mGammaSBChange
      end
      object GroupBox2: TGroupBox
        Left = 446
        Top = 8
        Width = 113
        Height = 64
        Caption = 'Mirror planes'
        TabOrder = 2
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
      object GroupBox3: TGroupBox
        Left = 446
        Top = 99
        Width = 113
        Height = 64
        Caption = 'Settings'
        TabOrder = 3
        object mAutoExposureCB: TPropertyCheckBox
          Left = 3
          Top = 17
          Width = 109
          Height = 17
          Caption = 'Auto Exposure'
          TabOrder = 0
          OnClick = AutoParaCBClick
        end
      end
      object GroupBox6: TGroupBox
        Left = 0
        Top = 264
        Width = 521
        Height = 86
        Caption = 'Folders (raw files)'
        TabOrder = 4
        object mBrowseForImagesFolderBtn: TButton
          Left = 228
          Top = 40
          Width = 27
          Height = 25
          Caption = '...'
          TabOrder = 0
          OnClick = BrowseForFolder
        end
        object mBrowseForMoviesFolderBtn: TButton
          Left = 483
          Top = 40
          Width = 27
          Height = 25
          Caption = '...'
          TabOrder = 1
          OnClick = BrowseForFolder
        end
        object mMoviesFolderE: TSTDStringLabeledEdit
          Left = 261
          Top = 44
          Width = 219
          Height = 21
          EditLabel.Width = 66
          EditLabel.Height = 13
          EditLabel.Caption = 'Movies Folder'
          TabOrder = 2
        end
        object mPhotoOutputBaseFolder: TSTDStringLabeledEdit
          Left = 6
          Top = 44
          Width = 219
          Height = 21
          EditLabel.AlignWithMargins = True
          EditLabel.Width = 61
          EditLabel.Height = 13
          EditLabel.Caption = 'Photo Folder'
          TabOrder = 3
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Peripherals'
      ImageIndex = 2
      object LightIntensitiesGB: TGroupBox
        Left = 3
        Top = 16
        Width = 350
        Height = 137
        Caption = 'Light Intensities'
        TabOrder = 0
        object mCoaxLbl: TLabel
          Left = 151
          Top = 103
          Width = 54
          Height = 13
          Caption = 'Coax (122)'
        end
        object mBackLEDLbl: TLabel
          Left = 151
          Top = 65
          Width = 72
          Height = 13
          Caption = 'Back LED (122)'
        end
        object mFrontLEDLbl: TLabel
          Left = 151
          Top = 26
          Width = 76
          Height = 13
          Caption = 'Front LED (122)'
        end
        object Panel2: TPanel
          Left = 2
          Top = 15
          Width = 143
          Height = 120
          Align = alLeft
          BevelOuter = bvNone
          TabOrder = 0
          object mBackLEDTB: TTrackBar
            Left = 0
            Top = 40
            Width = 143
            Height = 40
            Align = alTop
            Max = 255
            TabOrder = 0
            ThumbLength = 30
            TickStyle = tsNone
            OnChange = SettingsChange
          end
          object mCoaxTB: TTrackBar
            Left = 0
            Top = 80
            Width = 143
            Height = 40
            Align = alTop
            Max = 255
            TabOrder = 1
            ThumbLength = 30
            TickStyle = tsNone
            OnChange = SettingsChange
          end
          object mFrontLEDTB: TTrackBar
            Left = 0
            Top = 0
            Width = 143
            Height = 40
            Align = alTop
            Max = 255
            TabOrder = 2
            ThumbLength = 30
            TickStyle = tsNone
            OnChange = SettingsChange
          end
        end
        object mPairLEDsCB: TPropertyCheckBox
          Left = 248
          Top = 25
          Width = 97
          Height = 17
          Caption = 'Pair F/B LEDs'
          TabOrder = 1
          OnClick = mPairLEDsCBClick
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Connections'
      ImageIndex = 1
      object GroupBox1: TGroupBox
        Left = 3
        Top = 16
        Width = 273
        Height = 161
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
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 380
    Width = 578
    Height = 55
    Align = alBottom
    TabOrder = 1
    object Button1: TButton
      Left = 464
      Top = 2
      Width = 99
      Height = 45
      Caption = 'Close'
      TabOrder = 0
      OnClick = Button1Click
    end
  end
  object mUIUpdateTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = mUIUpdateTimerTimer
    Left = 264
    Top = 216
  end
end
