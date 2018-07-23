object CoverSlipScanFrame: TCoverSlipScanFrame
  Left = 0
  Top = 0
  Width = 1369
  Height = 831
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 1369
    Height = 831
    Align = alClient
    Caption = 'Ribbon Info'
    TabOrder = 0
    object TopPanel: TPanel
      Left = 2
      Top = 15
      Width = 1365
      Height = 82
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 1365
        Height = 88
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object CSIDE: TIntegerLabeledEdit
          Left = 32
          Top = 43
          Width = 121
          Height = 33
          EditLabel.Width = 113
          EditLabel.Height = 25
          EditLabel.Caption = 'Coverslip ID'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -21
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          Text = '0'
        end
      end
    end
    object Panel2: TPanel
      Left = 2
      Top = 97
      Width = 1365
      Height = 416
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object GroupBox3: TGroupBox
        Left = 0
        Top = 0
        Width = 1365
        Height = 416
        Align = alClient
        Caption = 'Ribbon History'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object Label2: TLabel
          Left = 32
          Top = 49
          Width = 93
          Height = 25
          Caption = 'Animal ID'
          FocusControl = DBEdit2
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Label3: TLabel
          Left = 256
          Top = 49
          Width = 109
          Height = 25
          Caption = 'Intake Date'
          FocusControl = DBEdit3
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Label4: TLabel
          Left = 32
          Top = 129
          Width = 72
          Height = 25
          Caption = 'Slice ID'
          FocusControl = DBEdit4
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Label5: TLabel
          Left = 32
          Top = 208
          Width = 78
          Height = 25
          Caption = 'Block ID'
          FocusControl = DBEdit5
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Label6: TLabel
          Left = 32
          Top = 291
          Width = 76
          Height = 25
          Caption = 'Knife ID'
          FocusControl = DBEdit6
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Label7: TLabel
          Left = 256
          Top = 291
          Width = 129
          Height = 25
          Caption = 'Cutting Order'
          FocusControl = DBEdit7
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Label8: TLabel
          Left = 480
          Top = 291
          Width = 184
          Height = 25
          Caption = 'Number of Sections'
          FocusControl = DBEdit8
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Label9: TLabel
          Left = 256
          Top = 208
          Width = 114
          Height = 25
          Caption = 'Block Status'
          FocusControl = DBLookupComboBox1
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Label10: TLabel
          Left = 704
          Top = 291
          Width = 130
          Height = 25
          Caption = 'Ribbon Status'
          FocusControl = DBLookupComboBox2
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Label1: TLabel
          Left = 477
          Top = 49
          Width = 187
          Height = 25
          Caption = 'Specimen Summary'
          FocusControl = DBEdit1
        end
        object Label11: TLabel
          Left = 480
          Top = 208
          Width = 106
          Height = 25
          Caption = 'Block Resin'
          FocusControl = DBLookupComboBox3
        end
        object DBNavigator1: TDBNavigator
          Left = 2
          Top = 368
          Width = 1361
          Height = 46
          DataSource = DataSource1
          VisibleButtons = [nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
          Align = alBottom
          TabOrder = 0
        end
        object DBEdit2: TDBEdit
          Left = 32
          Top = 80
          Width = 200
          Height = 33
          DataField = 'animal_id'
          DataSource = DataSource1
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
        end
        object DBEdit3: TDBEdit
          Left = 256
          Top = 80
          Width = 200
          Height = 33
          DataField = 'intake_date'
          DataSource = DataSource1
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
        object DBEdit4: TDBEdit
          Left = 32
          Top = 160
          Width = 200
          Height = 33
          DataField = 'slice_id'
          DataSource = DataSource1
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object DBEdit5: TDBEdit
          Left = 32
          Top = 237
          Width = 200
          Height = 33
          DataField = 'block_id'
          DataSource = DataSource1
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object DBEdit6: TDBEdit
          Left = 32
          Top = 322
          Width = 200
          Height = 33
          DataField = 'knife_id'
          DataSource = DataSource1
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
        object DBEdit7: TDBEdit
          Left = 256
          Top = 322
          Width = 200
          Height = 33
          DataField = 'cutting_order'
          DataSource = DataSource1
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
        end
        object DBEdit8: TDBEdit
          Left = 480
          Top = 322
          Width = 186
          Height = 33
          DataField = 'nr_of_sections'
          DataSource = DataSource1
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 7
        end
        object DBLookupComboBox1: TDBLookupComboBox
          Left = 256
          Top = 237
          Width = 200
          Height = 33
          DataField = 'blockStatusL'
          DataSource = DataSource1
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 8
        end
        object DBLookupComboBox2: TDBLookupComboBox
          Left = 704
          Top = 322
          Width = 214
          Height = 33
          DataField = 'ribbonStatusL'
          DataSource = DataSource1
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 9
        end
        object DBEdit1: TDBEdit
          Left = 477
          Top = 80
          Width = 524
          Height = 33
          DataField = 'summary'
          DataSource = DataSource1
          TabOrder = 10
        end
        object DBLookupComboBox3: TDBLookupComboBox
          Left = 480
          Top = 237
          Width = 200
          Height = 33
          DataField = 'blockResin'
          DataSource = DataSource1
          TabOrder = 11
        end
      end
    end
    object BottomPanel: TPanel
      Left = 2
      Top = 513
      Width = 1365
      Height = 316
      Align = alClient
      TabOrder = 2
      inline MoviesFrame1: TMoviesFrame
        AlignWithMargins = True
        Left = 4
        Top = 4
        Width = 746
        Height = 308
        Align = alClient
        TabOrder = 0
        ExplicitLeft = 4
        ExplicitTop = 4
        ExplicitWidth = 746
        ExplicitHeight = 308
        inherited Panel22: TPanel
          Top = 253
          Width = 746
          ExplicitTop = 253
          ExplicitWidth = 746
          inherited Label4: TLabel
            Top = 12
            ExplicitTop = 12
          end
          inherited NrOfRecordsLbl: TIntLabel
            Left = 237
            Top = 12
            ExplicitLeft = 237
            ExplicitTop = 12
          end
        end
        inherited ScrollBox2: TScrollBox
          Width = 746
          Height = 253
          ExplicitWidth = 746
          ExplicitHeight = 253
          inherited FlowPanel1: TFlowPanel
            Width = 725
            ExplicitWidth = 725
          end
        end
      end
      inline TRibbonNotesFrame1: TRibbonNotesFrame
        Left = 753
        Top = 1
        Width = 611
        Height = 314
        Align = alRight
        TabOrder = 1
        ExplicitLeft = 753
        ExplicitTop = 1
        ExplicitWidth = 611
        ExplicitHeight = 314
        inherited GroupBox1: TGroupBox
          Width = 611
          Height = 314
          ExplicitWidth = 611
          ExplicitHeight = 314
          inherited Panel15: TPanel
            Height = 297
            ExplicitHeight = 297
            inherited mRibbonNotesGrid: TDBGrid
              Height = 270
            end
            inherited RibbonNotesNavigator: TDBNavigator
              Top = 271
              Hints.Strings = ()
              ExplicitTop = 271
            end
          end
          inherited Panel16: TPanel
            Width = 422
            Height = 297
            ExplicitWidth = 422
            ExplicitHeight = 297
            inherited mRibbonNoteMemo: TDBMemo
              Width = 420
              Height = 270
              ExplicitWidth = 420
              ExplicitHeight = 270
            end
            inherited RibbonNoteNavigator: TDBNavigator
              Top = 271
              Width = 420
              Hints.Strings = ()
              ExplicitTop = 271
              ExplicitWidth = 420
            end
          end
        end
      end
    end
  end
  object DataSource1: TDataSource
    DataSet = ClientDataSet1
    Left = 808
    Top = 104
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = SQLDataSet1
    Left = 800
    Top = 40
  end
  object ClientDataSet1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 696
    Top = 112
    object ClientDataSet1ribbon_id: TWideStringField
      DisplayLabel = 'Ribbon ID'
      FieldName = 'ribbon_id'
      ProviderFlags = [pfInWhere]
      ReadOnly = True
      Size = 36
    end
    object ClientDataSet1animal_id: TWideStringField
      DisplayLabel = 'Animal ID'
      FieldName = 'animal_id'
      ProviderFlags = [pfInWhere]
      ReadOnly = True
      Size = 64
    end
    object ClientDataSet1intake_date: TSQLTimeStampField
      DisplayLabel = 'Intake Date'
      FieldName = 'intake_date'
      ProviderFlags = [pfInWhere]
      ReadOnly = True
    end
    object ClientDataSet1slice_id: TIntegerField
      DisplayLabel = 'Slice ID'
      FieldName = 'slice_id'
      ProviderFlags = [pfInWhere]
      ReadOnly = True
    end
    object ClientDataSet1block_id: TIntegerField
      DisplayLabel = 'Block ID'
      FieldName = 'block_id'
      ProviderFlags = [pfInWhere]
      ReadOnly = True
    end
    object ClientDataSet1knife_id: TIntegerField
      DisplayLabel = 'Knife ID'
      FieldName = 'knife_id'
      ProviderFlags = [pfInWhere]
      ReadOnly = True
    end
    object ClientDataSet1cutting_order: TIntegerField
      DisplayLabel = 'Cutting Order'
      FieldName = 'cutting_order'
      ProviderFlags = [pfInWhere]
    end
    object ClientDataSet1nr_of_sections: TSmallintField
      DisplayLabel = 'Number of Sections'
      FieldName = 'nr_of_sections'
      ProviderFlags = [pfInWhere]
    end
    object ClientDataSet1blockStatusL: TStringField
      DisplayLabel = 'Block Status'
      FieldKind = fkLookup
      FieldName = 'blockStatusL'
      LookupDataSet = pgDM.blockstatusDS
      LookupKeyFields = 'id'
      LookupResultField = 'status'
      KeyFields = 'block_status'
      Lookup = True
    end
    object ClientDataSet1ribbonStatusL: TStringField
      DisplayLabel = 'Ribbon Status'
      FieldKind = fkLookup
      FieldName = 'ribbonStatusL'
      LookupDataSet = pgDM.ribbonStatusDS
      LookupKeyFields = 'id'
      LookupResultField = 'status'
      KeyFields = 'ribbon_status'
      Lookup = True
    end
    object ClientDataSet1block_status: TSmallintField
      FieldName = 'block_status'
    end
    object ClientDataSet1ribbon_status: TIntegerField
      FieldName = 'ribbon_status'
    end
    object ClientDataSet1summary: TWideStringField
      DisplayLabel = 'Specimen Summary'
      FieldName = 'summary'
      Size = 256
    end
    object ClientDataSet1infiltration_protocol: TSmallintField
      FieldName = 'infiltration_protocol'
    end
    object ClientDataSet1blockResin: TStringField
      FieldKind = fkLookup
      FieldName = 'blockResin'
      LookupDataSet = pgDM.infiltrationProtocolDS
      LookupKeyFields = 'id'
      LookupResultField = 'protocol'
      KeyFields = 'infiltration_protocol'
      ReadOnly = True
      Lookup = True
    end
  end
  object SQLDataSet1: TSQLDataSet
    CommandText = 
      'SELECT specimen.animal_id, specimen.intake_date, specimen.summar' +
      'y,'#13#10'slices.id as slice_id, '#13#10'blocks.id as block_id, blocks.statu' +
      's as block_status, blocks.infiltration_protocol,'#13#10'ribbons.id as ' +
      'ribbon_id, ribbons.knife_id, ribbons.cutting_order, ribbons.nr_o' +
      'f_sections, ribbons.status as ribbon_status'#13#10'    FROM specimen'#13#10 +
      '    JOIN slices  ON specimen.id = slices.specimen_id'#13#10'    JOIN b' +
      'locks  ON slices.id = blocks.slice_id '#13#10'    JOIN ribbons ON bloc' +
      'ks.id = ribbons.block_id'#13#10'    WHERE ribbons.coverslip_id = :csID'
    DataSource = DataSource1
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftInteger
        Name = 'csID'
        ParamType = ptInput
      end>
    SQLConnection = pgDM.SQLConnection1
    Left = 704
    Top = 40
    object SQLDataSet1ribbon_id: TWideStringField
      FieldName = 'ribbon_id'
      Size = 36
    end
    object SQLDataSet1animal_id: TWideStringField
      FieldName = 'animal_id'
      Size = 64
    end
    object SQLDataSet1intake_date: TSQLTimeStampField
      FieldName = 'intake_date'
    end
    object SQLDataSet1slice_id: TIntegerField
      FieldName = 'slice_id'
    end
    object SQLDataSet1block_id: TIntegerField
      FieldName = 'block_id'
    end
    object SQLDataSet1block_status: TSmallintField
      FieldName = 'block_status'
    end
    object SQLDataSet1knife_id: TIntegerField
      FieldName = 'knife_id'
    end
    object SQLDataSet1cutting_order: TIntegerField
      FieldName = 'cutting_order'
    end
    object SQLDataSet1nr_of_sections: TSmallintField
      FieldName = 'nr_of_sections'
    end
    object SQLDataSet1ribbon_status: TIntegerField
      FieldName = 'ribbon_status'
    end
    object SQLDataSet1summary: TWideStringField
      FieldName = 'summary'
      Size = 256
    end
    object SQLDataSet1infiltration_protocol: TSmallintField
      FieldName = 'infiltration_protocol'
    end
  end
end
