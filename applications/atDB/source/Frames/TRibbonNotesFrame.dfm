object RibbonNotesFrame: TRibbonNotesFrame
  Left = 0
  Top = 0
  Width = 739
  Height = 274
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 739
    Height = 274
    Align = alClient
    Caption = 'Ribbon Notes'
    TabOrder = 0
    object Panel15: TPanel
      Left = 2
      Top = 15
      Width = 185
      Height = 257
      Align = alLeft
      TabOrder = 0
      object mRibbonNotesGrid: TDBGrid
        Left = 1
        Top = 1
        Width = 183
        Height = 230
        Align = alClient
        DataSource = DataSource1
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
            FieldName = 'created_on'
            Title.Caption = 'Date'
            Width = 143
            Visible = True
          end>
      end
      object RibbonNotesNavigator: TDBNavigator
        Left = 1
        Top = 231
        Width = 183
        Height = 25
        DataSource = DataSource1
        VisibleButtons = [nbInsert, nbDelete, nbRefresh, nbApplyUpdates]
        Align = alBottom
        ConfirmDelete = False
        TabOrder = 1
        OnClick = RibbonNotesNavigatorClick
      end
    end
    object Panel16: TPanel
      Left = 187
      Top = 15
      Width = 550
      Height = 257
      Align = alClient
      TabOrder = 1
      object mRibbonNoteMemo: TDBMemo
        Left = 1
        Top = 1
        Width = 548
        Height = 230
        Align = alClient
        DataField = 'note'
        DataSource = DataSource1
        TabOrder = 0
      end
      object RibbonNoteNavigator: TDBNavigator
        Left = 1
        Top = 231
        Width = 548
        Height = 25
        DataSource = DataSource1
        VisibleButtons = [nbPost, nbCancel]
        Align = alBottom
        TabOrder = 1
      end
    end
  end
  object NotesForRibbonDS: TSQLDataSet
    CommandText = 
      'SELECT * from notes WHERE id IN '#13#10'(SELECT note_id from ribbon_no' +
      'te WHERE ribbon_id = :ribbon_id)'
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftUnknown
        Name = 'ribbon_id'
        ParamType = ptInput
      end>
    SQLConnection = pgDM.SQLConnection1
    Left = 240
    Top = 64
    object NotesForRibbonDSid: TIntegerField
      FieldName = 'id'
    end
    object NotesForRibbonDSnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftWideMemo
      Size = -1
    end
    object NotesForRibbonDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
    end
    object NotesForRibbonDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
  end
  object DataSource1: TDataSource
    DataSet = NotesForRibbonCDS
    Left = 592
    Top = 64
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = NotesForRibbonDS
    Left = 368
    Top = 72
  end
  object NotesForRibbonCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 480
    Top = 64
    object NotesForRibbonCDSid: TIntegerField
      FieldName = 'id'
    end
    object NotesForRibbonCDSnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftWideMemo
    end
    object NotesForRibbonCDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
    end
    object NotesForRibbonCDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
  end
end
