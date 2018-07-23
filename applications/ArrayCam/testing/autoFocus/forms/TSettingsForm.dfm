object SettingsForm: TSettingsForm
  Left = 0
  Top = 0
  Caption = 'ArrayCam Settings'
  ClientHeight = 531
  ClientWidth = 600
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
  OnCreate = FormCreate
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 600
    Height = 476
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Camera'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox2: TGroupBox
        Left = 9
        Top = 152
        Width = 192
        Height = 64
        Caption = 'Mirror planes'
        TabOrder = 0
        object mVerticalMirrorCB: TPropertyCheckBox
          Left = 10
          Top = 18
          Width = 65
          Height = 17
          Caption = 'Vertical'
          TabOrder = 0
          OnClick = mVerticalMirrorCBClick
        end
        object mHorizontalMirrorCB: TPropertyCheckBox
          Left = 98
          Top = 18
          Width = 65
          Height = 17
          Caption = 'Horizontal'
          TabOrder = 1
          OnClick = mHorizontalMirrorCBClick
        end
      end
      object GroupBox3: TGroupBox
        Left = 9
        Top = 19
        Width = 411
        Height = 118
        Caption = 'Camera Settings'
        TabOrder = 1
        object Label1: TLabel
          Left = 19
          Top = 40
          Width = 94
          Height = 13
          Caption = 'Exposure Time (ms)'
        end
        object mExposureTimeLbl: TFloatLabel
          Left = 248
          Top = 64
          Width = 26
          Height = 13
          Caption = '-1.00'
          ValueString = '-1.00'
          Value = -1.000000000000000000
          TheFont.Charset = DEFAULT_CHARSET
          TheFont.Color = clWindowText
          TheFont.Height = -11
          TheFont.Name = 'Tahoma'
          TheFont.Style = []
        end
        object mAutoExposureCB: TPropertyCheckBox
          Left = 19
          Top = 64
          Width = 109
          Height = 17
          Caption = 'Auto'
          TabOrder = 0
          OnClick = AutoParaCBClick
        end
        object mExposureTimeTB: TTrackBar
          Left = 148
          Top = 30
          Width = 260
          Height = 35
          Max = 300
          Min = 10
          Position = 10
          ShowSelRange = False
          TabOrder = 1
          ThumbLength = 35
          TickStyle = tsNone
          OnChange = mExposureTimeTBChange
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Image'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox4: TGroupBox
        Left = 19
        Top = 19
        Width = 390
        Height = 214
        Caption = 'Master Gain'
        TabOrder = 0
        object mGainLbl: TLabel
          Left = 18
          Top = 46
          Width = 6
          Height = 13
          Caption = '1'
        end
        object Label2: TLabel
          Left = 18
          Top = 27
          Width = 21
          Height = 13
          Caption = 'Gain'
        end
        object Label3: TLabel
          Left = 18
          Top = 147
          Width = 52
          Height = 13
          Caption = 'Black Level'
        end
        object mBlackLevelLbl: TIntLabel
          Left = 126
          Top = 184
          Width = 10
          Height = 13
          Caption = '-1'
          Value = -1
          TheFont.Charset = DEFAULT_CHARSET
          TheFont.Color = clWindowText
          TheFont.Height = -11
          TheFont.Name = 'Tahoma'
          TheFont.Style = []
        end
        object mAutoGainCB: TPropertyCheckBox
          Left = 18
          Top = 79
          Width = 109
          Height = 17
          Caption = 'Auto'
          TabOrder = 0
          OnClick = AutoParaCBClick
        end
        object mGainTB: TTrackBar
          Left = 117
          Top = 34
          Width = 258
          Height = 47
          Enabled = False
          Max = 100
          ShowSelRange = False
          TabOrder = 1
          ThumbLength = 35
          TickStyle = tsNone
          OnChange = mGainTBChange
        end
        object mBlackLevelTB: TTrackBar
          Left = 117
          Top = 138
          Width = 258
          Height = 47
          Enabled = False
          Max = 100
          ShowSelRange = False
          TabOrder = 2
          ThumbLength = 35
          TickStyle = tsNone
          OnChange = mBlackLevelTBChange
        end
        object mAutoBlackLevelCB: TPropertyCheckBox
          Left = 18
          Top = 166
          Width = 109
          Height = 17
          Caption = 'Auto'
          TabOrder = 3
          OnClick = AutoParaCBClick
        end
        object mGainBoostCB: TCheckBox
          Left = 18
          Top = 102
          Width = 87
          Height = 17
          Caption = 'Gain Boost'
          TabOrder = 4
          OnClick = mGainBoostCBClick
        end
      end
      object Gamma: TGroupBox
        Left = 19
        Top = 311
        Width = 390
        Height = 81
        Caption = 'Gamma'
        TabOrder = 1
        object Label4: TLabel
          Left = 18
          Top = 28
          Width = 82
          Height = 13
          Caption = 'Software Gamma'
        end
        object mSoftwareGammaLbl: TFloatLabel
          Left = 18
          Top = 47
          Width = 22
          Height = 13
          Caption = '1.00'
          ValueString = '1.00'
          Value = 1.000000000000000000
          TheFont.Charset = DEFAULT_CHARSET
          TheFont.Color = clWindowText
          TheFont.Height = -11
          TheFont.Name = 'Tahoma'
          TheFont.Style = []
        end
        object mGammaSB: TTrackBar
          Left = 117
          Top = 30
          Width = 260
          Height = 35
          Max = 300
          Min = 10
          Position = 10
          ShowSelRange = False
          TabOrder = 0
          ThumbLength = 35
          TickStyle = tsNone
          OnChange = mGammaSBChange
        end
      end
      object GroupBox5: TGroupBox
        Left = 19
        Top = 239
        Width = 390
        Height = 66
        Caption = 'Color Gain'
        TabOrder = 2
        object mAutoWhiteBalanceCB: TPropertyCheckBox
          Left = 18
          Top = 32
          Width = 109
          Height = 17
          Caption = 'Auto White Balance'
          TabOrder = 0
          OnClick = AutoParaCBClick
        end
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 476
    Width = 600
    Height = 55
    Align = alBottom
    TabOrder = 1
    object mCloseButton: TButton
      Left = 488
      Top = 2
      Width = 99
      Height = 45
      Caption = 'Close'
      TabOrder = 0
      OnClick = mCloseButtonClick
    end
  end
  object mUIUpdateTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = mUIUpdateTimerTimer
    Left = 496
    Top = 104
  end
end
