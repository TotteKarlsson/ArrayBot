object NewBlockForm: TNewBlockForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Tissue Block Form'
  ClientHeight = 786
  ClientWidth = 747
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label10: TLabel
    Left = 18
    Top = 453
    Width = 36
    Height = 13
    Caption = 'Species'
  end
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 747
    Height = 735
    Align = alClient
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 16
      Width = 51
      Height = 13
      Caption = 'Process ID'
      FocusControl = DBEdit1
    end
    object Label12: TLabel
      Left = 16
      Top = 64
      Width = 26
      Height = 13
      Caption = 'Serial'
      FocusControl = DBEdit2
    end
    object Label13: TLabel
      Left = 174
      Top = 61
      Width = 54
      Height = 13
      Caption = 'Created by'
      FocusControl = DBLookupComboBox10
    end
    object Label14: TLabel
      Left = 290
      Top = 64
      Width = 78
      Height = 13
      Caption = 'date_embedded'
      FocusControl = DBEdit3
    end
    object Label15: TLabel
      Left = 392
      Top = 64
      Width = 31
      Height = 13
      Caption = 'Status'
      FocusControl = DBLookupComboBox11
    end
    object DBEdit1: TDBEdit
      Left = 16
      Top = 32
      Width = 512
      Height = 21
      DataField = 'specimen_id'
      DataSource = DataSource1
      Enabled = False
      ReadOnly = True
      TabOrder = 0
    end
    object GroupBox1: TGroupBox
      Left = 16
      Top = 128
      Width = 561
      Height = 549
      Caption = 'Protocols'
      TabOrder = 5
      object Label11: TLabel
        Left = 12
        Top = 474
        Width = 94
        Height = 13
        Caption = 'Embedding Protocol'
        FocusControl = DBLookupComboBox9
      end
      object Label3: TLabel
        Left = 12
        Top = 80
        Width = 80
        Height = 13
        Caption = 'Fixative Protocol'
        FocusControl = DBLookupComboBox2
      end
      object Label4: TLabel
        Left = 12
        Top = 136
        Width = 80
        Height = 13
        Caption = 'Fixation Protocol'
        FocusControl = DBLookupComboBox3
      end
      object Label5: TLabel
        Left = 12
        Top = 192
        Width = 77
        Height = 13
        Caption = 'PostFix Protocol'
        FocusControl = DBLookupComboBox4
      end
      object Label6: TLabel
        Left = 12
        Top = 248
        Width = 114
        Height = 13
        Caption = 'CryoProtection Protocol'
        FocusControl = DBLookupComboBox5
      end
      object Label7: TLabel
        Left = 12
        Top = 305
        Width = 83
        Height = 13
        Caption = 'Freezing Protocol'
        FocusControl = DBLookupComboBox6
      end
      object Label8: TLabel
        Left = 12
        Top = 361
        Width = 99
        Height = 13
        Caption = 'Substitution Protocol'
        FocusControl = DBLookupComboBox7
      end
      object Label9: TLabel
        Left = 12
        Top = 417
        Width = 92
        Height = 13
        Caption = 'Infiltration Protocol'
        FocusControl = DBLookupComboBox8
      end
      object Label2: TLabel
        Left = 12
        Top = 21
        Width = 146
        Height = 13
        Caption = 'Preprocess treatment protocol'
      end
      object DBLookupComboBox2: TDBLookupComboBox
        Left = 12
        Top = 96
        Width = 500
        Height = 21
        DataField = 'LFixativeProtocol'
        DataSource = DataSource1
        TabOrder = 1
      end
      object DBLookupComboBox3: TDBLookupComboBox
        Left = 12
        Top = 152
        Width = 500
        Height = 21
        DataField = 'LFixationProtocol'
        DataSource = DataSource1
        TabOrder = 2
      end
      object DBLookupComboBox4: TDBLookupComboBox
        Left = 12
        Top = 209
        Width = 500
        Height = 21
        DataField = 'LPostFixProtocol'
        DataSource = DataSource1
        TabOrder = 3
      end
      object DBLookupComboBox5: TDBLookupComboBox
        Left = 12
        Top = 266
        Width = 500
        Height = 21
        DataField = 'LCryoProtectionProtocol'
        DataSource = DataSource1
        TabOrder = 4
      end
      object DBLookupComboBox6: TDBLookupComboBox
        Left = 12
        Top = 322
        Width = 500
        Height = 21
        DataField = 'LFreezingProtocol'
        DataSource = DataSource1
        TabOrder = 5
      end
      object DBLookupComboBox7: TDBLookupComboBox
        Left = 12
        Top = 436
        Width = 500
        Height = 21
        DataField = 'LInfiltrationProtocol'
        DataSource = DataSource1
        TabOrder = 7
      end
      object DBLookupComboBox8: TDBLookupComboBox
        Left = 12
        Top = 493
        Width = 500
        Height = 21
        DataField = 'LEmbeddingProtocol'
        DataSource = DataSource1
        TabOrder = 8
      end
      object DBLookupComboBox9: TDBLookupComboBox
        Left = 12
        Top = 380
        Width = 500
        Height = 21
        DataField = 'LSubstitutionProtocol'
        DataSource = DataSource1
        TabOrder = 6
      end
      object DBLookupComboBox1: TDBLookupComboBox
        Left = 12
        Top = 40
        Width = 500
        Height = 21
        DataField = 'LPreprocessTreatmentProtocol'
        DataSource = DataSource1
        TabOrder = 0
      end
    end
    object DBEdit2: TDBEdit
      Left = 16
      Top = 80
      Width = 134
      Height = 21
      DataField = 'serial'
      DataSource = DataSource1
      Enabled = False
      ReadOnly = True
      TabOrder = 1
    end
    object DBLookupComboBox10: TDBLookupComboBox
      Left = 174
      Top = 80
      Width = 91
      Height = 21
      DataField = 'LUser'
      DataSource = DataSource1
      DropDownRows = 15
      TabOrder = 2
    end
    object DBEdit3: TDBEdit
      Left = 290
      Top = 80
      Width = 87
      Height = 21
      DataField = 'date_embedded'
      DataSource = DataSource1
      TabOrder = 3
    end
    object DBLookupComboBox11: TDBLookupComboBox
      Left = 392
      Top = 80
      Width = 136
      Height = 21
      DataField = 'LBlockStatus'
      DataSource = DataSource1
      TabOrder = 4
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 735
    Width = 747
    Height = 51
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      747
      51)
    object Button1: TButton
      Left = 667
      Top = 16
      Width = 60
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Post'
      ModalResult = 1
      TabOrder = 1
    end
    object Button2: TButton
      Left = 586
      Top = 16
      Width = 60
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
      OnClick = Button2Click
    end
  end
  object DataSource1: TDataSource
    DataSet = pgDM.blocksCDS
    Left = 576
    Top = 24
  end
end
