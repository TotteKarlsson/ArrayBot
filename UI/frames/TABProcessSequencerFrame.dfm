object ABProcessSequencerFrame: TABProcessSequencerFrame
  Left = 0
  Top = 0
  Width = 1001
  Height = 652
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
    Width = 1001
    Height = 490
    Align = alTop
    TabOrder = 0
    ExplicitWidth = 878
    inline TCombinedMoveFrame1: TCombinedMoveFrame
      Left = 292
      Top = 25
      Width = 530
      Height = 463
      AutoSize = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      ExplicitLeft = 292
      ExplicitTop = 25
      ExplicitHeight = 463
      inherited TMotorMoveProcessFrame1: TMotorMoveProcessFrame
        Height = 463
        ExplicitHeight = 463
        inherited MainGB: TGroupBox
          Height = 463
          inherited mMovePosE: TFloatLabeledEdit
            EditLabel.ExplicitLeft = 0
            EditLabel.ExplicitTop = -26
            EditLabel.ExplicitWidth = 99
            OnKeyDown = nil
          end
          inherited mMaxVelE: TFloatLabeledEdit
            EditLabel.ExplicitLeft = 0
            EditLabel.ExplicitTop = -26
            EditLabel.ExplicitWidth = 86
            OnKeyDown = nil
          end
          inherited mAccE: TFloatLabeledEdit
            EditLabel.ExplicitLeft = 0
            EditLabel.ExplicitTop = -26
            EditLabel.ExplicitWidth = 56
            OnKeyDown = nil
          end
          inherited mPostDwellTimeE: TFloatLabeledEdit
            EditLabel.ExplicitLeft = 0
            EditLabel.ExplicitTop = -26
            EditLabel.ExplicitWidth = 147
            OnKeyDown = nil
          end
          inherited MotorsCB: TComboBox
            OnChange = nil
            OnClick = nil
          end
          inherited mPreDwellTimeE: TFloatLabeledEdit
            EditLabel.ExplicitLeft = 0
            EditLabel.ExplicitTop = -26
            EditLabel.ExplicitWidth = 140
            OnKeyDown = nil
          end
        end
      end
      inherited GroupBox1: TGroupBox
        Height = 463
      end
    end
    object GroupBox2: TGroupBox
      Left = 2
      Top = 25
      Width = 290
      Height = 463
      Align = alLeft
      Caption = 'Sequences'
      Padding.Top = 10
      TabOrder = 1
      ExplicitLeft = 9
      ExplicitTop = 3
      object mAddMoveBtn: TButton
        Left = 13
        Top = 303
        Width = 200
        Height = 50
        Action = addCombinedMovesProcessA
        TabOrder = 0
      end
      object mAddSeqBtn: TButton
        Left = 13
        Top = 32
        Width = 53
        Height = 44
        Caption = 'Add'
        TabOrder = 1
        OnClick = mAddSeqBtnClick
      end
      object mDeleteMoveBtn: TButton
        Left = 13
        Top = 409
        Width = 200
        Height = 50
        Action = removeProcessA
        TabOrder = 2
      end
      object mDeleteSequenceBtn: TButton
        Left = 72
        Top = 32
        Width = 74
        Height = 44
        Caption = 'Delete'
        TabOrder = 3
        OnClick = mDeleteSequenceBtnClick
      end
      object mProcessesLB: TListBox
        Left = 13
        Top = 195
        Width = 200
        Height = 102
        ItemHeight = 23
        TabOrder = 4
        OnClick = mProcessesLBClick
      end
      object mSaveSequenceBtn: TButton
        Left = 152
        Top = 32
        Width = 61
        Height = 44
        Caption = 'Save'
        TabOrder = 5
        OnClick = mSaveSequenceBtnClick
      end
      object mSequencesCB: TComboBox
        Left = 13
        Top = 82
        Width = 200
        Height = 31
        Style = csDropDownList
        ItemIndex = 0
        TabOrder = 6
        Text = 'MoveSequence'
        OnChange = mSequencesCBChange
        Items.Strings = (
          'MoveSequence')
      end
      object mSequenceNameE: mtkSTDStringEdit
        Left = 13
        Top = 158
        Width = 200
        Height = 31
        EditLabel.Width = 49
        EditLabel.Height = 23
        EditLabel.Caption = 'Name'
        TabOrder = 7
        Text = '<none>'
        OnKeyDown = mSequenceNameEKeyDown
        Value = '<none>'
      end
      object Button1: TButton
        Left = 13
        Top = 356
        Width = 200
        Height = 50
        Action = addTimeDelayProcess
        TabOrder = 8
      end
    end
    inline TTimeDelayFrame1: TTimeDelayFrame
      Left = 297
      Top = 121
      Width = 313
      Height = 463
      AutoSize = True
      TabOrder = 2
      ExplicitLeft = 297
      ExplicitTop = 121
      ExplicitHeight = 463
      inherited GroupBox1: TGroupBox
        Height = 463
        ExplicitLeft = -160
        ExplicitTop = 115
        ExplicitHeight = 463
        inherited mTimeDelayE: TIntegerLabeledEdit
          Height = 31
          EditLabel.Width = 137
          EditLabel.Height = 23
          EditLabel.ExplicitTop = 30
          EditLabel.ExplicitWidth = 137
          EditLabel.ExplicitHeight = 23
          ExplicitHeight = 31
        end
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 490
    Width = 1001
    Height = 95
    Align = alTop
    TabOrder = 1
    object mStatusLbl: TLabel
      Left = 154
      Top = 35
      Width = 148
      Height = 23
      Caption = 'Sequencer Status'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object mStartBtn: TButton
      Left = 1
      Top = 1
      Width = 112
      Height = 93
      Align = alLeft
      Caption = 'Start'
      TabOrder = 0
      OnClick = mStartBtnClick
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
      Caption = 'Add Combined Move'
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
