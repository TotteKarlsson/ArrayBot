object NewCaseForm: TNewCaseForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'New Case Form'
  ClientHeight = 319
  ClientWidth = 384
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
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 384
    Height = 268
    Align = alClient
    TabOrder = 0
    object Label2: TLabel
      Left = 24
      Top = 24
      Width = 44
      Height = 13
      Caption = 'animal_id'
      FocusControl = DBEdit2
    end
    object Label3: TLabel
      Left = 24
      Top = 64
      Width = 57
      Height = 13
      Caption = 'intake_date'
      FocusControl = DBEdit3
    end
    object Label4: TLabel
      Left = 24
      Top = 104
      Width = 30
      Height = 13
      Caption = 'specie'
    end
    object DBEdit2: TDBEdit
      Left = 24
      Top = 40
      Width = 250
      Height = 21
      DataField = 'animal_id'
      DataSource = DataSource1
      TabOrder = 0
    end
    object DBEdit3: TDBEdit
      Left = 24
      Top = 80
      Width = 250
      Height = 21
      DataField = 'intake_date'
      DataSource = DataSource1
      TabOrder = 1
    end
    object UserCB: TDBLookupComboBox
      Left = 24
      Top = 168
      Width = 250
      Height = 21
      DataField = 'LUser'
      DataSource = DataSource1
      TabOrder = 2
    end
    object DBLookupComboBox1: TDBLookupComboBox
      Left = 24
      Top = 123
      Width = 250
      Height = 21
      DataField = 'LSpecie'
      DataSource = DataSource1
      TabOrder = 3
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 268
    Width = 384
    Height = 51
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      384
      51)
    object Button1: TButton
      Left = 304
      Top = 16
      Width = 60
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Post'
      ModalResult = 1
      TabOrder = 1
    end
    object CancelBtn: TButton
      Left = 223
      Top = 16
      Width = 60
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
    end
  end
  object DataSource1: TDataSource
    DataSet = pgDM.casesCDS
    Left = 312
    Top = 80
  end
end
