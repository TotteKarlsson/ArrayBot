object MoviesFrame: TMoviesFrame
  Left = 0
  Top = 0
  Width = 849
  Height = 514
  TabOrder = 0
  object Panel22: TPanel
    Left = 0
    Top = 459
    Width = 849
    Height = 55
    Align = alBottom
    TabOrder = 0
    object Label4: TLabel
      Left = 32
      Top = 24
      Width = 96
      Height = 13
      Caption = 'Number of Records:'
    end
    object NrOfRecordsLbl: TIntLabel
      Left = 197
      Top = 20
      Width = 19
      Height = 25
      Caption = '-1'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      Value = -1
      TheFont.Charset = DEFAULT_CHARSET
      TheFont.Color = clWindowText
      TheFont.Height = -21
      TheFont.Name = 'Tahoma'
      TheFont.Style = []
    end
  end
  object ScrollBox2: TScrollBox
    Left = 0
    Top = 0
    Width = 849
    Height = 459
    Align = alClient
    TabOrder = 1
    object FlowPanel1: TFlowPanel
      Left = 0
      Top = 0
      Width = 828
      Height = 521
      Align = alTop
      AutoSize = True
      BevelOuter = bvNone
      TabOrder = 0
    end
  end
  object GetMoviesQuery: TSQLQuery
    DataSource = pgDM.blockIDsDataSource
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftUnknown
        Name = 'id'
        ParamType = ptInput
      end>
    SQL.Strings = (
      
        'SELECT id,created,fileextension from movies where block_id=:id O' +
        'RDER by created DESC')
    SQLConnection = pgDM.SQLConnection1
    Left = 69
    Top = 96
  end
end
