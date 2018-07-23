object ZebraScannerFrame: TZebraScannerFrame
  Left = 0
  Top = 0
  Width = 252
  Height = 352
  TabOrder = 0
  object mMiddleLeftPanel: TPanel
    Left = 0
    Top = 0
    Width = 252
    Height = 352
    Align = alClient
    TabOrder = 0
    object GroupBox3: TGroupBox
      Left = 1
      Top = 1
      Width = 250
      Height = 58
      Align = alTop
      Caption = 'Zebra Connection'
      TabOrder = 0
      object mTopPanel: TPanel
        Left = 2
        Top = 15
        Width = 246
        Height = 34
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object mComportCB: TComboBox
          Left = 8
          Top = 7
          Width = 73
          Height = 21
          TabOrder = 0
          Text = 'COM1'
          Items.Strings = (
            'COM1'
            'COM2'
            'COM3'
            'COM4'
            'COM5'
            'COM6'
            'COM7'
            'COM8'
            'COM9'
            'COM10'
            'COM11'
            'COM12'
            'COM13'
            'COM14'
            'COM15'
            'COM16'
            'COM17'
            'COM18'
            'COM19'
            'COM20')
        end
        object mConnectZebraBtn: TButton
          Left = 174
          Top = 1
          Width = 62
          Height = 32
          Caption = 'Open'
          TabOrder = 1
          OnClick = mConnectZebraBtnClick
        end
        object mBaudRateCB: TComboBox
          Left = 92
          Top = 8
          Width = 76
          Height = 21
          ItemIndex = 0
          TabOrder = 2
          Text = '9600'
          Items.Strings = (
            '9600'
            '14400'
            '19200'
            '38400'
            '57600'
            '115200'
            '128000'
            '256000')
        end
      end
    end
    object GroupBox1: TGroupBox
      Left = 1
      Top = 149
      Width = 250
      Height = 58
      Align = alTop
      Caption = 'Beeper'
      TabOrder = 1
      object mBeepBtn: TButton
        Left = 16
        Top = 16
        Width = 75
        Height = 36
        Caption = 'Beep'
        TabOrder = 0
        OnClick = BtnClick
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 207
      Width = 250
      Height = 144
      Align = alClient
      Caption = 'Session'
      TabOrder = 2
      object mDecodeSessionBtn: TButton
        AlignWithMargins = True
        Left = 17
        Top = 30
        Width = 216
        Height = 97
        Margins.Left = 15
        Margins.Top = 15
        Margins.Right = 15
        Margins.Bottom = 15
        Align = alClient
        Caption = 'Start'
        TabOrder = 0
      end
    end
    object mScannerEnabledRG: TRadioGroup
      Left = 1
      Top = 59
      Width = 250
      Height = 49
      Align = alTop
      Caption = 'Enabled'
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        'On'
        'Off')
      TabOrder = 3
      OnClick = SettingsRGClick
    end
    object Panel1: TPanel
      Left = 1
      Top = 108
      Width = 250
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 4
      object mScannerIllumRG: TRadioGroup
        Left = 0
        Top = 0
        Width = 112
        Height = 41
        Align = alLeft
        Caption = 'Illumination'
        Columns = 2
        ItemIndex = 1
        Items.Strings = (
          'On'
          'Off')
        TabOrder = 0
      end
      object mScannerAimRG: TRadioGroup
        Left = 112
        Top = 0
        Width = 138
        Height = 41
        Align = alClient
        Caption = 'Aim'
        Columns = 2
        ItemIndex = 1
        Items.Strings = (
          'On'
          'Off')
        TabOrder = 1
      end
    end
  end
end
