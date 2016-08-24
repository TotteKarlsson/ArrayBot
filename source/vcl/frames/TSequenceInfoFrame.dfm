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
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 286
    Height = 448
    Align = alClient
    TabOrder = 0
    object GroupBox3: TPanel
      Left = 2
      Top = 25
      Width = 282
      Height = 67
      Align = alTop
      BevelEdges = [beLeft, beRight, beBottom]
      BevelOuter = bvNone
      ParentColor = True
      TabOrder = 0
      object mSequenceNameE: TSTDStringLabeledEdit
        Left = 13
        Top = 24
        Width = 200
        Height = 31
        BevelEdges = [beLeft, beRight, beBottom]
        BevelInner = bvNone
        BevelOuter = bvNone
        EditLabel.Width = 49
        EditLabel.Height = 23
        EditLabel.Caption = 'Name'
        TabOrder = 0
        Text = '<none>'
        Value = '<none>'
      end
    end
    object mAddMoveBtn: TButton
      Left = 15
      Top = 266
      Width = 260
      Height = 50
      Action = AddCombinedMoveA
      Caption = 'New'
      TabOrder = 1
    end
    object GroupBox2: TGroupBox
      Left = 2
      Top = 92
      Width = 282
      Height = 155
      Align = alTop
      Caption = 'Processes'
      TabOrder = 2
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
    end
  end
  object mSequenceAL: TActionList
    Left = 224
    Top = 24
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
