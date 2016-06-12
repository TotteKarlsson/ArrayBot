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
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object logLabel: TLabel
    Left = 32
    Top = 200
    Width = 79
    Height = 22
    Caption = 'Initializing...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -16
    Font.Name = 'Myriad Pro'
    Font.Style = []
    ParentFont = False
    StyleElements = [seClient, seBorder]
  end
  object Label1: TLabel
    Left = 289
    Top = 321
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
  object closeTimer: TTimer
    Enabled = False
    Interval = 50
    OnTimer = closeTimerTimer
    Left = 48
    Top = 240
  end
end
