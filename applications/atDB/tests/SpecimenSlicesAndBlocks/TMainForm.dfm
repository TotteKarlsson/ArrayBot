object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Specimen, Slices and Blocks'
  ClientHeight = 931
  ClientWidth = 1389
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  ShowHint = True
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 1389
    Height = 931
    Align = alClient
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 0
      Top = 73
      Width = 1385
      Height = 360
      Align = alTop
      Caption = 'Specimen'
      TabOrder = 0
      object DBGrid1: TDBGrid
        Left = 2
        Top = 112
        Width = 1381
        Height = 221
        Align = alClient
        DataSource = atdbDM.specimenDataSource
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnDblClick = DBGrid_DblClick
        Columns = <
          item
            Expanded = False
            FieldName = 'id'
            Width = 48
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'animal_id'
            Width = 171
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'LSpecie'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'intake_date'
            Width = 129
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'LUser'
            Width = 64
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'summary'
            Width = 84
            Visible = True
          end>
      end
      object SpecimenNavigator: TDBNavigator
        Left = 2
        Top = 333
        Width = 1381
        Height = 25
        DataSource = atdbDM.specimenDataSource
        VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
        Align = alBottom
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = NavigatorClick
      end
      object Panel1: TPanel
        Left = 2
        Top = 15
        Width = 1381
        Height = 97
        Align = alTop
        TabOrder = 2
        object GroupBox2: TGroupBox
          Left = 1
          Top = 1
          Width = 256
          Height = 95
          Align = alLeft
          Caption = 'Filters'
          TabOrder = 0
          object SpecieRG: TRadioGroup
            Left = 2
            Top = 15
            Width = 185
            Height = 78
            Align = alLeft
            Caption = 'Species'
            Columns = 2
            ItemIndex = 0
            Items.Strings = (
              'Human'
              'Mouse')
            TabOrder = 0
            OnClick = SpecieRGClick
          end
        end
      end
    end
    object GroupBox3: TGroupBox
      Left = 0
      Top = 0
      Width = 1385
      Height = 73
      Align = alTop
      Caption = 'Misc'
      TabOrder = 1
      object UserCB: TDBLookupComboBox
        Left = 24
        Top = 24
        Width = 145
        Height = 21
        KeyField = 'id'
        ListField = 'user_name'
        ListSource = atdbDM.usersDataSource
        TabOrder = 0
      end
    end
    object GroupBox4: TGroupBox
      Left = 0
      Top = 433
      Width = 1385
      Height = 200
      Align = alTop
      Caption = 'Slices'
      TabOrder = 2
      object DBGrid2: TDBGrid
        Left = 2
        Top = 15
        Width = 1381
        Height = 158
        Align = alClient
        DataSource = atdbDM.slicesDataSource
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnDblClick = DBGrid_DblClick
        Columns = <
          item
            Expanded = False
            FieldName = 'id'
            Width = 52
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'specimen_id'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'virus'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'virus_dilution'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'brain_region_dissection'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'culture_timeL'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'preprocess_treatment_protocolL'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'fixative_protocolL'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'fixation_protocolL'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'postfix_protocolL'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'entered_byL'
            Width = 120
            Visible = True
          end>
      end
      object SlicesNavigator: TDBNavigator
        Left = 2
        Top = 173
        Width = 1381
        Height = 25
        DataSource = atdbDM.slicesDataSource
        VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
        Align = alBottom
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = NavigatorClick
      end
    end
    object GroupBox5: TGroupBox
      Left = 0
      Top = 633
      Width = 1385
      Height = 294
      Align = alClient
      Caption = 'Blocks'
      TabOrder = 3
      object BlocksGrid: TDBGrid
        Left = 2
        Top = 15
        Width = 1381
        Height = 252
        Align = alClient
        DataSource = atdbDM.blocksDataSource
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnDblClick = DBGrid_DblClick
        Columns = <
          item
            Expanded = False
            FieldName = 'id'
            Width = 48
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'LBlockStatus'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'serial'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Cblock_label'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'date_embedded'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'LCryoProtectionProtocol'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'LFreezingProtocol'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'LSubstitutionProtocol'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'LInfiltrationProtocol'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'LEmbeddingProtocol'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'entered_byL'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'entered_on'
            Visible = True
          end>
      end
      object BlocksNavigator: TDBNavigator
        Left = 2
        Top = 267
        Width = 1381
        Height = 25
        DataSource = atdbDM.blocksDataSource
        VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
        Align = alBottom
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = NavigatorClick
      end
    end
  end
end
