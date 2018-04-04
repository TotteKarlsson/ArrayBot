object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Motor Frame Tester 0.5'
  ClientHeight = 854
  ClientWidth = 1083
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Btnpanel: TPanel
    Left = 956
    Top = 0
    Width = 127
    Height = 654
    Align = alRight
    TabOrder = 0
    ExplicitHeight = 854
    object Button7: TButton
      Left = 1
      Top = 531
      Width = 125
      Height = 60
      Action = stopAllA
      Align = alBottom
      BiDiMode = bdLeftToRight
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 0
      ExplicitTop = 731
    end
    object Button5: TButton
      Left = 1
      Top = 591
      Width = 125
      Height = 62
      Action = FileExit1
      Align = alBottom
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      ExplicitTop = 791
    end
    object Button1: TButton
      Left = 1
      Top = 471
      Width = 125
      Height = 60
      Action = checkForDevices
      Align = alBottom
      BiDiMode = bdLeftToRight
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 2
      ExplicitTop = 731
    end
  end
  object MainPanel: TPanel
    Left = 0
    Top = 0
    Width = 956
    Height = 654
    Align = alClient
    TabOrder = 1
    ExplicitHeight = 854
    object Splitter1: TSplitter
      Left = 1
      Top = 650
      Width = 954
      Height = 3
      Cursor = crVSplit
      Align = alBottom
      ExplicitLeft = -23
      ExplicitTop = 387
      ExplicitWidth = 755
    end
    object TopPanel: TPanel
      Left = 1
      Top = 1
      Width = 954
      Height = 649
      Align = alClient
      Constraints.MinHeight = 348
      Constraints.MinWidth = 670
      TabOrder = 0
      ExplicitHeight = 507
      object PageControl1: TPageControl
        Left = 1
        Top = 1
        Width = 952
        Height = 647
        ActivePage = TabSheet4
        Align = alClient
        TabHeight = 60
        TabOrder = 0
        TabWidth = 100
        ExplicitHeight = 505
        object TabSheet4: TTabSheet
          Caption = 'The Bot'
          ExplicitHeight = 435
          object ScrollBox1: TScrollBox
            Left = 0
            Top = 0
            Width = 944
            Height = 577
            Align = alClient
            TabOrder = 0
            ExplicitHeight = 777
          end
        end
      end
    end
  end
  inline TLogMemoFrame1: TLogMemoFrame
    Left = 0
    Top = 654
    Width = 1083
    Height = 200
    Align = alBottom
    TabOrder = 2
    ExplicitTop = 654
    ExplicitWidth = 1083
    ExplicitHeight = 200
    inherited Panel1: TPanel
      Width = 1083
      Height = 200
      inherited GroupBox1: TGroupBox
        Width = 1081
      end
      inherited infoMemo: TMemo
        Width = 1081
        Height = 148
      end
    end
  end
  object ActionList1: TActionList
    Left = 96
    Top = 304
    object checkForDevices: TAction
      Caption = 'Devices Check'
      OnExecute = checkForDevicesExecute
    end
    object addDevicesToListBox: TAction
      Caption = 'Connect All'
    end
    object identifyCurrent: TAction
      Caption = 'Identify'
    end
    object homeDevice: TAction
      Caption = 'Home'
    end
    object jogForward: TAction
      Caption = 'Fwd'
    end
    object jogBackwards: TAction
      Caption = 'Rev'
    end
    object moveForward: TAction
      Caption = 'Forward'
    end
    object moveBackward: TAction
      Caption = 'Backward'
    end
    object stopAllA: TAction
      Caption = 'Stop All'
    end
    object initBotA: TAction
      Caption = 'Initialize'
    end
    object ShutDownA: TAction
      Caption = 'ShutDown'
    end
    object FileExit1: TFileExit
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = ShutDownTimerTimer
    Left = 88
    Top = 504
  end
end
