object csDM: TcsDM
  OldCreateOrder = False
  Height = 638
  Width = 602
  object csDS: TSQLDataSet
    BeforeOpen = csDSBeforeOpen
    CommandText = 'SELECT * FROM `coverslips`'
    MaxBlobSize = 1
    Params = <>
    Left = 64
    Top = 56
    object csDSid: TIntegerField
      FieldName = 'id'
    end
    object csDSstatus: TIntegerField
      FieldName = 'status'
      Required = True
    end
    object csDStype: TIntegerField
      FieldName = 'type'
      Required = True
    end
    object csDSnotes: TMemoField
      FieldName = 'notes'
      BlobType = ftMemo
      Size = 1
    end
    object csDSfreshCSBatch: TIntegerField
      FieldName = 'freshCSBatch'
      Required = True
    end
    object csDScleanCSBatch: TIntegerField
      FieldName = 'cleanCSBatch'
    end
    object csDScarboncoatbatch: TIntegerField
      FieldName = 'carboncoatbatch'
    end
    object csDSfrom_lot: TStringField
      FieldName = 'from_lot'
      Size = 128
    end
  end
  object csP: TDataSetProvider
    DataSet = csDS
    Options = [poAllowCommandText, poUseQuoteChar]
    Left = 176
    Top = 56
  end
  object csCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'csP'
    AfterPost = CDSAfterPost
    AfterScroll = CDSAfterScroll
    Left = 304
    Top = 64
    object csCDSid: TIntegerField
      DisplayLabel = 'ID'
      FieldName = 'id'
    end
    object csCDSstatus: TIntegerField
      DisplayLabel = 'Status'
      FieldName = 'status'
      Required = True
    end
    object csCDStype: TIntegerField
      DisplayLabel = 'Type'
      FieldName = 'type'
      Required = True
    end
    object csCDSLStatus: TStringField
      DisplayLabel = 'Status'
      FieldKind = fkLookup
      FieldName = 'LStatus'
      LookupDataSet = csStatusCDS
      LookupKeyFields = 'id'
      LookupResultField = 'status'
      KeyFields = 'status'
      Lookup = True
    end
    object csCDSLType: TStringField
      DisplayLabel = 'Type'
      FieldKind = fkLookup
      FieldName = 'LType'
      LookupDataSet = csTypeCDS
      LookupKeyFields = 'id'
      LookupResultField = 'type'
      KeyFields = 'type'
      Lookup = True
    end
    object csCDSnotes: TMemoField
      DisplayLabel = 'Notes'
      FieldName = 'notes'
      BlobType = ftMemo
      Size = 1
    end
    object csCDSfreshCSBatch: TIntegerField
      FieldName = 'freshCSBatch'
      Required = True
    end
    object csCDScleanCSBatch: TIntegerField
      FieldName = 'cleanCSBatch'
    end
    object csCDScarboncoatbatch: TIntegerField
      FieldName = 'carboncoatbatch'
    end
    object csCDSfrom_lot: TStringField
      DisplayLabel = 'From LOT#'
      FieldName = 'from_lot'
      Size = 128
    end
  end
  object csDSource: TDataSource
    DataSet = csCDS
    Left = 424
    Top = 56
  end
  object csStatusDS: TSQLDataSet
    BeforeOpen = csDSBeforeOpen
    CommandText = 'SELECT * FROM `coverslipstatuses` ORDER by id'
    MaxBlobSize = 1
    Params = <>
    Left = 64
    Top = 136
    object csStatusDSid: TIntegerField
      FieldName = 'id'
    end
    object csStatusDSstatus: TStringField
      FieldName = 'status'
      Required = True
      Size = 255
    end
    object csStatusDSnote: TMemoField
      FieldName = 'note'
      BlobType = ftMemo
      Size = 1
    end
  end
  object csStatusP: TDataSetProvider
    DataSet = csStatusDS
    Left = 192
    Top = 136
  end
  object csStatusCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'csStatusP'
    AfterPost = CDSAfterPost
    Left = 312
    Top = 136
    object csStatusCDSid: TIntegerField
      FieldName = 'id'
    end
    object csStatusCDSstatus: TStringField
      FieldName = 'status'
      Required = True
      Size = 255
    end
    object csStatusCDSnote: TMemoField
      FieldName = 'note'
      BlobType = ftMemo
      Size = 1
    end
  end
  object csStatusDSource: TDataSource
    DataSet = csStatusCDS
    Left = 432
    Top = 136
  end
  object csTypeDS: TSQLDataSet
    BeforeOpen = csDSBeforeOpen
    CommandText = 'SELECT * FROM `coversliptypes` ORDER by id'
    MaxBlobSize = 1
    Params = <>
    Left = 64
    Top = 208
    object csTypeDSid: TIntegerField
      FieldName = 'id'
    end
    object csTypeDStype: TStringField
      FieldName = 'type'
      Required = True
      Size = 255
    end
    object csTypeDSnote: TMemoField
      FieldName = 'note'
      BlobType = ftMemo
      Size = 1
    end
  end
  object csTypeP: TDataSetProvider
    DataSet = csTypeDS
    Left = 192
    Top = 208
  end
  object csTypeCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'csTypeP'
    AfterPost = CDSAfterPost
    Left = 312
    Top = 208
    object csTypeCDSid: TIntegerField
      FieldName = 'id'
    end
    object csTypeCDStype: TStringField
      FieldName = 'type'
      Required = True
      Size = 255
    end
    object csTypeCDSnote: TMemoField
      FieldName = 'note'
      BlobType = ftMemo
      Size = 1
    end
  end
  object csTypeDSource: TDataSource
    DataSet = csTypeCDS
    Left = 432
    Top = 208
  end
  object csDustAssayDS: TSQLDataSet
    BeforeOpen = csDSBeforeOpen
    CommandText = 'SELECT * FROM coverslipdustassays where coverslip_id = :id'
    DataSource = csDSource
    MaxBlobSize = 1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    Left = 48
    Top = 488
  end
  object csDustAssayP: TDataSetProvider
    DataSet = csDustAssayDS
    Left = 184
    Top = 488
  end
  object csDustAssayCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'csDustAssayP'
    AfterPost = CDSAfterPost
    AfterDelete = CDSAfterDelete
    Left = 304
    Top = 488
  end
  object csDustAsssayDSource: TDataSource
    DataSet = csDustAssayCDS
    OnDataChange = csDustAsssayDSourceDataChange
    Left = 424
    Top = 488
  end
  object csFreshBatchesDSource: TDataSource
    DataSet = csFreshBatchesCDS
    OnDataChange = csDustAsssayDSourceDataChange
    Left = 432
    Top = 312
  end
  object csFreshBatchP: TDataSetProvider
    DataSet = csFreshBatchesDS
    Options = [poAllowCommandText, poUseQuoteChar]
    Left = 192
    Top = 312
  end
  object csFreshBatchesDS: TSQLDataSet
    BeforeOpen = csDSBeforeOpen
    CommandText = 'SELECT * FROM freshCSBatches ORDER by date_created DESC'
    DataSource = csDSource
    MaxBlobSize = 1
    Params = <>
    Left = 56
    Top = 312
  end
  object csFreshBatchesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'csFreshBatchP'
    AfterPost = CDSAfterPost
    AfterDelete = CDSAfterDelete
    Left = 296
    Top = 312
    object csFreshBatchesCDSid: TIntegerField
      DisplayLabel = 'ID'
      FieldName = 'id'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
      Required = True
    end
    object csFreshBatchesCDSdate_created: TSQLTimeStampField
      DisplayLabel = 'Date Entered'
      FieldName = 'date_created'
      Required = True
    end
    object csFreshBatchesCDScount: TIntegerField
      DisplayLabel = 'Count'
      FieldName = 'count'
    end
    object csFreshBatchesCDStype: TIntegerField
      DisplayLabel = 'Type'
      FieldName = 'type'
      Required = True
    end
    object csFreshBatchesCDSlot_number: TStringField
      DisplayLabel = 'LOT #'
      FieldName = 'lot_number'
      Size = 128
    end
    object csFreshBatchesCDSbox_number: TIntegerField
      DisplayLabel = 'Box #'
      FieldName = 'box_number'
      Required = True
    end
  end
end
