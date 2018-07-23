object PGImagesAndMoviesDM: TPGImagesAndMoviesDM
  OldCreateOrder = False
  Height = 422
  Width = 687
  object MoviesByBlockIDCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    AfterScroll = MoviesByBlockIDCDSAfterScroll
    AfterRefresh = MoviesByBlockIDCDSAfterRefresh
    Left = 288
    Top = 103
    object MoviesByBlockIDCDSid: TWideStringField
      FieldName = 'id'
      Required = True
      Size = 36
    end
    object MoviesByBlockIDCDScreated: TSQLTimeStampField
      FieldName = 'created'
      Required = True
    end
    object MoviesByBlockIDCDSfileextension: TWideStringField
      FieldName = 'fileextension'
      Size = 16
    end
    object MoviesByBlockIDCDScreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
    object MoviesByBlockIDCDScoverslip_id: TIntegerField
      FieldName = 'coverslip_id'
      Required = True
    end
    object MoviesByBlockIDCDSblock_id: TIntegerField
      FieldName = 'block_id'
      Required = True
    end
  end
  object MoviesDataSource: TDataSource
    DataSet = MoviesByBlockIDCDS
    Left = 434
    Top = 103
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = MoviesByBlockIDDS
    Left = 168
    Top = 103
  end
  object MoviesByBlockIDDS: TSQLDataSet
    CommandText = 'SELECT * from movies where block_id = :id'
    DataSource = pgDM.blockIDsDataSource
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = pgDM.SQLConnection1
    Left = 48
    Top = 103
    object MoviesByBlockIDDSid: TWideStringField
      FieldName = 'id'
      Required = True
      Size = 36
    end
    object MoviesByBlockIDDScreated: TSQLTimeStampField
      FieldName = 'created'
      Required = True
    end
    object MoviesByBlockIDDSfileextension: TWideStringField
      FieldName = 'fileextension'
      Size = 16
    end
    object MoviesByBlockIDDScreated_by: TIntegerField
      FieldName = 'created_by'
      Required = True
    end
    object MoviesByBlockIDDScoverslip_id: TIntegerField
      FieldName = 'coverslip_id'
      Required = True
    end
    object MoviesByBlockIDDSblock_id: TIntegerField
      FieldName = 'block_id'
      Required = True
    end
  end
end
