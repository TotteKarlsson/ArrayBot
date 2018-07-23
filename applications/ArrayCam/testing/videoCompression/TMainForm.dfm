object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Compressor'
  ClientHeight = 861
  ClientWidth = 1503
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
  PixelsPerInch = 96
  TextHeight = 13
  object infoMemo: TMemo
    Left = 0
    Top = 705
    Width = 1503
    Height = 156
    Align = alBottom
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
    WordWrap = False
  end
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 1503
    Height = 440
    Align = alTop
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 505
      Height = 438
      Align = alLeft
      Caption = 'File Selection'
      TabOrder = 0
      object FileListBox1: TFileListBox
        Left = 2
        Top = 56
        Width = 501
        Height = 299
        Align = alClient
        ItemHeight = 13
        Mask = '*.avi'
        MultiSelect = True
        TabOrder = 0
        ExplicitTop = 36
        ExplicitHeight = 400
      end
      object CompressBtn: TArrayBotButton
        Left = 2
        Top = 355
        Width = 501
        Height = 81
        Align = alBottom
        Caption = 'Compress selected'
        TabOrder = 1
        OnClick = CompressBtnClick
        SoundID = 'BUTTON_CLICK_4'
        ExplicitLeft = 368
        ExplicitTop = 327
        ExplicitWidth = 137
      end
      object Panel1: TPanel
        Left = 2
        Top = 15
        Width = 501
        Height = 41
        Align = alTop
        TabOrder = 2
        ExplicitLeft = 248
        ExplicitTop = 24
        ExplicitWidth = 185
        object MovieFolder: TSTDStringEdit
          Left = 9
          Top = 11
          Width = 440
          Height = 24
          TabOrder = 0
          Text = 'P:\videoCompressor\Movies'
          Value = 'P:\videoCompressor\Movies'
        end
        object Button1: TButton
          Left = 455
          Top = 10
          Width = 34
          Height = 25
          Action = BrowseForFolder1
          TabOrder = 1
        end
      end
    end
    inline TFFMPEGFrame1: TFFMPEGFrame
      Left = 506
      Top = 1
      Width = 996
      Height = 438
      Align = alClient
      AutoSize = True
      TabOrder = 1
      ExplicitLeft = 632
      ExplicitTop = 32
    end
  end
  object MPEGPanel: TFlowPanel
    Left = 0
    Top = 440
    Width = 1503
    Height = 265
    Align = alClient
    TabOrder = 2
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 50
    OnTimer = ShutDownTimerTimer
    Left = 256
    Top = 136
  end
  object CleanupTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = CleanupTimerTimer
    Left = 408
    Top = 240
  end
  object ActionList1: TActionList
    Left = 360
    Top = 120
    object BrowseForFolder1: TBrowseForFolder
      Category = 'File'
      Caption = '...'
      DialogCaption = '...'
      BrowseOptions = [bifBrowseForComputer, bifEditBox, bifNewDialogStyle]
      OnAccept = BrowseForFolder1Accept
    end
  end
end
