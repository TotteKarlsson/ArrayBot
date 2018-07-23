object NewSpecimenForm: TNewSpecimenForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Specimen Form'
  ClientHeight = 320
  ClientWidth = 541
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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 541
    Height = 269
    Align = alClient
    TabOrder = 0
    ExplicitLeft = -8
    ExplicitTop = -6
    ExplicitWidth = 545
    ExplicitHeight = 421
    object Label1: TLabel
      Left = 24
      Top = 16
      Width = 36
      Height = 13
      Caption = 'case_id'
      FocusControl = DBEdit1
    end
    object Label2: TLabel
      Left = 24
      Top = 56
      Width = 23
      Height = 13
      Caption = 'virus'
      FocusControl = DBEdit2
    end
    object Label3: TLabel
      Left = 24
      Top = 96
      Width = 113
      Height = 13
      Caption = 'brain_region_dissection'
      FocusControl = DBEdit3
    end
    object Label4: TLabel
      Left = 24
      Top = 211
      Width = 57
      Height = 13
      Caption = 'Entered By:'
      FocusControl = DBEdit3
    end
    object Label5: TLabel
      Left = 24
      Top = 149
      Width = 90
      Height = 13
      Caption = 'Cultured Timepoint'
      FocusControl = DBEdit3
    end
    object DBEdit1: TDBEdit
      Left = 24
      Top = 29
      Width = 200
      Height = 21
      DataField = 'case_id'
      DataSource = DataSource1
      TabOrder = 0
    end
    object DBEdit2: TDBEdit
      Left = 24
      Top = 69
      Width = 200
      Height = 21
      DataField = 'virus'
      DataSource = DataSource1
      TabOrder = 1
    end
    object DBEdit3: TDBEdit
      Left = 24
      Top = 109
      Width = 200
      Height = 21
      DataField = 'brain_region_dissection'
      DataSource = DataSource1
      TabOrder = 2
    end
    object DBLookupComboBox1: TDBLookupComboBox
      Left = 24
      Top = 230
      Width = 200
      Height = 21
      DataField = 'LEnteredBy'
      DataSource = DataSource1
      TabOrder = 3
    end
    object DBLookupComboBox2: TDBLookupComboBox
      Left = 24
      Top = 168
      Width = 200
      Height = 21
      DataField = 'LCulturedTP'
      DataSource = DataSource1
      TabOrder = 4
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 269
    Width = 541
    Height = 51
    Align = alBottom
    TabOrder = 1
    ExplicitTop = 421
    ExplicitWidth = 548
    DesignSize = (
      541
      51)
    object Button1: TButton
      Left = 461
      Top = 16
      Width = 60
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Post'
      ModalResult = 1
      TabOrder = 1
      ExplicitLeft = 468
    end
    object CancelBtn: TButton
      Left = 380
      Top = 16
      Width = 60
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
      ExplicitLeft = 387
    end
  end
  object DataSource1: TDataSource
    DataSet = pgDM.specimenCDS
    Left = 344
    Top = 160
  end
end
