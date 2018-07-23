object atdbDM: TatdbDM
  OldCreateOrder = False
  Height = 1042
  Width = 1038
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
      'HostName=atdb'
      'Database=atdb-live'
      'User_Name=atdb'
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
    Top = 352
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
    Top = 352
    object blocksCDSid: TIntegerField
      AutoGenerateValue = arAutoInc
      FieldName = 'id'
    end
    object blocksCDSslice_id: TIntegerField
      FieldName = 'slice_id'
    end
    object blocksCDSentered_by: TIntegerField
      FieldName = 'entered_by'
      Required = True
    end
    object blocksCDSentered_on: TSQLTimeStampField
      FieldName = 'entered_on'
      Required = True
    end
    object blocksCDSlabel: TStringField
      DisplayLabel = 'Label'
      FieldName = 'label'
      Size = 255
    end
    object blocksCDSstatus: TSmallintField
      FieldName = 'status'
      Required = True
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
      Alignment = taLeftJustify
      DisplayLabel = 'Serial'
      FieldName = 'serial'
      Required = True
    end
    object blocksCDSCBlockLabel: TStringField
      DisplayLabel = 'Label'
      FieldKind = fkCalculated
      FieldName = 'Cblock_label'
      Size = 50
      Calculated = True
    end
    object blocksCDSdate_embedded: TDateField
      DisplayLabel = 'Date Embedded'
      FieldName = 'date_embedded'
    end
    object blocksCDScryoprotection_protocol: TSmallintField
      FieldName = 'cryoprotection_protocol'
    end
    object blocksCDSfreezing_protocol: TSmallintField
      FieldName = 'freezing_protocol'
    end
    object blocksCDSsubstitution_protocol: TSmallintField
      FieldName = 'substitution_protocol'
    end
    object blocksCDSinfiltration_protocol: TSmallintField
      FieldName = 'infiltration_protocol'
    end
    object blocksCDSembedding_protocol: TSmallintField
      FieldName = 'embedding_protocol'
    end
    object blocksCDSLCryoProtectionProtocol: TStringField
      DisplayLabel = 'Cryoprotection Protocol'
      FieldKind = fkLookup
      FieldName = 'LCryoProtectionProtocol'
      LookupDataSet = cryoprotectionDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'cryoprotection_protocol'
      Lookup = True
    end
    object blocksCDSLFreezingProtocol: TStringField
      DisplayLabel = 'Freezing Protocol'
      FieldKind = fkLookup
      FieldName = 'LFreezingProtocol'
      LookupDataSet = freezeprotocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'freezing_protocol'
      Lookup = True
    end
    object blocksCDSLSubstitutionProtocol: TStringField
      DisplayLabel = 'Substitution Protocol'
      FieldKind = fkLookup
      FieldName = 'LSubstitutionProtocol'
      LookupDataSet = substitutionProtocol
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'substitution_protocol'
      Lookup = True
    end
    object blocksCDSLInfiltrationProtocol: TStringField
      DisplayLabel = 'Infiltration Protocol'
      FieldKind = fkLookup
      FieldName = 'LInfiltrationProtocol'
      LookupDataSet = infiltrationProtocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'infiltration_protocol'
      Lookup = True
    end
    object blocksCDSLEmbeddingProtocol: TStringField
      DisplayLabel = 'Embedding Protocol'
      FieldKind = fkLookup
      FieldName = 'LEmbeddingProtocol'
      LookupDataSet = embeddingProtocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'embedding_protocol'
      Lookup = True
    end
    object blocksCDSLUser: TStringField
      DisplayLabel = 'Entered By'
      FieldKind = fkLookup
      FieldName = 'entered_byL'
      LookupDataSet = usersCDS
      LookupKeyFields = 'id'
      LookupResultField = 'user_name'
      KeyFields = 'entered_by'
      Lookup = True
    end
  end
  object blocksProvider: TDataSetProvider
    DataSet = blocksDS
    Options = [poFetchBlobsOnDemand, poAllowCommandText, poRetainServerOrder, poUseQuoteChar]
    Left = 136
    Top = 352
  end
  object blocksDS: TSQLDataSet
    CommandText = 'select * from blocks WHERE slice_id = :id ORDER by id DESC'
    DataSource = slicesDataSource
    MaxBlobSize = 1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 352
    object blocksDSid: TIntegerField
      FieldName = 'id'
    end
    object blocksDSslice_id: TIntegerField
      FieldName = 'slice_id'
    end
    object blocksDSstatus: TSmallintField
      FieldName = 'status'
      Required = True
    end
    object blocksDSentered_by: TIntegerField
      FieldName = 'entered_by'
      Required = True
    end
    object blocksDSlabel: TStringField
      FieldName = 'label'
      Size = 255
    end
    object blocksDSserial: TSmallintField
      FieldName = 'serial'
      Required = True
    end
    object blocksDSdate_embedded: TDateField
      FieldName = 'date_embedded'
    end
    object blocksDScryoprotection_protocol: TSmallintField
      FieldName = 'cryoprotection_protocol'
    end
    object blocksDSfreezing_protocol: TSmallintField
      FieldName = 'freezing_protocol'
    end
    object blocksDSsubstitution_protocol: TSmallintField
      FieldName = 'substitution_protocol'
    end
    object blocksDSinfiltration_protocol: TSmallintField
      FieldName = 'infiltration_protocol'
    end
    object blocksDSembedding_protocol: TSmallintField
      FieldName = 'embedding_protocol'
    end
    object blocksDSentered_on: TSQLTimeStampField
      FieldName = 'entered_on'
      Required = True
    end
  end
  object usersDS: TSQLDataSet
    CommandText = 'select * from users'
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
    Top = 424
  end
  object blockNotesProvider: TDataSetProvider
    DataSet = blockNotesDS
    Left = 160
    Top = 424
  end
  object blockNotesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'blockNotesProvider'
    AfterPost = cdsAfterPost
    AfterDelete = cdsAfterDelete
    Left = 272
    Top = 424
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
    CommandText = 'select * from notes'
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
    Top = 504
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
    Top = 504
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
      DisplayLabel = 'Cutting Order'
      FieldName = 'cutting_order'
    end
    object mRibbonCDSnr_of_sections: TSmallintField
      DisplayLabel = 'Nr of Sections'
      FieldName = 'nr_of_sections'
    end
    object mRibbonCDScreated: TSQLTimeStampField
      FieldName = 'created'
      OnGetText = TimeStampGetText
    end
    object mRibbonCDSmodified: TSQLTimeStampField
      FieldName = 'modified'
    end
    object mRibbonCDScreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
    object mRibbonCDScoverslip_id: TIntegerField
      DisplayLabel = 'Coverslip ID'
      FieldName = 'coverslip_id'
      Required = True
    end
    object mRibbonCDSstatusL: TStringField
      DisplayLabel = 'Status'
      FieldKind = fkLookup
      FieldName = 'statusL'
      LookupDataSet = ribbonStatusDS
      LookupKeyFields = 'id'
      LookupResultField = 'status'
      KeyFields = 'status'
      Lookup = True
    end
    object mRibbonCDScreated_byL: TStringField
      FieldKind = fkLookup
      FieldName = 'created_byL'
      LookupDataSet = usersCDS
      LookupKeyFields = 'id'
      LookupResultField = 'user_name'
      KeyFields = 'created_by'
      Lookup = True
    end
  end
  object mRibbonDSource: TDataSource
    DataSet = mRibbonCDS
    Left = 336
    Top = 504
  end
  object ribbonNotesProvider: TDataSetProvider
    DataSet = ribbonNotesDS
    Left = 152
    Top = 584
  end
  object ribbonNotesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'ribbonNotesProvider'
    AfterPost = cdsAfterPost
    Left = 264
    Top = 584
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
    Top = 584
  end
  object ribbonsDS: TSQLDataSet
    CommandText = 
      'SELECT * from ribbons where block_id=:id ORDER by cutting_order ' +
      'DESC'
    DataSource = blocksDataSource
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftUnknown
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 32
    Top = 504
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
    object ribbonsDScreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
    object ribbonsDScoverslip_id: TIntegerField
      FieldName = 'coverslip_id'
      Required = True
    end
  end
  object blockNotesDS: TSQLDataSet
    CommandText = 
      'SELECT * FROM notes n '#13#10'INNER JOIN block_note bn '#13#10'ON (bn.note_i' +
      'd = n.id) '#13#10'WHERE block_id = :id '#13#10'ORDER BY created_on ASC'
    DataSource = blocksDataSource
    MaxBlobSize = 1
    ParamCheck = False
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 64
    Top = 424
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
      'SELECT * FROM notes n '#13#10'INNER JOIN ribbon_note rn '#13#10'ON (rn.note_' +
      'id = n.id) '#13#10'WHERE ribbon_id = :id '#13#10'ORDER BY created_on ASC'
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
    Top = 584
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
  object slicesDS: TSQLDataSet
    CommandText = 'SELECT * from slices where specimen_id = :id'
    DataSource = specimenDataSource
    MaxBlobSize = 1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 32
    Top = 272
    object slicesDSid: TIntegerField
      FieldName = 'id'
    end
    object slicesDSspecimen_id: TIntegerField
      FieldName = 'specimen_id'
    end
    object slicesDSvirus: TStringField
      FieldName = 'virus'
      Size = 255
    end
    object slicesDSbrain_region_dissection: TStringField
      FieldName = 'brain_region_dissection'
      Size = 255
    end
    object slicesDSculture_time: TIntegerField
      FieldName = 'culture_time'
    end
    object slicesDSpreprocess_treatment_protocol: TSmallintField
      FieldName = 'preprocess_treatment_protocol'
    end
    object slicesDSfixative_protocol: TSmallintField
      FieldName = 'fixative_protocol'
    end
    object slicesDSfixation_protocol: TSmallintField
      FieldName = 'fixation_protocol'
    end
    object slicesDSpostfix_protocol: TSmallintField
      FieldName = 'postfix_protocol'
    end
    object slicesDSvirus_dilution: TStringField
      FieldName = 'virus_dilution'
      Size = 16
    end
    object slicesDSentered_by: TIntegerField
      FieldName = 'entered_by'
      Required = True
    end
  end
  object slicesProvider: TDataSetProvider
    DataSet = slicesDS
    Left = 136
    Top = 272
  end
  object slicesCDS: TClientDataSet
    Aggregates = <>
    FieldDefs = <
      item
        Name = 'id'
        DataType = ftInteger
      end
      item
        Name = 'specimen_id'
        DataType = ftInteger
      end
      item
        Name = 'virus'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'brain_region_dissection'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'culture_time'
        DataType = ftInteger
      end
      item
        Name = 'preprocess_treatment_protocol'
        DataType = ftSmallint
      end
      item
        Name = 'fixative_protocol'
        DataType = ftSmallint
      end
      item
        Name = 'fixation_protocol'
        DataType = ftSmallint
      end
      item
        Name = 'postfix_protocol'
        DataType = ftSmallint
      end
      item
        Name = 'virus_dilution'
        DataType = ftString
        Size = 16
      end
      item
        Name = 'entered_by'
        Attributes = [faRequired]
        DataType = ftInteger
      end>
    IndexDefs = <>
    Params = <>
    ProviderName = 'slicesProvider'
    StoreDefs = True
    AfterOpen = slicesCDSAfterOpen
    BeforeClose = slicesCDSBeforeClose
    AfterClose = slicesCDSAfterClose
    AfterPost = cdsAfterPost
    AfterScroll = cdsAfterScroll
    BeforeRefresh = cdsBeforeRefresh
    AfterRefresh = cdsAfterRefresh
    Left = 248
    Top = 272
    object slicesCDSid: TIntegerField
      FieldName = 'id'
    end
    object slicesCDSspecimen_id: TIntegerField
      DisplayLabel = 'Specimen ID'
      FieldName = 'specimen_id'
    end
    object slicesCDSvirus: TStringField
      DisplayLabel = 'Virus'
      FieldName = 'virus'
      Size = 255
    end
    object slicesCDSvirus_dilution: TStringField
      DisplayLabel = 'Virus Dilution'
      FieldName = 'virus_dilution'
      Size = 16
    end
    object slicesCDSbrain_region_dissection: TStringField
      DisplayLabel = 'Brain Region'
      FieldName = 'brain_region_dissection'
      Size = 255
    end
    object slicesCDSculture_time: TIntegerField
      FieldName = 'culture_time'
    end
    object slicesCDSculture_timeL: TStringField
      DisplayLabel = 'Culture Time'
      FieldKind = fkLookup
      FieldName = 'culture_timeL'
      LookupDataSet = culturedTimePoints
      LookupKeyFields = 'id'
      LookupResultField = 'time_point'
      KeyFields = 'culture_time'
      Lookup = True
    end
    object slicesCDSentered_by: TIntegerField
      FieldName = 'entered_by'
      Required = True
    end
    object slicesCDSentered_byL: TStringField
      DisplayLabel = 'Entered By'
      FieldKind = fkLookup
      FieldName = 'entered_byL'
      LookupDataSet = usersCDS
      LookupKeyFields = 'id'
      LookupResultField = 'user_name'
      KeyFields = 'entered_by'
      Lookup = True
    end
    object slicesCDSpreprocess_treatment_protocol: TSmallintField
      FieldName = 'preprocess_treatment_protocol'
    end
    object slicesCDSLPre: TStringField
      DisplayLabel = 'Preprocess Treatment'
      FieldKind = fkLookup
      FieldName = 'preprocess_treatment_protocolL'
      LookupDataSet = preprocesstreatmentDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'preprocess_treatment_protocol'
      Lookup = True
    end
    object slicesCDSfixative_protocol: TSmallintField
      FieldName = 'fixative_protocol'
    end
    object slicesCDSfixative_protocolL: TStringField
      DisplayLabel = 'Fixative Protocol'
      FieldKind = fkLookup
      FieldName = 'fixative_protocolL'
      LookupDataSet = fixativeTBL
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'fixative_protocol'
      Lookup = True
    end
    object slicesCDSfixation_protocol: TSmallintField
      FieldName = 'fixation_protocol'
    end
    object slicesCDSfixation_protocolL: TStringField
      DisplayLabel = 'Fixation Protocol'
      FieldKind = fkLookup
      FieldName = 'fixation_protocolL'
      LookupDataSet = fixationMethodDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'fixation_protocol'
      Lookup = True
    end
    object slicesCDSpostfix_protocol: TSmallintField
      FieldName = 'postfix_protocol'
    end
    object slicesCDSpostfix_protocolL: TStringField
      DisplayLabel = 'Postfix Protocol'
      FieldKind = fkLookup
      FieldName = 'postfix_protocolL'
      LookupDataSet = postfix
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'postfix_protocol'
      Lookup = True
    end
  end
  object slicesDataSource: TDataSource
    DataSet = slicesCDS
    Left = 344
    Top = 272
  end
  object fixativeTBL: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'SELECT * from fixativeprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    AfterPost = fixativeTBLAfterPost
    Left = 472
    Top = 616
  end
  object speciesDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'SELECT * from species'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 472
    Top = 680
  end
  object preprocesstreatmentDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from  preprocesstreatmentprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 472
    Top = 744
  end
  object fixationMethodDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from `fixationprotocols`'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 568
    Top = 616
  end
  object postfix: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from postfixprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 568
    Top = 680
  end
  object cryoprotectionDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from cryoprotectionprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 576
    Top = 744
  end
  object freezeprotocolDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from freezeprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 672
    Top = 616
  end
  object substitutionProtocol: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from substitutionprotocols'
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
    Top = 520
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
  end
  object infiltrationProtocolDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from infiltrationprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 672
    Top = 744
  end
  object embeddingProtocolDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from embeddingprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 784
    Top = 616
  end
  object blockstatusDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'SELECT * from blockstatuses'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    AfterPost = fixativeTBLAfterPost
    Left = 472
    Top = 552
  end
  object ROnCoverSlipsSource: TDataSource
    DataSet = ROnCS_CDS
    Left = 320
    Top = 774
  end
  object ROnCS_CDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'RibbonsOnCoverslipsProvider'
    Left = 200
    Top = 766
  end
  object RibbonsOnCoverslipsProvider: TDataSetProvider
    DataSet = ribbonsOnCoverSlipsDS
    Options = [poFetchBlobsOnDemand, poAllowCommandText, poRetainServerOrder, poUseQuoteChar]
    Left = 200
    Top = 694
  end
  object ribbonsOnCoverSlipsDS: TSQLDataSet
    CommandText = 'SELECT * from ribbons where coverslip_id = :id'
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 694
  end
  object settingsDS: TSQLDataSet
    CommandText = 'select * from settings order by id ASC'
    MaxBlobSize = 1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 32
    Top = 846
    object settingsDSid: TIntegerField
      FieldName = 'id'
    end
    object settingsDSlabel_printer_command: TMemoField
      FieldName = 'label_printer_command'
      BlobType = ftMemo
      Size = 1
    end
  end
  object settingsProvider: TDataSetProvider
    DataSet = settingsDS
    Left = 128
    Top = 846
  end
  object settingsCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'settingsProvider'
    AfterPost = cdsAfterPost
    Left = 256
    Top = 846
    object settingsCDSid: TIntegerField
      FieldName = 'id'
    end
    object settingsCDSlabel_printer_command: TMemoField
      FieldName = 'label_printer_command'
      BlobType = ftMemo
      Size = 1
    end
  end
  object specimenCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'specimenProvider'
    AfterPost = cdsAfterPost
    AfterScroll = cdsAfterScroll
    Left = 256
    Top = 192
    object specimenCDSid: TIntegerField
      DisplayWidth = 50
      FieldName = 'id'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
    end
    object specimenCDSanimal_id: TStringField
      DisplayWidth = 50
      FieldName = 'animal_id'
      Required = True
      Size = 64
    end
    object specimenCDSintake_date: TSQLTimeStampField
      DisplayWidth = 50
      FieldName = 'intake_date'
    end
    object specimenCDSspecie: TSmallintField
      DisplayWidth = 50
      FieldName = 'specie'
      Required = True
    end
    object specimenCDSLSpecie: TStringField
      DisplayLabel = 'Specie'
      FieldKind = fkLookup
      FieldName = 'LSpecie'
      LookupDataSet = speciesDS
      LookupKeyFields = 'id'
      LookupResultField = 'name'
      KeyFields = 'specie'
      Lookup = True
    end
    object specimenCDSsummary: TStringField
      FieldName = 'summary'
      Size = 256
    end
    object specimenCDSentered_by: TIntegerField
      DisplayWidth = 50
      FieldName = 'entered_by'
      Required = True
    end
    object specimenCDSLUser: TStringField
      DisplayLabel = 'User'
      FieldKind = fkLookup
      FieldName = 'LUser'
      LookupDataSet = usersCDS
      LookupKeyFields = 'id'
      LookupResultField = 'user_name'
      KeyFields = 'entered_by'
      Lookup = True
    end
  end
  object specimenDS: TSQLDataSet
    CommandText = 'select * from specimen order by id DESC'
    DataSource = specimenDataSource
    MaxBlobSize = 1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 192
    object specimenDSid: TIntegerField
      FieldName = 'id'
    end
    object specimenDSanimal_id: TStringField
      FieldName = 'animal_id'
      Required = True
      Size = 64
    end
    object specimenDSintake_date: TSQLTimeStampField
      FieldName = 'intake_date'
    end
    object specimenDSspecie: TSmallintField
      FieldName = 'specie'
      Required = True
    end
    object specimenDSentered_by: TIntegerField
      FieldName = 'entered_by'
      Required = True
    end
    object specimenDSsummary: TStringField
      FieldName = 'summary'
      Size = 256
    end
  end
  object specimenProvider: TDataSetProvider
    DataSet = specimenDS
    Left = 144
    Top = 192
  end
  object culturedTimePoints: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'SELECT * from cultured_time_point'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 488
    Top = 208
  end
  object specimenDataSource: TDataSource
    DataSet = specimenCDS
    Left = 368
    Top = 184
  end
  object blockIDsDS: TSQLDataSet
    CommandText = 'select id from blocks ORDER by id DESC'
    MaxBlobSize = 1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 456
    Top = 360
    object blockIDsDSid: TIntegerField
      FieldName = 'id'
      Required = True
    end
  end
  object blockIdsProvider: TDataSetProvider
    DataSet = blockIDsDS
    Options = [poFetchBlobsOnDemand, poAllowCommandText, poRetainServerOrder, poUseQuoteChar]
    Left = 552
    Top = 360
  end
  object blockIDSCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'blockIdsProvider'
    BeforePost = cdsBeforePost
    AfterPost = cdsAfterPost
    AfterDelete = cdsAfterDelete
    AfterScroll = cdsAfterScroll
    AfterRefresh = cdsAfterRefresh
    OnCalcFields = blocksCDSCalcFields
    Left = 656
    Top = 360
    object IntegerField4: TIntegerField
      AutoGenerateValue = arAutoInc
      FieldName = 'id'
    end
  end
  object blockIDsDataSource: TDataSource
    DataSet = blockIDSCDS
    Left = 768
    Top = 360
  end
  object ribbonStatusDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'SELECT * from ribbonstatuses'
    DataSet.MaxBlobSize = 1
    DataSet.Params = <>
    Params = <>
    AfterPost = fixativeTBLAfterPost
    Left = 568
    Top = 544
  end
end
