object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'atDB'
  ClientHeight = 997
  ClientWidth = 1666
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object TopPanel: TPanel
    Left = 0
    Top = 49
    Width = 1666
    Height = 929
    Align = alClient
    TabOrder = 0
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 1664
      Height = 927
      ActivePage = TabSheet4
      Align = alClient
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      object TabSheet4: TTabSheet
        Caption = 'Tissue to Block'
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object PageControl2: TPageControl
          Left = 0
          Top = 0
          Width = 1656
          Height = 899
          ActivePage = TabSheet8
          Align = alClient
          TabOrder = 0
          OnChange = PageControl2Change
          object TabSheet8: TTabSheet
            Caption = 'Specimen, Slices && Blocks'
            ExplicitLeft = 0
            ExplicitTop = 0
            ExplicitWidth = 0
            ExplicitHeight = 0
            object GroupBox4: TGroupBox
              Left = 0
              Top = 177
              Width = 1648
              Height = 208
              Align = alTop
              Caption = 'Slices'
              TabOrder = 0
              object SlicesGrid: TDBGrid
                Left = 2
                Top = 15
                Width = 1644
                Height = 166
                Align = alClient
                DataSource = pgDM.slicesDataSource
                Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
                TabOrder = 0
                TitleFont.Charset = DEFAULT_CHARSET
                TitleFont.Color = clWindowText
                TitleFont.Height = -11
                TitleFont.Name = 'Tahoma'
                TitleFont.Style = []
                OnDrawDataCell = SlicesGridDrawDataCell
                OnDrawColumnCell = SlicesGridDrawColumnCell
                OnDblClick = DBGridDblClick
                OnMouseDown = SlicesGridMouseDown
                OnMouseMove = SlicesGridMouseMove
                OnMouseUp = SlicesGridMouseUp
                OnTitleClick = SlicesGridTitleClick
                Columns = <
                  item
                    Expanded = False
                    FieldName = 'id'
                    Title.Caption = 'Slice ID'
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'specimen_id'
                    Width = 74
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'virus'
                    Title.Caption = 'Fluorescence (Virus/Genotype)'
                    Width = 161
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'virus_dilution'
                    Title.Caption = 'Dilution'
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'brain_region_dissection'
                    Width = 120
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'culture_timeL'
                    Width = 120
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'preprocess_treatment_protocolL'
                    Width = 120
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'fixative_protocolL'
                    Width = 120
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'fixation_protocolL'
                    Width = 120
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'postfix_protocolL'
                    Width = 120
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'entered_byL'
                    Width = 120
                    Visible = True
                  end>
              end
              object SlicesNavigator: TDBNavigator
                Left = 2
                Top = 181
                Width = 1644
                Height = 25
                DataSource = pgDM.slicesDataSource
                VisibleButtons = [nbInsert, nbDelete, nbRefresh, nbApplyUpdates, nbCancelUpdates]
                Align = alBottom
                TabOrder = 1
                OnClick = NavigatorClick
              end
            end
            object SpecimenGB: TGroupBox
              Left = 0
              Top = 0
              Width = 1648
              Height = 177
              Align = alTop
              Caption = 'Specimen'
              TabOrder = 1
              object SpecimenNavigator: TDBNavigator
                Left = 2
                Top = 150
                Width = 1644
                Height = 25
                DataSource = SpecimenDS
                VisibleButtons = [nbInsert, nbDelete, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
                Align = alBottom
                TabOrder = 0
                BeforeAction = NavigatorBeforeAction
                OnClick = NavigatorClick
              end
              object SpecimenGrid: TDBGrid
                Left = 2
                Top = 15
                Width = 1644
                Height = 135
                Align = alClient
                DataSource = SpecimenDS
                Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
                TabOrder = 1
                TitleFont.Charset = DEFAULT_CHARSET
                TitleFont.Color = clWindowText
                TitleFont.Height = -11
                TitleFont.Name = 'Tahoma'
                TitleFont.Style = []
                OnDblClick = DBGridDblClick
                Columns = <
                  item
                    Expanded = False
                    FieldName = 'id'
                    Title.Caption = 'Specimen ID'
                    Width = 79
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'animal_id'
                    Title.Caption = 'Animal ID'
                    Width = 117
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'intake_date'
                    Title.Caption = 'Intake Date'
                    Width = 148
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'LSpecie'
                    Width = 171
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'summary'
                    Title.Caption = 'Summary'
                    Width = 185
                    Visible = True
                  end
                  item
                    Expanded = False
                    FieldName = 'LUser'
                    Width = 86
                    Visible = True
                  end>
              end
            end
            object mBlocksGB: TGroupBox
              Left = 0
              Top = 385
              Width = 1648
              Height = 486
              Align = alClient
              Caption = 'Blocks'
              TabOrder = 2
              object BlockNotesGB: TGroupBox
                Left = 2
                Top = 287
                Width = 1644
                Height = 197
                Align = alBottom
                Caption = 'Notes'
                Padding.Left = 5
                Padding.Top = 5
                Padding.Right = 5
                Padding.Bottom = 5
                TabOrder = 0
                object Panel3: TPanel
                  Left = 206
                  Top = 20
                  Width = 1431
                  Height = 170
                  Align = alClient
                  TabOrder = 0
                  object mBlockNoteMemo: TDBMemo
                    Left = 1
                    Top = 1
                    Width = 1429
                    Height = 143
                    Align = alClient
                    DataField = 'note'
                    DataSource = pgDM.blockNotesDSource
                    TabOrder = 0
                  end
                  object BlockNoteNavigator: TDBNavigator
                    Left = 1
                    Top = 144
                    Width = 1429
                    Height = 25
                    DataSource = pgDM.blockNotesDSource
                    VisibleButtons = [nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
                    Align = alBottom
                    TabOrder = 1
                    OnClick = NavigatorClick
                  end
                end
                object Panel4: TPanel
                  Left = 7
                  Top = 20
                  Width = 199
                  Height = 170
                  Align = alLeft
                  BevelOuter = bvNone
                  TabOrder = 1
                  object BlockNotesNavigator: TDBNavigator
                    Left = 0
                    Top = 145
                    Width = 199
                    Height = 25
                    DataSource = pgDM.blockNotesDSource
                    VisibleButtons = [nbInsert, nbDelete, nbRefresh, nbApplyUpdates]
                    Align = alBottom
                    ConfirmDelete = False
                    TabOrder = 0
                    OnClick = NavigatorClick
                  end
                  object mBlockNotesGrid: TDBGrid
                    Left = 0
                    Top = 0
                    Width = 199
                    Height = 145
                    Align = alClient
                    DataSource = pgDM.blockNotesDSource
                    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
                    TabOrder = 1
                    TitleFont.Charset = DEFAULT_CHARSET
                    TitleFont.Color = clWindowText
                    TitleFont.Height = -11
                    TitleFont.Name = 'Tahoma'
                    TitleFont.Style = []
                    Columns = <
                      item
                        Expanded = False
                        FieldName = 'created_on'
                        Title.Caption = 'Date'
                        Width = 161
                        Visible = True
                      end>
                  end
                end
              end
              object Panel2: TPanel
                Left = 2
                Top = 15
                Width = 1354
                Height = 272
                Align = alClient
                BevelEdges = []
                BevelOuter = bvNone
                TabOrder = 1
                object Panel5: TPanel
                  Left = 0
                  Top = 0
                  Width = 1354
                  Height = 272
                  Align = alClient
                  TabOrder = 0
                  object BlocksGrid: TDBGrid
                    Left = 1
                    Top = 1
                    Width = 1352
                    Height = 245
                    Align = alClient
                    DataSource = pgDM.blocksDataSource
                    Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
                    TabOrder = 0
                    TitleFont.Charset = DEFAULT_CHARSET
                    TitleFont.Color = clWindowText
                    TitleFont.Height = -11
                    TitleFont.Name = 'Tahoma'
                    TitleFont.Style = []
                    OnCellClick = BlocksGridCellClick
                    OnDblClick = DBGridDblClick
                    OnKeyUp = BlocksGridKeyUp
                    Columns = <
                      item
                        Expanded = False
                        FieldName = 'id'
                        Width = 35
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'slice_id'
                        Width = 78
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'entered_on'
                        Width = 98
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'LBlockStatus'
                        Width = 86
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'serial'
                        Width = 65
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'date_embedded'
                        Width = 120
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'LCryoProtectionProtocol'
                        Width = 120
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'LFreezingProtocol'
                        Width = 120
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'LSubstitutionProtocol'
                        Width = 120
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'LInfiltrationProtocol'
                        Width = 120
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'LEmbeddingProtocol'
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'Cblock_label'
                        Width = 120
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'entered_byL'
                        Width = 120
                        Visible = True
                      end>
                  end
                  object BlocksNavigator: TDBNavigator
                    Left = 1
                    Top = 246
                    Width = 1352
                    Height = 25
                    DataSource = pgDM.blocksDataSource
                    VisibleButtons = [nbInsert, nbDelete, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
                    Align = alBottom
                    TabOrder = 1
                    BeforeAction = NavigatorBeforeAction
                    OnClick = NavigatorClick
                  end
                end
              end
              object GroupBox10: TGroupBox
                Left = 1356
                Top = 15
                Width = 290
                Height = 272
                Align = alRight
                Caption = 'Print block labels'
                TabOrder = 2
                object mLblMakerMemo: TMemo
                  Left = 2
                  Top = 15
                  Width = 144
                  Height = 255
                  Align = alLeft
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -11
                  Font.Name = 'Times New Roman'
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 0
                end
                object Button1: TButton
                  Left = 168
                  Top = 23
                  Width = 107
                  Height = 37
                  Caption = 'Print Block Info'
                  TabOrder = 1
                  OnClick = Button1Click
                end
              end
            end
          end
          object RibbonsTS: TTabSheet
            Caption = 'Ribbons'
            ImageIndex = 6
            ExplicitLeft = 0
            ExplicitTop = 0
            ExplicitWidth = 0
            ExplicitHeight = 0
            object Splitter2: TSplitter
              Left = 0
              Top = 449
              Width = 1648
              Height = 16
              Cursor = crVSplit
              Align = alTop
            end
            object GroupBox2: TGroupBox
              Left = 0
              Top = 0
              Width = 1648
              Height = 449
              Align = alTop
              Caption = 'Ribbon Data'
              TabOrder = 0
              object GroupBox1: TGroupBox
                Left = 960
                Top = 121
                Width = 686
                Height = 326
                Align = alRight
                Caption = 'Ribbon Notes'
                TabOrder = 0
                object Panel15: TPanel
                  Left = 2
                  Top = 15
                  Width = 185
                  Height = 309
                  Align = alLeft
                  TabOrder = 0
                  object mRibbonNotesGrid: TDBGrid
                    Left = 1
                    Top = 1
                    Width = 183
                    Height = 282
                    Align = alClient
                    DataSource = pgDM.ribbonNotesDSource
                    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
                    TabOrder = 0
                    TitleFont.Charset = DEFAULT_CHARSET
                    TitleFont.Color = clWindowText
                    TitleFont.Height = -11
                    TitleFont.Name = 'Tahoma'
                    TitleFont.Style = []
                    Columns = <
                      item
                        Expanded = False
                        FieldName = 'created_on'
                        Title.Caption = 'Date'
                        Width = 143
                        Visible = True
                      end>
                  end
                  object RibbonNotesNavigator: TDBNavigator
                    Left = 1
                    Top = 283
                    Width = 183
                    Height = 25
                    DataSource = pgDM.ribbonNotesDSource
                    VisibleButtons = [nbInsert, nbDelete, nbRefresh, nbApplyUpdates]
                    Align = alBottom
                    ConfirmDelete = False
                    TabOrder = 1
                    OnClick = NavigatorClick
                  end
                end
                object Panel16: TPanel
                  Left = 187
                  Top = 15
                  Width = 497
                  Height = 309
                  Align = alClient
                  TabOrder = 1
                  object mRibbonNoteMemo: TDBMemo
                    Left = 1
                    Top = 1
                    Width = 495
                    Height = 282
                    Align = alClient
                    DataField = 'note'
                    DataSource = pgDM.ribbonNotesDSource
                    TabOrder = 0
                  end
                  object RibbonNoteNavigator: TDBNavigator
                    Left = 1
                    Top = 283
                    Width = 495
                    Height = 25
                    DataSource = pgDM.ribbonNotesDSource
                    VisibleButtons = [nbPost, nbCancel]
                    Align = alBottom
                    TabOrder = 1
                    OnClick = NavigatorClick
                  end
                end
              end
              object Panel13: TPanel
                Left = 2
                Top = 121
                Width = 958
                Height = 326
                Align = alClient
                TabOrder = 1
                object mRibbonsGrid: TDBGrid
                  Left = 1
                  Top = 1
                  Width = 956
                  Height = 258
                  Align = alClient
                  DataSource = pgDM.ribbonsDSource
                  Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
                  ReadOnly = True
                  TabOrder = 0
                  TitleFont.Charset = DEFAULT_CHARSET
                  TitleFont.Color = clWindowText
                  TitleFont.Height = -11
                  TitleFont.Name = 'Tahoma'
                  TitleFont.Style = []
                  OnCellClick = mRibbonsGridCellClick
                  OnDblClick = DBGridDblClick
                  Columns = <
                    item
                      Expanded = False
                      FieldName = 'statusL'
                      Width = 100
                      Visible = True
                    end
                    item
                      Expanded = False
                      FieldName = 'nr_of_sections'
                      Width = 80
                      Visible = True
                    end
                    item
                      Expanded = False
                      FieldName = 'cutting_order'
                      Width = 81
                      Visible = True
                    end
                    item
                      Expanded = False
                      FieldName = 'coverslip_id'
                      Visible = True
                    end
                    item
                      Expanded = False
                      FieldName = 'created_byL'
                      Width = 100
                      Visible = True
                    end
                    item
                      Expanded = False
                      FieldName = 'created_on'
                      Visible = True
                    end
                    item
                      Expanded = False
                      FieldName = 'knife_id'
                      Visible = True
                    end>
                end
                object RibbonsNavigator: TDBNavigator
                  Left = 1
                  Top = 259
                  Width = 956
                  Height = 25
                  DataSource = pgDM.ribbonsDSource
                  VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast]
                  Align = alBottom
                  ConfirmDelete = False
                  TabOrder = 1
                  OnClick = NavigatorClick
                end
                object Panel17: TPanel
                  Left = 1
                  Top = 284
                  Width = 956
                  Height = 41
                  Align = alBottom
                  TabOrder = 2
                  object RibbonIDLbl: TDBText
                    Left = 110
                    Top = 6
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
                  object Label4: TLabel
                    Left = 24
                    Top = 10
                    Width = 51
                    Height = 13
                    Caption = 'Ribbon ID:'
                  end
                end
              end
              object Panel14: TPanel
                Left = 2
                Top = 15
                Width = 1644
                Height = 106
                Align = alTop
                TabOrder = 2
                object Label8: TLabel
                  Left = 25
                  Top = 51
                  Width = 34
                  Height = 13
                  Caption = 'slice_id'
                  Enabled = False
                  FocusControl = DBEdit2
                end
                object Label9: TLabel
                  Left = 184
                  Top = 5
                  Width = 31
                  Height = 13
                  Caption = 'Status'
                  Enabled = False
                  FocusControl = DBLookupComboBox2
                end
                object Label11: TLabel
                  Left = 184
                  Top = 51
                  Width = 26
                  Height = 13
                  Caption = 'Serial'
                  Enabled = False
                  FocusControl = DBEdit3
                end
                object Label12: TLabel
                  Left = 352
                  Top = 8
                  Width = 76
                  Height = 13
                  Caption = 'Date Embedded'
                  Enabled = False
                  FocusControl = DBEdit4
                end
                object Label13: TLabel
                  Left = 352
                  Top = 51
                  Width = 114
                  Height = 13
                  Caption = 'Cryoprotection Protocol'
                  Enabled = False
                  FocusControl = DBLookupComboBox3
                end
                object Label14: TLabel
                  Left = 543
                  Top = 8
                  Width = 83
                  Height = 13
                  Caption = 'Freezing Protocol'
                  Enabled = False
                  FocusControl = DBLookupComboBox4
                end
                object Label15: TLabel
                  Left = 543
                  Top = 51
                  Width = 99
                  Height = 13
                  Caption = 'Substitution Protocol'
                  Enabled = False
                  FocusControl = DBLookupComboBox5
                end
                object Label17: TLabel
                  Left = 848
                  Top = 8
                  Width = 92
                  Height = 13
                  Caption = 'Infiltration Protocol'
                  Enabled = False
                  FocusControl = DBLookupComboBox6
                end
                object Label18: TLabel
                  Left = 848
                  Top = 51
                  Width = 94
                  Height = 13
                  Caption = 'Embedding Protocol'
                  Enabled = False
                  FocusControl = DBLookupComboBox7
                end
                object Label7: TLabel
                  Left = 25
                  Top = 5
                  Width = 38
                  Height = 13
                  Caption = 'Block ID'
                end
                object DBEdit2: TDBEdit
                  Left = 25
                  Top = 67
                  Width = 134
                  Height = 21
                  DataField = 'slice_id'
                  DataSource = pgDM.allBlocksDataSource
                  Enabled = False
                  TabOrder = 0
                end
                object DBLookupComboBox2: TDBLookupComboBox
                  Left = 184
                  Top = 24
                  Width = 145
                  Height = 21
                  DataField = 'LBlockStatus'
                  DataSource = pgDM.allBlocksDataSource
                  Enabled = False
                  TabOrder = 1
                end
                object DBEdit3: TDBEdit
                  Left = 184
                  Top = 67
                  Width = 134
                  Height = 21
                  DataField = 'serial'
                  DataSource = pgDM.allBlocksDataSource
                  Enabled = False
                  TabOrder = 2
                end
                object DBEdit4: TDBEdit
                  Left = 352
                  Top = 24
                  Width = 134
                  Height = 21
                  DataField = 'date_embedded'
                  DataSource = pgDM.allBlocksDataSource
                  Enabled = False
                  TabOrder = 3
                end
                object DBLookupComboBox3: TDBLookupComboBox
                  Left = 352
                  Top = 67
                  Width = 161
                  Height = 21
                  DataField = 'LCryoProtectionProtocol'
                  DataSource = pgDM.allBlocksDataSource
                  Enabled = False
                  TabOrder = 4
                end
                object DBLookupComboBox4: TDBLookupComboBox
                  Left = 543
                  Top = 24
                  Width = 274
                  Height = 21
                  DataField = 'LFreezingProtocol'
                  DataSource = pgDM.allBlocksDataSource
                  Enabled = False
                  TabOrder = 5
                end
                object DBLookupComboBox5: TDBLookupComboBox
                  Left = 543
                  Top = 67
                  Width = 274
                  Height = 21
                  DataField = 'LSubstitutionProtocol'
                  DataSource = pgDM.allBlocksDataSource
                  Enabled = False
                  TabOrder = 6
                end
                object DBLookupComboBox6: TDBLookupComboBox
                  Left = 848
                  Top = 24
                  Width = 274
                  Height = 21
                  DataField = 'LInfiltrationProtocol'
                  DataSource = pgDM.allBlocksDataSource
                  Enabled = False
                  TabOrder = 7
                end
                object DBLookupComboBox7: TDBLookupComboBox
                  Left = 848
                  Top = 67
                  Width = 274
                  Height = 21
                  DataField = 'LEmbeddingProtocol'
                  DataSource = pgDM.allBlocksDataSource
                  Enabled = False
                  TabOrder = 8
                end
                object BlockIDCB: TDBLookupComboBox
                  Left = 24
                  Top = 24
                  Width = 135
                  Height = 21
                  DropDownRows = 15
                  KeyField = 'id'
                  ListField = 'id'
                  ListSource = pgDM.allBlocksDataSource
                  TabOrder = 9
                  OnCloseUp = BlockIDCBCloseUp
                end
                object CoverslipIDE: TSTDStringLabeledEdit
                  Left = 1146
                  Top = 24
                  Width = 159
                  Height = 33
                  EditLabel.Width = 58
                  EditLabel.Height = 13
                  EditLabel.Caption = 'Coverslip ID'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -21
                  Font.Name = 'Tahoma'
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 10
                  Text = 'C00003556'
                  OnKeyDown = CoverslipIDEKeyDown
                  Value = 'C00003556'
                end
              end
            end
            inline MoviesFrame1: TMoviesFrame
              AlignWithMargins = True
              Left = 3
              Top = 468
              Width = 1642
              Height = 400
              Align = alClient
              TabOrder = 1
              ExplicitLeft = 3
              ExplicitTop = 468
              ExplicitWidth = 1642
              ExplicitHeight = 400
              inherited Panel22: TPanel
                Top = 345
                Width = 1642
                ExplicitTop = 345
                ExplicitWidth = 1642
              end
              inherited ScrollBox2: TScrollBox
                Width = 1642
                Height = 345
                ExplicitWidth = 1642
                ExplicitHeight = 345
                inherited FlowPanel1: TFlowPanel
                  Width = 1621
                  ExplicitWidth = 1621
                end
              end
            end
          end
        end
      end
      object TabSheet9: TTabSheet
        Caption = 'Coverslips'
        ImageIndex = 5
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object Splitter4: TSplitter
          Left = 369
          Top = 0
          Height = 899
          ExplicitLeft = 8
          ExplicitTop = 24
          ExplicitHeight = 100
        end
        object Panel7: TPanel
          Left = 0
          Top = 0
          Width = 369
          Height = 899
          Align = alLeft
          TabOrder = 0
          object Splitter7: TSplitter
            Left = 1
            Top = 201
            Width = 367
            Height = 4
            Cursor = crVSplit
            Align = alTop
            ExplicitTop = 192
          end
          object GroupBox8: TGroupBox
            Left = 1
            Top = 205
            Width = 367
            Height = 661
            Align = alClient
            Caption = 'Cover Slips'
            TabOrder = 0
            object CSNavigator: TDBNavigator
              Left = 2
              Top = 518
              Width = 363
              Height = 25
              VisibleButtons = [nbPrior, nbNext, nbDelete, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
              Align = alBottom
              TabOrder = 0
              OnClick = NavigatorClick
            end
            object CoverSlipsGrid: TDBGrid
              Left = 2
              Top = 15
              Width = 363
              Height = 503
              Align = alClient
              Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
              PopupMenu = CoverSlipPopup
              TabOrder = 1
              TitleFont.Charset = DEFAULT_CHARSET
              TitleFont.Color = clWindowText
              TitleFont.Height = -11
              TitleFont.Name = 'Tahoma'
              TitleFont.Style = []
              OnCellClick = CoverSlipsGridCellClick
              OnKeyUp = CoverSlipsGridKeyUp
              Columns = <
                item
                  Expanded = False
                  FieldName = 'id'
                  Visible = True
                end
                item
                  Expanded = False
                  FieldName = 'LStatus'
                  Visible = True
                end
                item
                  Expanded = False
                  FieldName = 'LType'
                  Visible = True
                end>
            end
            object CSgridPanel: TPanel
              Left = 2
              Top = 543
              Width = 363
              Height = 116
              Align = alBottom
              BevelOuter = bvNone
              TabOrder = 2
              object mNrOfSelectedCS: TIntLabel
                Left = 319
                Top = 16
                Width = 10
                Height = 13
                Caption = '-1'
                Value = -1
                TheFont.Charset = DEFAULT_CHARSET
                TheFont.Color = clWindowText
                TheFont.Height = -11
                TheFont.Name = 'Tahoma'
                TheFont.Style = []
              end
              object Label6: TLabel
                Left = 231
                Top = 16
                Width = 82
                Height = 13
                Caption = 'Selection Count: '
              end
              object mRegisterCarbonCoatBatchBtn: TButton
                Left = 79
                Top = 75
                Width = 152
                Height = 25
                Caption = 'Register Carbon Coat Batch'
                TabOrder = 0
                OnClick = mRegisterCarbonCoatBatchBtnClick
              end
              object RegisterPostSilanizationBatch: TButton
                Left = 47
                Top = 44
                Width = 132
                Height = 25
                Caption = 'Register Silanized Batch'
                TabOrder = 1
                OnClick = mRegisterCleanRoundBtnClick
              end
              object mRegisterCleanRoundBtn: TButton
                Left = 15
                Top = 13
                Width = 132
                Height = 25
                Caption = 'Register Clean Batch'
                Enabled = False
                TabOrder = 2
                OnClick = mRegisterCleanRoundBtnClick
              end
            end
          end
          object Panel9: TPanel
            Left = 1
            Top = 866
            Width = 367
            Height = 32
            Align = alBottom
            TabOrder = 1
            object mPrintCSLabelsBtn: TButton
              Left = 201
              Top = 4
              Width = 152
              Height = 25
              Caption = 'Print Labels for Selected'
              TabOrder = 0
              OnClick = FormBtnClick
            end
            object mAddCSNote: TButton
              Left = 4
              Top = 4
              Width = 145
              Height = 25
              Caption = 'Add Note to Multiple'
              TabOrder = 1
              OnClick = FormBtnClick
            end
          end
          object BatchesGB: TGroupBox
            Left = 1
            Top = 1
            Width = 367
            Height = 200
            Align = alTop
            Caption = 'Coverslip Batches'
            TabOrder = 2
            object FreshBatchesGrid: TDBGrid
              Left = 2
              Top = 56
              Width = 363
              Height = 117
              Align = alClient
              Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
              TabOrder = 0
              TitleFont.Charset = DEFAULT_CHARSET
              TitleFont.Color = clWindowText
              TitleFont.Height = -11
              TitleFont.Name = 'Tahoma'
              TitleFont.Style = []
              OnCellClick = FreshBatchesGridCellClick
              OnKeyUp = FreshBatchesGridKeyUp
              Columns = <
                item
                  Expanded = False
                  FieldName = 'date_created'
                  Width = 139
                  Visible = True
                end
                item
                  Expanded = False
                  FieldName = 'count'
                  Width = 50
                  Visible = True
                end
                item
                  Expanded = False
                  FieldName = 'lot_number'
                  Width = 68
                  Visible = True
                end>
            end
            object CSFreshBatchNavigator: TDBNavigator
              Left = 2
              Top = 173
              Width = 363
              Height = 25
              VisibleButtons = [nbPrior, nbNext, nbDelete, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
              Align = alBottom
              TabOrder = 1
              BeforeAction = NavigatorBeforeAction
              OnClick = NavigatorClick
            end
            object Panel12: TPanel
              Left = 2
              Top = 15
              Width = 363
              Height = 41
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 2
              object mRegisterFreshBatchBtn: TButton
                Left = 15
                Top = 10
                Width = 132
                Height = 25
                Caption = 'Register New Batch'
                TabOrder = 0
                OnClick = mRegisterFreshBatchBtnClick
              end
              object mPrintBatchLblBtn: TButton
                Left = 226
                Top = 7
                Width = 125
                Height = 25
                Caption = 'Print Box Label'
                TabOrder = 1
                OnClick = mPrintBatchLblBtnClick
              end
            end
          end
        end
        object Panel8: TPanel
          Left = 372
          Top = 0
          Width = 1284
          Height = 899
          Align = alClient
          TabOrder = 1
          object PageControl3: TPageControl
            Left = 1
            Top = 1
            Width = 1282
            Height = 897
            ActivePage = TabSheet11
            Align = alClient
            TabOrder = 0
            object TabSheet11: TTabSheet
              Caption = 'Coverslip Info'
              ExplicitLeft = 0
              ExplicitTop = 0
              ExplicitWidth = 0
              ExplicitHeight = 0
              object GroupBox12: TGroupBox
                Left = 0
                Top = 529
                Width = 1274
                Height = 340
                Align = alClient
                Caption = 'Coverslip notes'
                TabOrder = 0
                object DBMemo1: TDBMemo
                  Left = 2
                  Top = 15
                  Width = 1270
                  Height = 323
                  Align = alClient
                  DataField = 'notes'
                  ScrollBars = ssBoth
                  TabOrder = 0
                end
              end
              object Panel18: TPanel
                Left = 0
                Top = 0
                Width = 1274
                Height = 529
                Align = alTop
                TabOrder = 1
                object GroupBox11: TGroupBox
                  Left = 1
                  Top = 1
                  Width = 280
                  Height = 527
                  Align = alLeft
                  Caption = 'Identification'
                  TabOrder = 0
                  object Label10: TLabel
                    Left = 16
                    Top = 64
                    Width = 31
                    Height = 13
                    Caption = 'Status'
                    FocusControl = DBLookupComboBox1
                  end
                  object Label16: TLabel
                    Left = 191
                    Top = 64
                    Width = 46
                    Height = 13
                    Caption = 'From LOT'
                    FocusControl = DBEdit7
                  end
                  object CSID: TDBText
                    Left = 16
                    Top = 32
                    Width = 65
                    Height = 17
                    DataField = 'id'
                    Font.Charset = DEFAULT_CHARSET
                    Font.Color = clWindowText
                    Font.Height = -16
                    Font.Name = 'Tahoma'
                    Font.Style = []
                    ParentFont = False
                  end
                  object DBLookupComboBox1: TDBLookupComboBox
                    Left = 16
                    Top = 80
                    Width = 169
                    Height = 21
                    DataField = 'LStatus'
                    TabOrder = 0
                  end
                  object DBEdit7: TDBEdit
                    Left = 191
                    Top = 80
                    Width = 74
                    Height = 21
                    DataField = 'from_lot'
                    Enabled = False
                    ReadOnly = True
                    TabOrder = 1
                  end
                end
                object GroupBox18: TGroupBox
                  Left = 281
                  Top = 1
                  Width = 992
                  Height = 527
                  Align = alClient
                  Caption = 'Ribbon(s)'
                  TabOrder = 1
                  object Label5: TLabel
                    Left = 528
                    Top = 304
                    Width = 60
                    Height = 13
                    Caption = 'created_byL'
                  end
                  object DBGrid1: TDBGrid
                    Left = 2
                    Top = 15
                    Width = 988
                    Height = 485
                    Align = alClient
                    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
                    TabOrder = 0
                    TitleFont.Charset = DEFAULT_CHARSET
                    TitleFont.Color = clWindowText
                    TitleFont.Height = -11
                    TitleFont.Name = 'Tahoma'
                    TitleFont.Style = []
                    Columns = <
                      item
                        Expanded = False
                        FieldName = 'statusL'
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'block_id'
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'cutting_order'
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'nr_of_sections'
                        Width = 98
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'created_on'
                        Visible = True
                      end
                      item
                        Expanded = False
                        FieldName = 'created_byL'
                        Visible = True
                      end>
                  end
                  object DBNavigator1: TDBNavigator
                    Left = 2
                    Top = 500
                    Width = 988
                    Height = 25
                    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbDelete, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
                    Align = alBottom
                    TabOrder = 1
                  end
                end
              end
            end
          end
        end
      end
      object TabSheet10: TTabSheet
        Caption = 'Media'
        ImageIndex = 6
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object MediaPageControl: TPageControl
          Left = 73
          Top = 0
          Width = 1583
          Height = 899
          ActivePage = TabSheet1
          Align = alClient
          TabOrder = 0
          OnChange = MediaPageControlChange
          object TabSheet1: TTabSheet
            Caption = 'Movies'
            ImageIndex = 1
            inline TMoviesFrame1: TMoviesFrame
              Left = 0
              Top = 0
              Width = 1575
              Height = 871
              Align = alClient
              TabOrder = 0
              ExplicitWidth = 1575
              ExplicitHeight = 871
              inherited Panel22: TPanel
                Top = 816
                Width = 1575
                ExplicitTop = 816
                ExplicitWidth = 1575
              end
              inherited ScrollBox2: TScrollBox
                Width = 1575
                Height = 816
                ExplicitWidth = 1575
                ExplicitHeight = 816
                inherited FlowPanel1: TFlowPanel
                  Width = 1571
                  ExplicitWidth = 1571
                end
              end
            end
          end
          object TabSheet14: TTabSheet
            Caption = 'Images'
            ImageIndex = 2
            inline TImagesFrame1: TImagesFrame
              Left = 0
              Top = 0
              Width = 1575
              Height = 871
              Align = alClient
              TabOrder = 0
              ExplicitWidth = 1575
              ExplicitHeight = 871
              inherited Panel22: TPanel
                Top = 816
                Width = 1575
                ExplicitTop = 816
                ExplicitWidth = 1575
              end
              inherited ScrollBox2: TScrollBox
                Width = 1575
                Height = 816
                ExplicitWidth = 1575
                ExplicitHeight = 816
                inherited FlowPanel1: TFlowPanel
                  Width = 1571
                  ExplicitWidth = 1571
                end
              end
            end
          end
        end
        object GroupBox16: TGroupBox
          Left = 0
          Top = 0
          Width = 73
          Height = 899
          Align = alLeft
          Caption = 'Block IDs'
          Color = clBtnFace
          ParentColor = False
          TabOrder = 1
          object BlockIDSLLB: TDBLookupListBox
            Left = 2
            Top = 15
            Width = 69
            Height = 875
            Align = alClient
            KeyField = 'id'
            ListField = 'id'
            ListSource = pgDM.blockIDsDataSource
            TabOrder = 0
            OnKeyDown = BlockIDSLLBKeyDown
            OnKeyUp = BlockIDSLLBKeyUp
            OnMouseUp = BlockIDSLLBMouseUp
          end
        end
      end
      object TabSheet12: TTabSheet
        Caption = 'Knifes'
        ImageIndex = 6
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object GroupBox6: TGroupBox
          Left = 289
          Top = 0
          Width = 1367
          Height = 899
          Align = alClient
          Caption = 'Note'
          Padding.Left = 5
          Padding.Top = 5
          Padding.Right = 5
          Padding.Bottom = 5
          TabOrder = 0
          object Panel11: TPanel
            Left = 7
            Top = 20
            Width = 1353
            Height = 872
            Align = alClient
            TabOrder = 0
            object DBMemo2: TDBMemo
              Left = 1
              Top = 1
              Width = 1351
              Height = 845
              Align = alClient
              DataField = 'note'
              DataSource = pgDM.knifeNotesDataSource
              TabOrder = 0
            end
            object KnifeNoteNavigator: TDBNavigator
              Left = 1
              Top = 846
              Width = 1351
              Height = 25
              DataSource = pgDM.knifeNotesDataSource
              VisibleButtons = [nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
              Align = alBottom
              TabOrder = 1
              OnClick = NavigatorClick
            end
          end
        end
        object Panel22: TPanel
          Left = 0
          Top = 0
          Width = 289
          Height = 899
          Align = alLeft
          TabOrder = 1
          object GroupBox3: TGroupBox
            Left = 1
            Top = 1
            Width = 287
            Height = 161
            Align = alTop
            Caption = 'Knifes'
            TabOrder = 0
            object DBGrid2: TDBGrid
              Left = 2
              Top = 15
              Width = 283
              Height = 119
              Align = alClient
              DataSource = pgDM.knifesDSource
              Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
              ReadOnly = True
              TabOrder = 0
              TitleFont.Charset = DEFAULT_CHARSET
              TitleFont.Color = clWindowText
              TitleFont.Height = -11
              TitleFont.Name = 'Tahoma'
              TitleFont.Style = []
              Columns = <
                item
                  Expanded = False
                  FieldName = 'id'
                  Width = 45
                  Visible = True
                end
                item
                  Expanded = False
                  FieldName = 'date_entered'
                  Visible = True
                end>
            end
            object DBNavigator2: TDBNavigator
              Left = 2
              Top = 134
              Width = 283
              Height = 25
              DataSource = pgDM.knifesDSource
              VisibleButtons = [nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
              Align = alBottom
              TabOrder = 1
            end
          end
          object GroupBox7: TGroupBox
            Left = 1
            Top = 162
            Width = 287
            Height = 736
            Align = alClient
            Caption = 'Notes'
            TabOrder = 1
            object DBGrid3: TDBGrid
              Left = 2
              Top = 15
              Width = 283
              Height = 694
              Align = alClient
              DataSource = pgDM.knifeNotesDataSource
              Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
              TabOrder = 0
              TitleFont.Charset = DEFAULT_CHARSET
              TitleFont.Color = clWindowText
              TitleFont.Height = -11
              TitleFont.Name = 'Tahoma'
              TitleFont.Style = []
              Columns = <
                item
                  Expanded = False
                  FieldName = 'Lcreated_by'
                  Width = 67
                  Visible = True
                end
                item
                  Expanded = False
                  FieldName = 'created_on'
                  Visible = True
                end>
            end
            object KnifeNotesNavigator: TDBNavigator
              Left = 2
              Top = 709
              Width = 283
              Height = 25
              DataSource = pgDM.knifeNotesDataSource
              VisibleButtons = [nbInsert, nbDelete, nbRefresh, nbApplyUpdates]
              Align = alBottom
              ConfirmDelete = False
              TabOrder = 1
              OnClick = NavigatorClick
            end
          end
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'All Tables'
        ImageIndex = 4
        object mTablesLB: TListBox
          Left = 0
          Top = 0
          Width = 153
          Height = 899
          Align = alLeft
          ItemHeight = 13
          TabOrder = 0
          OnClick = mTablesLBClick
        end
        object Panel6: TPanel
          Left = 153
          Top = 0
          Width = 1503
          Height = 899
          Align = alClient
          Caption = 'Panel6'
          TabOrder = 1
          inline TTableFrame1: TTableFrame
            Left = 1
            Top = 65
            Width = 1501
            Height = 833
            Align = alClient
            TabOrder = 0
            ExplicitLeft = 1
            ExplicitTop = 65
            ExplicitWidth = 1501
            ExplicitHeight = 833
            inherited GroupBox1: TGroupBox
              Width = 1501
              Height = 833
              Align = alClient
              ExplicitWidth = 1501
              ExplicitHeight = 833
              inherited DBGrid1: TDBGrid
                Top = 15
                Width = 1497
                Height = 774
                Align = alClient
              end
              inherited DBNavigator1: TDBNavigator
                Top = 789
                Width = 1497
                Hints.Strings = ()
                ExplicitTop = 789
                ExplicitWidth = 1497
              end
            end
            inherited DataSource1: TDataSource
              Left = 672
              Top = 280
            end
            inherited ClientDataSet1: TClientDataSet
              Left = 568
              Top = 288
            end
            inherited DataSetProvider1: TDataSetProvider
              Left = 456
              Top = 288
            end
            inherited SQLDataSet1: TSQLDataSet
              Left = 520
              Top = 112
            end
            inherited LockoutCheckTimer: TTimer
              Left = 256
              Top = 216
            end
          end
          object Panel19: TPanel
            Left = 1
            Top = 1
            Width = 1501
            Height = 64
            Align = alTop
            TabOrder = 1
            object UnlocktablesBtn: TBitBtn
              Left = 5
              Top = 11
              Width = 84
              Height = 38
              Caption = 'Unlock'
              Glyph.Data = {
                F6060000424DF606000000000000360000002800000018000000180000000100
                180000000000C0060000C30E0000C30E00000000000000000000C6D4DDABB5C3
                B3BBC7DDDDDEFEFEFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFF98D0EB308CDE2874D85688C3D9DADCFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFF85AEDB42A2E32F88D91D77DDA7BACDFEFEFEFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF64BDE9307CCB45A9E440AEE37699
                BB9EB6C8DCDDDEFEFEFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDEEDF44DAAE9
                2974C749B2E549AEE5399BEC79ABC8F3F3F3FFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFDEECF452B3EE3082CA54B7E95BB4E3509ACE90B0C4DBDBDCFEFEFE
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE1EFF461C7F13A8ACE6BC5EB6BBBE136
                A2EA6BA7C9DBDCDDFEFEFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDFEDF468C6
                F24792CD69C4EA46A3DE3AA1EB72AAC9DBDBDCFEFEFEFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFE2EEF49BE5F44B95CD53BBEB4CA8DD3CA0E86DA8C8D7D8D9FEFE
                FEFEFEFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE6F1F58CDCF33D8ECE58C0ED4CA2D8
                379CE467A9C7BBC5C9C2C9CBEEEEEFD5D9DDC2C8CECBCFD3E5E5E6F9F9F9FFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE2EEF46C
                D1F43C8DCB57BFEC52A6D5308BCB56C6F166CCEB4875B22765BC2B85DF359AE5
                489CD27E9FBAD8D9DAFDFDFDFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFE4F0F567CAF32880C64FBBEB61D1FA5BD4FF59D4FF55C3F545
                B2F361D1FC50C4FA41AFF6369AF34B8CCFC1C8CEFDFDFDFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDFEDF469CBF456C8F668DAFF61DC
                FF5ED9FF58D2FF51CAFF68D9FE59CEFB68CCF881CBF64E9EF0488ED7D3D7DAFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE3EEF3
                79DCFA6BDEFF64E1FF61DDFF5BD6FF54CEFF65D6FD8EDBFD9BE2FDC3DDE7B5DB
                F73B92F0709CCAF7F7F7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFF4F7F966B1EF71E2FE65E2FF62DDFF5CD7FF53CBFEB0E6FEA9E5FD
                BBD7DFFDFEFEE4F0F95DA2ED3E90E3D9DCDFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFD7E4F065B8F86BE0FF62DDFF5DD8FF57D1FEAB
                E5FEC4EFFDC4DBE1FDFDFDFFFFFFFDFEFE67A1E348A2F3B2C4D2FFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFCADEED75CAFD5FD7FF59D3
                FF57CDFEB2E9FEC2F3FDCBDEE1FEFEFEFFFFFFFFFFFFFFFFFF72A1E058AFF7A6
                C2D4FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD4E4EF
                83D1FD50C5FC4BBFFBA7E2FDCBF8FDCADCDDFEFEFEFFFFFFFFFFFFFFFFFFFFFF
                FF6997D956B3F9B3CCDCFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFEDF3F78AD4F953B5F74CB1F6B7F1FDC7DBDCFDFDFDFFFFFFFFFFFF
                FFFFFFFFFFFFEEF1F44E8CDE51B3F6D7E1E7FFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFDFEFE9FD8F384C6F73D9EEEB6D4D7FDFDFDFF
                FFFFFFFFFFFFFFFFFFFFFFFEFEFE86AAD851A3F26BB6EAFBFBFBFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDFEEF6B7E5FC6DAE
                EE6D93BCD3D4D5F5F5F5FCFCFCFCFBFCEEEFF18FB5D85EA8EF45A6F7C8DEEDFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFD6ECF6EBF7FD9EC5F35188D0648CBF7CA1C574A5CC6BAFE17EC3FA52AD
                F9A8D1EDFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFE5F2F8E0F3F9D4F4FDACDCF9A0D7F9ABE0FC
                91D7FE7BC5F7C3E0F3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF8FCFDDFF0F8C7
                EAF7B9E6F6C2E7F7D3EAF6F6FBFDFFFFFFFFFFFFFFFFFFFFFFFF}
              TabOrder = 0
              OnClick = UnlocktablesBtnClick
            end
          end
        end
      end
      object TabSheet6: TTabSheet
        Caption = 'Settings'
        ImageIndex = 5
        object GroupBox13: TGroupBox
          Left = 16
          Top = 130
          Width = 345
          Height = 233
          Caption = 'ATDB Users'
          TabOrder = 0
          object mUsersDBGrid: TDBGrid
            Left = 2
            Top = 15
            Width = 341
            Height = 191
            Align = alClient
            DataSource = pgDM.usersDataSource
            TabOrder = 0
            TitleFont.Charset = DEFAULT_CHARSET
            TitleFont.Color = clWindowText
            TitleFont.Height = -11
            TitleFont.Name = 'Tahoma'
            TitleFont.Style = []
            Columns = <
              item
                Expanded = False
                FieldName = 'user_name'
                Title.Caption = 'User'
                Width = 182
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'id'
                Visible = True
              end>
          end
          object UsersNavigator: TDBNavigator
            Left = 2
            Top = 206
            Width = 341
            Height = 25
            DataSource = pgDM.usersDataSource
            VisibleButtons = [nbPrior, nbNext, nbInsert, nbDelete, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
            Align = alBottom
            TabOrder = 1
            OnClick = NavigatorClick
          end
        end
        object GroupBox14: TGroupBox
          Left = 16
          Top = 379
          Width = 635
          Height = 310
          Caption = 'Coverslip Print Settings'
          TabOrder = 1
          object DBText4: TDBText
            Left = 16
            Top = 25
            Width = 65
            Height = 17
            DataField = 'id'
            DataSource = settingsDS
          end
          object mTestLabel: TSTDStringLabeledEdit
            Left = 352
            Top = 200
            Width = 121
            Height = 21
            EditLabel.Width = 75
            EditLabel.Height = 13
            EditLabel.Caption = 'Test Label Data'
            TabOrder = 0
            Text = 'C0001234'
            Value = 'C0001234'
          end
          object mPrintTestLabelBtn: TButton
            Left = 352
            Top = 244
            Width = 87
            Height = 25
            Caption = 'Print One'
            TabOrder = 1
            OnClick = mPrintTestLabelBtnClick
          end
          object mBarCodeCommandMemo: TDBMemo
            Left = 16
            Top = 48
            Width = 297
            Height = 169
            DataField = 'label_printer_command'
            DataSource = settingsDS
            TabOrder = 2
          end
          object settingsNavigator: TDBNavigator
            Left = 16
            Top = 240
            Width = 297
            Height = 25
            DataSource = settingsDS
            VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates]
            TabOrder = 3
            OnClick = NavigatorClick
          end
        end
        object GroupBox20: TGroupBox
          Left = 384
          Top = 130
          Width = 395
          Height = 85
          BiDiMode = bdLeftToRight
          Caption = 'Media'
          ParentBiDiMode = False
          TabOrder = 2
          object BrowseForMediaFolderBtn: TButton
            Left = 339
            Top = 47
            Width = 27
            Height = 25
            Action = BrowseForFolder1
            TabOrder = 0
          end
          object MediaFolderE: TSTDStringLabeledEdit
            Left = 16
            Top = 49
            Width = 317
            Height = 21
            EditLabel.Width = 87
            EditLabel.Height = 13
            EditLabel.Caption = 'Media Root Folder'
            TabOrder = 1
          end
        end
        inline TPGConnectionFrame1: TPGConnectionFrame
          Left = 1
          Top = 50
          Width = 917
          Height = 74
          TabOrder = 3
          ExplicitLeft = 1
          ExplicitTop = 50
          ExplicitWidth = 917
          ExplicitHeight = 74
          inherited GBox1: TGroupBox
            Width = 917
            Height = 74
            Align = alClient
            Caption = 'Database Connection'
            ExplicitWidth = 917
            ExplicitHeight = 74
            inherited mServerIPE: TSTDStringLabeledEdit
              Top = 36
              Width = 341
              EditLabel.ExplicitLeft = 16
              EditLabel.ExplicitTop = 20
              EditLabel.ExplicitWidth = 74
              ExplicitTop = 36
              ExplicitWidth = 341
            end
            inherited mDBUserE: TSTDStringLabeledEdit
              Left = 519
              Top = 36
              EditLabel.ExplicitLeft = 519
              EditLabel.ExplicitTop = 20
              EditLabel.ExplicitWidth = 22
              ExplicitLeft = 519
              ExplicitTop = 36
            end
            inherited mPasswordE: TSTDStringLabeledEdit
              Left = 657
              Top = 36
              EditLabel.ExplicitLeft = 657
              EditLabel.ExplicitTop = 20
              EditLabel.ExplicitWidth = 46
              PasswordChar = '*'
              ExplicitLeft = 657
              ExplicitTop = 36
            end
            inherited mDatabaseE: TSTDStringLabeledEdit
              Left = 371
              Top = 36
              EditLabel.ExplicitLeft = 371
              EditLabel.ExplicitTop = 20
              EditLabel.ExplicitWidth = 46
              ExplicitLeft = 371
              ExplicitTop = 36
            end
            inherited ArrayBotButton1: TArrayBotButton
              Left = 796
              Top = 18
              ExplicitLeft = 796
              ExplicitTop = 18
            end
          end
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'Logs'
        ImageIndex = 6
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object BottomPanel: TPanel
          Left = 0
          Top = 0
          Width = 1656
          Height = 899
          Align = alClient
          TabOrder = 0
          object Panel1: TPanel
            Left = 1
            Top = 1
            Width = 1654
            Height = 897
            Align = alClient
            Caption = 'Panel1'
            TabOrder = 0
            object infoMemo: TMemo
              Left = 1
              Top = 22
              Width = 1652
              Height = 874
              Align = alClient
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Consolas'
              Font.Style = []
              ParentFont = False
              PopupMenu = LogMemoPopup
              ScrollBars = ssBoth
              TabOrder = 0
            end
            object ToolBar1: TToolBar
              Left = 1
              Top = 1
              Width = 1652
              Height = 21
              AutoSize = True
              ButtonHeight = 21
              ButtonWidth = 82
              Caption = 'ToolBar1'
              ShowCaptions = True
              TabOrder = 1
              object ToolButton2: TToolButton
                Left = 0
                Top = 0
                Action = ClearMemoA
              end
              object ToolButton1: TToolButton
                Left = 82
                Top = 0
                Width = 41
                Caption = 'ToolButton1'
                ImageIndex = 0
                Style = tbsSeparator
              end
              object LogLevelCB: TComboBox
                Left = 123
                Top = 0
                Width = 145
                Height = 21
                ItemIndex = 0
                TabOrder = 0
                Text = 'INFO'
                OnChange = LogLevelCBChange
                Items.Strings = (
                  'INFO'
                  'Everything')
              end
            end
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Tools'
        ImageIndex = 7
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
      end
    end
  end
  object SB: TStatusBar
    Left = 0
    Top = 978
    Width = 1666
    Height = 19
    Panels = <>
  end
  object MenuPanel: TPanel
    Left = 0
    Top = 0
    Width = 1666
    Height = 49
    Align = alTop
    TabOrder = 2
    object SpecieRG: TRadioGroup
      Left = 1
      Top = 1
      Width = 129
      Height = 47
      Align = alLeft
      Caption = 'Species'
      Columns = 2
      ItemIndex = 1
      Items.Strings = (
        'Human'
        'Mouse')
      TabOrder = 0
      OnClick = SpecieRGClick
    end
    object Panel10: TPanel
      Left = 315
      Top = 1
      Width = 169
      Height = 47
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 1
      object ArrayBotButton1: TArrayBotButton
        Left = 0
        Top = 0
        Width = 169
        Height = 47
        Align = alClient
        Caption = 'Scan Mode'
        TabOrder = 0
        OnClick = ArrayBotButton1Click
        SoundID = 'BUTTON_CLICK_4'
      end
    end
    object GroupBox5: TGroupBox
      Left = 130
      Top = 1
      Width = 185
      Height = 47
      Align = alLeft
      Caption = 'Current User'
      TabOrder = 2
      DesignSize = (
        185
        47)
      object UsersCB: TDBLookupComboBox
        Left = 18
        Top = 15
        Width = 145
        Height = 21
        Anchors = [akTop, akRight]
        KeyField = 'id'
        ListField = 'user_name'
        ListSource = pgDM.usersDataSource
        TabOrder = 0
        OnCloseUp = UsersCBCloseUp
      end
    end
  end
  object ActionList1: TActionList
    Left = 712
    Top = 24
    object ClearMemoA: TAction
      Category = 'Memo'
      Caption = 'Clear Messages'
      OnExecute = ClearMemoAExecute
    end
    object FileExit1: TFileExit
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
    object OpenAboutFormA: TAction
      Caption = 'About'
      OnExecute = OpenAboutFormAExecute
    end
    object BrowseForFolder1: TBrowseForFolder
      Category = 'File'
      Caption = '...'
      DialogCaption = '...'
      BrowseOptions = [bifEditBox, bifNewDialogStyle, bifStatusText]
      BrowseOptionsEx = []
      OnAccept = BrowseForFolder1Accept
    end
  end
  object LogMemoPopup: TPopupMenu
    Left = 128
    Top = 280
    object ClearMemoA1: TMenuItem
      Action = ClearMemoA
    end
  end
  object mIniFileC: TIniFileC
    IniFileName = 'atDB.ini'
    RootFolder = '.'
    Left = 546
    Top = 16
  end
  object MainMenu1: TMainMenu
    Left = 653
    Top = 24
    object File1: TMenuItem
      Caption = 'File'
      object Exit1: TMenuItem
        Action = FileExit1
      end
    end
    object Options1: TMenuItem
      Caption = 'Options'
      object ThemesMenu: TMenuItem
        Caption = 'Appearance'
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object About1: TMenuItem
        Action = OpenAboutFormA
      end
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 50
    OnTimer = ShutDownTimerTimer
    Left = 1602
    Top = 24
  end
  object SpecimenPopup: TPopupMenu
    Left = 240
    Top = 320
    object openDocument: TMenuItem
      Caption = 'Open Document'
    end
  end
  object CoverSlipPopup: TPopupMenu
    Left = 328
    Top = 280
    object SetStatus1: TMenuItem
      Caption = 'Set Status'
      object FreshoutoftheBoxMenuItem: TMenuItem
        Caption = 'Fresh out of the Box'
        OnClick = DiscardedMenuItemClick
      end
      object DiscardedMenuItem: TMenuItem
        Caption = 'Discarded'
        OnClick = DiscardedMenuItemClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
    end
  end
  object settingsDS: TDataSource
    DataSet = pgDM.settingsCDS
    Left = 640
    Top = 440
  end
  object SpecimenDS: TDataSource
    DataSet = pgDM.specimenCDS
    Left = 816
    Top = 432
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 576
    Top = 232
  end
end
