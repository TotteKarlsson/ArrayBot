object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Main'
  ClientHeight = 712
  ClientWidth = 905
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
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 577
    Width = 905
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 76
    ExplicitTop = 1
    ExplicitWidth = 39
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 114
    Width = 905
    Height = 463
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Blocks'
      DesignSize = (
        897
        435)
      object Label1: TLabel
        Left = 20
        Top = 272
        Width = 28
        Height = 13
        Caption = 'Notes'
      end
      object Label2: TLabel
        Left = 344
        Top = 272
        Width = 23
        Height = 13
        Caption = 'Note'
      end
      object mBlocksT: TRzStringGrid
        Left = 20
        Top = 15
        Width = 838
        Height = 170
        Anchors = [akLeft, akTop, akRight]
        ColCount = 1
        DefaultColWidth = 120
        FixedCols = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
        TabOrder = 0
        OnClick = mBlocksTClick
      end
      object mDeleteRowB: TButton
        Left = 167
        Top = 191
        Width = 142
        Height = 65
        Caption = 'Delete Selected'
        Enabled = False
        TabOrder = 1
        OnClick = mDeleteRowBClick
      end
      object mRegisterBlockBtn: TArrayBotButton
        Left = 20
        Top = 191
        Width = 141
        Height = 65
        Caption = 'Register New Block'
        TabOrder = 2
        OnClick = mRegisterBlockBtnClick
        SoundID = 'BUTTON_CLICK_4'
      end
      object mNotesGrid: TRzStringGrid
        Left = 20
        Top = 291
        Width = 161
        Height = 101
        ColCount = 1
        DefaultColWidth = 130
        FixedCols = 0
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
        ScrollBars = ssVertical
        TabOrder = 3
        OnClick = mNotesGridClick
      end
      object mNotesMemo: TMemo
        Left = 344
        Top = 291
        Width = 233
        Height = 101
        Lines.Strings = (
          'mNotesMemo')
        ScrollBars = ssVertical
        TabOrder = 4
      end
      object mAddNoteBtn: TButton
        Left = 187
        Top = 289
        Width = 75
        Height = 32
        Caption = 'Add Note'
        TabOrder = 5
        OnClick = mAddNoteBtnClick
      end
      object mUpdateNoteBtn: TButton
        Left = 583
        Top = 291
        Width = 75
        Height = 32
        Caption = 'Update'
        TabOrder = 6
        OnClick = mUpdateNoteBtnClick
      end
      object mDeleteNoteBtn: TButton
        Left = 187
        Top = 327
        Width = 75
        Height = 32
        Caption = 'Delete Note'
        TabOrder = 7
        OnClick = mAddNoteBtnClick
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Ribbons'
      ImageIndex = 1
      object mBlockIDEdit: TLabeledEdit
        Left = 4
        Top = 24
        Width = 121
        Height = 21
        EditLabel.Width = 38
        EditLabel.Height = 13
        EditLabel.Caption = 'Block ID'
        Enabled = False
        TabOrder = 0
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 905
    Height = 73
    Align = alTop
    TabOrder = 1
    object mConnectDBBtn: TArrayBotButton
      Left = 1
      Top = 1
      Width = 120
      Height = 71
      Align = alLeft
      Caption = 'Sync DB'
      TabOrder = 0
      OnClick = mConnectDBBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 580
    Width = 905
    Height = 132
    Align = alBottom
    Caption = 'Panel2'
    TabOrder = 2
    object infoMemo: TMemo
      Left = 1
      Top = 42
      Width = 903
      Height = 89
      Align = alClient
      Lines.Strings = (
        'infoMemo')
      ScrollBars = ssVertical
      TabOrder = 0
    end
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 903
      Height = 41
      Align = alTop
      TabOrder = 1
      object Button2: TButton
        Left = 1
        Top = 1
        Width = 75
        Height = 39
        Align = alLeft
        Caption = 'Clear'
        TabOrder = 0
        OnClick = Button2Click
      end
    end
  end
  object Panel4: TPanel
    Left = 0
    Top = 73
    Width = 905
    Height = 41
    Align = alTop
    TabOrder = 3
    object Label3: TLabel
      Left = 8
      Top = 14
      Width = 66
      Height = 13
      Caption = 'Current User:'
    end
    object mUserIDLbl: TLabel
      Left = 241
      Top = 14
      Width = 54
      Height = 13
      Caption = 'mUserIDLbl'
    end
    object mUserCB: TComboBox
      Left = 90
      Top = 10
      Width = 145
      Height = 21
      Style = csDropDownList
      TabOrder = 0
      OnCloseUp = mUserCBCloseUp
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = ShutDownTimerTimer
    Left = 256
    Top = 24
  end
end
