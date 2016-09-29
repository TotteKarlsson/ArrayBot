object iBotDataModule: TiBotDataModule
  OldCreateOrder = False
  Height = 405
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
    Left = 48
    Top = 40
  end
  object mImageStainSessionDS: TSQLDataSet
    Active = True
    CommandText = 'SELECT * from imageStainSession'
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 48
    Top = 128
    object mImageStainSessionDSid: TIntegerField
      FieldName = 'id'
    end
    object mImageStainSessionDSname: TWideMemoField
      FieldName = 'name'
      BlobType = ftWideMemo
      Size = -1
    end
    object mImageStainSessionDSimmunoProtocol: TIntegerField
      FieldName = 'immunoProtocol'
    end
  end
  object mImageStainProvider: TDataSetProvider
    DataSet = mImageStainSessionDS
    Left = 176
    Top = 128
  end
  object mImageStainSessionCDSet: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'mImageStainProvider'
    AfterPost = mImageStainSessionCDSetAfterPost
    Left = 336
    Top = 128
    object mImageStainSessionCDSetid: TIntegerField
      FieldName = 'id'
    end
    object mImageStainSessionCDSetname: TWideMemoField
      FieldName = 'name'
      BlobType = ftWideMemo
    end
    object mImageStainSessionCDSetimmunoProtocol: TIntegerField
      FieldName = 'immunoProtocol'
    end
  end
  object mImageStainSessionsDataSource: TDataSource
    DataSet = mImageStainSessionCDSet
    Left = 520
    Top = 128
  end
end
