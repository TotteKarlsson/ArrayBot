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
    object Label1: TLabel
      Left = 16
      Top = 26
      Width = 52
      Height = 13
      Caption = 'Sequences'
    end
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
    object mProcessesLB: TListBox
      Left = 16
      Top = 105
      Width = 97
      Height = 97
      ItemHeight = 13
      TabOrder = 1
      OnClick = mProcessesLBClick
    end
    object mSequencesCB: TComboBox
      Left = 16
      Top = 78
      Width = 136
      Height = 21
      ItemIndex = 0
      TabOrder = 2
      Text = 'MoveSequence'
      OnChange = mSequencesCBChange
      Items.Strings = (
        'MoveSequence')
    end
    object mSaveSequenceBtn: TButton
      Left = 110
      Top = 44
      Width = 41
      Height = 28
      Caption = 'Save'
      TabOrder = 3
      OnClick = mSaveSequenceBtnClick
    end
    object mAddMoveBtn: TButton
      Left = 14
      Top = 208
      Width = 35
      Height = 25
      Action = addProcessA
      TabOrder = 4
    end
    object mDeleteSequenceBtn: TButton
      Left = 63
      Top = 44
      Width = 41
      Height = 28
      Caption = 'Delete'
      TabOrder = 5
      OnClick = mDeleteSequenceBtnClick
    end
    object mAddSeqBtn: TButton
      Left = 16
      Top = 44
      Width = 41
      Height = 28
      Caption = 'Add'
      TabOrder = 6
      OnClick = mAddSeqBtnClick
    end
    object mDeleteMoveBtn: TButton
      Left = 64
      Top = 208
      Width = 49
      Height = 25
      Action = removeProcessA
      TabOrder = 7
    end
    object Button1: TButton
      Left = 132
      Top = 208
      Width = 33
      Height = 25
      Action = addMotorAction
      TabOrder = 8
    end
    object mMoveMotorLB: TListBox
      Left = 132
      Top = 105
      Width = 105
      Height = 97
      ItemHeight = 13
      TabOrder = 9
    end
    inline TMotorMoveProcessFrame1: TMotorMoveProcessFrame
      Left = 317
      Top = 20
      Width = 242
      Height = 207
      AutoSize = True
      TabOrder = 10
      ExplicitLeft = 317
      ExplicitTop = 20
    end
    object Button2: TButton
      Left = 171
      Top = 208
      Width = 54
      Height = 25
      Action = removeMotorA
      TabOrder = 11
    end
  end
  object mSequenceStatusTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = mSequenceTimerTimer
    Left = 240
    Top = 32
  end
  object Actions: TActionList
    Left = 280
    Top = 104
    object addMotorAction: TAction
      Caption = 'Add'
    end
    object removeMotorA: TAction
      Caption = 'Remove'
    end
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
