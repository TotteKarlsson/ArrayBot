object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Array Cam 0.5'
  ClientHeight = 663
  ClientWidth = 967
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 485
    Width = 967
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 8
    ExplicitTop = 528
  end
  object Splitter2: TSplitter
    Left = 822
    Top = 0
    Height = 485
    Align = alRight
    ExplicitLeft = 784
    ExplicitTop = 184
    ExplicitHeight = 100
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 822
    Height = 485
    Align = alClient
    TabOrder = 0
  end
  object infoMemo: TMemo
    Left = 0
    Top = 488
    Width = 967
    Height = 175
    Align = alBottom
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object Panel2: TPanel
    Left = 825
    Top = 0
    Width = 142
    Height = 485
    Align = alRight
    TabOrder = 2
    object mCameraStartLiveBtn: TButton
      Left = 1
      Top = 1
      Width = 140
      Height = 65
      Align = alTop
      Caption = 'Start'
      TabOrder = 0
      OnClick = mCameraStartLiveBtnClick
    end
    object Button2: TButton
      Left = 1
      Top = 66
      Width = 140
      Height = 73
      Align = alTop
      Caption = 'Info'
      TabOrder = 1
      OnClick = Button2Click
    end
    object CheckBox1: TCheckBox
      Left = 1
      Top = 139
      Width = 140
      Height = 17
      Align = alTop
      Caption = 'CheckBox1'
      TabOrder = 2
      OnClick = CheckBox1Click
    end
    object TrackBar1: TTrackBar
      Left = 1
      Top = 156
      Width = 140
      Height = 45
      Align = alTop
      Max = 1000
      TabOrder = 3
      OnChange = TrackBar1Change
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 1
    OnTimer = Timer1Timer
    Left = 736
    Top = 232
  end
  object mShutDownTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = mShutDownTimerTimer
    Left = 808
    Top = 232
  end
end
