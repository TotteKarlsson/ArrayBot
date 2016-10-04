object ImagesAndMoviesDM: TImagesAndMoviesDM
  OldCreateOrder = False
  Height = 591
  Width = 604
  object images: TSQLDataSet
    Active = True
    CommandText = 'select * from abImage order by date desc'
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 40
    Top = 112
    object imagesid: TIntegerField
      FieldName = 'id'
    end
    object imagesfile_name: TWideStringField
      FieldName = 'file_name'
      Size = 1024
    end
    object imagesdate: TSQLTimeStampField
      FieldName = 'date'
    end
  end
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
      'Database=C:\Users\matsk\AppData\Local\ArrayBot\atDB.db'
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
    Left = 32
    Top = 32
  end
  object imageNote: TSQLQuery
    DataSource = image_note
    MaxBlobSize = -1
    Params = <>
    SQL.Strings = (
      'select * from abImage_note where image_id = 5')
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
    MaxBlobSize = -1
    Params = <>
    SQL.Strings = (
      
        ' SELECT * FROM note WHERE id IN (SELECT note_id FROM abImage_not' +
        'e WHERE image_id = "")')
    SQLConnection = SQLConnection1
    Left = 40
    Top = 256
    object notesQid: TIntegerField
      FieldName = 'id'
    end
    object notesQnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftWideMemo
      Size = -1
    end
    object notesQcreated_on: TSQLTimeStampField
      FieldName = 'created_on'
    end
    object notesQcreated_by: TWideStringField
      FieldName = 'created_by'
      Size = 512
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
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'imagesProvider'
    AfterScroll = imagesCDSAfterScroll
    Left = 256
    Top = 112
    object imagesCDSid: TIntegerField
      FieldName = 'id'
    end
    object imagesCDSfile_name: TWideStringField
      FieldName = 'file_name'
      Size = 1024
    end
    object imagesCDSdate: TSQLTimeStampField
      FieldName = 'date'
      OnGetText = imagesCDSdateGetText
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
    end
    object notesCDSnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftWideMemo
    end
    object notesCDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
      OnGetText = notesCDScreated_onGetText
    end
    object notesCDScreated_by: TWideStringField
      FieldName = 'created_by'
      Size = 512
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
    Active = True
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
