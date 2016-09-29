object SQLiteDBFrame: TSQLiteDBFrame
  Left = 0
  Top = 0
  Width = 451
  Height = 304
  Align = alClient
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 451
    Height = 304
    Align = alClient
    Caption = 'Database Info'
    TabOrder = 0
    DesignSize = (
      451
      304)
    object NrOfOrdersLbl: TIntLabel
      Left = 89
      Top = 72
      Width = 10
      Height = 13
      Caption = '-1'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ValueString = '-1'
      Value = -1
      TheFont.Charset = DEFAULT_CHARSET
      TheFont.Color = clWindowText
      TheFont.Height = -11
      TheFont.Name = 'Tahoma'
      TheFont.Style = []
    end
    object Label1: TLabel
      Left = 11
      Top = 72
      Width = 64
      Height = 13
      Caption = 'Nr of Orders:'
    end
    object DBNameE: TSTDStringLabeledEdit
      Left = 11
      Top = 32
      Width = 430
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 32
      EditLabel.Height = 13
      EditLabel.Caption = 'DB File'
      TabOrder = 0
    end
    object Button1: TButton
      Left = 366
      Top = 67
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Truncate'
      TabOrder = 1
      OnClick = Button1Click
    end
  end
end
