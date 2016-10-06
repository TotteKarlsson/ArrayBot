object atdbDM: TatdbDM
  OldCreateOrder = False
  Height = 720
  Width = 647
  object SQLConnection1: TSQLConnection
    DriverName = 'MySQL'
    KeepConnection = False
    LoginPrompt = False
    Params.Strings = (
      'DriverUnit=Data.DBXMySQL'
      
        'DriverPackageLoader=TDBXDynalinkDriverLoader,DbxCommonDriver170.' +
        'bpl'
      
        'DriverAssemblyLoader=Borland.Data.TDBXDynalinkDriverLoader,Borla' +
        'nd.Data.DbxCommonDriver,Version=17.0.0.0,Culture=neutral,PublicK' +
        'eyToken=91d62ebb5b0d1b1b'
      
        'MetaDataPackageLoader=TDBXMySqlMetaDataCommandFactory,DbxMySQLDr' +
        'iver170.bpl'
      
        'MetaDataAssemblyLoader=Borland.Data.TDBXMySqlMetaDataCommandFact' +
        'ory,Borland.Data.DbxMySQLDriver,Version=17.0.0.0,Culture=neutral' +
        ',PublicKeyToken=91d62ebb5b0d1b1b'
      'GetDriverFunc=getSQLDriverMYSQL'
      'LibraryName=dbxmys.dll'
      'LibraryNameOsx=libsqlmys.dylib'
      'VendorLib=LIBMYSQL.dll'
      'VendorLibWin64=libmysql.dll'
      'VendorLibOsx=libmysqlclient.dylib'
      'HostName=localhost'
      'Database=atdb'
      'User_Name=atdb_client'
      'Password=atdb123'
      'MaxBlobSize=-1'
      'LocaleCode=0000'
      'Compressed=False'
      'Encrypted=False'
      'BlobSize=-1'
      'ErrorResourceFile=')
    AfterConnect = SQLConnection1AfterConnect
    BeforeConnect = SQLConnection1BeforeConnect
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
      AutoGenerateValue = arAutoInc
      FieldName = 'id'
    end
    object blocksCDScreated: TSQLTimeStampField
      AutoGenerateValue = arDefault
      FieldName = 'created'
    end
    object blocksCDScreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
    object blocksCDSmodified: TSQLTimeStampField
      FieldName = 'modified'
    end
    object blocksCDSstatus: TIntegerField
      FieldName = 'status'
    end
    object blocksCDSlabel: TMemoField
      FieldName = 'label'
      BlobType = ftMemo
      Size = 1
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
    CommandText = 'select * from block'
    DataSource = mRibbonDSource
    MaxBlobSize = 1
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
      Required = True
    end
    object blocksDSmodified: TSQLTimeStampField
      FieldName = 'modified'
    end
    object blocksDSstatus: TIntegerField
      FieldName = 'status'
    end
    object blocksDSlabel: TMemoField
      FieldName = 'label'
      BlobType = ftMemo
      Size = 1
    end
  end
  object usersDS: TSQLDataSet
    CommandText = 'select * from user'
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 88
    object usersDSid: TIntegerField
      FieldName = 'id'
    end
    object usersDSuser_name: TStringField
      FieldName = 'user_name'
      Required = True
      Size = 255
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
  object usersCDS: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'usersProvider'
    AfterPost = usersCDSAfterPost
    AfterCancel = usersCDSAfterCancel
    AfterDelete = usersCDSAfterDelete
    AfterScroll = usersCDSAfterScroll
    Left = 240
    Top = 88
    object usersCDSid: TIntegerField
      FieldName = 'id'
    end
    object usersCDSuser_name: TStringField
      FieldName = 'user_name'
      Required = True
      Size = 255
    end
    object usersCDScreated: TSQLTimeStampField
      FieldName = 'created'
    end
  end
  object usersDataSource: TDataSource
    DataSet = usersCDS
    Left = 336
    Top = 88
  end
  object blockNotesQ: TSQLQuery
    Active = True
    DataSource = blocksDataSource
    MaxBlobSize = 1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQL.Strings = (
      'SELECT * FROM note n '
      'INNER JOIN block_note bn '
      'ON (bn.note_id = n.id) '
      'WHERE block_id = :id '
      'ORDER BY created_on ASC')
    SQLConnection = SQLConnection1
    Left = 48
    Top = 392
    object blockNotesQid: TIntegerField
      FieldName = 'id'
    end
    object blockNotesQnote: TMemoField
      FieldName = 'note'
      BlobType = ftMemo
      Size = 1
    end
    object blockNotesQcreated_on: TSQLTimeStampField
      FieldName = 'created_on'
    end
    object blockNotesQcreated_by: TMemoField
      FieldName = 'created_by'
      BlobType = ftMemo
      Size = 1
    end
    object blockNotesQblock_id: TIntegerField
      FieldName = 'block_id'
      Required = True
    end
    object blockNotesQnote_id: TIntegerField
      FieldName = 'note_id'
      Required = True
    end
  end
  object blockNotesDSource: TDataSource
    DataSet = blockNotesCDS
    Left = 352
    Top = 392
  end
  object blockNotesProvider: TDataSetProvider
    DataSet = blockNotesQ
    Left = 144
    Top = 392
  end
  object blockNotesCDS: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'blockNotesProvider'
    AfterPost = blockNotesCDSAfterPost
    Left = 256
    Top = 392
    object blockNotesCDSid: TIntegerField
      DisplayWidth = 6
      FieldName = 'id'
    end
    object blockNotesCDSnote: TMemoField
      DisplayWidth = 11
      FieldName = 'note'
      BlobType = ftMemo
      Size = 1
    end
    object blockNotesCDScreated_on: TSQLTimeStampField
      DisplayWidth = 41
      FieldName = 'created_on'
    end
    object blockNotesCDScreated_by: TMemoField
      DisplayWidth = 12
      FieldName = 'created_by'
      BlobType = ftMemo
      Size = 1
    end
    object blockNotesCDSblock_id: TIntegerField
      DisplayWidth = 12
      FieldName = 'block_id'
      Required = True
    end
    object blockNotesCDSnote_id: TIntegerField
      DisplayWidth = 12
      FieldName = 'note_id'
      Required = True
    end
  end
  object noteDS: TSQLDataSet
    Active = True
    CommandText = 'select * from note'
    DataSource = blocksDataSource
    MaxBlobSize = 1
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
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
      Required = True
    end
    object notesCDSnote: TMemoField
      FieldName = 'note'
      Required = True
      BlobType = ftMemo
      Size = 1
    end
    object notesCDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
      Required = True
    end
    object notesCDScreated_by: TMemoField
      FieldName = 'created_by'
      Required = True
      BlobType = ftMemo
      Size = 1
    end
  end
  object notesDSource: TDataSource
    DataSet = notesCDS
    Left = 328
    Top = 640
  end
  object mRibbonProvider: TDataSetProvider
    DataSet = ribbonsQ
    Left = 128
    Top = 224
  end
  object mRibbonCDS: TClientDataSet
    Active = True
    Aggregates = <>
    MasterFields = 'id'
    Params = <>
    ProviderName = 'mRibbonProvider'
    BeforePost = mRibbonCDSBeforePost
    AfterPost = mRibbonCDSAfterPost
    AfterDelete = mRibbonCDSAfterDelete
    OnCalcFields = mRibbonCDSCalcFields
    Left = 240
    Top = 224
    object mRibbonCDSid: TStringField
      FieldName = 'id'
      Size = 36
    end
    object mRibbonCDSstatus: TIntegerField
      FieldName = 'status'
    end
    object mRibbonCDScreated: TSQLTimeStampField
      FieldName = 'created'
    end
    object mRibbonCDSmodified: TSQLTimeStampField
      FieldName = 'modified'
    end
    object mRibbonCDSblock_id: TIntegerField
      FieldName = 'block_id'
      Required = True
    end
    object mRibbonCDScutting_order: TIntegerField
      FieldName = 'cutting_order'
    end
    object mRibbonCDSnr_of_sections: TSmallintField
      FieldName = 'nr_of_sections'
    end
  end
  object mRibbonDSource: TDataSource
    DataSet = mRibbonCDS
    Left = 336
    Top = 224
  end
  object ribbonsQ: TSQLQuery
    DataSource = blocksDataSource
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQL.Strings = (
      'select * from ribbon where block_id = :BLOCK_ID')
    SQLConnection = SQLConnection1
    Left = 32
    Top = 224
    object ribbonsQid: TStringField
      FieldName = 'id'
      Size = 36
    end
    object ribbonsQstatus: TIntegerField
      FieldName = 'status'
    end
    object ribbonsQcreated: TSQLTimeStampField
      FieldName = 'created'
    end
    object ribbonsQmodified: TSQLTimeStampField
      FieldName = 'modified'
    end
    object ribbonsQblock_id: TIntegerField
      FieldName = 'block_id'
      Required = True
    end
    object ribbonsQcutting_order: TIntegerField
      FieldName = 'cutting_order'
    end
    object ribbonsQnr_of_sections: TSmallintField
      FieldName = 'nr_of_sections'
    end
  end
end
