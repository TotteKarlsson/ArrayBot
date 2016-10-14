object atdbDM: TatdbDM
  OldCreateOrder = False
  Height = 765
  Width = 887
  object SQLConnection1: TSQLConnection
    DriverName = 'MySQL'
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
    Left = 40
    Top = 24
  end
  object blocksDataSource: TDataSource
    DataSet = blocksCDS
    Left = 336
    Top = 152
  end
  object blocksCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'blocksProvider'
    BeforePost = cdsBeforePost
    AfterPost = cdsAfterPost
    AfterDelete = cdsAfterDelete
    AfterScroll = cdsAfterScroll
    AfterRefresh = cdsAfterRefresh
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
    object blocksCDSfreeze_type: TIntegerField
      FieldName = 'freeze_type'
    end
    object blocksCDSlabel: TStringField
      FieldName = 'label'
      Size = 255
    end
    object blocksCDSlBlockStatus: TStringField
      FieldKind = fkLookup
      FieldName = 'lBlockStatus'
      LookupDataSet = blockstatusDS
      LookupKeyFields = 'id'
      LookupResultField = 'status'
      KeyFields = 'status'
      Lookup = True
    end
    object blocksCDSLFreezeType: TStringField
      FieldKind = fkLookup
      FieldName = 'LFreezeType'
      LookupDataSet = freezeprotocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'freeze_type'
      Lookup = True
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
    CommandText = 'select * from block ORDER by id DESC'
    MaxBlobSize = 1
    Params = <>
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
    object blocksDSfreeze_type: TIntegerField
      FieldName = 'freeze_type'
    end
    object blocksDSlabel: TStringField
      FieldName = 'label'
      Size = 255
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
    Aggregates = <>
    Params = <>
    ProviderName = 'usersProvider'
    AfterPost = cdsAfterPost
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
  object blockNotesDSource: TDataSource
    DataSet = blockNotesCDS
    Left = 368
    Top = 224
  end
  object blockNotesProvider: TDataSetProvider
    DataSet = blockNotesDS
    Left = 160
    Top = 224
  end
  object blockNotesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'blockNotesProvider'
    AfterPost = cdsAfterPost
    AfterDelete = cdsAfterDelete
    Left = 272
    Top = 224
    object blockNotesCDSid: TIntegerField
      FieldName = 'id'
      Required = True
    end
    object blockNotesCDSnote: TMemoField
      FieldName = 'note'
      Required = True
      BlobType = ftMemo
      Size = 1
    end
    object blockNotesCDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
      Required = True
    end
    object blockNotesCDScreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
  end
  object noteDS: TSQLDataSet
    CommandText = 'select * from note'
    DataSource = notesDSource
    MaxBlobSize = 1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 544
    Top = 88
  end
  object notesProvider: TDataSetProvider
    DataSet = noteDS
    Left = 640
    Top = 88
  end
  object notesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'notesProvider'
    AfterPost = cdsAfterPost
    Left = 744
    Top = 88
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
    object notesCDScreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
  end
  object notesDSource: TDataSource
    DataSet = notesCDS
    Left = 840
    Top = 88
  end
  object mRibbonProvider: TDataSetProvider
    DataSet = ribbonsDS
    Left = 128
    Top = 304
  end
  object mRibbonCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'mRibbonProvider'
    BeforePost = cdsBeforePost
    AfterPost = cdsAfterPost
    AfterDelete = cdsAfterDelete
    AfterScroll = cdsAfterScroll
    AfterRefresh = cdsAfterRefresh
    OnCalcFields = mRibbonCDSCalcFields
    Left = 240
    Top = 304
    object mRibbonCDSid: TStringField
      FieldName = 'id'
      Size = 36
    end
    object mRibbonCDSstatus: TIntegerField
      FieldName = 'status'
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
    object mRibbonCDScreated: TSQLTimeStampField
      FieldName = 'created'
    end
    object mRibbonCDSmodified: TSQLTimeStampField
      FieldName = 'modified'
    end
  end
  object mRibbonDSource: TDataSource
    DataSet = mRibbonCDS
    Left = 336
    Top = 304
  end
  object ribbonNotesProvider: TDataSetProvider
    DataSet = ribbonNotesDS
    Left = 152
    Top = 384
  end
  object ribbonNotesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'ribbonNotesProvider'
    AfterPost = cdsAfterPost
    Left = 264
    Top = 384
    object ribbonNotesCDSid: TIntegerField
      FieldName = 'id'
      Required = True
    end
    object ribbonNotesCDSnote: TMemoField
      FieldName = 'note'
      Required = True
      BlobType = ftMemo
      Size = 1
    end
    object ribbonNotesCDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
      Required = True
    end
    object ribbonNotesCDScreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
  end
  object ribbonNotesDSource: TDataSource
    DataSet = ribbonNotesCDS
    Left = 360
    Top = 384
  end
  object ribbonsDS: TSQLDataSet
    CommandText = 'SELECT * from ribbon where block_id=:id'
    DataSource = blocksDataSource
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 32
    Top = 304
    object ribbonsDSid: TStringField
      FieldName = 'id'
      Size = 36
    end
    object ribbonsDSstatus: TIntegerField
      FieldName = 'status'
    end
    object ribbonsDSblock_id: TIntegerField
      FieldName = 'block_id'
      Required = True
    end
    object ribbonsDScutting_order: TIntegerField
      FieldName = 'cutting_order'
    end
    object ribbonsDSnr_of_sections: TSmallintField
      FieldName = 'nr_of_sections'
    end
    object ribbonsDScreated: TSQLTimeStampField
      FieldName = 'created'
    end
    object ribbonsDSmodified: TSQLTimeStampField
      FieldName = 'modified'
    end
  end
  object blockNotesDS: TSQLDataSet
    CommandText = 
      'SELECT * FROM note n '#13#10'INNER JOIN block_note bn '#13#10'ON (bn.note_id' +
      ' = n.id) '#13#10'WHERE block_id = :id '#13#10'ORDER BY created_on ASC'
    DataSource = blocksDataSource
    MaxBlobSize = 1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 64
    Top = 224
    object blockNotesDSid: TIntegerField
      FieldName = 'id'
      Required = True
    end
    object blockNotesDSnote: TMemoField
      FieldName = 'note'
      Required = True
      BlobType = ftMemo
      Size = 1
    end
    object blockNotesDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
      Required = True
    end
    object blockNotesDScreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
  end
  object ribbonNotesDS: TSQLDataSet
    CommandText = 
      'SELECT * FROM note n '#13#10'INNER JOIN ribbon_note rn '#13#10'ON (rn.note_i' +
      'd = n.id) '#13#10'WHERE ribbon_id = :id '#13#10'ORDER BY created_on ASC'
    DataSource = mRibbonDSource
    MaxBlobSize = 1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 48
    Top = 384
    object ribbonNotesDSid: TIntegerField
      FieldName = 'id'
      Required = True
    end
    object ribbonNotesDSnote: TMemoField
      FieldName = 'note'
      BlobType = ftMemo
      Size = 1
    end
    object ribbonNotesDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
    end
    object ribbonNotesDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
  end
  object specimentDS: TSQLDataSet
    CommandText = 'select * from speciment order by id'
    MaxBlobSize = 1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 472
    object specimentDSid: TIntegerField
      FieldName = 'id'
    end
    object specimentDSspeciment_id: TStringField
      FieldName = 'speciment_id'
      Required = True
      Size = 255
    end
    object specimentDSspecies: TIntegerField
      FieldName = 'species'
    end
    object specimentDSadditional_identifier: TStringField
      FieldName = 'additional_identifier'
      Size = 255
    end
    object specimentDSage: TStringField
      FieldName = 'age'
      Size = 255
    end
    object specimentDSlims_number: TIntegerField
      FieldName = 'lims_number'
    end
    object specimentDSdeath_date: TDateField
      FieldName = 'death_date'
    end
    object specimentDSpreprocess_treatment: TSmallintField
      FieldName = 'preprocess_treatment'
    end
    object specimentDSfixative: TSmallintField
      FieldName = 'fixative'
    end
    object specimentDSfixation_method: TSmallintField
      FieldName = 'fixation_method'
    end
    object specimentDSbrain_region_dissection: TStringField
      FieldName = 'brain_region_dissection'
      Size = 255
    end
    object specimentDSpostfix_protocol: TShortintField
      FieldName = 'postfix_protocol'
    end
    object specimentDSdate_received: TDateField
      FieldName = 'date_received'
    end
    object specimentDSdate_embedded: TDateField
      FieldName = 'date_embedded'
    end
    object specimentDScryoprotection_protocol: TShortintField
      FieldName = 'cryoprotection_protocol'
    end
    object specimentDSfreezing_protocol: TShortintField
      FieldName = 'freezing_protocol'
    end
    object specimentDSsubstitution_protocol: TShortintField
      FieldName = 'substitution_protocol'
    end
    object specimentDSinfiltration_protocol: TShortintField
      FieldName = 'infiltration_protocol'
    end
    object specimentDSembedding_protocol: TShortintField
      FieldName = 'embedding_protocol'
    end
  end
  object specimentProvider: TDataSetProvider
    DataSet = specimentDS
    Left = 144
    Top = 472
  end
  object specimentCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'specimentProvider'
    Left = 256
    Top = 472
    object specimentCDSid: TIntegerField
      FieldName = 'id'
    end
    object specimentCDSspeciment_id: TStringField
      FieldName = 'speciment_id'
      Required = True
      Size = 255
    end
    object specimentCDSspecies: TIntegerField
      FieldName = 'species'
    end
    object specimentCDSadditional_identifier: TStringField
      FieldName = 'additional_identifier'
      Size = 255
    end
    object specimentCDSage: TStringField
      FieldName = 'age'
      Size = 255
    end
    object specimentCDSlims_number: TIntegerField
      FieldName = 'lims_number'
    end
    object specimentCDSdeath_date: TDateField
      FieldName = 'death_date'
    end
    object specimentCDSpreprocess_treatment: TSmallintField
      FieldName = 'preprocess_treatment'
    end
    object specimentCDSfixative: TSmallintField
      FieldName = 'fixative'
    end
    object specimentCDSfixation_method: TSmallintField
      FieldName = 'fixation_method'
    end
    object specimentCDSbrain_region_dissection: TStringField
      FieldName = 'brain_region_dissection'
      Size = 255
    end
    object specimentCDSpostfix_protocol: TShortintField
      FieldName = 'postfix_protocol'
    end
    object specimentCDSdate_received: TDateField
      FieldName = 'date_received'
    end
    object specimentCDSdate_embedded: TDateField
      FieldName = 'date_embedded'
    end
    object specimentCDScryoprotection_protocol: TShortintField
      FieldName = 'cryoprotection_protocol'
    end
    object specimentCDSfreezing_protocol: TShortintField
      FieldName = 'freezing_protocol'
    end
    object specimentCDSsubstitution_protocol: TShortintField
      FieldName = 'substitution_protocol'
    end
    object specimentCDSinfiltration_protocol: TShortintField
      FieldName = 'infiltration_protocol'
    end
    object specimentCDSembedding_protocol: TShortintField
      FieldName = 'embedding_protocol'
    end
    object specimentCDSLpreproctreat: TStringField
      FieldKind = fkLookup
      FieldName = 'Lpreproctreat'
      LookupDataSet = preprocesstreatmentDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'preprocess_treatment'
      Lookup = True
    end
    object specimentCDSLspecie: TStringField
      FieldKind = fkLookup
      FieldName = 'Lspecie'
      LookupDataSet = speciesDS
      LookupKeyFields = 'id'
      LookupResultField = 'name'
      KeyFields = 'species'
      Lookup = True
    end
    object specimentCDSLFixative: TStringField
      FieldKind = fkLookup
      FieldName = 'LFixative'
      LookupDataSet = fixativeTBL
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'fixative'
      Lookup = True
    end
    object specimentCDSLfixationMethod: TStringField
      FieldKind = fkLookup
      FieldName = 'LfixationMethod'
      LookupDataSet = fixationMethodDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'fixation_method'
      Lookup = True
    end
    object specimentCDSLpostfix: TStringField
      FieldKind = fkLookup
      FieldName = 'Lpostfix'
      LookupDataSet = postfix
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'postfix_protocol'
      Lookup = True
    end
    object specimentCDSLcryoprotection: TStringField
      FieldKind = fkLookup
      FieldName = 'Lcryoprotection'
      LookupDataSet = cryoprotectionDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'cryoprotection_protocol'
      Lookup = True
    end
    object specimentCDSLfreezeProtocol: TStringField
      FieldKind = fkLookup
      FieldName = 'LfreezeProtocol'
      LookupDataSet = freezeprotocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'freezing_protocol'
      Lookup = True
    end
    object specimentCDSLsubstitutionProtocol: TStringField
      FieldKind = fkLookup
      FieldName = 'LsubstitutionProtocol'
      LookupDataSet = substitutionProtocol
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'substitution_protocol'
      Lookup = True
    end
    object specimentCDSLinfiltration: TStringField
      FieldKind = fkLookup
      FieldName = 'Linfiltration'
      LookupDataSet = infiltrationProtocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'infiltration_protocol'
      Lookup = True
    end
    object specimentCDSLembedding: TStringField
      FieldKind = fkLookup
      FieldName = 'Lembedding'
      LookupDataSet = embeddingProtocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'embedding_protocol'
      Lookup = True
    end
  end
  object specimentDSrc: TDataSource
    DataSet = specimentCDS
    Left = 352
    Top = 472
  end
  object fixativeTBL: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'SELECT * from fixative'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    AfterPost = fixativeTBLAfterPost
    Left = 472
    Top = 504
  end
  object speciesDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'SELECT * from species'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 472
    Top = 568
  end
  object preprocesstreatmentDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from  preprocesstreatment'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 472
    Top = 632
  end
  object fixationMethodDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from `fixmethod`'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 568
    Top = 504
  end
  object postfix: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from postfix'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 568
    Top = 568
  end
  object cryoprotectionDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from cryoprotection'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 576
    Top = 632
  end
  object freezeprotocolDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from freezeprotocol'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 672
    Top = 504
  end
  object substitutionProtocol: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from substitution'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 672
    Top = 568
  end
  object infiltrationProtocolDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from infiltration'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 672
    Top = 632
  end
  object embeddingProtocolDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from embedding'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 784
    Top = 504
  end
  object blockstatusDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'SELECT * from blockstatus'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    AfterPost = fixativeTBLAfterPost
    Left = 464
    Top = 192
  end
end
