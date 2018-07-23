object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 282
  ClientWidth = 1325
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid1: TDBGrid
    Left = 0
    Top = 25
    Width = 1325
    Height = 257
    Align = alClient
    DataSource = atdbDM.slicesDataSource
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'specimen_id'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'case_id'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lims_number'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'virus'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'age'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'death_date'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'brain_region_dissection'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'entered_by'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'culture_time'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'LEnteredBy'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'LCulturedTP'
        Width = 80
        Visible = True
      end>
  end
  object DBNavigator1: TDBNavigator
    Left = 0
    Top = 0
    Width = 1325
    Height = 25
    DataSource = atdbDM.slicesDataSource
    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
    Align = alTop
    TabOrder = 1
    OnClick = DBNavigator1Click
    ExplicitWidth = 771
  end
end
