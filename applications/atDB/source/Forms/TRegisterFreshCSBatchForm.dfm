object RegisterFreshCSBatchForm: TRegisterFreshCSBatchForm
  Left = 0
  Top = 0
  Caption = 'Register Fresh Coverslip Batch'
  ClientHeight = 127
  ClientWidth = 483
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 168
    Top = 24
    Width = 24
    Height = 13
    Caption = 'Type'
  end
  object Label2: TLabel
    Left = 346
    Top = 24
    Width = 23
    Height = 13
    Caption = 'Date'
  end
  object mDT: TDateTimePicker
    Left = 344
    Top = 40
    Width = 121
    Height = 21
    Date = 0.587392870373150800
    Time = 0.587392870373150800
    Enabled = False
    TabOrder = 0
  end
  object mCSCount: TIntegerLabeledEdit
    Left = 16
    Top = 40
    Width = 121
    Height = 21
    EditLabel.Width = 102
    EditLabel.Height = 13
    EditLabel.Caption = 'Number of Coverslips'
    TabOrder = 1
    Text = '100'
    Value = 100
  end
  object mCSTypeLookup: TDBLookupComboBox
    Left = 168
    Top = 40
    Width = 145
    Height = 21
    KeyField = 'id'
    ListField = 'type'
    ListSource = csPGDM.csTypeDSource
    TabOrder = 2
  end
  object mRegisterBtn: TButton
    Left = 344
    Top = 67
    Width = 121
    Height = 50
    Caption = 'Register'
    TabOrder = 3
    OnClick = mRegisterBtnClick
  end
  object mCoverSlipLOTE: TSTDStringLabeledEdit
    Left = 16
    Top = 96
    Width = 121
    Height = 21
    EditLabel.Width = 98
    EditLabel.Height = 13
    EditLabel.Caption = 'Manufacturer LOT #'
    TabOrder = 4
  end
  object mBoxof100NrEdit: TSTDStringLabeledEdit
    Left = 168
    Top = 96
    Width = 121
    Height = 21
    EditLabel.Width = 78
    EditLabel.Height = 13
    EditLabel.Caption = 'Box # From LOT'
    TabOrder = 5
    Text = '-1'
    Visible = False
    Value = '-1'
  end
end
