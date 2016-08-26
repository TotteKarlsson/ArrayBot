object TextInputDialog: TTextInputDialog
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'TextInputDialog'
  ClientHeight = 226
  ClientWidth = 510
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    510
    226)
  PixelsPerInch = 96
  TextHeight = 23
  object Panel1: TPanel
    Left = 0
    Top = 136
    Width = 510
    Height = 90
    Align = alBottom
    TabOrder = 0
    DesignSize = (
      510
      90)
    object Button1: TButton
      Left = 383
      Top = 16
      Width = 115
      Height = 65
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
    end
    object Button2: TButton
      Left = 262
      Top = 16
      Width = 115
      Height = 65
      Anchors = [akTop, akRight]
      Caption = 'OK'
      Enabled = False
      ModalResult = 1
      TabOrder = 1
    end
  end
  object STDStringLabeledEdit1: TSTDStringLabeledEdit
    Left = 24
    Top = 56
    Width = 452
    Height = 31
    Anchors = [akLeft, akTop, akRight]
    EditLabel.Width = 89
    EditLabel.Height = 23
    EditLabel.Caption = 'New Value'
    TabOrder = 1
  end
end
