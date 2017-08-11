object ABProcessSequencerFrame: TABProcessSequencerFrame
  Left = 0
  Top = 0
  Width = 1399
  Height = 821
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object Panel1: TPanel
    Left = 0
    Top = 726
    Width = 1399
    Height = 95
    Align = alBottom
    TabOrder = 1
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
      Left = 1038
      Top = 1
      Width = 360
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
    object mSteppedExecutionCB: TCheckBox
      Left = 233
      Top = 30
      Width = 304
      Height = 27
      Caption = 'Execute Process by Process'
      Checked = True
      State = cbChecked
      TabOrder = 2
    end
    object mRewindButton: TButton
      Left = 862
      Top = 1
      Width = 176
      Height = 93
      Align = alRight
      Caption = 'Reset Sequence'
      TabOrder = 3
      OnClick = mRewindButtonClick
    end
  end
  object mMainPanel: TPanel
    Left = 0
    Top = 0
    Width = 1399
    Height = 726
    Align = alClient
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 385
      Top = 1
      Height = 724
      ExplicitLeft = 433
      ExplicitTop = 2
    end
    object mLeftPanel: TPanel
      Left = 1
      Top = 1
      Width = 384
      Height = 724
      Align = alLeft
      TabOrder = 0
      object GroupBox2: TGroupBox
        Left = 1
        Top = 1
        Width = 382
        Height = 128
        Align = alTop
        Caption = 'Select Sequence'
        Padding.Top = 10
        TabOrder = 0
        DesignSize = (
          382
          128)
        object mSequencesCB: TComboBox
          Left = 15
          Top = 33
          Width = 358
          Height = 31
          Style = csDropDownList
          Anchors = [akLeft, akTop, akRight]
          ItemIndex = 0
          TabOrder = 0
          Text = 'MoveSequence'
          OnChange = mSequencesCBChange
          Items.Strings = (
            'MoveSequence')
        end
        object mAddSeqBtn: TArrayBotButton
          Left = 15
          Top = 72
          Width = 80
          Height = 44
          Anchors = [akLeft, akTop, akRight]
          Caption = 'New'
          ParentDoubleBuffered = True
          TabOrder = 1
          OnClick = mAddSeqBtnClick
          SoundID = 'BUTTON_CLICK_4'
        end
        object mDeleteSequenceBtn: TArrayBotButton
          Left = 196
          Top = 72
          Width = 80
          Height = 44
          Anchors = [akTop, akRight]
          Caption = 'Delete'
          ParentDoubleBuffered = True
          TabOrder = 2
          OnClick = mDeleteSequenceBtnClick
          SoundID = 'BUTTON_CLICK_4'
        end
        object mRenameButton: TArrayBotButton
          Left = 287
          Top = 72
          Width = 80
          Height = 44
          Anchors = [akTop, akRight]
          Caption = 'Rename'
          ParentDoubleBuffered = True
          TabOrder = 3
          OnClick = mRenameButtonClick
          SoundID = 'BUTTON_CLICK_4'
        end
        object ArrayBotButton1: TArrayBotButton
          Left = 105
          Top = 72
          Width = 80
          Height = 44
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Save'
          ParentDoubleBuffered = True
          TabOrder = 4
          OnClick = BtnClick
          SoundID = 'BUTTON_CLICK_4'
        end
      end
    end
    object mProcessPanel: TScrollBox
      Left = 388
      Top = 1
      Width = 1010
      Height = 724
      Align = alClient
      BevelInner = bvNone
      BevelOuter = bvRaised
      BorderStyle = bsNone
      Color = clBtnFace
      ParentBackground = True
      ParentColor = False
      TabOrder = 1
    end
  end
  object mSequenceStatusTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = mSequenceTimerTimer
    Left = 256
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
