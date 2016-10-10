object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'atDB'
  ClientHeight = 793
  ClientWidth = 1142
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDefault
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 645
    Width = 1142
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 0
    ExplicitWidth = 505
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 648
    Width = 1142
    Height = 126
    Align = alBottom
    TabOrder = 0
    object Panel4: TPanel
      Left = 1
      Top = 1
      Width = 1140
      Height = 124
      Align = alClient
      Caption = 'Panel4'
      TabOrder = 0
      object infoMemo: TMemo
        Left = 1
        Top = 22
        Width = 1138
        Height = 101
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Consolas'
        Font.Style = []
        ParentFont = False
        PopupMenu = PopupMenu1
        ScrollBars = ssBoth
        TabOrder = 0
      end
      object ToolBar2: TToolBar
        Left = 1
        Top = 1
        Width = 1138
        Height = 21
        AutoSize = True
        ButtonHeight = 21
        ButtonWidth = 32
        Caption = 'ToolBar2'
        ShowCaptions = True
        TabOrder = 1
        object ToolButton4: TToolButton
          Left = 0
          Top = 0
          Action = ClearMemoA
          Caption = 'Clear'
        end
        object ToolButton1: TToolButton
          Left = 32
          Top = 0
          Width = 41
          Caption = 'ToolButton1'
          ImageIndex = 0
          Style = tbsSeparator
        end
        object LogLevelCB: TComboBox
          Left = 73
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
  object TopPanel: TPanel
    Left = 0
    Top = 41
    Width = 1142
    Height = 604
    Align = alClient
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 1140
      Height = 602
      ActivePage = TabSheet1
      Align = alClient
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      object TabSheet2: TTabSheet
        Caption = 'Overview'
        ImageIndex = 1
        object ScrollBox1: TScrollBox
          Left = 0
          Top = 0
          Width = 1132
          Height = 574
          Align = alClient
          TabOrder = 0
          object GroupBox6: TGroupBox
            Left = 18
            Top = 343
            Width = 935
            Height = 326
            Caption = 'Ribbons'
            TabOrder = 0
            object Label3: TLabel
              Left = 14
              Top = 252
              Width = 67
              Height = 13
              Caption = 'Nr of Sections'
            end
            object Label4: TLabel
              Left = 158
              Top = 250
              Width = 66
              Height = 13
              Caption = 'Cutting Order'
            end
            object mRibbonsGrid: TDBGrid
              Left = 14
              Top = 54
              Width = 396
              Height = 187
              DataSource = atdbDM.mRibbonDSource
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
                  FieldName = 'created'
                  Title.Caption = 'Date'
                  Width = 80
                  Visible = True
                end
                item
                  Expanded = False
                  FieldName = 'status'
                  Title.Caption = 'Status'
                  Width = 80
                  Visible = True
                end
                item
                  Expanded = False
                  FieldName = 'cutting_order'
                  Title.Caption = 'Cutting Order'
                  Width = 80
                  Visible = True
                end
                item
                  Expanded = False
                  FieldName = 'nr_of_sections'
                  Title.Caption = 'Sections'
                  Width = 80
                  Visible = True
                end>
            end
            object mRibbonsNavigator: TDBNavigator
              Left = 14
              Top = 23
              Width = 200
              Height = 25
              DataSource = atdbDM.mRibbonDSource
              VisibleButtons = [nbInsert, nbDelete, nbRefresh, nbApplyUpdates]
              ConfirmDelete = False
              TabOrder = 1
              BeforeAction = mRibbonsNavigatorBeforeAction
              OnClick = RibbonsNavigatorClick
            end
            object PrintBarCodeBtn: TButton
              Left = 782
              Top = 231
              Width = 113
              Height = 25
              Caption = 'PrintBarCodeBtn'
              TabOrder = 2
              OnClick = PrintBarCodeClick
            end
            object DBEdit2: TDBEdit
              Left = 14
              Top = 271
              Width = 121
              Height = 21
              DataField = 'nr_of_sections'
              DataSource = atdbDM.mRibbonDSource
              TabOrder = 3
            end
            object DBEdit3: TDBEdit
              Left = 158
              Top = 269
              Width = 121
              Height = 21
              DataField = 'cutting_order'
              DataSource = atdbDM.mRibbonDSource
              TabOrder = 4
            end
            object GroupBox1: TGroupBox
              Left = 416
              Top = 23
              Width = 497
              Height = 289
              Caption = 'Ribbon Notes'
              TabOrder = 5
              object DBGrid1: TDBGrid
                Left = 13
                Top = 29
                Width = 199
                Height = 187
                DataSource = atdbDM.ribbonNotesDSource
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
                    Width = 80
                    Visible = True
                  end>
              end
              object DBLookupComboBox4: TDBLookupComboBox
                Left = 220
                Top = 29
                Width = 253
                Height = 21
                DataField = 'created_by'
                DataSource = atdbDM.ribbonNotesDSource
                Enabled = False
                KeyField = 'id'
                ListField = 'user_name'
                ListSource = atdbDM.usersDataSource
                TabOrder = 1
              end
              object DBMemo3: TDBMemo
                Left = 218
                Top = 56
                Width = 255
                Height = 160
                DataField = 'note'
                DataSource = atdbDM.ribbonNotesDSource
                TabOrder = 2
              end
              object DBNavigator4: TDBNavigator
                Left = 219
                Top = 222
                Width = 254
                Height = 25
                DataSource = atdbDM.ribbonNotesDSource
                VisibleButtons = [nbPost, nbCancel]
                TabOrder = 3
              end
              object mDeleteRibbonNoteBtn: TButton
                Left = 103
                Top = 221
                Width = 75
                Height = 27
                Caption = 'Delete Note'
                TabOrder = 4
                OnClick = mDeleteNoteBtnClick
              end
              object mNewRibbonNote: TButton
                Left = 21
                Top = 221
                Width = 76
                Height = 27
                Caption = 'New Note'
                TabOrder = 5
                OnClick = mNewNoteBtnClick
              end
            end
          end
          object mBlocksGB: TGroupBox
            Left = 16
            Top = 12
            Width = 934
            Height = 325
            Caption = 'Blocks'
            TabOrder = 1
            object Label1: TLabel
              Left = 20
              Top = 272
              Width = 53
              Height = 13
              Caption = 'Block label:'
            end
            object mBlocksGrid: TDBGrid
              Left = 15
              Top = 62
              Width = 394
              Height = 188
              DataSource = atdbDM.blocksDataSource
              Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
              ReadOnly = True
              TabOrder = 0
              TitleFont.Charset = DEFAULT_CHARSET
              TitleFont.Color = clWindowText
              TitleFont.Height = -11
              TitleFont.Name = 'Tahoma'
              TitleFont.Style = []
              OnDblClick = mBlocksGridDblClick
              Columns = <
                item
                  Expanded = False
                  FieldName = 'id'
                  Title.Caption = 'ID'
                  Width = 48
                  Visible = True
                end
                item
                  Expanded = False
                  FieldName = 'status'
                  Title.Caption = 'Status'
                  Width = 62
                  Visible = True
                end
                item
                  Expanded = False
                  FieldName = 'label'
                  Title.Caption = 'Label'
                  Width = 100
                  Visible = True
                end>
            end
            object Panel3: TPanel
              Left = 2
              Top = 15
              Width = 930
              Height = 41
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 1
              object mBlocksNavigator: TDBNavigator
                Left = 13
                Top = 8
                Width = 208
                Height = 25
                DataSource = atdbDM.blocksDataSource
                VisibleButtons = [nbInsert, nbDelete, nbRefresh, nbApplyUpdates]
                ConfirmDelete = False
                TabOrder = 0
                BeforeAction = mBlocksNavigatorBeforeAction
                OnClick = mBlocksNavigatorClick
              end
            end
            object DBMemo2: TDBMemo
              Left = 79
              Top = 265
              Width = 120
              Height = 25
              DataField = 'label'
              DataSource = atdbDM.blocksDataSource
              TabOrder = 2
              WantReturns = False
              WordWrap = False
            end
            object DBLookupComboBox1: TDBLookupComboBox
              Left = 205
              Top = 264
              Width = 145
              Height = 21
              DataField = 'created_by'
              DataSource = atdbDM.blocksDataSource
              KeyField = 'id'
              ListField = 'user_name'
              ListSource = atdbDM.usersDataSource
              TabOrder = 3
            end
            object BlockNotesGB: TGroupBox
              Left = 415
              Top = 23
              Width = 498
              Height = 282
              Caption = 'Block Notes'
              TabOrder = 4
              object DBLookupComboBox2: TDBLookupComboBox
                Left = 223
                Top = 23
                Width = 258
                Height = 21
                DataField = 'created_by'
                DataSource = atdbDM.blockNotesDSource
                Enabled = False
                KeyField = 'id'
                ListField = 'user_name'
                ListSource = atdbDM.usersDataSource
                TabOrder = 0
              end
              object DBMemo1: TDBMemo
                Left = 223
                Top = 50
                Width = 263
                Height = 177
                DataField = 'note'
                DataSource = atdbDM.blockNotesDSource
                TabOrder = 1
              end
              object DBNavigator2: TDBNavigator
                Left = 223
                Top = 233
                Width = 262
                Height = 25
                DataSource = atdbDM.blockNotesDSource
                VisibleButtons = [nbPost, nbCancel]
                TabOrder = 2
              end
              object mBlockNotesGrid: TDBGrid
                Left = 8
                Top = 24
                Width = 209
                Height = 203
                DataSource = atdbDM.blockNotesDSource
                Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
                TabOrder = 3
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
                    Width = 100
                    Visible = True
                  end>
              end
              object mDeleteBlockNoteBtn: TButton
                Left = 106
                Top = 233
                Width = 75
                Height = 27
                Caption = 'Delete Note'
                TabOrder = 4
                OnClick = mDeleteNoteBtnClick
              end
              object mNewBlockNoteBtn: TButton
                Left = 8
                Top = 233
                Width = 76
                Height = 27
                Caption = 'New Note'
                TabOrder = 5
                OnClick = mNewNoteBtnClick
              end
            end
          end
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'Users'
        ImageIndex = 2
        object DBGrid3: TDBGrid
          Left = 13
          Top = 63
          Width = 340
          Height = 186
          DataSource = atdbDM.usersDataSource
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
              FieldName = 'id'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'user_name'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'created'
              Width = 121
              Visible = True
            end>
        end
        object DBNavigator1: TDBNavigator
          Left = 13
          Top = 20
          Width = 240
          Height = 25
          DataSource = atdbDM.usersDataSource
          VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
          TabOrder = 1
        end
        object DBEdit1: TDBEdit
          Left = 13
          Top = 268
          Width = 121
          Height = 21
          DataField = 'user_name'
          DataSource = atdbDM.usersDataSource
          TabOrder = 2
        end
      end
      object TabSheet4: TTabSheet
        Caption = 'Notes'
        ImageIndex = 3
        object DBNavigator3: TDBNavigator
          Left = 13
          Top = 25
          Width = 240
          Height = 25
          DataSource = atdbDM.notesDSource
          VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
          ConfirmDelete = False
          TabOrder = 0
        end
        object DBGrid5: TDBGrid
          Left = 13
          Top = 56
          Width = 468
          Height = 249
          DataSource = atdbDM.notesDSource
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
          TabOrder = 1
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
        end
      end
      object TabSheet1: TTabSheet
        Caption = 'DB Server'
        ImageIndex = 3
        object GroupBox3: TGroupBox
          Left = 3
          Top = 16
          Width = 286
          Height = 233
          Caption = 'ATDB Connection'
          TabOrder = 0
          object mServerIPE: TSTDStringLabeledEdit
            Left = 16
            Top = 40
            Width = 121
            Height = 21
            EditLabel.Width = 45
            EditLabel.Height = 13
            EditLabel.Caption = 'Server IP'
            TabOrder = 1
            Text = '127.0.0.1'
            Value = '127.0.0.1'
          end
          object mDBUserE: TSTDStringLabeledEdit
            Left = 16
            Top = 89
            Width = 121
            Height = 21
            EditLabel.Width = 22
            EditLabel.Height = 13
            EditLabel.Caption = 'User'
            TabOrder = 2
            Text = 'atdb-client'
            Value = 'atdb-client'
          end
          object mPasswordE: TSTDStringLabeledEdit
            Left = 16
            Top = 137
            Width = 121
            Height = 21
            EditLabel.Width = 46
            EditLabel.Height = 13
            EditLabel.Caption = 'Password'
            TabOrder = 3
            Text = 'atdb123'
            Value = 'atdb123'
          end
          object mATDBServerBtnConnect: TArrayBotButton
            Left = 159
            Top = 164
            Width = 105
            Height = 48
            Caption = 'Connect/Disconnect'
            TabOrder = 0
            OnClick = mATDBServerBtnConnectClick
            SoundID = 'BUTTON_CLICK_4'
          end
          object mDatabaseE: TSTDStringLabeledEdit
            Left = 16
            Top = 185
            Width = 121
            Height = 21
            EditLabel.Width = 46
            EditLabel.Height = 13
            EditLabel.Caption = 'Database'
            TabOrder = 4
            Text = 'atdb'
            Value = 'atdb'
          end
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'Miscellaneous'
        ImageIndex = 4
        object mBarCodeImage: TImage
          Left = 3
          Top = 15
          Width = 375
          Height = 98
          ParentShowHint = False
          Proportional = True
          ShowHint = True
          Stretch = True
        end
      end
    end
  end
  object SB: TStatusBar
    Left = 0
    Top = 774
    Width = 1142
    Height = 19
    Panels = <>
  end
  object MenuPanel: TPanel
    Left = 0
    Top = 0
    Width = 1142
    Height = 41
    Align = alTop
    TabOrder = 3
    object Label2: TLabel
      Left = 10
      Top = 12
      Width = 26
      Height = 13
      Caption = 'User:'
    end
    object mUsersDBCB: TDBLookupComboBox
      Left = 42
      Top = 9
      Width = 145
      Height = 21
      KeyField = 'id'
      ListField = 'user_name'
      ListSource = atdbDM.usersDataSource
      TabOrder = 0
      OnCloseUp = mUsersDBCBCloseUp
    end
  end
  object ActionList1: TActionList
    Left = 896
    Top = 160
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
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 368
    Top = 72
    object ClearMemoA1: TMenuItem
      Action = ClearMemoA
    end
  end
  object mIniFileC: mtkIniFileC
    IniFileName = 'atDB.ini'
    RootFolder = '.'
    Left = 810
    Top = 384
  end
  object MainMenu1: TMainMenu
    Left = 221
    Top = 56
    object File1: TMenuItem
      Caption = 'File'
      object Exit1: TMenuItem
        Action = FileExit1
      end
    end
    object ools1: TMenuItem
      Caption = 'Options'
      object ThemesMenu: TMenuItem
        Caption = 'Themes'
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
    Left = 898
    Top = 224
  end
  object BindingsList1: TBindingsList
    Methods = <>
    OutputConverters = <>
    UseAppManager = True
    Left = 804
    Top = 181
  end
  object ActionList2: TActionList
    Left = 896
    Top = 48
  end
  object mUsersQ: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQL.Strings = (
      'select id,user_name from user')
    SQLConnection = atdbDM.SQLConnection1
    Left = 584
    Top = 48
  end
  object Barcode1D_Code391: TBarcode1D_Code39
    Stretch = True
    DisplayText = dtBarcode
    TextPosition = tpBottomOut
    TextAlignment = taCenter
    TextFont.Charset = DEFAULT_CHARSET
    TextFont.Color = clBlack
    TextFont.Height = -11
    TextFont.Name = 'Tahoma'
    TextFont.Style = []
    ShowGuards = True
    Barcode = '123-12343'
    Ratio = 1.000000000000000000
    Left = 160
    Top = 504
  end
  object DBBarcode1D1: TDBBarcode1D
    DataField = 'bar_code'
    ReadOnly = True
    Barcode1D = Barcode1D_Code391
    Left = 56
    Top = 504
  end
end
