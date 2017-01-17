object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'UC7 Controller'
  ClientHeight = 543
  ClientWidth = 873
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDefault
  Scaled = False
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 331
    Width = 873
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 88
    ExplicitTop = 430
    ExplicitWidth = 973
  end
  object TopPanel: TPanel
    Left = 0
    Top = 41
    Width = 873
    Height = 290
    Align = alClient
    TabOrder = 0
    ExplicitWidth = 626
    object GroupBox3: TGroupBox
      Left = 1
      Top = 1
      Width = 392
      Height = 288
      Align = alLeft
      Caption = 'Controls'
      TabOrder = 0
      ExplicitLeft = -2
      ExplicitTop = -1
      object mStartStopBtn: TButton
        Left = 16
        Top = 40
        Width = 121
        Height = 89
        Caption = 'Start'
        Enabled = False
        TabOrder = 0
        OnClick = mStartStopBtnClick
      end
    end
  end
  object SB: TStatusBar
    Left = 0
    Top = 524
    Width = 873
    Height = 19
    Panels = <>
    ExplicitWidth = 626
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 334
    Width = 873
    Height = 190
    Align = alBottom
    TabOrder = 2
    ExplicitWidth = 626
    object infoMemo: TMemo
      Left = 1
      Top = 49
      Width = 871
      Height = 140
      Align = alClient
      ScrollBars = ssBoth
      TabOrder = 0
      WordWrap = False
      ExplicitWidth = 624
    end
    object Panel1: TPanel
      Left = 1
      Top = 1
      Width = 871
      Height = 48
      Align = alTop
      TabOrder = 1
      ExplicitWidth = 624
      object Button1: TButton
        Left = 8
        Top = 12
        Width = 75
        Height = 25
        Caption = 'Clear'
        TabOrder = 0
        OnClick = ClearMemoAExecute
      end
      object LogLevelCB: TComboBox
        Left = 89
        Top = 12
        Width = 145
        Height = 21
        TabOrder = 1
        Text = 'INFO'
        OnChange = LogLevelCBChange
        Items.Strings = (
          'ERRORS'
          'WARNINGS'
          'INFO'
          'DEBUG'
          'DEBUG1'
          'DEBUG2'
          'DEBUG3'
          'DEBUG4'
          'DEBUG5'
          'EVERYTHING')
      end
    end
  end
  object mTopPanel: TPanel
    Left = 0
    Top = 0
    Width = 873
    Height = 41
    Align = alTop
    TabOrder = 3
    ExplicitWidth = 626
    DesignSize = (
      873
      41)
    object mComportCB: TComboBox
      Left = 8
      Top = 12
      Width = 145
      Height = 21
      ItemIndex = 0
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
    object mConnectUC7Btn: TButton
      Left = 165
      Top = 10
      Width = 50
      Height = 25
      Caption = 'Open'
      TabOrder = 1
      OnClick = mConnectUC7BtnClick
    end
    object mSendBtn1: TButton
      Left = 396
      Top = 10
      Width = 50
      Height = 25
      Caption = '->'
      Enabled = False
      TabOrder = 2
      OnClick = mSendBtn1Click
    end
    object mSendRAW1: TSTDStringLabeledEdit
      Left = 245
      Top = 12
      Width = 145
      Height = 21
      EditLabel.Width = 62
      EditLabel.Height = 13
      EditLabel.Caption = 'mSendRAW1'
      Enabled = False
      TabOrder = 3
      Text = 's10'
      Value = 's10'
    end
    object mResetBtn: TButton
      Left = 772
      Top = 5
      Width = 85
      Height = 30
      Anchors = [akTop, akRight]
      Caption = 'Reset UC7'
      Enabled = False
      TabOrder = 4
      ExplicitLeft = 525
    end
  end
  object ActionList1: TActionList
    Left = 584
    Top = 192
    object ClearMemoA: TAction
      Category = 'Memo'
      Caption = 'Clear Messages'
      OnExecute = ClearMemoAExecute
    end
    object FileExit1: TFileExit
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
    object OpenAboutFormA: TAction
      Caption = 'About'
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 512
    Top = 232
    object ClearMemoA1: TMenuItem
      Action = ClearMemoA
    end
  end
  object mIniFileC: mtkIniFileC
    IniFileName = 'atUC7.ini'
    RootFolder = '.'
    Left = 482
    Top = 88
  end
  object MainMenu1: TMainMenu
    Left = 533
    Top = 136
    object File1: TMenuItem
      Caption = 'File'
      object Exit1: TMenuItem
        Action = FileExit1
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object About1: TMenuItem
        Action = OpenAboutFormA
      end
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 50
    OnTimer = ShutDownTimerTimer
    Left = 578
    Top = 72
  end
end
