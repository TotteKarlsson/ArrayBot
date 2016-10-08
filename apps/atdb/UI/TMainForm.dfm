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
    Top = 0
    Width = 1142
    Height = 645
    Align = alClient
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 1140
      Height = 643
      ActivePage = TabSheet2
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
          Height = 615
          VertScrollBar.Position = 90
          Align = alClient
          TabOrder = 0
          object Label2: TLabel
            Left = 37
            Top = -73
            Width = 26
            Height = 13
            Caption = 'User:'
          end
          object GroupBox6: TGroupBox
            Left = 23
            Top = 288
            Width = 930
            Height = 400
            Caption = 'Ribbons'
            TabOrder = 0
            object mBarCodeImage: TImage
              Left = 14
              Top = 284
              Width = 375
              Height = 98
              ParentShowHint = False
              Proportional = True
              ShowHint = True
              Stretch = True
            end
            object Label3: TLabel
              Left = 396
              Top = 61
              Width = 67
              Height = 13
              Caption = 'Nr of Sections'
            end
            object Label4: TLabel
              Left = 396
              Top = 115
              Width = 66
              Height = 13
              Caption = 'Cutting Order'
            end
            object mRibbonsGrid: TDBGrid
              Left = 14
              Top = 54
              Width = 375
              Height = 227
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
              Width = 204
              Height = 25
              DataSource = atdbDM.mRibbonDSource
              VisibleButtons = [nbInsert, nbDelete, nbPost, nbRefresh, nbApplyUpdates, nbCancelUpdates]
              ConfirmDelete = False
              TabOrder = 1
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
            object DBGrid1: TDBGrid
              Left = 522
              Top = 54
              Width = 176
              Height = 199
              DataSource = atdbDM.ribbonNotesDSource
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
                  Width = 80
                  Visible = True
                end>
            end
            object DBMemo3: TDBMemo
              Left = 704
              Top = 96
              Width = 191
              Height = 160
              DataField = 'note'
              DataSource = atdbDM.ribbonNotesDSource
              TabOrder = 4
            end
            object DBNavigator4: TDBNavigator
              Left = 704
              Top = 262
              Width = 190
              Height = 25
              DataSource = atdbDM.ribbonNotesDSource
              VisibleButtons = [nbPost, nbCancel]
              TabOrder = 5
            end
            object mNewRibbonNote: TButton
              Left = 526
              Top = 259
              Width = 76
              Height = 27
              Caption = 'New Note'
              TabOrder = 6
              OnClick = mNewNoteBtnClick
            end
            object mDeleteRibbonNote: TButton
              Left = 608
              Top = 259
              Width = 75
              Height = 27
              Caption = 'Delete Note'
              TabOrder = 7
              OnClick = mDeleteNoteBtnClick
            end
            object DBEdit2: TDBEdit
              Left = 396
              Top = 77
              Width = 121
              Height = 21
              DataField = 'nr_of_sections'
              DataSource = atdbDM.mRibbonDSource
              TabOrder = 8
            end
            object DBEdit3: TDBEdit
              Left = 395
              Top = 131
              Width = 121
              Height = 21
              DataField = 'cutting_order'
              DataSource = atdbDM.mRibbonDSource
              TabOrder = 9
            end
            object DBLookupComboBox4: TDBLookupComboBox
              Left = 704
              Top = 69
              Width = 189
              Height = 21
              DataField = 'created_by'
              DataSource = atdbDM.ribbonNotesDSource
              Enabled = False
              KeyField = 'id'
              ListField = 'user_name'
              ListSource = atdbDM.usersDataSource
              TabOrder = 10
            end
          end
          object mUsersCB: TComboBox
            Left = 77
            Top = -76
            Width = 145
            Height = 21
            Style = csDropDownList
            Sorted = True
            TabOrder = 1
            OnChange = mUsersCBChange
            OnEnter = mUsersCBEnter
          end
          object GroupBox2: TGroupBox
            Left = 24
            Top = -54
            Width = 934
            Height = 325
            Caption = 'Blocks'
            TabOrder = 2
            object Label1: TLabel
              Left = 20
              Top = 287
              Width = 53
              Height = 13
              Caption = 'Block label:'
            end
            object mBlocksGrid: TDBGrid
              Left = 15
              Top = 62
              Width = 394
              Height = 203
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
                Width = 225
                Height = 25
                DataSource = atdbDM.blocksDataSource
                VisibleButtons = [nbPrior, nbNext, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
                TabOrder = 0
              end
              object mNewBlockBtn: TButton
                Left = 292
                Top = 8
                Width = 115
                Height = 33
                Caption = 'Register New Block'
                Enabled = False
                TabOrder = 1
                OnClick = RegisterNewBlock
              end
            end
            object mBlockNotesGrid: TDBGrid
              Left = 415
              Top = 62
              Width = 209
              Height = 203
              DataSource = atdbDM.blockNotesDSource
              Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
              TabOrder = 2
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
            object DBMemo1: TDBMemo
              Left = 630
              Top = 88
              Width = 263
              Height = 177
              DataField = 'note'
              DataSource = atdbDM.blockNotesDSource
              TabOrder = 3
            end
            object DBNavigator2: TDBNavigator
              Left = 630
              Top = 271
              Width = 262
              Height = 25
              DataSource = atdbDM.blockNotesDSource
              VisibleButtons = [nbPost, nbCancel]
              TabOrder = 4
            end
            object DBMemo2: TDBMemo
              Left = 79
              Top = 280
              Width = 120
              Height = 25
              DataField = 'label'
              DataSource = atdbDM.blocksDataSource
              TabOrder = 5
              WantReturns = False
              WordWrap = False
            end
            object mDeleteNoteBtn: TButton
              Left = 498
              Top = 267
              Width = 75
              Height = 27
              Caption = 'Delete Note'
              TabOrder = 6
              OnClick = mDeleteNoteBtnClick
            end
            object mNewNoteBtn: TButton
              Left = 416
              Top = 267
              Width = 76
              Height = 27
              Caption = 'New Note'
              TabOrder = 7
              OnClick = mNewNoteBtnClick
            end
            object DBLookupComboBox1: TDBLookupComboBox
              Left = 264
              Top = 271
              Width = 145
              Height = 21
              DataField = 'created_by'
              DataSource = atdbDM.blocksDataSource
              KeyField = 'id'
              ListField = 'user_name'
              ListSource = atdbDM.usersDataSource
              TabOrder = 8
            end
            object DBLookupComboBox2: TDBLookupComboBox
              Left = 630
              Top = 61
              Width = 229
              Height = 21
              DataField = 'created_by'
              DataSource = atdbDM.blockNotesDSource
              Enabled = False
              KeyField = 'id'
              ListField = 'user_name'
              ListSource = atdbDM.usersDataSource
              TabOrder = 9
            end
          end
          object DBLookupComboBox3: TDBLookupComboBox
            Left = 248
            Top = -81
            Width = 145
            Height = 21
            KeyField = 'id'
            ListField = 'user_name'
            ListSource = atdbDM.usersDataSource
            TabOrder = 3
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
          Left = 29
          Top = 16
          Width = 240
          Height = 25
          DataSource = atdbDM.notesDSource
          VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
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
        object STDStringLabeledEdit1: TSTDStringLabeledEdit
          Left = 16
          Top = 40
          Width = 121
          Height = 21
          EditLabel.Width = 45
          EditLabel.Height = 13
          EditLabel.Caption = 'Server IP'
          TabOrder = 0
        end
        object mATDBServerBtnConnect: TArrayBotButton
          Left = 143
          Top = 27
          Width = 105
          Height = 48
          Caption = 'Connect/Disconnect'
          TabOrder = 1
          OnClick = mATDBServerBtnConnectClick
          SoundID = 'BUTTON_CLICK_4'
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
    Left = 912
    Top = 456
    object ClearMemoA1: TMenuItem
      Action = ClearMemoA
    end
  end
  object mIniFileC: mtkIniFileC
    IniFileName = 'atDB.ini'
    RootFolder = '.'
    Left = 906
    Top = 336
  end
  object MainMenu1: TMainMenu
    Left = 909
    Top = 400
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
  object BindSourceDB1: TBindSourceDB
    ScopeMappings = <>
    Left = 848
    Top = 88
  end
  object BindingsList1: TBindingsList
    Methods = <>
    OutputConverters = <>
    UseAppManager = True
    Left = 804
    Top = 181
  end
  object Barcode1D_Code391: TBarcode1D_Code39
    Image = mBarCodeImage
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
    Left = 848
    Top = 416
  end
  object DBBarcode1D1: TDBBarcode1D
    DataField = 'bar_code'
    ReadOnly = True
    Barcode1D = Barcode1D_Code391
    Left = 656
    Top = 312
  end
  object ActionList2: TActionList
    Left = 896
    Top = 48
  end
  object BindSourceDB2: TBindSourceDB
    ScopeMappings = <>
    Left = 488
    Top = 392
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
end
