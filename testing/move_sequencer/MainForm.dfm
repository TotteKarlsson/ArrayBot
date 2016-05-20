object Main: TMain
  Left = 0
  Top = 0
  Caption = 'ArrayBot Version 0.1'
  ClientHeight = 814
  ClientWidth = 1262
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Btnpanel: TPanel
    Left = 1135
    Top = 0
    Width = 127
    Height = 814
    Align = alRight
    TabOrder = 0
    object Button7: TButton
      Left = 1
      Top = 691
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
    end
    object Button5: TButton
      Left = 1
      Top = 751
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
    end
  end
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 1135
    Height = 814
    Align = alClient
    Constraints.MinHeight = 348
    Constraints.MinWidth = 670
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 1133
      Height = 812
      ActivePage = TabSheet4
      Align = alClient
      TabHeight = 60
      TabOrder = 0
      TabWidth = 100
      object TabSheet4: TTabSheet
        Caption = 'The Bot'
        inline TMotorFrame1: TMotorFrame
          Left = 0
          Top = 0
          Width = 293
          Height = 742
          Align = alLeft
          TabOrder = 0
          ExplicitLeft = 128
          ExplicitTop = 168
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'Logging'
        ImageIndex = 4
        object BottomPanel: TPanel
          Left = 0
          Top = 0
          Width = 1125
          Height = 742
          Align = alClient
          TabOrder = 0
          object infoMemo: TMemo
            Left = 1
            Top = 51
            Width = 1123
            Height = 690
            Align = alClient
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ScrollBars = ssVertical
            TabOrder = 0
            WordWrap = False
          end
          object ToolBar1: TToolBar
            Left = 1
            Top = 1
            Width = 1123
            Height = 50
            ButtonHeight = 44
            Caption = 'ToolBar1'
            TabOrder = 1
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
