object PrintLabelForm: TPrintLabelForm
  Left = 0
  Top = 0
  Caption = 'Print Labels'
  ClientHeight = 148
  ClientWidth = 416
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object mLblToPrint: TLabel
    Left = 24
    Top = 24
    Width = 112
    Height = 25
    Caption = 'mLblToPrint'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object mCopiesLbl: TIntegerLabeledEdit
    Left = 24
    Top = 104
    Width = 41
    Height = 21
    EditLabel.Width = 32
    EditLabel.Height = 13
    EditLabel.Caption = 'Copies'
    TabOrder = 0
    Text = '1'
    Value = 1
  end
  object mPrintButton: TButton
    Left = 188
    Top = 73
    Width = 99
    Height = 63
    Caption = 'Print'
    TabOrder = 1
    OnClick = mPrintButtonClick
  end
  object Button1: TButton
    Left = 309
    Top = 73
    Width = 99
    Height = 63
    Caption = 'Close'
    TabOrder = 2
    OnClick = Button1Click
  end
end
