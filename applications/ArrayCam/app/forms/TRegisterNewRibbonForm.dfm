object RegisterNewRibbonForm: TRegisterNewRibbonForm
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'Register New Ribbon'
  ClientHeight = 823
  ClientWidth = 943
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 19
  object GroupBox2: TGroupBox
    Left = 0
    Top = 0
    Width = 943
    Height = 743
    Align = alClient
    Caption = 'Coverslip, Block and Ribbon Details'
    TabOrder = 0
    object GroupBox5: TGroupBox
      Left = 2
      Top = 448
      Width = 939
      Height = 293
      Align = alBottom
      Caption = 'Ribbon Note'
      TabOrder = 0
      object Panel3: TPanel
        Left = 2
        Top = 21
        Width = 935
        Height = 270
        Align = alClient
        TabOrder = 0
        object mRibbonNoteMemo: TMemo
          Left = 1
          Top = 1
          Width = 933
          Height = 268
          Align = alClient
          TabOrder = 0
        end
      end
    end
    object GroupBox4: TGroupBox
      Left = 2
      Top = 115
      Width = 939
      Height = 94
      Align = alTop
      Caption = 'Block Info'
      TabOrder = 1
      object DBText3: TDBText
        Left = 160
        Top = 32
        Width = 65
        Height = 17
        DataField = 'slice_id'
        DataSource = pgDM.allBlocksDataSource
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object DBText5: TDBText
        Left = 160
        Top = 58
        Width = 152
        Height = 17
        DataField = 'label'
        DataSource = pgDM.allBlocksDataSource
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label5: TLabel
        Left = 24
        Top = 30
        Width = 60
        Height = 19
        Caption = 'Slice ID:'
      end
      object Label6: TLabel
        Left = 247
        Top = 32
        Width = 87
        Height = 19
        Caption = 'Block Serial:'
      end
      object Label7: TLabel
        Left = 24
        Top = 58
        Width = 85
        Height = 19
        Caption = 'Block Label:'
      end
      object DBText4: TDBText
        Left = 356
        Top = 32
        Width = 97
        Height = 17
        DataField = 'serial'
        DataSource = pgDM.allBlocksDataSource
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
    end
    object GroupBox6: TGroupBox
      Left = 2
      Top = 21
      Width = 939
      Height = 94
      Align = alTop
      Caption = 'Misc'
      TabOrder = 2
      object DBText2: TDBText
        Left = 160
        Top = 28
        Width = 65
        Height = 17
        DataField = 'user_name'
        DataSource = pgDM.usersDataSource
      end
      object Label1: TLabel
        Left = 24
        Top = 59
        Width = 93
        Height = 19
        Caption = 'Coverslip ID:'
      end
      object Label3: TLabel
        Left = 24
        Top = 31
        Width = 38
        Height = 19
        Caption = 'User:'
      end
      object mCSBarcode: TLabel
        Left = 160
        Top = 59
        Width = 64
        Height = 19
        Caption = 'C000123'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object DBText6: TDBText
        Left = 470
        Top = 59
        Width = 201
        Height = 17
        DataField = 'statusL'
        DataSource = csPGDM.ROnCoverSlipsSource
      end
      object Label8: TLabel
        Left = 357
        Top = 59
        Width = 107
        Height = 19
        Caption = 'Current Status:'
      end
    end
    object GroupBox7: TGroupBox
      Left = 2
      Top = 209
      Width = 939
      Height = 239
      Align = alClient
      Caption = 'Ribbon Info'
      TabOrder = 3
      object Label2: TLabel
        Left = 24
        Top = 36
        Width = 139
        Height = 19
        Caption = 'Number of Sections'
      end
      object Label4: TLabel
        Left = 24
        Top = 135
        Width = 97
        Height = 19
        Caption = 'Cutting Order'
      end
      object mNrOfSectionsDBLbl: TDBText
        Left = 232
        Top = 71
        Width = 152
        Height = 36
        DataField = 'nr_of_sections'
        DataSource = pgDM.ribbonsDSource
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object mCuttingOrderDBLbl: TDBText
        Left = 232
        Top = 174
        Width = 152
        Height = 36
        DataField = 'cutting_order'
        DataSource = pgDM.ribbonsDSource
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object RibbonID: TDBText
        Left = 293
        Top = 25
        Width = 236
        Height = 17
        DataField = 'id'
        DataSource = pgDM.ribbonsDSource
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object mDecrementCuttingOrderBtn: TArrayBotButton
        Left = 24
        Top = 162
        Width = 75
        Height = 50
        Caption = '-'
        TabOrder = 0
        OnClick = miscBtnClick
        SoundID = 'BUTTON_CLICK_4'
      end
      object mDecrementSectionBtn: TArrayBotButton
        Left = 24
        Top = 61
        Width = 75
        Height = 50
        Caption = '-'
        TabOrder = 1
        OnClick = miscBtnClick
        SoundID = 'BUTTON_CLICK_4'
      end
      object mIncrementCuttingOrderBtn: TArrayBotButton
        Left = 127
        Top = 162
        Width = 75
        Height = 50
        Caption = '+'
        TabOrder = 2
        OnClick = miscBtnClick
        SoundID = 'BUTTON_CLICK_4'
      end
      object mIncrementSectionBtn: TArrayBotButton
        Left = 127
        Top = 61
        Width = 75
        Height = 50
        Caption = '+'
        TabOrder = 3
        OnClick = miscBtnClick
        SoundID = 'BUTTON_CLICK_4'
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 743
    Width = 943
    Height = 80
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      943
      80)
    object mCancelBtn: TArrayBotButton
      Left = 677
      Top = 10
      Width = 110
      Height = 57
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
      OnClick = mOkCancelBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
    object mRegisterBtn: TArrayBotButton
      Left = 813
      Top = 10
      Width = 110
      Height = 57
      Anchors = [akTop, akRight]
      Caption = 'Register'
      ModalResult = 1
      TabOrder = 1
      OnClick = mOkCancelBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
  end
end
