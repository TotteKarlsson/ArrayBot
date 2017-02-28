object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 638
  ClientWidth = 885
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid1: TDBGrid
    Left = 8
    Top = 80
    Width = 320
    Height = 120
    DataSource = imagesDS
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
  end
  object DBGrid2: TDBGrid
    Left = 8
    Top = 206
    Width = 320
    Height = 120
    DataSource = image_note
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
  end
  object DBNavigator1: TDBNavigator
    Left = 8
    Top = 49
    Width = 240
    Height = 25
    DataSource = imagesDS
    TabOrder = 2
  end
  object DBGrid3: TDBGrid
    Left = 8
    Top = 333
    Width = 320
    Height = 120
    DataSource = imageNotes
    TabOrder = 3
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
  end
  object DBMemo1: TDBMemo
    Left = 334
    Top = 332
    Width = 323
    Height = 121
    DataField = 'note'
    DataSource = imageNotes
    TabOrder = 4
  end
  object DBNavigator2: TDBNavigator
    Left = 8
    Top = 472
    Width = 240
    Height = 25
    DataSource = imageNotes
    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
    TabOrder = 5
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
    Connected = True
    Left = 432
    Top = 24
  end
  object images: TSQLDataSet
    Active = True
    CommandText = 'select * from abImage'
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 432
    Top = 104
  end
  object imagesProvider: TDataSetProvider
    DataSet = images
    Left = 544
    Top = 104
  end
  object imagesCDS: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'imagesProvider'
    AfterScroll = imagesCDSAfterScroll
    Left = 656
    Top = 104
  end
  object imagesDS: TDataSource
    DataSet = imagesCDS
    Left = 736
    Top = 104
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = imageNote
    Left = 544
    Top = 176
  end
  object imageNoteCDS: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 656
    Top = 176
  end
  object image_note: TDataSource
    DataSet = imageNoteCDS
    Left = 736
    Top = 176
  end
  object imageNote: TSQLQuery
    Active = True
    DataSource = image_note
    MaxBlobSize = -1
    Params = <>
    SQL.Strings = (
      'select * from abImage_note where image_id = 5')
    SQLConnection = SQLConnection1
    Left = 440
    Top = 176
  end
  object imageNotesQ: TSQLQuery
    Active = True
    DataSource = imageNotes
    MaxBlobSize = -1
    Params = <>
    SQL.Strings = (
      
        ' SELECT * FROM note WHERE id IN (SELECT note_id FROM abImage_not' +
        'e WHERE image_id = "")')
    SQLConnection = SQLConnection1
    Left = 440
    Top = 248
  end
  object DataSetProvider2: TDataSetProvider
    DataSet = imageNotesQ
    Left = 544
    Top = 248
  end
  object imageNotesCDS: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider2'
    Left = 656
    Top = 248
  end
  object imageNotes: TDataSource
    DataSet = imageNotesCDS
    Left = 736
    Top = 248
  end
end
