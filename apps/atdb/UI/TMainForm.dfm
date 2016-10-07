object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'atDB'
  ClientHeight = 753
  ClientWidth = 993
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
    Top = 605
    Width = 993
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 0
    ExplicitWidth = 505
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 608
    Width = 993
    Height = 126
    Align = alBottom
    TabOrder = 0
    object Panel4: TPanel
      Left = 1
      Top = 1
      Width = 991
      Height = 124
      Align = alClient
      Caption = 'Panel4'
      TabOrder = 0
      object infoMemo: TMemo
        Left = 1
        Top = 22
        Width = 989
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
        Width = 989
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
    Width = 993
    Height = 605
    Align = alClient
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 991
      Height = 603
      ActivePage = TabSheet2
      Align = alClient
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      object TabSheet2: TTabSheet
        Caption = 'Overview'
        ImageIndex = 1
        object GroupBox2: TGroupBox
          Left = 23
          Top = 39
          Width = 882
          Height = 219
          Caption = 'Blocks'
          TabOrder = 0
          object Label1: TLabel
            Left = 20
            Top = 183
            Width = 53
            Height = 13
            Caption = 'Block label:'
          end
          object mBlocksGrid: TDBGrid
            Left = 15
            Top = 62
            Width = 394
            Height = 99
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
                Width = 48
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'created_by'
                Width = 77
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'status'
                Width = 62
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'label'
                Width = 100
                Visible = True
              end>
          end
          object Panel3: TPanel
            Left = 2
            Top = 15
            Width = 878
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
            Height = 99
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
                Width = 100
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'created_by'
                Width = 100
                Visible = True
              end>
          end
          object DBMemo1: TDBMemo
            Left = 630
            Top = 62
            Width = 229
            Height = 99
            DataField = 'note'
            DataSource = atdbDM.blockNotesDSource
            TabOrder = 3
          end
          object DBNavigator2: TDBNavigator
            Left = 630
            Top = 167
            Width = 234
            Height = 25
            DataSource = atdbDM.blockNotesDSource
            VisibleButtons = [nbPost, nbCancel]
            TabOrder = 4
          end
          object DBMemo2: TDBMemo
            Left = 79
            Top = 176
            Width = 185
            Height = 25
            DataField = 'label'
            DataSource = atdbDM.blocksDataSource
            TabOrder = 5
            WantReturns = False
            WordWrap = False
            OnKeyPress = DBMemo2KeyPress
          end
          object mDeleteNoteBtn: TButton
            Left = 497
            Top = 167
            Width = 75
            Height = 27
            Caption = 'Delete Note'
            TabOrder = 6
            OnClick = mDeleteNoteBtnClick
          end
          object mNewNoteBtn: TButton
            Left = 415
            Top = 167
            Width = 76
            Height = 27
            Caption = 'New Note'
            TabOrder = 7
            OnClick = mNewNoteBtnClick
          end
        end
        object GroupBox6: TGroupBox
          Left = 23
          Top = 278
          Width = 798
          Height = 251
          Caption = 'Ribbons'
          TabOrder = 1
          object mBarCodeImage: TImage
            Left = 672
            Top = 22
            Width = 98
            Height = 179
            ParentShowHint = False
            Proportional = True
            ShowHint = True
            Stretch = True
          end
          object DBText2: TDBText
            Left = 280
            Top = 224
            Width = 65
            Height = 17
            DataField = 'bar_code'
          end
          object mRibbonsGrid: TDBGrid
            Left = 15
            Top = 22
            Width = 610
            Height = 184
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
                FieldName = 'id'
                Width = 80
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'status'
                Width = 80
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'created'
                Width = 80
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'block_id'
                Width = 80
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'cutting_order'
                Width = 80
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'nr_of_sections'
                Width = 80
                Visible = True
              end>
          end
          object mRibbonsNavigator: TDBNavigator
            Left = 15
            Top = 212
            Width = 204
            Height = 25
            DataSource = atdbDM.mRibbonDSource
            VisibleButtons = [nbInsert, nbDelete, nbPost, nbRefresh, nbApplyUpdates, nbCancelUpdates]
            ConfirmDelete = False
            TabOrder = 1
            OnClick = RibbonsNavigatorClick
          end
          object PrintBarCodeBtn: TButton
            Left = 672
            Top = 215
            Width = 113
            Height = 25
            Caption = 'PrintBarCodeBtn'
            TabOrder = 2
            OnClick = PrintBarCodeClick
          end
        end
        object mUsersCB: TComboBox
          Left = 23
          Top = 12
          Width = 145
          Height = 21
          Style = csDropDownList
          Sorted = True
          TabOrder = 2
          OnChange = mUsersCBChange
          OnEnter = mUsersCBEnter
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
    Top = 734
    Width = 993
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
    Orientation = boBottomTop
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
    Ratio = 2.000000000000000000
    Left = 736
    Top = 320
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
