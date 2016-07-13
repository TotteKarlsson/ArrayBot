object ABProcessSequencerFrame: TABProcessSequencerFrame
  Left = 0
  Top = 0
  Width = 673
  Height = 408
  AutoSize = True
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 673
    Height = 364
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
      Height = 347
      Align = alLeft
      AutoSize = True
      TabOrder = 1
      ExplicitLeft = 161
      ExplicitTop = 15
      ExplicitHeight = 347
      inherited GroupBox1: TGroupBox [0]
        Height = 347
        Caption = 'Combined Moves'
        ExplicitHeight = 347
      end
      inherited TMotorMoveProcessFrame1: TMotorMoveProcessFrame [1]
        Height = 347
        ExplicitHeight = 347
        inherited MainGB: TGroupBox
          Height = 347
          ExplicitHeight = 347
        end
      end
    end
    object GroupBox2: TGroupBox
      Left = 2
      Top = 15
      Width = 159
      Height = 347
      Align = alLeft
      Caption = 'Sequences'
      TabOrder = 2
      object mAddMoveBtn: TButton
        Left = 8
        Top = 193
        Width = 135
        Height = 25
        Action = addCombinedMovesProcessA
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
        Left = 8
        Top = 255
        Width = 135
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
        Width = 45
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
        Width = 135
        Height = 21
        EditLabel.Width = 77
        EditLabel.Height = 13
        EditLabel.Caption = 'Sequence Name'
        TabOrder = 7
        Text = '<none>'
        OnKeyDown = mSequenceNameEKeyDown
        Value = '<none>'
      end
      object Button1: TButton
        Left = 8
        Top = 224
        Width = 135
        Height = 25
        Action = addTimeDelayProcess
        TabOrder = 8
      end
    end
    inline TTimeDelayFrame1: TTimeDelayFrame
      Left = 523
      Top = 15
      Width = 137
      Height = 347
      Align = alLeft
      AutoSize = True
      TabOrder = 3
      ExplicitLeft = 350
      ExplicitTop = 279
      inherited GroupBox1: TGroupBox
        Height = 347
        ExplicitHeight = 207
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 364
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
    Left = 608
    Top = 192
  end
  object Actions: TActionList
    Left = 544
    Top = 176
    object addCombinedMovesProcessA: TAction
      Caption = 'Add Combined Moves'
      OnExecute = addCombinedMovesProcessAExecute
    end
    object removeProcessA: TAction
      Caption = 'Remove Current'
      OnExecute = removeProcessAExecute
    end
    object addTimeDelayProcess: TAction
      Caption = 'Add TimeDelay'
      OnExecute = addTimeDelayProcessExecute
    end
  end
end
