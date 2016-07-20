object Main: TMain
  Left = 0
  Top = 0
  Caption = 'ArrayBot Version 0.5.8'
  ClientHeight = 791
  ClientWidth = 1087
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
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
  TextHeight = 23
  object mButtonPanel: TPanel
    Left = 904
    Top = 0
    Width = 183
    Height = 791
    Align = alRight
    TabOrder = 0
    object mAboutBtn: TSpeedButton
      Left = 1
      Top = 1
      Width = 181
      Height = 134
      Align = alTop
      AllowAllUp = True
      Caption = 'About'
      ExplicitTop = -57
      ExplicitWidth = 125
    end
    object BottomBtnPanel: TPanel
      Left = 1
      Top = 663
      Width = 181
      Height = 127
      Align = alBottom
      AutoSize = True
      TabOrder = 0
      ExplicitTop = 538
      object Button5: TSpeedButton
        Left = 1
        Top = 1
        Width = 179
        Height = 125
        Action = FileExit1
        Align = alBottom
      end
    end
  end
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 904
    Height = 791
    Align = alClient
    Constraints.MinHeight = 348
    Constraints.MinWidth = 670
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 902
      Height = 789
      ActivePage = TabSheet4
      Align = alClient
      TabHeight = 60
      TabOrder = 0
      TabWidth = 150
      object TabSheet4: TTabSheet
        Caption = 'The Bot'
      end
      object TabSheet2: TTabSheet
        Caption = 'Settings'
        ImageIndex = 2
      end
      object TabSheet5: TTabSheet
        Caption = 'Logging'
        ImageIndex = 4
        object BottomPanel: TPanel
          Left = 0
          Top = 0
          Width = 894
          Height = 719
          Align = alClient
          TabOrder = 0
          object infoMemo: TMemo
            Left = 1
            Top = 31
            Width = 892
            Height = 687
            Align = alClient
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            ScrollBars = ssBoth
            TabOrder = 0
            WordWrap = False
          end
          object ToolBar1: TToolBar
            Left = 1
            Top = 1
            Width = 892
            Height = 30
            AutoSize = True
            ButtonHeight = 30
            Caption = 'ToolBar1'
            TabOrder = 1
            object BitBtn2: TBitBtn
              Left = 0
              Top = 0
              Width = 75
              Height = 30
              Caption = 'Clear'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
            end
            object LogLevelCB: TComboBox
              Left = 75
              Top = 0
              Width = 145
              Height = 31
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -19
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 1
              Text = 'INFO'
              Items.Strings = (
                'INFO'
                'Everything')
            end
          end
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 436
    Top = 680
    object checkForDevices: TAction
      Caption = 'Devices Check'
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
    object reInitBotA: TAction
      Caption = 'Reinitialize Devices'
    end
    object ShutDownA: TAction
      Caption = 'Disconnect Devices'
    end
    object FileExit1: TFileExit
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
    object abortLiftA: TAction
      Caption = 'Abort Lift'
    end
    object liftA: TAction
      Caption = 'Lift'
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = ShutDownTimerTimer
    Left = 652
    Top = 680
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 328
    Top = 680
  end
  object UIUpdateTimer: TTimer
    Enabled = False
    Interval = 150
    Left = 220
    Top = 680
  end
end
