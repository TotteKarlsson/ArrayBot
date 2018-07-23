object TableUpdateForm: TTableUpdateForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'TableUpdateForm'
  ClientHeight = 609
  ClientWidth = 704
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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 704
    Height = 609
    Align = alClient
    Caption = 'Table Updater'
    TabOrder = 0
    object tableCB: TComboBox
      Left = 16
      Top = 32
      Width = 177
      Height = 21
      Style = csDropDownList
      ItemIndex = 0
      Sorted = True
      TabOrder = 0
      Text = 'blockstatus'
      OnChange = tableCBChange
      Items.Strings = (
        'blockstatus'
        'freezetype')
    end
    object DBGrid1: TDBGrid
      Left = 2
      Top = 390
      Width = 700
      Height = 217
      Align = alBottom
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
    end
    object DBNavigator1: TDBNavigator
      Left = 2
      Top = 348
      Width = 700
      Height = 42
      DataSource = DataSource1
      VisibleButtons = [nbPrior, nbNext, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
      Align = alBottom
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
    end
  end
  object SQLDataSet1: TSQLDataSet
    Params = <>
    Left = 472
    Top = 144
  end
  object ClientDataSet1: TClientDataSet
    Aggregates = <>
    Params = <>
    Left = 472
    Top = 264
  end
  object DataSetProvider1: TDataSetProvider
    Left = 472
    Top = 208
  end
  object DataSource1: TDataSource
    Left = 584
    Top = 272
  end
end
