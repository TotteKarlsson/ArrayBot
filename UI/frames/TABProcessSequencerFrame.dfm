object ABProcessSequencerFrame: TABProcessSequencerFrame
  Left = 0
  Top = 0
  Width = 673
  Height = 285
  AutoSize = True
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 673
    Height = 241
    Align = alTop
    Caption = 'Move Sequencer'
    TabOrder = 0
    object mStartBtn: TButton
      Left = 576
      Top = 25
      Width = 81
      Height = 65
      Caption = 'Start'
      TabOrder = 0
      OnClick = mStartBtnClick
    end
    inline TCombinedMoveFrame1: TCombinedMoveFrame
      Left = 161
      Top = 15
      Width = 362
      Height = 224
      Align = alLeft
      AutoSize = True
      TabOrder = 1
      ExplicitLeft = 161
      ExplicitTop = 15
      ExplicitHeight = 224
      inherited GroupBox1: TGroupBox [0]
        Height = 224
        ExplicitHeight = 224
      end
      inherited TMotorMoveProcessFrame1: TMotorMoveProcessFrame [1]
        Height = 224
        ExplicitHeight = 224
        inherited MainGB: TGroupBox
          Height = 224
          ExplicitHeight = 224
        end
      end
    end
    object GroupBox2: TGroupBox
      Left = 2
      Top = 15
      Width = 159
      Height = 224
      Align = alLeft
      Caption = 'Sequences'
      TabOrder = 2
      object mAddMoveBtn: TButton
        Left = 8
        Top = 191
        Width = 57
        Height = 25
        Action = addProcessA
        TabOrder = 0
      end
      object mAddSeqBtn: TButton
        Left = 8
        Top = 18
        Width = 41
        Height = 28
        Caption = 'Add'
        TabOrder = 1
        OnClick = mAddSeqBtnClick
      end
      object mDeleteMoveBtn: TButton
        Left = 88
        Top = 191
        Width = 56
        Height = 25
        Action = removeProcessA
        TabOrder = 2
      end
      object mDeleteSequenceBtn: TButton
        Left = 55
        Top = 18
        Width = 41
        Height = 28
        Caption = 'Delete'
        TabOrder = 3
        OnClick = mDeleteSequenceBtnClick
      end
      object mProcessesLB: TListBox
        Left = 8
        Top = 127
        Width = 135
        Height = 60
        ItemHeight = 13
        TabOrder = 4
        OnClick = mProcessesLBClick
      end
      object mSaveSequenceBtn: TButton
        Left = 98
        Top = 18
        Width = 41
        Height = 28
        Caption = 'Save'
        TabOrder = 5
        OnClick = mSaveSequenceBtnClick
      end
      object mSequencesCB: TComboBox
        Left = 8
        Top = 52
        Width = 135
        Height = 21
        Style = csDropDownList
        ItemIndex = 0
        TabOrder = 6
        Text = 'MoveSequence'
        OnChange = mSequencesCBChange
        Items.Strings = (
          'MoveSequence')
      end
      object mSequenceNameE: mtkSTDStringEdit
        Left = 8
        Top = 100
        Width = 121
        Height = 21
        EditLabel.Width = 77
        EditLabel.Height = 13
        EditLabel.Caption = 'Sequence Name'
        TabOrder = 7
        Text = '<none>'
        OnKeyDown = mSequenceNameEKeyDown
        Value = '<none>'
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 241
    Width = 673
    Height = 44
    Align = alTop
    TabOrder = 1
    object mStatusLbl: TLabel
      Left = 15
      Top = 11
      Width = 52
      Height = 23
      Caption = 'Status'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
  end
  object mSequenceStatusTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = mSequenceTimerTimer
    Left = 496
    Top = 32
  end
  object Actions: TActionList
    Left = 584
    Top = 160
    object addProcessA: TAction
      Caption = 'Add'
      OnExecute = addProcessAExecute
    end
    object removeProcessA: TAction
      Caption = 'Remove'
      OnExecute = removeProcessAExecute
    end
  end
end
