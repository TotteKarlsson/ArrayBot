object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 409
  ClientWidth = 850
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 0
    Top = 233
    Width = 850
    Height = 176
    Align = alBottom
    Lines.Strings = (
      'Memo1')
    TabOrder = 0
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 289
    Height = 233
    Align = alLeft
    Caption = 'Window Mouse Clicker'
    TabOrder = 1
    object winXLbl: TLabel
      Left = 32
      Top = 24
      Width = 13
      Height = 13
      Caption = 'X: '
    end
    object winYLbl: TLabel
      Left = 124
      Top = 24
      Width = 13
      Height = 13
      Caption = 'Y: '
    end
    object ClickX: TIntegerLabeledEdit
      Left = 136
      Top = 100
      Width = 121
      Height = 21
      EditLabel.Width = 30
      EditLabel.Height = 13
      EditLabel.Caption = 'Click X'
      TabOrder = 0
      Text = '0'
    end
    object ClickY: TIntegerLabeledEdit
      Left = 136
      Top = 143
      Width = 121
      Height = 21
      EditLabel.Width = 30
      EditLabel.Height = 13
      EditLabel.Caption = 'Click Y'
      TabOrder = 1
      Text = '0'
    end
    object Button1: TButton
      Left = 16
      Top = 100
      Width = 105
      Height = 64
      Caption = 'Click'
      TabOrder = 2
      OnClick = Button1Click
    end
  end
  object WinCaption: TSTDStringLabeledEdit
    Left = 320
    Top = 48
    Width = 105
    Height = 21
    EditLabel.Width = 55
    EditLabel.Height = 13
    EditLabel.Caption = 'WinCaption'
    TabOrder = 2
    Text = 'ELLO'
    Value = 'ELLO'
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 50
    OnTimer = Timer1Timer
    Left = 672
    Top = 48
  end
end
