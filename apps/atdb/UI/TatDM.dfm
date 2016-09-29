object atDM: TatDM
  OldCreateOrder = False
  Height = 744
  Width = 647
  object SQLConnection1: TSQLConnection
    ConnectionName = 'ATDBDebug'
    DriverName = 'DevartSQLite'
    LoginPrompt = False
    Params.Strings = (
      'DriverName=DevartSQLite'
      'DriverUnit=DbxDevartSQLite'
      
        'DriverPackageLoader=TDBXDynalinkDriverLoader,DBXCommonDriver170.' +
        'bpl'
      
        'MetaDataPackageLoader=TDBXDevartSQLiteMetaDataCommandFactory,Dbx' +
        'DevartSQLiteDriver170.bpl'
      'ProductName=DevartSQLite'
      'LibraryName=dbexpsqlite40.dll'
      'VendorLib=sqlite3.dll'
      'Database=p:\iBot\db\atDB.db'
      'LocaleCode=0000'
      'IsolationLevel=ReadCommitted'
      'ASCIIDataBase=False'
      'BusyTimeout=0'
      'EnableSharedCache=False'
      'MaxBlobSize=-1'
      'FetchAll=True'
      'ForceCreateDatabase=False'
      'ForeignKeys=True'
      'UseUnicode=True'
      'EnableLoadExtension=False'
      'BlobSize=-1')
    AfterConnect = SQLConnection1AfterConnect
    Connected = True
    Left = 40
    Top = 24
  end
  object blocksDataSource: TDataSource
    DataSet = blocksCDS
    Left = 336
    Top = 152
  end
  object blocksCDS: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'blocksProvider'
    BeforePost = blocksCDSBeforePost
    AfterPost = blocksCDSAfterPost
    AfterDelete = blocksCDSAfterDelete
    AfterScroll = blocksCDSAfterScroll
    Left = 240
    Top = 152
    object blocksCDSid: TIntegerField
      Alignment = taLeftJustify
      FieldName = 'id'
    end
    object blocksCDScreated: TSQLTimeStampField
      FieldName = 'created'
    end
    object blocksCDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
    object blocksCDSmodified: TSQLTimeStampField
      FieldName = 'modified'
    end
    object blocksCDSstatus: TIntegerField
      FieldName = 'status'
    end
    object blocksCDSlabel: TWideStringField
      FieldName = 'label'
      Size = 400
    end
  end
  object blocksProvider: TDataSetProvider
    DataSet = blocksDS
    Options = [poFetchBlobsOnDemand, poUseQuoteChar]
    Left = 136
    Top = 152
  end
  object blocksDS: TSQLDataSet
    ObjectView = True
    Active = True
    CommandText = 'select * from block'
    DataSource = mRibbonDSource
    MaxBlobSize = -1
    Params = <>
    SortFieldNames = 'id'
    SQLConnection = SQLConnection1
    Left = 40
    Top = 152
    object blocksDSid: TIntegerField
      FieldName = 'id'
    end
    object blocksDScreated: TSQLTimeStampField
      FieldName = 'created'
    end
    object blocksDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
    object blocksDSmodified: TSQLTimeStampField
      FieldName = 'modified'
    end
    object blocksDSstatus: TIntegerField
      FieldName = 'status'
    end
    object blocksDSlabel: TWideStringField
      FieldName = 'label'
      Size = 400
    end
  end
  object usersDS: TSQLDataSet
    Active = True
    CommandText = 'select * from user'
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 88
    object usersDSid: TIntegerField
      FieldName = 'id'
    end
    object usersDSuser_name: TWideMemoField
      FieldName = 'user_name'
      OnValidate = usersDSuser_nameValidate
      BlobType = ftWideMemo
      Size = -1
    end
    object usersDScreated: TSQLTimeStampField
      FieldName = 'created'
    end
  end
  object usersProvider: TDataSetProvider
    DataSet = usersDS
    Options = [poFetchBlobsOnDemand, poUseQuoteChar]
    Left = 136
    Top = 88
  end
  object usersClientDataSet: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'usersProvider'
    BeforeInsert = usersClientDataSetBeforeInsert
    BeforePost = usersClientDataSetBeforePost
    AfterPost = usersClientDataSetAfterPost
    AfterCancel = usersClientDataSetAfterCancel
    AfterDelete = usersClientDataSetAfterDelete
    AfterScroll = usersClientDataSetAfterScroll
    BeforeApplyUpdates = usersClientDataSetBeforeApplyUpdates
    Left = 240
    Top = 88
    object usersClientDataSetid: TIntegerField
      FieldName = 'id'
    end
    object usersClientDataSetuser_name: TWideMemoField
      FieldName = 'user_name'
      OnGetText = usersClientDataSetuser_nameGetText
      BlobType = ftWideMemo
    end
    object usersClientDataSetcreated: TSQLTimeStampField
      FieldName = 'created'
    end
  end
  object usersDataSource: TDataSource
    DataSet = usersClientDataSet
    Left = 336
    Top = 88
  end
  object blockNotesQ: TSQLQuery
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftUnknown
        Name = 'blockID'
        ParamType = ptInput
      end>
    SQL.Strings = (
      'SELECT * FROM note n '
      'INNER JOIN block_note bn '
      'ON (bn.note_id = n.id) '
      'WHERE block_id = :blockID '
      'ORDER BY created_on ASC')
    SQLConnection = SQLConnection1
    Left = 232
    Top = 560
  end
  object blockNotesDSource: TDataSource
    DataSet = blockNotesDSet
    Left = 544
    Top = 560
  end
  object blockNotesProvider: TDataSetProvider
    DataSet = blockNotesQ
    Left = 336
    Top = 560
  end
  object blockNotesDSet: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'blockNotesProvider'
    AfterPost = blockNotesDSetAfterPost
    Left = 448
    Top = 560
    object blockNotesDSetid: TIntegerField
      FieldName = 'id'
    end
    object blockNotesDSetnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftWideMemo
    end
    object blockNotesDSetcreated_on: TSQLTimeStampField
      FieldName = 'created_on'
    end
    object blockNotesDSetcreated_by: TWideStringField
      FieldName = 'created_by'
      Size = 512
    end
    object blockNotesDSetblock_id: TIntegerField
      FieldName = 'block_id'
    end
    object blockNotesDSetnote_id: TIntegerField
      FieldName = 'note_id'
    end
  end
  object updateNoteQ: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 464
    Top = 632
  end
  object noteDS: TSQLDataSet
    Active = True
    CommandText = 'select * from note'
    DataSource = blocksDataSource
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 32
    Top = 640
  end
  object notesProvider: TDataSetProvider
    DataSet = noteDS
    Left = 128
    Top = 640
  end
  object notesCDS: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'notesProvider'
    Left = 232
    Top = 640
    object notesCDSid: TIntegerField
      FieldName = 'id'
    end
    object notesCDSnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftWideMemo
    end
    object notesCDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
    end
    object notesCDScreated_by: TWideStringField
      FieldName = 'created_by'
      Size = 512
    end
  end
  object notesDSource: TDataSource
    Left = 328
    Top = 640
  end
  object mRibbonProvider: TDataSetProvider
    DataSet = ribbonsQ
    Left = 128
    Top = 224
  end
  object mRibbonCDSet: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'mRibbonProvider'
    BeforePost = mRibbonCDSetBeforePost
    AfterPost = mRibbonCDSetAfterPost
    AfterDelete = mRibbonCDSetAfterDelete
    OnCalcFields = mRibbonCDSetCalcFields
    Left = 240
    Top = 224
    object mRibbonCDSetid: TIntegerField
      Alignment = taLeftJustify
      DisplayWidth = 11
      FieldName = 'id'
    end
    object mRibbonCDSetblock_id: TIntegerField
      Alignment = taLeftJustify
      DisplayWidth = 12
      FieldName = 'block_id'
    end
    object mRibbonCDSetstatus: TIntegerField
      DisplayWidth = 12
      FieldName = 'status'
    end
    object mRibbonCDSetcreated: TSQLTimeStampField
      DisplayWidth = 14
      FieldName = 'created'
    end
    object mRibbonCDSetmodified: TSQLTimeStampField
      DisplayWidth = 15
      FieldName = 'modified'
    end
    object mRibbonCDSetcutting_order: TIntegerField
      DisplayWidth = 13
      FieldName = 'cutting_order'
    end
    object mRibbonCDSetnotes: TWideMemoField
      DisplayWidth = 12
      FieldName = 'notes'
      BlobType = ftWideMemo
    end
    object mRibbonCDSetbar_code: TIntegerField
      FieldKind = fkCalculated
      FieldName = 'bar_code'
      Calculated = True
    end
  end
  object mRibbonDSource: TDataSource
    DataSet = mRibbonCDSet
    Left = 336
    Top = 224
  end
  object ribbonsQ: TSQLQuery
    Active = True
    DataSource = mRibbonDSource
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftInteger
        Name = 'ID'
        ParamType = ptInput
      end>
    SQL.Strings = (
      'select * from ribbon where block_id = :ID')
    SQLConnection = SQLConnection1
    Left = 32
    Top = 224
  end
end
