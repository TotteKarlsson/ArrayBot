inherited BlockEntryForm: TBlockEntryForm
  BorderStyle = bsDialog
  Caption = 'BlockEntryForm'
  ClientHeight = 329
  ClientWidth = 526
  Position = poOwnerFormCenter
  OnShow = FormShow
  ExplicitWidth = 532
  ExplicitHeight = 357
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel [0]
    Left = 16
    Top = 13
    Width = 22
    Height = 13
    Caption = 'User'
  end
  object mUserCB: TComboBox [1]
    Left = 16
    Top = 32
    Width = 145
    Height = 21
    Style = csDropDownList
    TabOrder = 2
  end
  object mBlockNote: TLabeledEdit [2]
    Left = 16
    Top = 136
    Width = 297
    Height = 21
    EditLabel.Width = 23
    EditLabel.Height = 13
    EditLabel.Caption = 'Note'
    TabOrder = 1
  end
  object mBlockLabel: TLabeledEdit [3]
    Left = 16
    Top = 84
    Width = 121
    Height = 21
    EditLabel.Width = 25
    EditLabel.Height = 13
    EditLabel.Caption = 'Label'
    TabOrder = 0
  end
  inherited Panel1: TPanel
    Top = 263
    Width = 526
    TabOrder = 3
    ExplicitTop = 263
    ExplicitWidth = 526
  end
end
