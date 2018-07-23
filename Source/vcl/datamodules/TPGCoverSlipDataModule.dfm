object csPGDM: TcsPGDM
  OldCreateOrder = False
  Height = 638
  Width = 602
  object csDS: TSQLDataSet
    BeforeOpen = csDSBeforeOpen
    CommandText = 'SELECT * FROM coverslips'
    MaxBlobSize = 1
    Params = <>
    SQLConnection = pgDM.SQLConnection1
    Left = 64
    Top = 56
    object csDSid: TIntegerField
      FieldName = 'id'
    end
    object csDSstatus: TIntegerField
      FieldName = 'status'
    end
    object csDStype: TIntegerField
      FieldName = 'type'
    end
    object csDSnotes: TWideMemoField
      FieldName = 'notes'
      BlobType = ftWideMemo
      Size = -1
    end
    object csDSfreshCSBatch: TIntegerField
      FieldName = 'freshcsbatch'
    end
    object csDScleanCSBatch: TIntegerField
      FieldName = 'cleancsbatch'
    end
    object csDScarboncoatbatch: TIntegerField
      FieldName = 'carboncoatbatch'
    end
    object csDSfrom_lot: TWideStringField
      FieldName = 'from_lot'
      Size = 128
    end
    object csDSsilanizedCSBatch: TIntegerField
      FieldName = 'silanizedcsbatch'
    end
    object csDSmodified: TSQLTimeStampField
      FieldName = 'modified'
      ProviderFlags = [pfInUpdate]
    end
  end
  object csP: TDataSetProvider
    DataSet = csDS
    Options = [poAllowCommandText, poUseQuoteChar]
    Left = 215
    Top = 56
  end
  object csCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'csP'
    AfterPost = CDSAfterPost
    AfterDelete = CDSAfterDelete
    AfterScroll = CDSAfterScroll
    Left = 345
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
    object csCDSLStatus: TWideStringField
      DisplayLabel = 'Status'
      FieldKind = fkLookup
      FieldName = 'LStatus'
      LookupDataSet = csStatusCDS
      LookupKeyFields = 'id'
      LookupResultField = 'status'
      KeyFields = 'status'
      Lookup = True
    end
    object csCDSLType: TWideStringField
      DisplayLabel = 'Type'
      FieldKind = fkLookup
      FieldName = 'LType'
      LookupDataSet = csTypeCDS
      LookupKeyFields = 'id'
      LookupResultField = 'type'
      KeyFields = 'type'
      Lookup = True
    end
    object csCDSnotes: TWideMemoField
      DisplayLabel = 'Notes'
      FieldName = 'notes'
      BlobType = ftMemo
      Size = 1
    end
    object csCDSfreshCSBatch: TIntegerField
      FieldName = 'freshcsbatch'
      Required = True
    end
    object csCDScleanCSBatch: TIntegerField
      FieldName = 'cleancsbatch'
    end
    object csCDScarboncoatbatch: TIntegerField
      FieldName = 'carboncoatbatch'
    end
    object csCDSfrom_lot: TWideStringField
      DisplayLabel = 'From LOT#'
      FieldName = 'from_lot'
      Size = 128
    end
  end
  object csDSource: TDataSource
    DataSet = csCDS
    Left = 465
    Top = 56
  end
  object csStatusDS: TSQLDataSet
    BeforeOpen = csDSBeforeOpen
    CommandText = 'SELECT * FROM coverslipstatuses ORDER by id'
    MaxBlobSize = 1
    Params = <>
    SQLConnection = pgDM.SQLConnection1
    Left = 64
    Top = 136
    object csStatusDSid: TIntegerField
      FieldName = 'id'
    end
    object csStatusDSstatus: TWideStringField
      FieldName = 'status'
      Required = True
      Size = 255
    end
    object csStatusDSnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftMemo
      Size = 1
    end
  end
  object csStatusP: TDataSetProvider
    DataSet = csStatusDS
    Left = 208
    Top = 136
  end
  object csStatusCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'csStatusP'
    AfterPost = CDSAfterPost
    Left = 353
    Top = 136
    object csStatusCDSid: TIntegerField
      FieldName = 'id'
    end
    object csStatusCDSstatus: TWideStringField
      FieldName = 'status'
      Required = True
      Size = 255
    end
    object csStatusCDSnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftMemo
      Size = 1
    end
  end
  object csStatusDSource: TDataSource
    DataSet = csStatusCDS
    Left = 473
    Top = 136
  end
  object csTypeDS: TSQLDataSet
    BeforeOpen = csDSBeforeOpen
    CommandText = 'SELECT * FROM coversliptypes ORDER by id'
    MaxBlobSize = 1
    Params = <>
    SQLConnection = pgDM.SQLConnection1
    Left = 64
    Top = 208
    object csTypeDSid: TIntegerField
      FieldName = 'id'
    end
    object csTypeDStype: TWideStringField
      FieldName = 'type'
      Required = True
      Size = 255
    end
    object csTypeDSnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftMemo
      Size = 1
    end
  end
  object csTypeP: TDataSetProvider
    DataSet = csTypeDS
    Left = 208
    Top = 208
  end
  object csTypeCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'csTypeP'
    AfterPost = CDSAfterPost
    Left = 353
    Top = 208
    object csTypeCDSid: TIntegerField
      FieldName = 'id'
    end
    object csTypeCDStype: TWideStringField
      FieldName = 'type'
      Required = True
      Size = 255
    end
    object csTypeCDSnote: TWideMemoField
      FieldName = 'note'
      BlobType = ftMemo
      Size = 1
    end
  end
  object csTypeDSource: TDataSource
    DataSet = csTypeCDS
    Left = 473
    Top = 208
  end
  object csFreshBatchesDSource: TDataSource
    DataSet = csFreshBatchesCDS
    Left = 473
    Top = 312
  end
  object csFreshBatchP: TDataSetProvider
    DataSet = csFreshBatchesDS
    Options = [poAllowCommandText, poUseQuoteChar]
    Left = 208
    Top = 312
  end
  object csFreshBatchesDS: TSQLDataSet
    BeforeOpen = csDSBeforeOpen
    CommandText = 'SELECT * FROM freshcsbatches ORDER by date_created DESC'
    DataSource = csDSource
    MaxBlobSize = 1
    Params = <>
    SQLConnection = pgDM.SQLConnection1
    Left = 56
    Top = 312
    object csFreshBatchesDSid: TIntegerField
      FieldName = 'id'
    end
    object csFreshBatchesDSdate_created: TSQLTimeStampField
      FieldName = 'date_created'
      ProviderFlags = [pfInUpdate]
    end
    object csFreshBatchesDScount: TIntegerField
      FieldName = 'count'
    end
    object csFreshBatchesDStype: TIntegerField
      FieldName = 'type'
    end
    object csFreshBatchesDSlot_number: TWideStringField
      FieldName = 'lot_number'
      Size = 128
    end
    object csFreshBatchesDSbox_number: TIntegerField
      FieldName = 'box_number'
    end
  end
  object csFreshBatchesCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'csFreshBatchP'
    AfterPost = CDSAfterPost
    AfterDelete = CDSAfterDelete
    Left = 337
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
    object csFreshBatchesCDSlot_number: TWideStringField
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
  object ROnCoverSlipsSource: TDataSource
    DataSet = ROnCS_CDS
    Left = 471
    Top = 414
  end
  object ROnCS_CDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'RibbonsOnCoverslipsProvider'
    Left = 336
    Top = 414
    object ROnCS_CDSid: TWideStringField
      FieldName = 'id'
      Size = 36
    end
    object ROnCS_CDSstatus: TIntegerField
      FieldName = 'status'
    end
    object ROnCS_CDSblock_id: TIntegerField
      DisplayLabel = 'Block ID'
      FieldName = 'block_id'
    end
    object ROnCS_CDScutting_order: TIntegerField
      DisplayLabel = 'Cutting Order'
      FieldName = 'cutting_order'
    end
    object ROnCS_CDSnr_of_sections: TSmallintField
      DisplayLabel = '# of Sections'
      FieldName = 'nr_of_sections'
    end
    object ROnCS_CDScreated_on: TSQLTimeStampField
      DisplayLabel = 'Cut on Date'
      FieldName = 'created_on'
    end
    object ROnCS_CDSmodified: TSQLTimeStampField
      FieldName = 'modified'
    end
    object ROnCS_CDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
    object ROnCS_CDScoverslip_id: TIntegerField
      FieldName = 'coverslip_id'
    end
    object ROnCS_CDScreated_byL: TStringField
      DisplayLabel = 'Created By'
      FieldKind = fkLookup
      FieldName = 'created_byL'
      LookupDataSet = pgDM.usersDS
      LookupKeyFields = 'id'
      LookupResultField = 'user_name'
      KeyFields = 'created_by'
      LookupCache = True
      Lookup = True
    end
    object ROnCS_CDSstatusL: TStringField
      FieldKind = fkLookup
      FieldName = 'statusL'
      LookupDataSet = pgDM.ribbonStatusDS
      LookupKeyFields = 'id'
      LookupResultField = 'status'
      KeyFields = 'status'
      Lookup = True
    end
  end
  object RibbonsOnCoverslipsProvider: TDataSetProvider
    DataSet = ribbonsOnCoverSlipsDS
    Options = [poFetchBlobsOnDemand, poAllowCommandText, poRetainServerOrder, poUseQuoteChar]
    Left = 200
    Top = 414
  end
  object ribbonsOnCoverSlipsDS: TSQLDataSet
    CommandText = 'SELECT * from ribbons where coverslip_id = :id'
    DataSource = csDSource
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftInteger
        Name = 'id'
        ParamType = ptInput
      end>
    SQLConnection = pgDM.SQLConnection1
    Left = 48
    Top = 414
    object ribbonsOnCoverSlipsDSid: TWideStringField
      FieldName = 'id'
      Size = 36
    end
    object ribbonsOnCoverSlipsDSstatus: TIntegerField
      FieldName = 'status'
    end
    object ribbonsOnCoverSlipsDSblock_id: TIntegerField
      FieldName = 'block_id'
    end
    object ribbonsOnCoverSlipsDScutting_order: TIntegerField
      FieldName = 'cutting_order'
    end
    object ribbonsOnCoverSlipsDSnr_of_sections: TSmallintField
      FieldName = 'nr_of_sections'
    end
    object ribbonsOnCoverSlipsDScreated_on: TSQLTimeStampField
      FieldName = 'created_on'
      ProviderFlags = [pfInUpdate]
    end
    object ribbonsOnCoverSlipsDSmodified: TSQLTimeStampField
      FieldName = 'modified'
      ProviderFlags = [pfInUpdate]
    end
    object ribbonsOnCoverSlipsDScreated_by: TIntegerField
      FieldName = 'created_by'
    end
    object ribbonsOnCoverSlipsDScoverslip_id: TIntegerField
      FieldName = 'coverslip_id'
    end
  end
end
