object SequenceInfoFrame: TSequenceInfoFrame
  Left = 0
  Top = 0
  Width = 286
  Height = 448
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object mMainGB: TGroupBox
    Left = 0
    Top = 0
    Width = 286
    Height = 448
    Align = alClient
    TabOrder = 0
    object GroupBox2: TGroupBox
      Left = 2
      Top = 25
      Width = 282
      Height = 296
      Align = alTop
      Caption = 'Processes'
      TabOrder = 0
      object mDeleteMoveBtn: TButton
        Left = 219
        Top = 26
        Width = 54
        Height = 34
        Action = RemoveProcessA
        TabOrder = 0
      end
      object mMoveSequenceDownBtn: TButton
        Left = 219
        Top = 105
        Width = 54
        Height = 34
        Caption = #9660
        TabOrder = 1
        OnClick = mMoveSequenceDownBtnClick
      end
      object mMoveSequenceUpBtn: TButton
        Left = 219
        Top = 63
        Width = 54
        Height = 36
        Caption = #9650
        TabOrder = 2
        OnClick = mMoveSequenceUpBtnClick
      end
      object mProcessesLB: TListBox
        Left = 13
        Top = 26
        Width = 200
        Height = 118
        ItemHeight = 23
        TabOrder = 3
        OnClick = mProcessesLBClick
      end
      object mAddMoveBtn: TButton
        Left = 13
        Top = 150
        Width = 148
        Height = 50
        Action = AddCombinedMoveA
        Caption = 'New Process'
        TabOrder = 4
      end
      object mRenameBtn: TArrayBotButton
        Left = 176
        Top = 150
        Width = 97
        Height = 51
        Caption = 'Rename'
        TabOrder = 5
        OnClick = mRenameBtnClick
        SoundID = 'BUTTON_CLICK_1'
      end
    end
    object mUpdatePositionsBtn: TButton
      Left = 25
      Top = 346
      Width = 228
      Height = 72
      TabOrder = 1
      OnClick = mUpdatePositionsBtnClick
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
end
