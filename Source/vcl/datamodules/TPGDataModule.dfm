object pgDM: TpgDM
  OldCreateOrder = False
  Height = 1042
  Width = 1566
  object SQLConnection1: TSQLConnection
    ConnectionName = 'LocalPG'
    DriverName = 'DevartPostgreSQL'
    LoginPrompt = False
    Params.Strings = (
      'DriverName=DevartPostgreSQL'
      'DriverUnit=DbxDevartPostgreSQL'
      
        'DriverPackageLoader=TDBXDynalinkDriverLoader,DBXCommonDriver170.' +
        'bpl'
      
        'MetaDataPackageLoader=TDBXDevartPostgreSQLMetaDataCommandFactory' +
        ',DbxDevartPostgreSQLDriver170.bpl'
      'ProductName=DevartPostgreSQL'
      'LibraryName=dbexppgsql40.dll'
      'LocaleCode=0000'
      'IsolationLevel=ReadCommitted'
      'MaxBlobSize=-1'
      'FetchAll=True'
      'UseQuoteChar=False'
      'UseUnicode=True'
      'IPVersion=IPv4'
      'VendorLib=dbexppgsql40.dll'
      'BlobSize=-1'
      'HostName=atdb'
      'SchemaName='
      'Database=shotgundb'
      'User_Name=admin'
      'Password=atdb123'
      'EnableBCD=True')
    AfterConnect = SQLConnection1AfterConnect
    AfterDisconnect = SQLConnection1AfterDisconnect
    BeforeConnect = SQLConnection1BeforeConnect
    Left = 40
    Top = 24
  end
  object blocksDataSource: TDataSource
    DataSet = blocksCDS
    Left = 464
    Top = 360
  end
  object blocksCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'blocksProvider'
    BeforePost = cdsBeforePost
    AfterPost = cdsAfterPost
    BeforeDelete = cdsbeforeDelete
    AfterDelete = cdsAfterDelete
    AfterScroll = cdsAfterScroll
    AfterRefresh = cdsAfterRefresh
    OnCalcFields = blocksCDSCalcFields
    Left = 336
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
    object blocksCDSlabel: TWideStringField
      DisplayLabel = 'Label'
      FieldName = 'label'
      Size = 255
    end
    object blocksCDSstatus: TSmallintField
      FieldName = 'status'
      Required = True
    end
    object blocksCDSLBlockStatus: TWideStringField
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
    object blocksCDSCBlockLabel: TWideStringField
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
    object blocksCDSLCryoProtectionProtocol: TWideStringField
      DisplayLabel = 'Cryoprotection Protocol'
      FieldKind = fkLookup
      FieldName = 'LCryoProtectionProtocol'
      LookupDataSet = cryoprotectionDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'cryoprotection_protocol'
      Lookup = True
    end
    object blocksCDSLFreezingProtocol: TWideStringField
      DisplayLabel = 'Freezing Protocol'
      FieldKind = fkLookup
      FieldName = 'LFreezingProtocol'
      LookupDataSet = freezeprotocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'freezing_protocol'
      Lookup = True
    end
    object blocksCDSLSubstitutionProtocol: TWideStringField
      DisplayLabel = 'Substitution Protocol'
      FieldKind = fkLookup
      FieldName = 'LSubstitutionProtocol'
      LookupDataSet = substitutionProtocol
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'substitution_protocol'
      Lookup = True
    end
    object blocksCDSLInfiltrationProtocol: TWideStringField
      DisplayLabel = 'Infiltration Protocol'
      FieldKind = fkLookup
      FieldName = 'LInfiltrationProtocol'
      LookupDataSet = infiltrationProtocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'infiltration_protocol'
      Lookup = True
    end
    object blocksCDSLEmbeddingProtocol: TWideStringField
      DisplayLabel = 'Embedding Protocol'
      FieldKind = fkLookup
      FieldName = 'LEmbeddingProtocol'
      LookupDataSet = embeddingProtocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'embedding_protocol'
      Lookup = True
    end
    object blocksCDSLUser: TWideStringField
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
    Options = [poFetchBlobsOnDemand, poUseQuoteChar]
    Left = 192
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
    object blocksDSlabel: TWideStringField
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
    object usersDSuser_name: TWideStringField
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
    Left = 192
    Top = 88
  end
  object usersCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'usersProvider'
    AfterPost = cdsAfterPost
    Left = 336
    Top = 88
    object usersCDSid: TIntegerField
      FieldName = 'id'
    end
    object usersCDSuser_name: TWideStringField
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
    Left = 464
    Top = 96
  end
  object blockNotesDSource: TDataSource
    DataSet = blockNotesCDS
    Left = 464
    Top = 432
  end
  object blockNotesProvider: TDataSetProvider
    DataSet = blockNotesDS
    Left = 192
    Top = 424
  end
  object blockNotesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'blockNotesProvider'
    AfterPost = cdsAfterPost
    AfterDelete = cdsAfterDelete
    Left = 336
    Top = 424
    object blockNotesCDSid: TIntegerField
      FieldName = 'id'
    end
    object blockNotesCDSnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftWideMemo
    end
    object blockNotesCDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
      ProviderFlags = [pfInUpdate]
    end
    object blockNotesCDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
  end
  object noteDS: TSQLDataSet
    CommandText = 'select * from notes'
    DataSource = notesDSource
    MaxBlobSize = 1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 624
    Top = 72
    object noteDSid: TIntegerField
      FieldName = 'id'
    end
    object noteDSnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftWideMemo
      Size = -1
    end
    object noteDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
    end
    object noteDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
  end
  object notesProvider: TDataSetProvider
    DataSet = noteDS
    Left = 744
    Top = 72
  end
  object notesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'notesProvider'
    AfterPost = cdsAfterPost
    Left = 888
    Top = 72
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
    object notesCDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
  end
  object notesDSource: TDataSource
    DataSet = notesCDS
    Left = 1040
    Top = 80
  end
  object ribbonsProvider: TDataSetProvider
    DataSet = ribbonsDS
    Left = 192
    Top = 504
  end
  object ribbonsCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'ribbonsProvider'
    BeforePost = cdsBeforePost
    AfterPost = cdsAfterPost
    AfterDelete = cdsAfterDelete
    AfterScroll = cdsAfterScroll
    AfterRefresh = cdsAfterRefresh
    OnCalcFields = ribbonsCDSCalcFields
    Left = 336
    Top = 504
    object ribbonsCDSid: TWideStringField
      FieldName = 'id'
      Size = 36
    end
    object ribbonsCDSstatus: TIntegerField
      FieldName = 'status'
    end
    object ribbonsCDSblock_id: TIntegerField
      FieldName = 'block_id'
      Required = True
    end
    object ribbonsCDScutting_order: TIntegerField
      DisplayLabel = 'Cutting Order'
      FieldName = 'cutting_order'
    end
    object ribbonsCDSnr_of_sections: TSmallintField
      DisplayLabel = 'Nr of Sections'
      FieldName = 'nr_of_sections'
    end
    object ribbonsCDScreated_on: TSQLTimeStampField
      DisplayLabel = 'Created On'
      FieldName = 'created_on'
      ProviderFlags = [pfInUpdate]
    end
    object ribbonsCDSmodified: TSQLTimeStampField
      FieldName = 'modified'
      ProviderFlags = [pfInUpdate]
    end
    object ribbonsCDScreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
    object ribbonsCDSknife_id: TIntegerField
      DisplayLabel = 'Knife ID'
      FieldName = 'knife_id'
    end
    object ribbonsCDScoverslip_id: TIntegerField
      DisplayLabel = 'Coverslip ID'
      FieldName = 'coverslip_id'
      Required = True
    end
    object ribbonsCDSstatusL: TWideStringField
      DisplayLabel = 'Status'
      FieldKind = fkLookup
      FieldName = 'statusL'
      LookupDataSet = ribbonStatusDS
      LookupKeyFields = 'id'
      LookupResultField = 'status'
      KeyFields = 'status'
      Lookup = True
    end
    object ribbonsCDScreated_byL: TStringField
      DisplayLabel = 'Created By'
      FieldKind = fkLookup
      FieldName = 'created_byL'
      LookupDataSet = usersCDS
      LookupKeyFields = 'id'
      LookupResultField = 'user_name'
      KeyFields = 'created_by'
      Size = 256
      Lookup = True
    end
  end
  object ribbonsDSource: TDataSource
    DataSet = ribbonsCDS
    Left = 464
    Top = 512
  end
  object ribbonNotesProvider: TDataSetProvider
    DataSet = ribbonNotesDS
    Left = 192
    Top = 584
  end
  object ribbonNotesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'ribbonNotesProvider'
    AfterPost = cdsAfterPost
    AfterDelete = cdsAfterDelete
    Left = 336
    Top = 584
    object ribbonNotesCDSid: TIntegerField
      FieldName = 'id'
    end
    object ribbonNotesCDSnote: TWideMemoField
      FieldName = 'note'
      ProviderFlags = [pfInUpdate]
      BlobType = ftWideMemo
    end
    object ribbonNotesCDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
      ProviderFlags = [pfInUpdate]
    end
    object ribbonNotesCDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
  end
  object ribbonNotesDSource: TDataSource
    DataSet = ribbonNotesCDS
    Left = 464
    Top = 592
  end
  object ribbonsDS: TSQLDataSet
    CommandText = 
      'SELECT * from ribbons where block_id=:id ORDER by created_on DES' +
      'C'
    DataSource = allBlocksDataSource
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SortFieldNames = ' created_on '
    SQLConnection = SQLConnection1
    Left = 40
    Top = 504
    object ribbonsDSid: TWideStringField
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
    object ribbonsDSmodified: TSQLTimeStampField
      FieldName = 'modified'
      ProviderFlags = [pfInUpdate]
    end
    object ribbonsDScreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
    object ribbonsDScoverslip_id: TIntegerField
      FieldName = 'coverslip_id'
      Required = True
    end
    object ribbonsDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
      ProviderFlags = [pfInUpdate]
    end
    object ribbonsDSknife_id: TIntegerField
      FieldName = 'knife_id'
    end
  end
  object blockNotesDS: TSQLDataSet
    CommandText = 
      'SELECT * FROM notes n '#13#10'INNER JOIN block_note bn '#13#10'ON (bn.note_i' +
      'd = n.id) '#13#10'WHERE block_id = :id '#13#10'ORDER BY created_on ASC'
    DataSource = blocksDataSource
    MaxBlobSize = 1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 424
    object blockNotesDSid: TIntegerField
      FieldName = 'id'
    end
    object blockNotesDSnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftWideMemo
      Size = -1
    end
    object blockNotesDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
      ProviderFlags = [pfInUpdate]
    end
    object blockNotesDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
  end
  object ribbonNotesDS: TSQLDataSet
    CommandText = 
      'SELECT * FROM notes n '#13#10'INNER JOIN ribbon_note rn '#13#10'ON (rn.note_' +
      'id = n.id) '#13#10'WHERE ribbon_id = :id '#13#10'ORDER BY created_on ASC'
    DataSource = ribbonsDSource
    MaxBlobSize = 1
    Params = <
      item
        DataType = ftWideString
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 584
    object ribbonNotesDSid: TIntegerField
      FieldName = 'id'
    end
    object ribbonNotesDSnote: TWideMemoField
      FieldName = 'note'
      ProviderFlags = [pfInUpdate]
      BlobType = ftWideMemo
      Size = -1
    end
    object ribbonNotesDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
      ProviderFlags = [pfInUpdate]
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
    Left = 40
    Top = 272
    object slicesDSid: TIntegerField
      FieldName = 'id'
    end
    object slicesDSspecimen_id: TIntegerField
      FieldName = 'specimen_id'
    end
    object slicesDSvirus: TWideStringField
      FieldName = 'virus'
      Size = 255
    end
    object slicesDSbrain_region_dissection: TWideStringField
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
    object slicesDSvirus_dilution: TWideStringField
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
    Left = 192
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
        DataType = ftWideString
        Size = 255
      end
      item
        Name = 'brain_region_dissection'
        DataType = ftWideString
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
        DataType = ftWideString
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
    Left = 336
    Top = 272
    object slicesCDSid: TIntegerField
      FieldName = 'id'
    end
    object slicesCDSspecimen_id: TIntegerField
      DisplayLabel = 'Specimen ID'
      FieldName = 'specimen_id'
    end
    object slicesCDSvirus: TWideStringField
      DisplayLabel = 'Virus'
      FieldName = 'virus'
      Size = 255
    end
    object slicesCDSvirus_dilution: TWideStringField
      DisplayLabel = 'Virus Dilution'
      FieldName = 'virus_dilution'
      Size = 16
    end
    object slicesCDSbrain_region_dissection: TWideStringField
      DisplayLabel = 'Brain Region'
      FieldName = 'brain_region_dissection'
      Size = 255
    end
    object slicesCDSculture_time: TIntegerField
      FieldName = 'culture_time'
    end
    object slicesCDSculture_timeL: TWideStringField
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
    object slicesCDSentered_byL: TWideStringField
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
    object slicesCDSpreprocess_treatment_protocolL: TWideStringField
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
    object slicesCDSfixative_protocolL: TWideStringField
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
    object slicesCDSfixation_protocolL: TWideStringField
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
    object slicesCDSpostfix_protocolL: TWideStringField
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
    Left = 464
    Top = 280
  end
  object fixativeTBL: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'SELECT * from fixativeprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    AfterPost = fixativeTBLAfterPost
    Left = 624
    Top = 656
  end
  object speciesDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'SELECT * from species'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 624
    Top = 720
  end
  object preprocesstreatmentDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from  preprocesstreatmentprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 624
    Top = 784
  end
  object fixationMethodDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from fixationprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 760
    Top = 656
  end
  object postfix: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from postfixprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 760
    Top = 720
  end
  object cryoprotectionDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from cryoprotectionprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 760
    Top = 784
  end
  object freezeprotocolDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from freezeprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 896
    Top = 656
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
        DataType = ftInteger
      end
      item
        Name = 'protocol'
        DataType = ftWideString
        Size = 255
      end
      item
        Name = 'document_id'
        DataType = ftInteger
      end>
    IndexDefs = <>
    Params = <>
    StoreDefs = True
    Left = 896
    Top = 592
    object substitutionProtocolid: TSmallintField
      FieldName = 'id'
      Required = True
    end
    object substitutionProtocolprotocol: TWideStringField
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
    Left = 896
    Top = 784
  end
  object embeddingProtocolDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'select * from embeddingprotocols'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 896
    Top = 720
  end
  object blockstatusDS: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'SELECT * from blockstatuses'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    AfterPost = fixativeTBLAfterPost
    Left = 624
    Top = 592
  end
  object settingsDS: TSQLDataSet
    CommandText = 'select * from settings order by id ASC'
    MaxBlobSize = 1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 846
    object settingsDSid: TIntegerField
      FieldName = 'id'
    end
    object settingsDSlabel_printer_command: TWideMemoField
      FieldName = 'label_printer_command'
      BlobType = ftWideMemo
      Size = -1
    end
  end
  object settingsProvider: TDataSetProvider
    DataSet = settingsDS
    Left = 192
    Top = 846
  end
  object settingsCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'settingsProvider'
    AfterPost = cdsAfterPost
    Left = 336
    Top = 846
    object settingsCDSid: TIntegerField
      FieldName = 'id'
    end
    object settingsCDSlabel_printer_command: TWideMemoField
      FieldName = 'label_printer_command'
      BlobType = ftWideMemo
    end
  end
  object specimenCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'specimenProvider'
    AfterPost = cdsAfterPost
    AfterScroll = cdsAfterScroll
    AfterRefresh = cdsAfterRefresh
    Left = 336
    Top = 192
    object specimenCDSid: TIntegerField
      DisplayWidth = 50
      FieldName = 'id'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
    end
    object specimenCDSanimal_id: TWideStringField
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
    object specimenCDSLSpecie: TWideStringField
      DisplayLabel = 'Specie'
      FieldKind = fkLookup
      FieldName = 'LSpecie'
      LookupDataSet = speciesDS
      LookupKeyFields = 'id'
      LookupResultField = 'name'
      KeyFields = 'specie'
      Lookup = True
    end
    object specimenCDSsummary: TWideStringField
      FieldName = 'summary'
      Size = 256
    end
    object specimenCDSentered_by: TIntegerField
      DisplayWidth = 50
      FieldName = 'entered_by'
      Required = True
    end
    object specimenCDSLUser: TWideStringField
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
    object specimenDSanimal_id: TWideStringField
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
    object specimenDSsummary: TWideStringField
      FieldName = 'summary'
      Size = 256
    end
  end
  object specimenProvider: TDataSetProvider
    DataSet = specimenDS
    Left = 192
    Top = 192
  end
  object culturedTimePoints: TSimpleDataSet
    Aggregates = <>
    Connection = SQLConnection1
    DataSet.CommandText = 'SELECT * from cultured_time_point'
    DataSet.MaxBlobSize = -1
    DataSet.Params = <>
    Params = <>
    Left = 624
    Top = 192
  end
  object specimenDataSource: TDataSource
    DataSet = specimenCDS
    Left = 464
    Top = 192
  end
  object blockIDsDS: TSQLDataSet
    CommandText = 'select id from blocks ORDER by id DESC'
    MaxBlobSize = 1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 624
    Top = 360
    object blockIDsDSid: TIntegerField
      FieldName = 'id'
      Required = True
    end
  end
  object blockIdsProvider: TDataSetProvider
    DataSet = blockIDsDS
    Options = [poFetchBlobsOnDemand, poAllowCommandText, poRetainServerOrder, poUseQuoteChar]
    Left = 760
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
    Left = 888
    Top = 360
    object IntegerField4: TIntegerField
      AutoGenerateValue = arAutoInc
      FieldName = 'id'
    end
  end
  object blockIDsDataSource: TDataSource
    DataSet = blockIDSCDS
    Left = 1040
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
    Left = 760
    Top = 600
  end
  object allBlocksDataSource: TDataSource
    DataSet = allBlocksCDS
    Left = 1040
    Top = 296
  end
  object allBlocksCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'allBlocksProvider'
    BeforePost = cdsBeforePost
    AfterPost = cdsAfterPost
    AfterDelete = cdsAfterDelete
    AfterScroll = cdsAfterScroll
    AfterRefresh = cdsAfterRefresh
    Left = 888
    Top = 296
    object IntegerField1: TIntegerField
      Alignment = taLeftJustify
      AutoGenerateValue = arAutoInc
      DisplayLabel = 'Block ID'
      FieldName = 'id'
    end
    object IntegerField2: TIntegerField
      FieldName = 'slice_id'
    end
    object IntegerField3: TIntegerField
      FieldName = 'entered_by'
      Required = True
    end
    object SQLTimeStampField1: TSQLTimeStampField
      FieldName = 'entered_on'
      Required = True
    end
    object WideStringField1: TWideStringField
      DisplayLabel = 'Label'
      FieldName = 'label'
      Size = 255
    end
    object SmallintField1: TSmallintField
      FieldName = 'status'
      Required = True
    end
    object WideStringField2: TWideStringField
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
    object SmallintField2: TSmallintField
      Alignment = taLeftJustify
      DisplayLabel = 'Serial'
      FieldName = 'serial'
      Required = True
    end
    object WideStringField3: TWideStringField
      DisplayLabel = 'Label'
      FieldKind = fkCalculated
      FieldName = 'Cblock_label'
      Size = 50
      Calculated = True
    end
    object DateField1: TDateField
      DisplayLabel = 'Date Embedded'
      FieldName = 'date_embedded'
    end
    object SmallintField3: TSmallintField
      FieldName = 'cryoprotection_protocol'
    end
    object SmallintField4: TSmallintField
      FieldName = 'freezing_protocol'
    end
    object SmallintField5: TSmallintField
      FieldName = 'substitution_protocol'
    end
    object SmallintField6: TSmallintField
      FieldName = 'infiltration_protocol'
    end
    object SmallintField7: TSmallintField
      FieldName = 'embedding_protocol'
    end
    object WideStringField4: TWideStringField
      DisplayLabel = 'Cryoprotection Protocol'
      FieldKind = fkLookup
      FieldName = 'LCryoProtectionProtocol'
      LookupDataSet = cryoprotectionDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'cryoprotection_protocol'
      Lookup = True
    end
    object WideStringField5: TWideStringField
      DisplayLabel = 'Freezing Protocol'
      FieldKind = fkLookup
      FieldName = 'LFreezingProtocol'
      LookupDataSet = freezeprotocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'freezing_protocol'
      Lookup = True
    end
    object WideStringField6: TWideStringField
      DisplayLabel = 'Substitution Protocol'
      FieldKind = fkLookup
      FieldName = 'LSubstitutionProtocol'
      LookupDataSet = substitutionProtocol
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'substitution_protocol'
      Lookup = True
    end
    object WideStringField7: TWideStringField
      DisplayLabel = 'Infiltration Protocol'
      FieldKind = fkLookup
      FieldName = 'LInfiltrationProtocol'
      LookupDataSet = infiltrationProtocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'infiltration_protocol'
      Lookup = True
    end
    object WideStringField8: TWideStringField
      DisplayLabel = 'Embedding Protocol'
      FieldKind = fkLookup
      FieldName = 'LEmbeddingProtocol'
      LookupDataSet = embeddingProtocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'embedding_protocol'
      Lookup = True
    end
    object WideStringField9: TWideStringField
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
  object allBlocksProvider: TDataSetProvider
    DataSet = allBlocksDS
    Options = [poFetchBlobsOnDemand, poAllowCommandText, poRetainServerOrder, poUseQuoteChar]
    Left = 776
    Top = 296
  end
  object allBlocksDS: TSQLDataSet
    CommandText = 'select * from blocks ORDER by id DESC'
    MaxBlobSize = 1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 624
    Top = 296
    object IntegerField5: TIntegerField
      FieldName = 'id'
    end
    object IntegerField6: TIntegerField
      FieldName = 'slice_id'
    end
    object SmallintField8: TSmallintField
      FieldName = 'status'
      Required = True
    end
    object IntegerField7: TIntegerField
      FieldName = 'entered_by'
      Required = True
    end
    object WideStringField10: TWideStringField
      FieldName = 'label'
      Size = 255
    end
    object SmallintField9: TSmallintField
      FieldName = 'serial'
      Required = True
    end
    object DateField2: TDateField
      FieldName = 'date_embedded'
    end
    object SmallintField10: TSmallintField
      FieldName = 'cryoprotection_protocol'
    end
    object SmallintField11: TSmallintField
      FieldName = 'freezing_protocol'
    end
    object SmallintField12: TSmallintField
      FieldName = 'substitution_protocol'
    end
    object SmallintField13: TSmallintField
      FieldName = 'infiltration_protocol'
    end
    object SmallintField14: TSmallintField
      FieldName = 'embedding_protocol'
    end
    object SQLTimeStampField2: TSQLTimeStampField
      FieldName = 'entered_on'
      Required = True
    end
  end
  object knifesDS: TSQLDataSet
    CommandText = 'select * from knifes'
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 672
    object knifesDSid: TIntegerField
      FieldName = 'id'
    end
    object knifesDSdate_entered: TDateField
      FieldName = 'date_entered'
      ProviderFlags = [pfInUpdate]
    end
  end
  object knifesProvider: TDataSetProvider
    DataSet = knifesDS
    Left = 184
    Top = 672
  end
  object knifesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'knifesProvider'
    AfterScroll = cdsAfterScroll
    AfterRefresh = cdsAfterRefresh
    Left = 336
    Top = 672
    object knifesCDSid: TIntegerField
      DisplayLabel = 'ID'
      FieldName = 'id'
    end
    object knifesCDSdate_entered: TDateField
      DisplayLabel = 'Date Entered'
      FieldName = 'date_entered'
      ProviderFlags = [pfInUpdate]
      ReadOnly = True
    end
  end
  object knifeNotesDS: TSQLDataSet
    CommandText = 
      'SELECT * FROM notes n '#13#10'INNER JOIN knife_notes kn '#13#10'ON (kn.note_' +
      'id = n.id) '#13#10'WHERE knife_id = :id '#13#10'ORDER BY created_on ASC'
    DataSource = knifesDSource
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 32
    Top = 752
    object knifeNotesDSid: TIntegerField
      FieldName = 'id'
    end
    object knifeNotesDSnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftWideMemo
      Size = -1
    end
    object knifeNotesDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
      ProviderFlags = [pfInUpdate]
    end
    object knifeNotesDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
  end
  object knifeNotesProvider: TDataSetProvider
    DataSet = knifeNotesDS
    Left = 176
    Top = 752
  end
  object knifeNotesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'knifeNotesProvider'
    AfterPost = cdsAfterPost
    Left = 336
    Top = 752
    object knifeNotesCDSid: TIntegerField
      FieldName = 'id'
    end
    object knifeNotesCDSnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftWideMemo
    end
    object knifeNotesCDScreated_on: TSQLTimeStampField
      DisplayLabel = 'Date'
      FieldName = 'created_on'
      ProviderFlags = [pfInUpdate]
    end
    object knifeNotesCDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
    object knifeNotesCDSLcreated_by: TStringField
      DisplayLabel = 'Created By'
      FieldKind = fkLookup
      FieldName = 'Lcreated_by'
      LookupDataSet = usersCDS
      LookupKeyFields = 'id'
      LookupResultField = 'user_name'
      KeyFields = 'created_by'
      Lookup = True
    end
  end
  object knifesDSource: TDataSource
    DataSet = knifesCDS
    Left = 464
    Top = 672
  end
  object knifeNotesDataSource: TDataSource
    DataSet = knifeNotesCDS
    Left = 456
    Top = 752
  end
end
