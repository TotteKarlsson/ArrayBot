inherited BlockEntryForm: TBlockEntryForm
  BorderStyle = bsDialog
  Caption = 'BlockEntryForm'
  ClientHeight = 332
  ClientWidth = 316
  Position = poOwnerFormCenter
  OnShow = FormShow
  ExplicitWidth = 322
  ExplicitHeight = 360
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel [0]
    Left = 16
    Top = 13
    Width = 22
    Height = 13
    Caption = 'User'
  end
  object Label2: TLabel [1]
    Left = 16
    Top = 117
    Width = 23
    Height = 13
    Caption = 'Note'
  end
  object mUserCB: TComboBox [2]
    Left = 16
    Top = 32
    Width = 281
    Height = 21
    Style = csDropDownList
    TabOrder = 0
  end
  object mBlockNote: TMemo [3]
    Left = 16
    Top = 136
    Width = 281
    Height = 124
    TabOrder = 2
  end
  object mBlockLabel: TLabeledEdit [4]
    Left = 16
    Top = 84
    Width = 281
    Height = 21
    EditLabel.Width = 121
    EditLabel.Height = 13
    EditLabel.Caption = 'Label (10 characters min)'
    TabOrder = 1
  end
  inherited Panel1: TPanel
    Top = 276
    Width = 316
    TabOrder = 3
    ExplicitTop = 276
    ExplicitWidth = 316
    inherited mSubmitButton: TButton
      Left = 236
      ExplicitLeft = 236
    end
    inherited mCancelBtn: TButton
      Left = 154
      ExplicitLeft = 154
    end
  end
  object mValidateTimer: TTimer
    Interval = 100
    OnTimer = mValidateTimerTimer
    Left = 256
    Top = 112
  end
end
