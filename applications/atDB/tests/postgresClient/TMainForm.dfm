object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'ATDB Master'
  ClientHeight = 753
  ClientWidth = 1278
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 169
    Width = 1278
    Height = 584
    ActivePage = TabSheet5
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Specimen'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 1270
        Height = 556
        Align = alClient
        Caption = 'Specimen'
        TabOrder = 0
        object DBGrid1: TDBGrid
          Left = 2
          Top = 73
          Width = 1266
          Height = 481
          Align = alClient
          DataSource = pgDM.specimenDataSource
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
          Columns = <
            item
              Expanded = False
              FieldName = 'id'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'animal_id'
              Width = 127
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'intake_date'
              Width = 119
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'LSpecie'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'summary'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'LUser'
              Width = 80
              Visible = True
            end>
        end
        object DBNavigator1: TDBNavigator
          Left = 2
          Top = 15
          Width = 1266
          Height = 58
          DataSource = pgDM.specimenDataSource
          VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
          Align = alTop
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Slices'
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox2: TGroupBox
        Left = 0
        Top = 0
        Width = 1270
        Height = 556
        Align = alClient
        Caption = 'Slices'
        TabOrder = 0
        object DBGrid2: TDBGrid
          Left = 2
          Top = 81
          Width = 1266
          Height = 473
          Align = alClient
          DataSource = pgDM.slicesDataSource
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
          Columns = <
            item
              Expanded = False
              FieldName = 'id'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'specimen_id'
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
              FieldName = 'virus_dilution'
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
              FieldName = 'culture_timeL'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'preprocess_treatment_protocolL'
              Width = 190
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'fixative_protocolL'
              Width = 152
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'fixation_protocolL'
              Width = 170
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'postfix_protocolL'
              Width = 174
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'entered_byL'
              Visible = True
            end>
        end
        object DBNavigator2: TDBNavigator
          Left = 2
          Top = 15
          Width = 1266
          Height = 66
          DataSource = pgDM.slicesDataSource
          VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
          Align = alTop
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Blocks'
      ImageIndex = 3
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object DBGrid4: TDBGrid
        Left = 0
        Top = 0
        Width = 89
        Height = 556
        Align = alLeft
        DataSource = pgDM.slicesDataSource
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        Columns = <
          item
            Alignment = taCenter
            Expanded = False
            FieldName = 'id'
            Visible = True
          end>
      end
      object Panel2: TPanel
        Left = 89
        Top = 0
        Width = 1181
        Height = 556
        Align = alClient
        Caption = 'Panel2'
        TabOrder = 1
        object DBGrid5: TDBGrid
          Left = 1
          Top = 1
          Width = 1179
          Height = 529
          Align = alClient
          DataSource = pgDM.blocksDataSource
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
        end
        object DBNavigator4: TDBNavigator
          Left = 1
          Top = 530
          Width = 1179
          Height = 25
          DataSource = pgDM.blocksDataSource
          Align = alBottom
          TabOrder = 1
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Ribbons'
      ImageIndex = 4
      object DBGrid6: TDBGrid
        Left = 0
        Top = 0
        Width = 1270
        Height = 531
        Align = alClient
        DataSource = pgDM.ribbonsDSource
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        Columns = <
          item
            Expanded = False
            FieldName = 'id'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'status'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'block_id'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'cutting_order'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'nr_of_sections'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'modified'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'created_by'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'coverslip_id'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'statusL'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'created_byL'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'created_on'
            Visible = True
          end>
      end
      object DBNavigator5: TDBNavigator
        Left = 0
        Top = 531
        Width = 1270
        Height = 25
        DataSource = pgDM.ribbonsDSource
        VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
        Align = alBottom
        TabOrder = 1
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Notes'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object DBGrid3: TDBGrid
        Left = 0
        Top = 0
        Width = 377
        Height = 556
        Align = alLeft
        DataSource = pgDM.notesDSource
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        Columns = <
          item
            Expanded = False
            FieldName = 'id'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'note'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'created_on'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'created_by'
            Visible = True
          end>
      end
      object DBMemo1: TDBMemo
        Left = 408
        Top = 16
        Width = 529
        Height = 281
        DataField = 'note'
        DataSource = pgDM.notesDSource
        TabOrder = 1
      end
      object DBNavigator3: TDBNavigator
        Left = 408
        Top = 322
        Width = 528
        Height = 25
        DataSource = pgDM.notesDSource
        VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
        TabOrder = 2
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1278
    Height = 169
    Align = alTop
    Caption = 'Panel1'
    TabOrder = 1
    inline TPGConnectionFrame1: TPGConnectionFrame
      Left = 1
      Top = 1
      Width = 286
      Height = 167
      Align = alLeft
      AutoSize = True
      TabOrder = 0
      ExplicitLeft = 1
      ExplicitTop = 1
      ExplicitHeight = 167
      inherited GBox1: TGroupBox
        inherited mDBUserE: TSTDStringLabeledEdit
          Text = 'admin'
          Value = 'admin'
        end
        inherited mPasswordE: TSTDStringLabeledEdit
          Text = 'totte'
          Value = 'totte'
        end
        inherited mDatabaseE: TSTDStringLabeledEdit
          Text = 'sg2'
          Value = 'sg2'
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 696
    Top = 56
    object ConnectToDBA: TAction
      Caption = 'ToggleDbConenctionA'
    end
  end
  object AllBlocksDSrc: TDataSource
    DataSet = pgDM.blocksDS
    Left = 480
    Top = 432
  end
end
