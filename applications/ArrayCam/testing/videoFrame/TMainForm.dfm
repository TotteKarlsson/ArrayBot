object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'AT Movies'
  ClientHeight = 964
  ClientWidth = 1521
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object infoMemo: TMemo
    Left = 0
    Top = 808
    Width = 1521
    Height = 156
    Align = alBottom
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
    WordWrap = False
  end
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 1521
    Height = 129
    Align = alTop
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 505
      Height = 127
      Align = alLeft
      Caption = 'Data Folder Selection'
      TabOrder = 0
      object Panel1: TPanel
        Left = 2
        Top = 15
        Width = 501
        Height = 41
        Align = alTop
        TabOrder = 0
        object MovieFolder: TSTDStringEdit
          Left = 9
          Top = 11
          Width = 440
          Height = 21
          TabOrder = 0
          Text = 'E:\at_media\movies'
          Value = 'E:\at_media\movies'
        end
        object Button1: TButton
          Left = 455
          Top = 10
          Width = 34
          Height = 25
          Action = BrowseForFolder1
          TabOrder = 1
        end
      end
    end
    inline TATDBConnectionFrame1: TATDBConnectionFrame
      Left = 1047
      Top = 1
      Width = 473
      Height = 127
      Align = alRight
      AutoSize = True
      TabOrder = 1
      ExplicitLeft = 1047
      ExplicitTop = 1
      ExplicitWidth = 473
      ExplicitHeight = 127
      inherited GBox1: TGroupBox
        Width = 473
        ExplicitWidth = 473
        inherited mServerIPE: TSTDStringLabeledEdit
          Text = 'atdb'
          Value = 'atdb'
        end
        inherited mDBUserE: TSTDStringLabeledEdit
          Text = 'atdb'
          Value = 'atdb'
        end
        inherited mATDBServerBtnConnect: TArrayBotButton
          Left = 311
          Top = 46
          ExplicitLeft = 311
          ExplicitTop = 46
        end
        inherited mDatabaseE: TSTDStringLabeledEdit
          Text = 'atdb-live'
          Value = 'atdb-live'
        end
      end
    end
  end
  object Panel2: TGroupBox
    Left = 0
    Top = 129
    Width = 113
    Height = 679
    Align = alLeft
    Caption = 'Block IDs'
    Color = clBtnFace
    ParentColor = False
    TabOrder = 2
    object DBNavigator1: TDBNavigator
      Left = 2
      Top = 652
      Width = 109
      Height = 25
      DataSource = atdbDM.blockIDsDataSource
      VisibleButtons = [nbPrior, nbNext]
      Align = alBottom
      TabOrder = 0
    end
    object DBLookupListBox1: TDBLookupListBox
      Left = 2
      Top = 15
      Width = 109
      Height = 628
      Align = alClient
      KeyField = 'id'
      ListField = 'id'
      ListSource = atdbDM.blockIDsDataSource
      TabOrder = 1
      OnKeyDown = DBLookupListBox1KeyDown
      OnKeyUp = DBLookupListBox1KeyUp
      OnMouseDown = DBLookupListBox1MouseDown
      OnMouseUp = DBLookupListBox1MouseUp
    end
  end
  object Button2: TButton
    Left = 984
    Top = 624
    Width = 75
    Height = 25
    Caption = 'Button2'
    TabOrder = 3
  end
  object PageControl1: TPageControl
    Left = 113
    Top = 129
    Width = 1408
    Height = 679
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 4
    object TabSheet2: TTabSheet
      Caption = 'Movies'
      ImageIndex = 1
      object ScrollBox1: TScrollBox
        Left = 0
        Top = 0
        Width = 1400
        Height = 596
        Align = alClient
        TabOrder = 0
        object FlowPanel1: TFlowPanel
          Left = 0
          Top = 0
          Width = 1396
          Height = 481
          Align = alTop
          AutoSize = True
          BevelOuter = bvNone
          TabOrder = 0
        end
      end
      object Panel3: TPanel
        Left = 0
        Top = 596
        Width = 1400
        Height = 55
        Align = alBottom
        TabOrder = 1
        object Label1: TLabel
          Left = 32
          Top = 24
          Width = 96
          Height = 13
          Caption = 'Number of Records:'
        end
        object NrOfRecordsLbl: TIntLabel
          Left = 134
          Top = 24
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
      end
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 50
    OnTimer = ShutDownTimerTimer
    Left = 256
    Top = 136
  end
  object ActionList1: TActionList
    Left = 448
    Top = 232
    object BrowseForFolder1: TBrowseForFolder
      Category = 'File'
      Caption = '...'
      DialogCaption = '...'
      BrowseOptions = [bifBrowseForComputer, bifEditBox, bifNewDialogStyle]
      OnAccept = BrowseForFolder1Accept
    end
  end
  object SQLQuery1: TSQLQuery
    DataSource = atdbDM.blockIDsDataSource
    MaxBlobSize = -1
    Params = <
      item
        DataType = ftUnknown
        Name = 'id'
        ParamType = ptInput
      end>
    SQL.Strings = (
      
        'SELECT id,created from movies where block_id=:id ORDER by create' +
        'd DESC')
    SQLConnection = atdbDM.SQLConnection1
    Left = 192
    Top = 296
  end
  object RefreshUITimer: TTimer
    Enabled = False
    Interval = 250
    OnTimer = RefreshUITimerTimer
    Left = 328
    Top = 248
  end
end
