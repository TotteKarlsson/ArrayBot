object ABProcessSequencerFrame: TABProcessSequencerFrame
  Left = 0
  Top = 0
  Width = 673
  Height = 241
  AutoSize = True
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 673
    Height = 241
    Caption = 'Move Sequencer'
    TabOrder = 0
    object mStatusLbl: TLabel
      Left = 576
      Top = 115
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
      Left = 203
      Top = 15
      Width = 362
      Height = 224
      Align = alLeft
      AutoSize = True
      TabOrder = 1
      ExplicitLeft = 203
      ExplicitTop = 15
      ExplicitHeight = 224
      inherited TMotorMoveProcessFrame1: TMotorMoveProcessFrame
        inherited MainGB: TGroupBox
          inherited mMovePosE: TFloatLabeledEdit
            EditLabel.ExplicitLeft = 0
            EditLabel.ExplicitTop = -16
            EditLabel.ExplicitWidth = 57
          end
        end
      end
      inherited GroupBox1: TGroupBox
        Height = 224
        ExplicitHeight = 224
      end
    end
    object GroupBox2: TGroupBox
      Left = 2
      Top = 15
      Width = 201
      Height = 224
      Align = alLeft
      Caption = 'Sequences'
      TabOrder = 2
      object mAddMoveBtn: TButton
        Left = 8
        Top = 179
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
        Top = 179
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
        Top = 78
        Width = 135
        Height = 97
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
