object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Arduino Controller'
  ClientHeight = 707
  ClientWidth = 986
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
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 986
    Height = 89
    Align = alTop
    TabOrder = 0
    object Button1: TArrayBotButton
      Left = 818
      Top = 1
      Width = 88
      Height = 87
      Align = alRight
      Caption = 'About'
      ParentDoubleBuffered = True
      TabOrder = 0
      OnClick = mAboutBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
    object Button5: TArrayBotButton
      Left = 906
      Top = 1
      Width = 79
      Height = 87
      Action = FileExit1
      Align = alRight
      Caption = 'E&xit'
      ParentDoubleBuffered = True
      TabOrder = 1
      SoundID = 'BUTTON_CLICK_4'
    end
  end
  object CenterPanel: TPanel
    Left = 0
    Top = 89
    Width = 986
    Height = 618
    Align = alClient
    Caption = 'CenterPanel'
    TabOrder = 1
    object Splitter1: TSplitter
      Left = 1
      Top = 419
      Width = 984
      Height = 3
      Cursor = crVSplit
      Align = alTop
      ExplicitLeft = 57
      ExplicitTop = 457
      ExplicitWidth = 821
    end
    object BottomPanel: TPanel
      Left = 1
      Top = 422
      Width = 984
      Height = 195
      Align = alClient
      TabOrder = 0
      object Panel2: TPanel
        Left = 1
        Top = 1
        Width = 982
        Height = 193
        Align = alClient
        Caption = 'Panel2'
        TabOrder = 0
        object infoMemo: TMemo
          Left = 1
          Top = 31
          Width = 980
          Height = 161
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
          Width = 980
          Height = 30
          AutoSize = True
          ButtonHeight = 30
          Caption = 'ToolBar1'
          TabOrder = 1
          object mClearLogMemoBtn: TBitBtn
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
            OnClick = mClearLogMemoBtnClick
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
            OnChange = LogLevelCBChange
            Items.Strings = (
              'INFO'
              'DEBUG'
              'DEBUG1'
              'DEBUG2'
              'DEBUG3'
              'DEBUG4'
              'DEBUG5')
          end
        end
      end
    end
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 984
      Height = 418
      ActivePage = TabSheet1
      Align = alTop
      TabOrder = 1
      object TabSheet1: TTabSheet
        Caption = 'Controls'
      end
    end
  end
  object ActionList1: TActionList
    Left = 164
    Top = 464
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
      ImageIndex = 0
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
    Left = 316
    Top = 352
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 96
    Top = 304
  end
end
