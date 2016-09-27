object ATDBServerEntry: TATDBServerEntry
  Left = 0
  Top = 0
  Caption = 'ATDBServerEntry'
  ClientHeight = 312
  ClientWidth = 513
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 246
    Width = 513
    Height = 66
    Align = alBottom
    TabOrder = 0
    object Button1: TButton
      Left = 416
      Top = 16
      Width = 83
      Height = 41
      Caption = 'Submit'
      ModalResult = 1
      TabOrder = 0
    end
    object Button2: TButton
      Left = 319
      Top = 16
      Width = 83
      Height = 41
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
    end
  end
end
