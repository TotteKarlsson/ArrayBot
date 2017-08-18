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
    Height = 854
    Align = alRight
    TabOrder = 0
    ExplicitLeft = 757
    ExplicitHeight = 631
    object Button7: TButton
      Left = 1
      Top = 731
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
      ExplicitTop = 508
    end
    object Button5: TButton
      Left = 1
      Top = 791
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
      ExplicitTop = 568
    end
  end
  object MainPanel: TPanel
    Left = 0
    Top = 0
    Width = 956
    Height = 854
    Align = alClient
    TabOrder = 1
    ExplicitWidth = 757
    ExplicitHeight = 695
    object Splitter1: TSplitter
      Left = 1
      Top = 508
      Width = 954
      Height = 3
      Cursor = crVSplit
      Align = alBottom
      ExplicitLeft = -23
      ExplicitTop = 387
      ExplicitWidth = 755
    end
    object BottomPanel: TPanel
      Left = 1
      Top = 511
      Width = 954
      Height = 342
      Align = alBottom
      TabOrder = 0
      ExplicitTop = 288
      ExplicitWidth = 755
      object infoMemo: TMemo
        Left = 1
        Top = 51
        Width = 952
        Height = 290
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
        WordWrap = False
        ExplicitWidth = 882
        ExplicitHeight = 91
      end
      object ToolBar1: TToolBar
        Left = 1
        Top = 1
        Width = 952
        Height = 50
        ButtonHeight = 44
        Caption = 'ToolBar1'
        TabOrder = 1
        ExplicitWidth = 882
        object BitBtn2: TBitBtn
          Left = 0
          Top = 0
          Width = 75
          Height = 44
          Caption = 'Clear'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          OnClick = BitBtn3Click
        end
      end
    end
    object TopPanel: TPanel
      Left = 1
      Top = 1
      Width = 954
      Height = 507
      Align = alClient
      Constraints.MinHeight = 348
      Constraints.MinWidth = 670
      TabOrder = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 757
      ExplicitHeight = 628
      object PageControl1: TPageControl
        Left = 1
        Top = 1
        Width = 952
        Height = 505
        ActivePage = TabSheet4
        Align = alClient
        TabHeight = 60
        TabOrder = 0
        TabWidth = 100
        ExplicitWidth = 755
        ExplicitHeight = 626
        object TabSheet4: TTabSheet
          Caption = 'The Bot'
          ExplicitLeft = 0
          ExplicitTop = 0
          ExplicitWidth = 747
          ExplicitHeight = 556
          object ScrollBox1: TScrollBox
            Left = 0
            Top = 0
            Width = 944
            Height = 435
            Align = alClient
            TabOrder = 0
            ExplicitWidth = 747
            ExplicitHeight = 556
          end
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 304
    Top = 648
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
      OnExecute = ShutDownAExecute
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
    Left = 32
    Top = 648
  end
  object StatusTimer: TTimer
    Enabled = False
    Interval = 500
    Left = 120
    Top = 648
  end
end
