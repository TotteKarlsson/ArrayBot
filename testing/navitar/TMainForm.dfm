object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Navitar Control'
  ClientHeight = 645
  ClientWidth = 962
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 423
    Width = 962
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ExplicitLeft = 73
    ExplicitTop = 414
    ExplicitWidth = 865
  end
  object mInfoMemo: TMemo
    Left = 0
    Top = 426
    Width = 962
    Height = 219
    Align = alClient
    Lines.Strings = (
      'Memo1')
    TabOrder = 0
    ExplicitTop = 423
    ExplicitWidth = 867
    ExplicitHeight = 118
  end
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 962
    Height = 423
    Align = alTop
    TabOrder = 1
    ExplicitLeft = 248
    ExplicitTop = 344
    ExplicitWidth = 185
    ExplicitHeight = 41
    object Button1: TButton
      Left = 32
      Top = 32
      Width = 153
      Height = 57
      Caption = 'Find connected devices'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 32
      Top = 104
      Width = 153
      Height = 57
      Caption = 'Connect'
      TabOrder = 1
      OnClick = Button1Click
    end
    object GroupBox1: TGroupBox
      Left = 224
      Top = 32
      Width = 321
      Height = 97
      Caption = 'Parameters'
      TabOrder = 2
      object ProductID: TIntegerLabeledEdit
        Left = 120
        Top = 36
        Width = 121
        Height = 21
        EditLabel.Width = 51
        EditLabel.Height = 13
        EditLabel.Caption = 'Product ID'
        TabOrder = 0
        Text = '0'
      end
      object DeviceID: TIntegerLabeledEdit
        Left = 24
        Top = 36
        Width = 65
        Height = 21
        EditLabel.Width = 46
        EditLabel.Height = 13
        EditLabel.Caption = 'Device ID'
        TabOrder = 1
        Text = '0'
      end
    end
    object Zoom: TGroupBox
      Left = 224
      Top = 160
      Width = 409
      Height = 153
      Caption = 'Zoom'
      TabOrder = 3
      object Button3: TButton
        Left = 14
        Top = 24
        Width = 91
        Height = 41
        Caption = 'Home'
        TabOrder = 0
      end
      object Button4: TButton
        Left = 111
        Top = 24
        Width = 91
        Height = 41
        Caption = 'Limit'
        TabOrder = 1
      end
      object CurrentPosition: TIntegerLabeledEdit
        Left = 224
        Top = 40
        Width = 121
        Height = 21
        EditLabel.Width = 77
        EditLabel.Height = 13
        EditLabel.Caption = 'Current Position'
        TabOrder = 2
        Text = '0'
      end
    end
  end
  object mShutDownTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = mShutDownTimerTimer
    Left = 80
    Top = 256
  end
end
