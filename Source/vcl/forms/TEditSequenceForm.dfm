object EditSequenceForm: TEditSequenceForm
  Left = 0
  Top = 0
  ActiveControl = SequenceOrderE
  BorderStyle = bsDialog
  Caption = 'Edit Sequence Form'
  ClientHeight = 275
  ClientWidth = 485
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object SequenceNameE: TSTDStringLabeledEdit
    Left = 32
    Top = 48
    Width = 161
    Height = 33
    EditLabel.Width = 27
    EditLabel.Height = 13
    EditLabel.Caption = 'Name'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object SequenceOrderE: TIntegerLabeledEdit
    Left = 308
    Top = 48
    Width = 121
    Height = 33
    EditLabel.Width = 125
    EditLabel.Height = 13
    EditLabel.Caption = 'Order (for shortcut panel)'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    Text = '0'
  end
  object OKBtn: TArrayBotButton
    Left = 279
    Top = 184
    Width = 150
    Height = 80
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 2
    SoundID = 'BUTTON_CLICK_4'
  end
  object CancelBtn: TArrayBotButton
    Left = 32
    Top = 184
    Width = 150
    Height = 80
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
    SoundID = 'BUTTON_CLICK_4'
  end
  object UseProcessControllerCB: TPropertyCheckBox
    Left = 32
    Top = 112
    Width = 473
    Height = 33
    Caption = 'Use Process Controller Form when Running'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
end
