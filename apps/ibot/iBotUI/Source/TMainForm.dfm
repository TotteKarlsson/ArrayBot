object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'iBot - Image & Stain'
  ClientHeight = 781
  ClientWidth = 943
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
    Top = 547
    Width = 943
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 0
    ExplicitWidth = 505
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 550
    Width = 943
    Height = 212
    Align = alBottom
    TabOrder = 0
    object Panel4: TPanel
      Left = 1
      Top = 1
      Width = 941
      Height = 210
      Align = alClient
      Caption = 'Panel4'
      TabOrder = 0
      object infoMemo: TMemo
        Left = 1
        Top = 22
        Width = 939
        Height = 187
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
        Width = 939
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
        object Button1: TButton
          Left = 218
          Top = 0
          Width = 75
          Height = 21
          Caption = 'Hide'
          TabOrder = 1
          OnClick = Button1Click
        end
      end
    end
  end
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 943
    Height = 547
    Align = alClient
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 941
      Height = 545
      ActivePage = TabSheet4
      Align = alClient
      TabOrder = 0
      object TabSheet4: TTabSheet
        Caption = 'Status'
        ImageIndex = 2
      end
      object TabSheet1: TTabSheet
        Caption = 'Session'
        object GroupBox1: TGroupBox
          Left = 13
          Top = 95
          Width = 868
          Height = 394
          Caption = 'Slots'
          TabOrder = 0
          inline SlotFrame1: TSlotFrame
            Left = 2
            Top = 15
            Width = 864
            Height = 73
            Align = alTop
            AutoSize = True
            TabOrder = 0
            ExplicitLeft = 2
            ExplicitTop = 15
            ExplicitWidth = 864
          end
          inline SlotFrame2: TSlotFrame
            Left = 2
            Top = 88
            Width = 864
            Height = 73
            Align = alTop
            AutoSize = True
            TabOrder = 1
            ExplicitLeft = 2
            ExplicitTop = 88
            ExplicitWidth = 864
          end
          inline SlotFrame3: TSlotFrame
            Left = 2
            Top = 161
            Width = 864
            Height = 73
            Align = alTop
            AutoSize = True
            TabOrder = 2
            ExplicitLeft = 2
            ExplicitTop = 161
            ExplicitWidth = 864
          end
          inline SlotFrame4: TSlotFrame
            Left = 2
            Top = 234
            Width = 864
            Height = 73
            Align = alTop
            AutoSize = True
            TabOrder = 3
            ExplicitLeft = 2
            ExplicitTop = 234
            ExplicitWidth = 864
          end
        end
        object GroupBox4: TGroupBox
          Left = 13
          Top = 16
          Width = 185
          Height = 73
          Caption = 'Select Tissue Block'
          TabOrder = 1
          object mBlocksCB: TDBLookupComboBox
            Left = 16
            Top = 29
            Width = 145
            Height = 21
            KeyField = 'id'
            ListField = 'id'
            ListSource = atDM.blocksDataSource
            TabOrder = 0
            OnCloseUp = DBLookupComboBox5CloseUp
          end
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'Image/Stain Protocols'
        ImageIndex = 2
        object GroupBox7: TGroupBox
          Left = 3
          Top = 32
          Width = 561
          Height = 313
          Caption = 'Select create new image/stain protocol'
          TabOrder = 0
          object Label1: TLabel
            Left = 13
            Top = 24
            Width = 156
            Height = 13
            Caption = 'Predefined Image/Stain sessions'
          end
          object Stains: TGroupBox
            Left = 13
            Top = 88
            Width = 468
            Height = 209
            Caption = 'Stain Protocols'
            TabOrder = 0
            object Label2: TLabel
              Left = 16
              Top = 61
              Width = 36
              Height = 13
              Caption = 'Species'
            end
            object Label3: TLabel
              Left = 111
              Top = 61
              Width = 36
              Height = 13
              Caption = 'Primary'
            end
            object Label4: TLabel
              Left = 231
              Top = 61
              Width = 120
              Height = 13
              Caption = 'Secondary (Fluorophore)'
            end
            object Label5: TLabel
              Left = 17
              Top = 15
              Width = 80
              Height = 13
              Caption = 'Immuno Protocol'
            end
            object ComboBox3: TComboBox
              Left = 16
              Top = 80
              Width = 81
              Height = 21
              TabOrder = 0
              Text = 'ComboBox3'
            end
            object ComboBox4: TComboBox
              Left = 111
              Top = 80
              Width = 106
              Height = 21
              TabOrder = 1
              Text = 'ComboBox4'
            end
            object ComboBox5: TComboBox
              Left = 231
              Top = 80
              Width = 107
              Height = 21
              TabOrder = 2
              Text = 'ComboBox5'
            end
            object ComboBox1: TComboBox
              Left = 16
              Top = 34
              Width = 145
              Height = 21
              TabOrder = 3
              Text = 'ComboBox1'
            end
          end
          object Button2: TButton
            Left = 244
            Top = 39
            Width = 66
            Height = 25
            Caption = 'New'
            TabOrder = 1
          end
          object mImageStainSessionCB: TDBLookupComboBox
            Left = 15
            Top = 43
            Width = 145
            Height = 21
            KeyField = 'id'
            ListField = 'id'
            TabOrder = 2
          end
        end
        object DBGrid3: TDBGrid
          Left = 584
          Top = 181
          Width = 320
          Height = 120
          TabOrder = 1
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Data Tables'
        ImageIndex = 1
        object PageControl2: TPageControl
          Left = 0
          Top = 0
          Width = 933
          Height = 517
          ActivePage = TabSheet3
          Align = alClient
          TabOrder = 0
          object TabSheet3: TTabSheet
            Caption = 'Blocks && Ribbons'
            object ScrollBox1: TScrollBox
              Left = 0
              Top = 0
              Width = 925
              Height = 489
              Align = alClient
              TabOrder = 0
              object GroupBox2: TGroupBox
                Left = 0
                Top = 201
                Width = 921
                Height = 281
                Align = alTop
                Caption = 'Ribbons'
                TabOrder = 0
                object DBNavigator1: TDBNavigator
                  Left = 23
                  Top = 24
                  Width = 240
                  Height = 25
                  DataSource = atDM.mRibbonDSource
                  TabOrder = 0
                end
                object DBGrid1: TDBGrid
                  Left = 23
                  Top = 55
                  Width = 882
                  Height = 120
                  DataSource = atDM.mRibbonDSource
                  TabOrder = 1
                  TitleFont.Charset = DEFAULT_CHARSET
                  TitleFont.Color = clWindowText
                  TitleFont.Height = -11
                  TitleFont.Name = 'Tahoma'
                  TitleFont.Style = []
                end
              end
              object GroupBox3: TGroupBox
                Left = 0
                Top = 0
                Width = 921
                Height = 201
                Align = alTop
                Caption = 'Blocks'
                TabOrder = 1
                object DBGrid2: TDBGrid
                  Left = 23
                  Top = 57
                  Width = 568
                  Height = 128
                  DataSource = atDM.blocksDataSource
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
                      FieldName = 'status'
                      Visible = True
                    end
                    item
                      Expanded = False
                      FieldName = 'created'
                      Width = 135
                      Visible = True
                    end
                    item
                      Expanded = False
                      FieldName = 'modified'
                      Width = 78
                      Visible = True
                    end
                    item
                      Expanded = False
                      FieldName = 'label'
                      Visible = True
                    end>
                end
                object DBNavigator2: TDBNavigator
                  Left = 23
                  Top = 26
                  Width = 240
                  Height = 25
                  DataSource = atDM.blocksDataSource
                  TabOrder = 1
                end
              end
            end
          end
        end
      end
    end
  end
  object SB: TStatusBar
    Left = 0
    Top = 762
    Width = 943
    Height = 19
    Panels = <>
  end
  object ActionList1: TActionList
    Left = 712
    Top = 96
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
    object NotImplementedYetA: TAction
      Caption = 'NotImplementedYetA'
      OnExecute = NotImplementedYetAExecute
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 872
    Top = 32
    object ClearMemoA1: TMenuItem
      Action = ClearMemoA
    end
  end
  object StartupTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = StartupTimerTimer
    Left = 880
    Top = 96
  end
  object mIniFileC: mtkIniFileC
    IniFileName = 'iBot.ini'
    RootFolder = '.'
    Left = 706
    Top = 32
  end
  object MainMenu1: TMainMenu
    Left = 789
    Top = 32
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
      object AmalyticoHelpDocuments1: TMenuItem
        Caption = 'Help Documents'
      end
      object About1: TMenuItem
        Action = OpenAboutFormA
      end
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 50
    OnTimer = ShutDownTimerTimer
    Left = 794
    Top = 96
  end
end
