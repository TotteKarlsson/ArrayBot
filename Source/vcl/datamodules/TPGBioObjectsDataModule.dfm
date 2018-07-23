object pgBioObjectsDM: TpgBioObjectsDM
  OldCreateOrder = False
  Height = 1042
  Width = 1566
  object SQLConnection1: TSQLConnection
    ConnectionName = 'synapseDB'
    DriverName = 'DevartPostgreSQL'
    LoginPrompt = False
    Params.Strings = (
      'DriverName=DevartPostgreSQL'
      'DriverUnit=DbxDevartPostgreSQL'
      
        'DriverPackageLoader=TDBXDynalinkDriverLoader,DBXCommonDriver250.' +
        'bpl'
      
        'MetaDataPackageLoader=TDBXDevartPostgreSQLMetaDataCommandFactory' +
        ',DbxDevartPostgreSQLDriver250.bpl'
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
      'HostName=atbigdawg.corp.alleninstitute.org'
      'SchemaName='
      'User_Name=postgres'
      'Password=synapsedb'
      'EnableBCD=True'
      'Database=postgres')
    AfterConnect = SQLConnection1AfterConnect
    AfterDisconnect = SQLConnection1AfterDisconnect
    BeforeConnect = SQLConnection1BeforeConnect
    Connected = True
    Left = 40
    Top = 24
  end
  object bioObjectCollectionProvider: TDataSetProvider
    DataSet = bioObjectCollectionDS
    Left = 272
    Top = 312
  end
  object bioObjectCollectionCDS: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'bioObjectCollectionProvider'
    AfterScroll = cdsAfterScroll
    AfterRefresh = bioObjectCollectionCDSAfterRefresh
    Left = 520
    Top = 312
    object bioObjectCollectionCDSname: TWideStringField
      FieldName = 'name'
      Size = 100
    end
    object bioObjectCollectionCDSvolume_id: TIntegerField
      FieldName = 'volume_id'
    end
    object bioObjectCollectionCDStype: TWideStringField
      FieldName = 'type'
      Size = 32
    end
    object bioObjectCollectionCDSid: TIntegerField
      FieldName = 'id'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
    end
    object bioObjectCollectionCDSsynapse_collection_type: TWideStringField
      FieldName = 'synapse_collection_type'
      Size = 100
    end
    object bioObjectCollectionCDSlink_id: TIntegerField
      FieldName = 'link_id'
    end
  end
  object bioObjectCollectionDS: TSQLDataSet
    CommandText = 'SELECT * from bioobjectcollection where volume_id=:id'
    DataSource = volumeDataSource
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 64
    Top = 312
    object bioObjectCollectionDSname: TWideStringField
      FieldName = 'name'
      Size = 100
    end
    object bioObjectCollectionDSvolume_id: TIntegerField
      FieldName = 'volume_id'
    end
    object bioObjectCollectionDStype: TWideStringField
      FieldName = 'type'
      Size = 32
    end
    object bioObjectCollectionDSid: TIntegerField
      FieldName = 'id'
    end
    object bioObjectCollectionDSsynapse_collection_type: TWideStringField
      FieldName = 'synapse_collection_type'
      Size = 100
    end
    object bioObjectCollectionDSlink_id: TIntegerField
      FieldName = 'link_id'
    end
  end
  object data_setProvider: TDataSetProvider
    DataSet = data_setDS
    Left = 272
    Top = 104
  end
  object data_setCDS: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'data_setProvider'
    AfterScroll = cdsAfterScroll
    Left = 520
    Top = 104
  end
  object data_setDS: TSQLDataSet
    Active = True
    CommandText = 'SELECT * FROM data_set'
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 72
    Top = 104
  end
  object volumeProvider: TDataSetProvider
    DataSet = volumeDS
    Left = 272
    Top = 208
  end
  object volumeCDS: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'volumeProvider'
    AfterScroll = cdsAfterScroll
    Left = 520
    Top = 208
  end
  object volumeDS: TSQLDataSet
    CommandText = 'select * from volume WHERE dataset_id=:id'
    DataSource = data_setDataSource
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 72
    Top = 208
  end
  object data_setDataSource: TDataSource
    DataSet = data_setCDS
    Left = 776
    Top = 104
  end
  object volumeDataSource: TDataSource
    DataSet = volumeCDS
    Left = 776
    Top = 208
  end
  object bioObjectCollectionDataSource: TDataSource
    DataSet = bioObjectCollectionCDS
    Left = 776
    Top = 312
  end
  object bioobjectDS: TSQLDataSet
    CommandText = 'SELECT * FROM bioobject WHERE object_collection_id = :id'
    DataSource = bioObjectCollectionDataSource
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = SQLConnection1
    Left = 56
    Top = 416
  end
  object bioObjectProvider: TDataSetProvider
    DataSet = bioobjectDS
    Left = 272
    Top = 416
  end
  object bioObjectCDS: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'bioObjectProvider'
    BeforeScroll = bioObjectCDSBeforeScroll
    AfterScroll = cdsAfterScroll
    BeforeRefresh = bioObjectCDSBeforeRefresh
    BeforeGetRecords = bioObjectCDSBeforeGetRecords
    Left = 520
    Top = 416
    object bioObjectCDSobject_collection_id: TIntegerField
      FieldName = 'object_collection_id'
    end
    object bioObjectCDStype: TWideStringField
      FieldName = 'type'
      Size = 32
    end
    object bioObjectCDSid: TIntegerField
      FieldName = 'id'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
    end
    object bioObjectCDSoid: TWideStringField
      FieldName = 'oid'
      Size = 50
    end
    object bioObjectCDSareas: TWideMemoField
      FieldName = 'areas'
      BlobType = ftWideMemo
    end
  end
  object bioobjectDataSource: TDataSource
    DataSet = bioObjectCDS
    Left = 776
    Top = 416
  end
end
