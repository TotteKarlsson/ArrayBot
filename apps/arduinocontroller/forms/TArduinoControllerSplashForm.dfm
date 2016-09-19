object ArduinoControllerSplashForm: TArduinoControllerSplashForm
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'ArduinoControllerSplashForm'
  ClientHeight = 359
  ClientWidth = 615
  Color = clHighlight
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  StyleElements = [seFont, seBorder]
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 289
    Top = 325
    Width = 311
    Height = 30
    Caption = 'Smith Lab.  - Allen institute 2016'
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -21
    Font.Name = 'Segoe UI Semibold'
    Font.Style = [fsItalic]
    ParentColor = False
    ParentFont = False
    StyleElements = [seClient, seBorder]
  end
  inline TAboutArduinoServerFrame1: TAboutArduinoServerFrame
    Left = 0
    Top = 0
    Width = 615
    Height = 301
    Align = alTop
    TabOrder = 0
    ExplicitWidth = 615
    ExplicitHeight = 301
    inherited Image1: TImage
      Width = 164
      ExplicitWidth = 164
    end
    inherited mChangeLogMemo: TMemo
      Top = -9
      Width = 615
      ExplicitTop = -9
      ExplicitWidth = 615
    end
  end
  object closeTimer: TTimer
    Enabled = False
    Interval = 50
    OnTimer = closeTimerTimer
    Left = 48
    Top = 240
  end
end
