object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'atDB'
  ClientHeight = 804
  ClientWidth = 973
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
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 480
    Width = 973
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 88
    ExplicitTop = 430
  end
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 973
    Height = 480
    Align = alClient
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 9
      Top = 24
      Width = 232
      Height = 113
      Caption = 'UC7'
      TabOrder = 0
      object mComportCB: TComboBox
        Left = 16
        Top = 24
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
        Left = 16
        Top = 72
        Width = 75
        Height = 25
        Caption = 'Connect'
        TabOrder = 1
        OnClick = mConnectUC7BtnClick
      end
    end
  end
  object SB: TStatusBar
    Left = 0
    Top = 785
    Width = 973
    Height = 19
    Panels = <>
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 483
    Width = 973
    Height = 302
    Align = alBottom
    TabOrder = 2
    object infoMemo: TMemo
      Left = 1
      Top = 49
      Width = 971
      Height = 252
      Align = alClient
      TabOrder = 0
    end
    object Panel1: TPanel
      Left = 1
      Top = 1
      Width = 971
      Height = 48
      Align = alTop
      TabOrder = 1
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
        ItemIndex = 0
        TabOrder = 1
        Text = 'INFO'
        Items.Strings = (
          'INFO'
          'Everything')
      end
    end
  end
  object ActionList1: TActionList
    Left = 616
    Top = 32
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
    Left = 808
    Top = 216
    object ClearMemoA1: TMenuItem
      Action = ClearMemoA
    end
  end
  object mIniFileC: mtkIniFileC
    IniFileName = 'atUC7.ini'
    RootFolder = '.'
    Left = 394
  end
  object MainMenu1: TMainMenu
    Left = 469
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
    Left = 290
    Top = 8
  end
end
