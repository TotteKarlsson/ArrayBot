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
      'Database=atdb_demo'
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
    Top = 240
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
    OnCalcFields = blocksCDSCalcFields
    Left = 240
    Top = 240
    object blocksCDSid: TIntegerField
      AutoGenerateValue = arAutoInc
      FieldName = 'id'
    end
    object blocksCDScreated: TSQLTimeStampField
      AutoGenerateValue = arDefault
      DisplayLabel = 'Created On'
      FieldName = 'created'
      OnGetText = TimeStampGetText
    end
    object blocksCDScreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
    object blocksCDSmodified: TSQLTimeStampField
      FieldName = 'modified'
    end
    object blocksCDSlabel: TStringField
      DisplayLabel = 'Label'
      FieldName = 'label'
      Size = 255
    end
    object blocksCDSprocess_id: TIntegerField
      DisplayLabel = 'Process ID'
      FieldName = 'process_id'
    end
    object blocksCDSstatus: TSmallintField
      FieldName = 'status'
      Required = True
    end
    object blocksCDSLprocess_id: TIntegerField
      DisplayLabel = 'Process ID'
      FieldKind = fkLookup
      FieldName = 'Lprocess_id'
      LookupDataSet = processIDDS
      LookupKeyFields = 'process_id'
      LookupResultField = 'process_id'
      KeyFields = 'process_id'
      Lookup = True
    end
    object blocksCDSLBlockStatus: TStringField
      DisplayLabel = 'Status'
      FieldKind = fkLookup
      FieldName = 'LBlockStatus'
      LookupDataSet = blockstatusDS
      LookupKeyFields = 'id'
      LookupResultField = 'status'
      KeyFields = 'status'
      Size = 255
      Lookup = True
    end
    object blocksCDSserial: TSmallintField
      DisplayLabel = 'Serial'
      FieldName = 'serial'
      Required = True
    end
    object blocksCDSCBlockLabel: TStringField
      FieldKind = fkCalculated
      FieldName = 'Cblock_label'
      Size = 50
      Calculated = True
    end
  end
  object blocksProvider: TDataSetProvider
    DataSet = blocksDS
    Options = [poFetchBlobsOnDemand, poAllowCommandText, poUseQuoteChar]
    Left = 136
    Top = 240
  end
  object blocksDS: TSQLDataSet
    CommandText = 
      'select * from block WHERE process_id = :process_id ORDER by id D' +
      'ESC'
    DataSource = specimenDSrc
    MaxBlobSize = 1
    Params = <
      item
        DataType = ftInteger
        Name = 'process_id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 240
    object blocksDSid: TIntegerField
      FieldName = 'id'
    end
    object blocksDSprocess_id: TIntegerField
      FieldName = 'process_id'
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
    object blocksDSstatus: TSmallintField
      FieldName = 'status'
      Required = True
    end
    object blocksDSlabel: TStringField
      FieldName = 'label'
      Required = True
      Size = 255
    end
    object blocksDSserial: TSmallintField
      FieldName = 'serial'
      Required = True
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
    Top = 312
  end
  object blockNotesProvider: TDataSetProvider
    DataSet = blockNotesDS
    Left = 160
    Top = 312
  end
  object blockNotesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'blockNotesProvider'
    AfterPost = cdsAfterPost
    AfterDelete = cdsAfterDelete
    Left = 272
    Top = 312
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
    Left = 472
    Top = 56
  end
  object notesProvider: TDataSetProvider
    DataSet = noteDS
    Left = 568
    Top = 56
  end
  object notesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'notesProvider'
    AfterPost = cdsAfterPost
    Left = 672
    Top = 56
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
    Left = 768
    Top = 56
  end
  object mRibbonProvider: TDataSetProvider
    DataSet = ribbonsDS
    Left = 128
    Top = 392
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
    Top = 392
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
      OnGetText = TimeStampGetText
    end
    object mRibbonCDSmodified: TSQLTimeStampField
      FieldName = 'modified'
    end
  end
  object mRibbonDSource: TDataSource
    DataSet = mRibbonCDS
    Left = 336
    Top = 392
  end
  object ribbonNotesProvider: TDataSetProvider
    DataSet = ribbonNotesDS
    Left = 152
    Top = 472
  end
  object ribbonNotesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'ribbonNotesProvider'
    AfterPost = cdsAfterPost
    Left = 264
    Top = 472
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
    Top = 472
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
    Top = 392
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
    Top = 312
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
        DataType = ftString
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 48
    Top = 472
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
  object specimenDS: TSQLDataSet
    CommandText = 'SELECT * from specimen order by process_id'
    MaxBlobSize = 1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 32
    Top = 160
    object specimenDSprocess_id: TIntegerField
      FieldName = 'process_id'
    end
    object specimenDSspecimen_id: TStringField
      FieldName = 'specimen_id'
      Required = True
      Size = 255
    end
    object specimenDSspecie: TSmallintField
      FieldName = 'specie'
    end
    object specimenDSadditional_identifier: TStringField
      FieldName = 'additional_identifier'
      Size = 255
    end
    object specimenDSage: TStringField
      FieldName = 'age'
      Size = 255
    end
    object specimenDSlims_number: TIntegerField
      FieldName = 'lims_number'
    end
    object specimenDSdeath_date: TDateField
      FieldName = 'death_date'
    end
    object specimenDSpreprocess_treatment: TSmallintField
      FieldName = 'preprocess_treatment'
    end
    object specimenDSfixative: TSmallintField
      FieldName = 'fixative'
    end
    object specimenDSfixation_method: TSmallintField
      DisplayWidth = 50
      FieldName = 'fixation_method'
    end
    object specimenDSbrain_region_dissection: TStringField
      FieldName = 'brain_region_dissection'
      Size = 255
    end
    object specimenDSpostfix_protocol: TSmallintField
      FieldName = 'postfix_protocol'
    end
    object specimenDSdate_received: TDateField
      FieldName = 'date_received'
    end
    object specimenDSdate_embedded: TDateField
      FieldName = 'date_embedded'
    end
    object specimenDScryoprotection_protocol: TSmallintField
      FieldName = 'cryoprotection_protocol'
    end
    object specimenDSfreezing_protocol: TSmallintField
      FieldName = 'freezing_protocol'
    end
    object specimenDSsubstitution_protocol: TSmallintField
      FieldName = 'substitution_protocol'
    end
    object specimenDSinfiltration_protocol: TSmallintField
      FieldName = 'infiltration_protocol'
    end
    object specimenDSembedding_protocol: TSmallintField
      FieldName = 'embedding_protocol'
    end
  end
  object specimenProvider: TDataSetProvider
    DataSet = specimenDS
    Left = 136
    Top = 160
  end
  object specimenCDS: TClientDataSet
    Aggregates = <>
    FieldDefs = <
      item
        Name = 'process_id'
        DataType = ftInteger
      end
      item
        Name = 'specimen_id'
        Attributes = [faRequired]
        DataType = ftString
        Size = 255
      end
      item
        Name = 'specie'
        DataType = ftSmallint
      end
      item
        Name = 'additional_identifier'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'age'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'lims_number'
        DataType = ftInteger
      end
      item
        Name = 'death_date'
        DataType = ftDate
      end
      item
        Name = 'preprocess_treatment'
        DataType = ftSmallint
      end
      item
        Name = 'fixative'
        DataType = ftSmallint
      end
      item
        Name = 'fixation_method'
        DataType = ftSmallint
      end
      item
        Name = 'brain_region_dissection'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'postfix_protocol'
        DataType = ftSmallint
      end
      item
        Name = 'date_received'
        DataType = ftDate
      end
      item
        Name = 'date_embedded'
        DataType = ftDate
      end
      item
        Name = 'cryoprotection_protocol'
        DataType = ftSmallint
      end
      item
        Name = 'freezing_protocol'
        DataType = ftSmallint
      end
      item
        Name = 'substitution_protocol'
        DataType = ftSmallint
      end
      item
        Name = 'infiltration_protocol'
        DataType = ftSmallint
      end
      item
        Name = 'embedding_protocol'
        DataType = ftSmallint
      end>
    IndexDefs = <>
    Params = <>
    ProviderName = 'specimenProvider'
    StoreDefs = True
    BeforeClose = specimenCDSBeforeClose
    AfterPost = cdsAfterPost
    AfterScroll = cdsAfterScroll
    BeforeRefresh = cdsBeforeRefresh
    AfterRefresh = cdsAfterRefresh
    Left = 248
    Top = 160
    object specimenCDSprocess_id: TIntegerField
      DisplayLabel = 'Process ID'
      FieldName = 'process_id'
    end
    object specimenCDSspeciment_id: TStringField
      DisplayLabel = 'Specimen ID'
      FieldName = 'specimen_id'
      Required = True
      Size = 255
    end
    object specimenCDSspecies: TIntegerField
      DisplayLabel = 'Species'
      FieldName = 'specie'
    end
    object specimenCDSadditional_identifier: TStringField
      DisplayLabel = 'Additional Identifier'
      FieldName = 'additional_identifier'
      Size = 255
    end
    object specimenCDSage: TStringField
      DisplayLabel = 'Age'
      FieldName = 'age'
      Size = 255
    end
    object specimenCDSlims_number: TIntegerField
      DisplayLabel = 'LIMS'
      FieldName = 'lims_number'
    end
    object specimenCDSdeath_date: TDateField
      DisplayLabel = 'DOD'
      FieldName = 'death_date'
    end
    object specimenCDSpreprocess_treatment: TSmallintField
      DisplayLabel = 'Preprocess Treatment'
      FieldName = 'preprocess_treatment'
    end
    object specimenCDSfixative: TSmallintField
      DisplayLabel = 'Fixative'
      FieldName = 'fixative'
    end
    object specimenCDSfixation_method: TSmallintField
      DisplayLabel = 'Fixation Method'
      DisplayWidth = 50
      FieldName = 'fixation_method'
    end
    object specimenCDSbrain_region_dissection: TStringField
      DisplayLabel = 'From Brain Region'
      FieldName = 'brain_region_dissection'
      Size = 255
    end
    object specimenCDSpostfix_protocol: TShortintField
      DisplayLabel = 'Postfix Protocol'
      FieldName = 'postfix_protocol'
    end
    object specimenCDSdate_received: TDateField
      DisplayLabel = 'Date Received'
      FieldName = 'date_received'
    end
    object specimenCDSdate_embedded: TDateField
      DisplayLabel = 'Date Embedded'
      FieldName = 'date_embedded'
    end
    object specimenCDScryoprotection_protocol: TShortintField
      DisplayLabel = 'Cryoprotection Protocol'
      FieldName = 'cryoprotection_protocol'
    end
    object specimenCDSfreezing_protocol: TShortintField
      DisplayLabel = 'Freezing Protocol'
      FieldName = 'freezing_protocol'
    end
    object specimenCDSsubstitution_protocol: TShortintField
      DisplayLabel = 'Substitution Protocol'
      FieldName = 'substitution_protocol'
    end
    object specimenCDSinfiltration_protocol: TShortintField
      DisplayLabel = 'Infiltration Protocol'
      FieldName = 'infiltration_protocol'
    end
    object specimenCDSembedding_protocol: TShortintField
      DisplayLabel = 'Embedding Protocol'
      FieldName = 'embedding_protocol'
    end
    object specimenCDSLpreproctreat: TStringField
      DisplayLabel = 'PreProcess Treatment'
      FieldKind = fkLookup
      FieldName = 'Lpreproctreat'
      LookupDataSet = preprocesstreatmentDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'preprocess_treatment'
      Size = 255
      Lookup = True
    end
    object specimenCDSLspecie: TStringField
      DisplayLabel = 'Specie'
      FieldKind = fkLookup
      FieldName = 'Lspecie'
      LookupDataSet = speciesDS
      LookupKeyFields = 'id'
      LookupResultField = 'name'
      KeyFields = 'specie'
      Size = 255
      Lookup = True
    end
    object specimenCDSLFixative: TStringField
      FieldKind = fkLookup
      FieldName = 'LFixative'
      LookupDataSet = fixativeTBL
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'fixative'
      Size = 255
      Lookup = True
    end
    object specimenCDSLfixationMethod: TStringField
      DisplayLabel = 'Fixation Method'
      DisplayWidth = 60
      FieldKind = fkLookup
      FieldName = 'LfixationMethod'
      LookupDataSet = fixationMethodDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'fixation_method'
      Size = 255
      Lookup = True
    end
    object specimenCDSLpostfix: TStringField
      DisplayLabel = 'PostFix'
      FieldKind = fkLookup
      FieldName = 'Lpostfix'
      LookupDataSet = postfix
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'postfix_protocol'
      Size = 255
      Lookup = True
    end
    object specimenCDSLcryoprotection: TStringField
      DisplayLabel = 'Cryo Protection'
      FieldKind = fkLookup
      FieldName = 'Lcryoprotection'
      LookupDataSet = cryoprotectionDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'cryoprotection_protocol'
      Size = 255
      Lookup = True
    end
    object specimenCDSLfreezeProtocol: TStringField
      DisplayLabel = 'Freeze Protocol'
      FieldKind = fkLookup
      FieldName = 'LfreezeProtocol'
      LookupDataSet = freezeprotocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'freezing_protocol'
      Size = 255
      Lookup = True
    end
    object specimenCDSLsubstitutionProtocol: TStringField
      DisplayLabel = 'Substitution Protocol'
      FieldKind = fkLookup
      FieldName = 'LsubstitutionProtocol'
      LookupDataSet = substitutionProtocol
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'substitution_protocol'
      Size = 255
      Lookup = True
    end
    object specimenCDSLinfiltration: TStringField
      DisplayLabel = 'Infilatration'
      FieldKind = fkLookup
      FieldName = 'Linfiltration'
      LookupDataSet = infiltrationProtocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'infiltration_protocol'
      Size = 255
      Lookup = True
    end
    object specimenCDSLembedding: TStringField
      DisplayLabel = 'Embedding'
      FieldKind = fkLookup
      FieldName = 'Lembedding'
      LookupDataSet = embeddingProtocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'embedding_protocol'
      Size = 255
      Lookup = True
    end
  end
  object specimenDSrc: TDataSource
    DataSet = specimenCDS
    Left = 344
    Top = 160
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
    DataSet.CommandText = 'SELECT * from specie'
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
    FieldDefs = <
      item
        Name = 'id'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'protocol'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'document_id'
        DataType = ftInteger
      end>
    IndexDefs = <>
    Params = <>
    StoreDefs = True
    Left = 720
    Top = 408
    object substitutionProtocolid: TSmallintField
      FieldName = 'id'
      Required = True
    end
    object substitutionProtocolprotocol: TStringField
      FieldName = 'protocol'
      Size = 255
    end
    object substitutionProtocoldocument_id: TIntegerField
      FieldName = 'document_id'
    end
    object substitutionProtocolLDocument: TStringField
      FieldKind = fkLookup
      FieldName = 'LDocument'
      LookupDataSet = documentsCDS
      LookupKeyFields = 'document_name'
      LookupResultField = 'id'
      KeyFields = 'document_id'
      Lookup = True
    end
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
    Left = 472
    Top = 264
  end
  object processIDDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'SELECT process_id  FROM specimen'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 552
    Top = 264
  end
  object documentsDS: TSQLDataSet
    CommandText = 'SELECT * from document'
    MaxBlobSize = 1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 32
    Top = 576
    object documentsDSid: TIntegerField
      FieldName = 'id'
      Required = True
    end
    object documentsDSdocument_name: TStringField
      FieldName = 'document_name'
      Required = True
      Size = 255
    end
    object documentsDSdocument: TBlobField
      FieldName = 'document'
      Size = 1
    end
    object documentsDStype: TStringField
      FieldName = 'type'
      Size = 16
    end
  end
  object documentsProvider: TDataSetProvider
    DataSet = documentsDS
    Left = 136
    Top = 576
  end
  object documentsCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'documentsProvider'
    Left = 224
    Top = 576
    object documentsCDSid: TIntegerField
      FieldName = 'id'
      Required = True
    end
    object documentsCDSdocument_name: TStringField
      DisplayLabel = 'Name'
      FieldName = 'document_name'
      Required = True
      Size = 255
    end
    object documentsCDSdocument: TBlobField
      FieldName = 'document'
      Size = 1
    end
    object documentsCDStype: TStringField
      DisplayLabel = 'Type'
      FieldName = 'type'
      Size = 16
    end
  end
  object documentsDSource: TDataSource
    DataSet = documentsCDS
    Left = 336
    Top = 584
  end
end
