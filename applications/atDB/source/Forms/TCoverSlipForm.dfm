object CoverSlipForm: TCoverSlipForm
  Left = 0
  Top = 0
  Caption = 'CoverSlip / Ribbon Information'
  ClientHeight = 597
  ClientWidth = 982
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
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object CoverslipIDCB: TDBLookupComboBox
    Left = 32
    Top = 72
    Width = 145
    Height = 21
    KeyField = 'id'
    ListField = 'id'
    ListSource = CSDataSource
    TabOrder = 0
  end
  object CSDataSource: TDataSource
    DataSet = csPGDM.csCDS
    Left = 664
    Top = 40
  end
end
