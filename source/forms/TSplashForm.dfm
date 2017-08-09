object SplashForm: TSplashForm
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'SplashForm'
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
    Left = 128
    Top = 321
    Width = 440
    Height = 30
    Margins.Right = 15
    AutoSize = False
    Caption = 'Smith Lab.  - Allen Institute 2016-2017'
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
  inline TAboutArrayBotFrame1: TAboutArrayBotFrame
    Left = 0
    Top = 0
    Width = 615
    Height = 301
    Align = alTop
    TabOrder = 0
    ExplicitWidth = 615
    inherited Image1: TImage
      Width = 164
      ExplicitWidth = 164
    end
    inherited Image2: TImage
      Width = 615
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
