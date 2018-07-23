object SelectIntegerForm: TSelectIntegerForm
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'Select a number'
  ClientHeight = 504
  ClientWidth = 623
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object mTheNumberLbl: TIntLabel
    Left = 185
    Top = 0
    Width = 438
    Height = 398
    Align = alClient
    Alignment = taCenter
    Caption = '-1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -85
    Font.Name = 'Segoe UI Semibold'
    Font.Style = [fsBold]
    ParentFont = False
    Layout = tlCenter
    Value = -1
    TheFont.Charset = DEFAULT_CHARSET
    TheFont.Color = clWindowText
    TheFont.Height = -85
    TheFont.Name = 'Segoe UI Semibold'
    TheFont.Style = [fsBold]
    ExplicitWidth = 81
    ExplicitHeight = 113
  end
  object Panel1: TPanel
    Left = 0
    Top = 398
    Width = 623
    Height = 106
    Align = alBottom
    TabOrder = 0
    object OkBtn: TArrayBotButton
      Left = 112
      Top = 32
      Width = 129
      Height = 57
      Caption = 'OK'
      ModalResult = 1
      TabOrder = 0
      SoundID = 'BUTTON_CLICK_4'
    end
    object CancelBtn: TArrayBotButton
      Left = 336
      Top = 32
      Width = 129
      Height = 57
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
      SoundID = 'BUTTON_CLICK_4'
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 185
    Height = 398
    Align = alLeft
    Caption = 'Numbers'
    TabOrder = 1
    object NumbersList: TListBox
      AlignWithMargins = True
      Left = 7
      Top = 20
      Width = 171
      Height = 371
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      BiDiMode = bdRightToLeft
      ExtendedSelect = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -32
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ItemHeight = 39
      Items.Strings = (
        '0'
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9'
        '10')
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 0
      OnClick = NumbersListClick
      OnDrawItem = NumbersListDrawItem
    end
  end
end
