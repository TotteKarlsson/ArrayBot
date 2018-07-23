object SequenceInfoFrame: TSequenceInfoFrame
  Left = 0
  Top = 0
  Width = 441
  Height = 754
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object MasterProcessGB: TGroupBox
    Left = 0
    Top = 0
    Width = 441
    Height = 504
    Align = alClient
    Caption = 'Master Processes'
    Constraints.MinHeight = 330
    TabOrder = 0
    object Panel1: TPanel
      Left = 2
      Top = 25
      Width = 437
      Height = 477
      Align = alClient
      BevelEdges = []
      BevelOuter = bvNone
      TabOrder = 0
      object ProcessesLB: TListBox
        Left = 0
        Top = 0
        Width = 332
        Height = 477
        Align = alClient
        ItemHeight = 23
        TabOrder = 0
        OnClick = ProcessesLBClick
      end
      object Panel2: TPanel
        Left = 332
        Top = 0
        Width = 105
        Height = 477
        Align = alRight
        TabOrder = 1
        object mDeleteMoveBtn: TArrayBotButton
          Left = 1
          Top = 241
          Width = 103
          Height = 60
          Action = RemoveProcessA
          Align = alTop
          Caption = 'X'
          ParentDoubleBuffered = True
          TabOrder = 0
          SoundID = 'BUTTON_CLICK_4'
        end
        object mMoveSequenceDownBtn: TArrayBotButton
          Left = 1
          Top = 61
          Width = 103
          Height = 60
          Align = alTop
          Caption = #9660
          ParentDoubleBuffered = True
          TabOrder = 1
          OnClick = mMoveSequenceDownBtnClick
          SoundID = 'BUTTON_CLICK_4'
        end
        object mMoveSequenceUpBtn: TArrayBotButton
          Left = 1
          Top = 1
          Width = 103
          Height = 60
          Align = alTop
          Caption = #9650
          ParentDoubleBuffered = True
          TabOrder = 2
          OnClick = mMoveSequenceUpBtnClick
          SoundID = 'BUTTON_CLICK_4'
        end
        object mRenameBtn: TArrayBotButton
          Left = 1
          Top = 121
          Width = 103
          Height = 60
          Align = alTop
          Caption = 'Rename'
          TabOrder = 3
          OnClick = mRenameBtnClick
          SoundID = 'BUTTON_CLICK_4'
        end
        object mAddMoveBtn: TArrayBotButton
          Left = 1
          Top = 181
          Width = 103
          Height = 60
          Action = AddCombinedMoveA
          Align = alTop
          Caption = 'New'
          ParentDoubleBuffered = True
          TabOrder = 4
          SoundID = 'BUTTON_CLICK_4'
        end
      end
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 504
    Width = 441
    Height = 121
    Align = alBottom
    Caption = 'Miscellaneous'
    PopupMenu = PopupMenu1
    TabOrder = 1
    object Label1: TLabel
      Left = 16
      Top = 27
      Width = 74
      Height = 23
      Caption = 'Category'
    end
    object CategoryCB: TComboBox
      Left = 16
      Top = 56
      Width = 185
      Height = 31
      TabOrder = 0
      Text = 'Preset'
      OnCloseUp = CategoryCBCloseUp
      Items.Strings = (
        'Cutting'
        'UC7'
        'Camera'
        'Setup'
        'Testing')
    end
    object NewSequenceCategoryBtn: TArrayBotButton
      Left = 232
      Top = 48
      Width = 129
      Height = 41
      Caption = 'New Category'
      TabOrder = 1
      OnClick = NewSequenceCategoryBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 625
    Width = 441
    Height = 129
    Align = alBottom
    TabOrder = 2
    object UpdateStateBtn: TArrayBotButton
      Left = 1
      Top = 1
      Width = 439
      Height = 127
      Align = alBottom
      Caption = 'Update from Current State'
      ParentDoubleBuffered = True
      TabOrder = 0
      Visible = False
      OnClick = UpdateStateBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
  end
  object mSequenceAL: TActionList
    Left = 208
    Top = 16
    object RemoveProcessA: TAction
      Caption = 'X'
      OnExecute = RemoveProcessAExecute
    end
    object AddCombinedMoveA: TAction
      Caption = 'New Master Process'
      OnExecute = AddCombinedMoveAExecute
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 176
    Top = 232
    object LogXML1: TMenuItem
      Caption = 'Log XML'
      OnClick = LogXML1Click
    end
  end
end
