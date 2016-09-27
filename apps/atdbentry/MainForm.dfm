object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Main'
  ClientHeight = 644
  ClientWidth = 755
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 509
    Width = 755
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 76
    ExplicitTop = 1
    ExplicitWidth = 39
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 73
    Width = 755
    Height = 436
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    ExplicitHeight = 413
    object TabSheet1: TTabSheet
      Caption = 'Blocks'
      ExplicitHeight = 385
      DesignSize = (
        747
        408)
      object mBlocksT: TRzStringGrid
        Left = 20
        Top = 31
        Width = 688
        Height = 170
        Anchors = [akLeft, akTop, akRight]
        ColCount = 1
        DefaultColWidth = 120
        FixedCols = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
        TabOrder = 0
        OnClick = mBlocksTClick
      end
      object Button1: TButton
        Left = 187
        Top = 207
        Width = 142
        Height = 65
        Caption = 'Delete Selected'
        TabOrder = 1
      end
      object ArrayBotButton2: TArrayBotButton
        Left = 20
        Top = 207
        Width = 161
        Height = 65
        Caption = 'Register New Block'
        TabOrder = 2
        OnClick = ArrayBotButton2Click
        SoundID = 'BUTTON_CLICK_4'
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 755
    Height = 73
    Align = alTop
    TabOrder = 1
    object ArrayBotButton1: TArrayBotButton
      Left = 1
      Top = 1
      Width = 137
      Height = 71
      Align = alLeft
      Caption = 'Connect to DB'
      TabOrder = 0
      OnClick = ArrayBotButton1Click
      SoundID = 'BUTTON_CLICK_4'
      ExplicitLeft = 32
      ExplicitTop = 2
      ExplicitHeight = 65
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 512
    Width = 755
    Height = 132
    Align = alBottom
    Caption = 'Panel2'
    TabOrder = 2
    object infoMemo: TMemo
      Left = 1
      Top = 42
      Width = 753
      Height = 89
      Align = alClient
      Lines.Strings = (
        'infoMemo')
      ScrollBars = ssVertical
      TabOrder = 0
      ExplicitLeft = 0
      ExplicitTop = 486
      ExplicitWidth = 755
      ExplicitHeight = 158
    end
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 753
      Height = 41
      Align = alTop
      TabOrder = 1
      ExplicitLeft = 376
      ExplicitTop = 56
      ExplicitWidth = 185
      object Button2: TButton
        Left = 1
        Top = 1
        Width = 75
        Height = 39
        Align = alLeft
        Caption = 'Clear'
        TabOrder = 0
        OnClick = Button2Click
        ExplicitLeft = 96
        ExplicitTop = 5
        ExplicitHeight = 25
      end
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = ShutDownTimerTimer
    Left = 352
    Top = 48
  end
end
