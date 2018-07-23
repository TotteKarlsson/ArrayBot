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
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  inline TLogMemoFrame1: TLogMemoFrame
    Left = 0
    Top = 0
    Width = 735
    Height = 356
    Align = alClient
    TabOrder = 0
    ExplicitLeft = 120
    ExplicitTop = 64
    ExplicitWidth = 735
    ExplicitHeight = 356
    inherited Panel1: TPanel
      Width = 735
      Height = 356
      ExplicitWidth = 735
      ExplicitHeight = 356
      inherited GroupBox1: TGroupBox
        Width = 733
        ExplicitWidth = 733
      end
      inherited infoMemo: TMemo
        Width = 733
        Height = 304
        ExplicitWidth = 733
        ExplicitHeight = 304
      end
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
