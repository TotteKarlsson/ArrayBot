object ImagesAndMoviesDM: TImagesAndMoviesDM
  OldCreateOrder = False
  Height = 591
  Width = 604
  object images: TSQLDataSet
    CommandText = 'select * from umimage order by date desc'
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 112
    object imagesid: TIntegerField
      FieldName = 'id'
      Required = True
    end
    object imagesfile_name: TStringField
      FieldName = 'file_name'
      Required = True
      Size = 512
    end
    object imagesdate: TSQLTimeStampField
      FieldName = 'date'
      Required = True
    end
  end
  object SQLConnection1: TSQLConnection
    ConnectionName = 'ATDBDebug'
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
      'HostName=127.0.0.1'
      'Database=umlocal'
      'User_Name=atdb_client'
      'Password=atdb123'
      'MaxBlobSize=-1'
      'LocaleCode=0000'
      'Compressed=False'
      'Encrypted=False'
      'BlobSize=-1'
      'ErrorResourceFile=')
    AfterConnect = SQLConnection1AfterConnect
    Left = 32
    Top = 32
  end
  object imageNote: TSQLQuery
    DataSource = image_note
    MaxBlobSize = -1
    Params = <>
    SQL.Strings = (
      'select * from umimage_note where image_id = 5')
    SQLConnection = SQLConnection1
    Left = 40
    Top = 184
    object imageNoteimage_id: TIntegerField
      FieldName = 'image_id'
    end
    object imageNotenote_ID: TIntegerField
      FieldName = 'note_ID'
    end
  end
  object notesQ: TSQLQuery
    DataSource = imageNotes
    MaxBlobSize = 1
    Params = <>
    SQL.Strings = (
      
        ' SELECT * FROM note WHERE id IN (SELECT note_id FROM umimage_not' +
        'e WHERE image_id = "")')
    SQLConnection = SQLConnection1
    Left = 40
    Top = 256
    object notesQid: TIntegerField
      FieldName = 'id'
      Required = True
    end
    object notesQnote: TMemoField
      FieldName = 'note'
      BlobType = ftMemo
      Size = 1
    end
    object notesQcreated_on: TSQLTimeStampField
      FieldName = 'created_on'
    end
    object notesQcreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
  end
  object DataSetProvider2: TDataSetProvider
    DataSet = notesQ
    Left = 144
    Top = 256
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = imageNote
    Left = 144
    Top = 184
  end
  object imagesProvider: TDataSetProvider
    DataSet = images
    Left = 144
    Top = 112
  end
  object imagesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'imagesProvider'
    AfterScroll = imagesCDSAfterScroll
    Left = 256
    Top = 112
    object imagesCDSid: TIntegerField
      FieldName = 'id'
      Required = True
    end
    object imagesCDSfile_name: TStringField
      FieldName = 'file_name'
      Required = True
      Size = 512
    end
    object imagesCDSdate: TSQLTimeStampField
      FieldName = 'date'
      Required = True
    end
  end
  object imagesDS: TDataSource
    DataSet = imagesCDS
    Left = 336
    Top = 112
  end
  object image_note: TDataSource
    DataSet = imageNoteCDS
    Left = 336
    Top = 184
  end
  object imageNoteCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 256
    Top = 184
    object imageNoteCDSimage_id: TIntegerField
      FieldName = 'image_id'
    end
    object imageNoteCDSnote_ID: TIntegerField
      FieldName = 'note_ID'
    end
  end
  object notesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider2'
    AfterScroll = notesCDSAfterScroll
    Left = 256
    Top = 256
    object notesCDSid: TIntegerField
      FieldName = 'id'
      Required = True
    end
    object notesCDSnote: TMemoField
      FieldName = 'note'
      BlobType = ftMemo
      Size = 1
    end
    object notesCDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
    end
    object notesCDScreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
  end
  object imageNotes: TDataSource
    DataSet = notesCDS
    Left = 336
    Top = 256
  end
  object sensors: TSQLDataSet
    CommandText = 'select * from sensor_data order by date desc'
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 344
    object sensorsid: TIntegerField
      FieldName = 'id'
    end
    object sensorsdevice_id: TIntegerField
      FieldName = 'device_id'
    end
    object sensorsdate: TSQLTimeStampField
      FieldName = 'date'
    end
    object sensorstemperature: TFloatField
      FieldName = 'temperature'
    end
    object sensorshumidity: TFloatField
      FieldName = 'humidity'
    end
  end
  object DataSetProvider3: TDataSetProvider
    DataSet = sensors
    Left = 144
    Top = 344
  end
  object sensorsCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider3'
    AfterScroll = imagesCDSAfterScroll
    Left = 256
    Top = 344
    object sensorsCDSdevice_id: TIntegerField
      FieldName = 'device_id'
    end
    object sensorsCDSdate: TSQLTimeStampField
      FieldName = 'date'
    end
    object sensorsCDStemperature: TFloatField
      FieldName = 'temperature'
    end
    object sensorsCDShumidity: TFloatField
      FieldName = 'humidity'
    end
  end
  object sensorsDS: TDataSource
    DataSet = sensorsCDS
    Left = 336
    Top = 344
  end
end
