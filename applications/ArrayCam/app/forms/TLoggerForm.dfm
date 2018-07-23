object LoggerForm: TLoggerForm
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'Logs'
  ClientHeight = 356
  ClientWidth = 735
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 735
    Height = 356
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    ExplicitWidth = 740
    ExplicitHeight = 425
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 733
      Height = 50
      Align = alTop
      Caption = 'Logs'
      TabOrder = 0
      ExplicitWidth = 738
      object ToolBar1: TToolBar
        Left = 2
        Top = 15
        Width = 258
        Height = 33
        Align = alLeft
        AutoSize = True
        ButtonHeight = 21
        Caption = 'ToolBar1'
        TabOrder = 0
        object mClearLogMemoBtn: TBitBtn
          Left = 0
          Top = 0
          Width = 113
          Height = 21
          Align = alLeft
          Caption = 'Clear'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          OnClick = mClearLogMemoBtnClick
        end
        object LogLevelCB: TComboBox
          Left = 113
          Top = 0
          Width = 145
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          Text = 'INFO'
          OnCloseUp = LogLevelCBCloseUp
          Items.Strings = (
            'ERROR'
            'WARNING'
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
    object infoMemo: TMemo
      Left = 1
      Top = 51
      Width = 733
      Height = 304
      Align = alClient
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 1
      WordWrap = False
      ExplicitWidth = 738
      ExplicitHeight = 373
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 50
    OnTimer = ShutDownTimerTimer
    Left = 552
    Top = 80
  end
end
