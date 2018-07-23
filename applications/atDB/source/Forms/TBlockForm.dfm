object BlockForm: TBlockForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Tissue Block Form'
  ClientHeight = 526
  ClientWidth = 571
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 35
    Height = 13
    Caption = 'Slice ID'
    FocusControl = DBEdit1
  end
  object Label12: TLabel
    Left = 174
    Top = 16
    Width = 26
    Height = 13
    Caption = 'Serial'
    FocusControl = DBEdit2
  end
  object Label13: TLabel
    Left = 16
    Top = 61
    Width = 53
    Height = 13
    Caption = 'Entered by'
    FocusControl = DBLookupComboBox10
  end
  object Label14: TLabel
    Left = 132
    Top = 64
    Width = 76
    Height = 13
    Caption = 'Date Embedded'
    FocusControl = DBEdit3
  end
  object Label15: TLabel
    Left = 234
    Top = 64
    Width = 31
    Height = 13
    Caption = 'Status'
    FocusControl = DBLookupComboBox11
  end
  object Label2: TLabel
    Left = 336
    Top = 16
    Width = 55
    Height = 13
    Caption = 'Entered On'
    FocusControl = DBEdit4
  end
  object Panel1: TPanel
    Left = 0
    Top = 475
    Width = 571
    Height = 51
    Align = alBottom
    TabOrder = 0
    ExplicitTop = 484
    DesignSize = (
      571
      51)
    object Button1: TButton
      Left = 379
      Top = 16
      Width = 60
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Post'
      ModalResult = 1
      TabOrder = 1
    end
    object Button2: TButton
      Left = 468
      Top = 16
      Width = 60
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
    end
  end
  object DBEdit1: TDBEdit
    Left = 16
    Top = 32
    Width = 134
    Height = 21
    DataField = 'slice_id'
    DataSource = DataSource1
    Enabled = False
    ReadOnly = True
    TabOrder = 1
  end
  object DBEdit2: TDBEdit
    Left = 174
    Top = 32
    Width = 134
    Height = 21
    DataField = 'serial'
    DataSource = DataSource1
    Enabled = False
    ReadOnly = True
    TabOrder = 2
  end
  object DBEdit3: TDBEdit
    Left = 132
    Top = 80
    Width = 87
    Height = 21
    DataField = 'date_embedded'
    DataSource = DataSource1
    TabOrder = 3
  end
  object DBLookupComboBox10: TDBLookupComboBox
    Left = 16
    Top = 80
    Width = 91
    Height = 21
    DataField = 'entered_by'
    DataSource = DataSource1
    DropDownRows = 15
    KeyField = 'id'
    ListField = 'user_name'
    ListSource = pgDM.usersDataSource
    TabOrder = 4
  end
  object DBLookupComboBox11: TDBLookupComboBox
    Left = 234
    Top = 80
    Width = 136
    Height = 21
    DataField = 'LBlockStatus'
    DataSource = DataSource1
    TabOrder = 5
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 107
    Width = 584
    Height = 353
    Caption = 'Protocols'
    TabOrder = 6
    object Label11: TLabel
      Left = 12
      Top = 260
      Width = 94
      Height = 13
      Caption = 'Embedding Protocol'
      FocusControl = DBLookupComboBox9
    end
    object Label6: TLabel
      Left = 12
      Top = 34
      Width = 114
      Height = 13
      Caption = 'CryoProtection Protocol'
      FocusControl = DBLookupComboBox5
    end
    object Label7: TLabel
      Left = 12
      Top = 91
      Width = 83
      Height = 13
      Caption = 'Freezing Protocol'
      FocusControl = DBLookupComboBox6
    end
    object Label8: TLabel
      Left = 12
      Top = 147
      Width = 99
      Height = 13
      Caption = 'Substitution Protocol'
      FocusControl = DBLookupComboBox7
    end
    object Label9: TLabel
      Left = 12
      Top = 203
      Width = 92
      Height = 13
      Caption = 'Infiltration Protocol'
      FocusControl = DBLookupComboBox8
    end
    object DBLookupComboBox5: TDBLookupComboBox
      Left = 12
      Top = 52
      Width = 500
      Height = 21
      DataField = 'LCryoProtectionProtocol'
      DataSource = DataSource1
      TabOrder = 0
    end
    object DBLookupComboBox6: TDBLookupComboBox
      Left = 12
      Top = 108
      Width = 500
      Height = 21
      DataField = 'LFreezingProtocol'
      DataSource = DataSource1
      TabOrder = 1
    end
    object DBLookupComboBox7: TDBLookupComboBox
      Left = 12
      Top = 222
      Width = 500
      Height = 21
      DataField = 'LInfiltrationProtocol'
      DataSource = DataSource1
      TabOrder = 3
    end
    object DBLookupComboBox8: TDBLookupComboBox
      Left = 12
      Top = 279
      Width = 500
      Height = 21
      DataField = 'LEmbeddingProtocol'
      DataSource = DataSource1
      TabOrder = 4
    end
    object DBLookupComboBox9: TDBLookupComboBox
      Left = 12
      Top = 166
      Width = 500
      Height = 21
      DataField = 'LSubstitutionProtocol'
      DataSource = DataSource1
      TabOrder = 2
    end
  end
  object DBEdit4: TDBEdit
    Left = 336
    Top = 32
    Width = 192
    Height = 21
    DataField = 'entered_on'
    DataSource = DataSource1
    Enabled = False
    TabOrder = 7
  end
  object DataSource1: TDataSource
    DataSet = pgDM.blocksCDS
    Left = 480
    Top = 120
  end
end
