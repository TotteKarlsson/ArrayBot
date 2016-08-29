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
      Width = 216
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
      Left = 305
      Top = 14
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
      Width = 304
      Height = 528
      Align = alLeft
      TabOrder = 0
      object GroupBox2: TGroupBox
        Left = 1
        Top = 1
        Width = 302
        Height = 128
        Align = alTop
        Caption = 'Select Sequence'
        Padding.Top = 10
        TabOrder = 0
        object mSequencesCB: TComboBox
          Left = 15
          Top = 33
          Width = 270
          Height = 31
          Style = csDropDownList
          ItemIndex = 0
          TabOrder = 2
          Text = 'MoveSequence'
          OnChange = mSequencesCBChange
          Items.Strings = (
            'MoveSequence')
        end
        object mAddSeqBtn: TArrayBotButton
          Left = 15
          Top = 78
          Width = 74
          Height = 44
          Caption = 'New'
          ParentDoubleBuffered = True
          TabOrder = 0
          OnClick = mAddSeqBtnClick
          SoundID = 'BUTTON_CLICK_1'
        end
        object mDeleteSequenceBtn: TArrayBotButton
          Left = 95
          Top = 78
          Width = 98
          Height = 44
          Caption = 'Delete'
          ParentDoubleBuffered = True
          TabOrder = 1
          OnClick = mDeleteSequenceBtnClick
          SoundID = 'BUTTON_CLICK_1'
        end
        object mRenameButton: TArrayBotButton
          Left = 199
          Top = 78
          Width = 86
          Height = 44
          Caption = 'Rename'
          ParentDoubleBuffered = True
          TabOrder = 3
          OnClick = mRenameButtonClick
          SoundID = 'BUTTON_CLICK_1'
        end
      end
      inline TSequenceInfoFrame1: TSequenceInfoFrame
        Left = 1
        Top = 129
        Width = 302
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
        ExplicitWidth = 302
        ExplicitHeight = 398
        inherited mMainGB: TGroupBox
          Width = 302
          Height = 398
          ExplicitWidth = 302
          ExplicitHeight = 398
          inherited GroupBox2: TGroupBox
            Width = 298
            ExplicitWidth = 298
          end
        end
        inherited mSequenceAL: TActionList
          Left = 112
          Top = 32
        end
      end
    end
    object mProcessPanel: TPanel
      Left = 305
      Top = 1
      Width = 695
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
