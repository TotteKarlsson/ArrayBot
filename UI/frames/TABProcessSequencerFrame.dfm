object ABProcessSequencerFrame: TABProcessSequencerFrame
  Left = 0
  Top = 0
  Width = 1001
  Height = 625
  AutoSize = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object Panel1: TPanel
    Left = 0
    Top = 530
    Width = 1001
    Height = 95
    Align = alBottom
    TabOrder = 0
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
    object Panel2: TPanel
      Left = 584
      Top = 1
      Width = 416
      Height = 93
      Align = alRight
      TabOrder = 1
      object mStatusLbl: TLabel
        Left = 50
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
    end
    object mContinousExecutionCB: TCheckBox
      Left = 119
      Top = 12
      Width = 114
      Height = 17
      Caption = 'Continous'
      TabOrder = 2
    end
    object mRewindButton: TButton
      Left = 464
      Top = 1
      Width = 120
      Height = 93
      Align = alRight
      Caption = 'Reset'
      TabOrder = 3
      OnClick = mRewindButtonClick
    end
  end
  object mMainPanel: TPanel
    Left = 0
    Top = 0
    Width = 1001
    Height = 530
    Align = alClient
    TabOrder = 1
    object mLeftPanel: TPanel
      Left = 1
      Top = 1
      Width = 280
      Height = 528
      Align = alLeft
      TabOrder = 0
      object GroupBox2: TGroupBox
        Left = 1
        Top = 1
        Width = 278
        Height = 128
        Align = alTop
        Caption = 'Sequence'
        Padding.Top = 10
        TabOrder = 0
        object mAddSeqBtn: TButton
          Left = 13
          Top = 70
          Width = 53
          Height = 44
          Caption = 'Add'
          TabOrder = 0
          OnClick = mAddSeqBtnClick
        end
        object mDeleteSequenceBtn: TButton
          Left = 72
          Top = 70
          Width = 74
          Height = 44
          Caption = 'Delete'
          TabOrder = 1
          OnClick = mDeleteSequenceBtnClick
        end
        object mSaveSequenceBtn: TButton
          Left = 152
          Top = 70
          Width = 61
          Height = 44
          Caption = 'Save'
          TabOrder = 2
          OnClick = mSaveSequenceBtnClick
        end
        object mSequencesCB: TComboBox
          Left = 13
          Top = 33
          Width = 200
          Height = 31
          Style = csDropDownList
          ItemIndex = 0
          TabOrder = 3
          Text = 'MoveSequence'
          OnChange = mSequencesCBChange
          Items.Strings = (
            'MoveSequence')
        end
      end
      inline TSequenceInfoFrame1: TSequenceInfoFrame
        Left = 1
        Top = 129
        Width = 278
        Height = 398
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        ExplicitLeft = 1
        ExplicitTop = 129
        ExplicitWidth = 278
        ExplicitHeight = 398
        inherited GroupBox1: TGroupBox
          Width = 278
          Height = 398
          ExplicitWidth = 278
          ExplicitHeight = 398
          inherited GroupBox3: TPanel
            Width = 274
            ExplicitTop = 25
            ExplicitWidth = 274
            inherited mSequenceNameE: TSTDStringLabeledEdit
              OnKeyDown = mSequenceNameEKeyDown
            end
          end
          inherited GroupBox2: TGroupBox
            Width = 274
            ExplicitWidth = 274
          end
        end
      end
    end
    object mProcessPanel: TPanel
      Left = 281
      Top = 1
      Width = 719
      Height = 528
      Align = alClient
      TabOrder = 1
    end
  end
  object mSequenceStatusTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = mSequenceTimerTimer
    Left = 320
    Top = 560
  end
  object Actions: TActionList
    Left = 616
    Top = 40
    object addCombinedMovesProcessA: TAction
      Caption = 'Add Combined Move'
    end
    object addTimeDelayProcess: TAction
      Caption = 'Add TimeDelay'
    end
    object removeProcessA: TAction
      Caption = #10005
    end
  end
end
