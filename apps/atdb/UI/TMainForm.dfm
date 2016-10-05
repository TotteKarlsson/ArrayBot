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
          Left = 19
          Top = 15
          Width = 734
          Height = 234
          Caption = 'Blocks'
          TabOrder = 0
          object DBGrid4: TDBGrid
            Left = 15
            Top = 62
            Width = 695
            Height = 145
            DataSource = atDM.blocksDataSource
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
                Width = 100
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'created_by'
                Width = 100
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'status'
                Width = 100
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
            Width = 730
            Height = 41
            Align = alTop
            BevelOuter = bvNone
            TabOrder = 1
            object mBlocksNavigator: TDBNavigator
              Left = 13
              Top = 8
              Width = 240
              Height = 25
              DataSource = atDM.blocksDataSource
              VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
              TabOrder = 0
            end
            object mNewBlockBtn: TButton
              Left = 590
              Top = 8
              Width = 115
              Height = 33
              Caption = 'Register New Block'
              Enabled = False
              TabOrder = 1
              OnClick = RegisterNewBlock
            end
            object ComboBox1: TComboBox
              Left = 439
              Top = 12
              Width = 145
              Height = 21
              Style = csDropDownList
              Sorted = True
              TabOrder = 2
              OnChange = ComboBox1Change
              OnEnter = ComboBox1Enter
            end
          end
        end
        object GroupBox6: TGroupBox
          Left = 19
          Top = 255
          Width = 798
          Height = 294
          Caption = 'Ribbons'
          TabOrder = 1
          object mBarCodeImage: TImage
            Left = 671
            Top = 22
            Width = 98
            Height = 259
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
          object DBGrid1: TDBGrid
            Left = 15
            Top = 22
            Width = 610
            Height = 184
            DataSource = atDM.mRibbonDSource
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
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'block_id'
                Width = 64
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'created'
                Width = 64
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'cutting_order'
                Width = 64
                Visible = True
              end
              item
                Expanded = False
                FieldName = 'bar_code'
                Visible = True
              end>
          end
          object mRibbonsNavigator: TDBNavigator
            Left = 15
            Top = 212
            Width = 210
            Height = 25
            VisibleButtons = [nbInsert, nbDelete]
            ConfirmDelete = False
            TabOrder = 1
            OnClick = RibbonsNavigatorClick
          end
          object PrintBarCodeBtn: TButton
            Left = 416
            Top = 212
            Width = 113
            Height = 25
            Caption = 'PrintBarCodeBtn'
            TabOrder = 2
            OnClick = PrintBarCodeClick
          end
        end
      end
      object TabSheet1: TTabSheet
        Caption = 'Blocks'
        ImageIndex = 1
        object DBGrid2: TDBGrid
          Left = 0
          Top = 89
          Width = 983
          Height = 486
          Align = alClient
          Anchors = [akLeft, akRight, akBottom]
          DataSource = atDM.blocksDataSource
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
        end
        object Panel1: TPanel
          Left = 0
          Top = 0
          Width = 983
          Height = 89
          Align = alTop
          TabOrder = 1
          object DBNavigator2: TDBNavigator
            Left = 0
            Top = 8
            Width = 240
            Height = 25
            DataSource = atDM.blocksDataSource
            VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
          end
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'Users'
        ImageIndex = 2
        object DBGrid3: TDBGrid
          Left = 21
          Top = 96
          Width = 708
          Height = 120
          DataSource = atDM.usersDataSource
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
        end
        object Panel2: TPanel
          Left = 0
          Top = 0
          Width = 983
          Height = 65
          Align = alTop
          TabOrder = 1
          object DBNavigator1: TDBNavigator
            Left = 29
            Top = 8
            Width = 240
            Height = 25
            DataSource = atDM.usersDataSource
            VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
            TabOrder = 0
          end
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
    Left = 660
    Top = 109
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
    DataSet = atDM.usersDS
    ScopeMappings = <>
    Left = 488
    Top = 392
  end
  object mUsersQ: TSQLQuery
    DataSource = atDM.usersDataSource
    MaxBlobSize = -1
    Params = <>
    SQL.Strings = (
      'select id,user_name from user')
    SQLConnection = atDM.SQLConnection1
    Left = 776
    Top = 48
  end
end
