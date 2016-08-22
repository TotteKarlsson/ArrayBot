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
  object mMainPanel: TPanel
    Left = 0
    Top = 0
    Width = 1001
    Height = 530
    Align = alClient
    TabOrder = 1
    inline TTimeDelayFrame1: TTimeDelayFrame
      Left = 281
      Top = 1
      Width = 719
      Height = 528
      Align = alClient
      AutoSize = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      Visible = False
      ExplicitLeft = 281
      ExplicitTop = 1
      ExplicitWidth = 719
      ExplicitHeight = 528
      inherited GroupBox1: TGroupBox
        Height = 528
        ExplicitHeight = 528
        inherited mNameEdit: TSTDStringLabeledEdit
          Top = 59
          Width = 164
          EditLabel.ExplicitTop = 33
          OnKeyDown = TTimeDelayFrame1mNameEditKeyDown
          ExplicitTop = 59
          ExplicitWidth = 164
        end
      end
    end
    object mLeftPanel: TPanel
      Left = 1
      Top = 1
      Width = 280
      Height = 528
      Align = alLeft
      TabOrder = 1
      object GroupBox1: TGroupBox
        Left = 1
        Top = 129
        Width = 278
        Height = 398
        Align = alClient
        Caption = 'Sequence'
        TabOrder = 0
        object mDeleteMoveBtn: TButton
          Left = 219
          Top = 162
          Width = 54
          Height = 34
          Action = removeProcessA
          TabOrder = 0
        end
        object mProcessesLB: TListBox
          Left = 13
          Top = 91
          Width = 200
          Height = 105
          ItemHeight = 23
          MultiSelect = True
          TabOrder = 1
          OnClick = mProcessesLBClick
        end
        object mSequenceNameE: TSTDStringLabeledEdit
          Left = 13
          Top = 54
          Width = 200
          Height = 31
          EditLabel.Width = 49
          EditLabel.Height = 23
          EditLabel.Caption = 'Name'
          TabOrder = 2
          Text = '<none>'
          OnKeyDown = mSequenceNameEKeyDown
          Value = '<none>'
        end
        object Button1: TButton
          Left = 13
          Top = 231
          Width = 200
          Height = 50
          Action = addTimeDelayProcess
          TabOrder = 3
        end
        object mAddMoveBtn: TButton
          Left = 13
          Top = 293
          Width = 200
          Height = 50
          Action = addCombinedMovesProcessA
          TabOrder = 4
        end
        object mMoveSequenceUpBtn: TButton
          Left = 227
          Top = 91
          Width = 33
          Height = 25
          Caption = #9650
          TabOrder = 5
          OnClick = mMoveSequenceUpBtnClick
        end
        object mMoveSequenceDownBtn: TButton
          Left = 227
          Top = 122
          Width = 33
          Height = 25
          Caption = #9660
          TabOrder = 6
          OnClick = mMoveSequenceDownBtnClick
        end
      end
      object GroupBox2: TGroupBox
        Left = 1
        Top = 1
        Width = 278
        Height = 128
        Align = alTop
        Caption = 'Sequences'
        Padding.Top = 10
        TabOrder = 1
        object mAddSeqBtn: TButton
          Left = 13
          Top = 78
          Width = 53
          Height = 44
          Caption = 'Add'
          TabOrder = 0
          OnClick = mAddSeqBtnClick
        end
        object mDeleteSequenceBtn: TButton
          Left = 72
          Top = 78
          Width = 74
          Height = 44
          Caption = 'Delete'
          TabOrder = 1
          OnClick = mDeleteSequenceBtnClick
        end
        object mSaveSequenceBtn: TButton
          Left = 152
          Top = 78
          Width = 61
          Height = 44
          Caption = 'Save'
          TabOrder = 2
          OnClick = mSaveSequenceBtnClick
        end
        object mSequencesCB: TComboBox
          Left = 13
          Top = 41
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
    end
    inline TCombinedMoveFrame1: TCombinedMoveFrame
      Left = 281
      Top = 1
      Width = 719
      Height = 528
      Align = alClient
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      ExplicitLeft = 281
      ExplicitTop = 1
      ExplicitWidth = 719
      ExplicitHeight = 528
      inherited GroupBox2: TGroupBox
        Width = 719
        Height = 528
        ExplicitWidth = 719
        ExplicitHeight = 528
        inherited GroupBox1: TGroupBox
          Width = 175
          Height = 417
          ExplicitWidth = 175
          ExplicitHeight = 417
        end
        inherited Panel1: TPanel
          Width = 715
          ExplicitWidth = 715
          inherited mProcessNameE: TSTDStringLabeledEdit
            OnKeyDown = TCombinedMoveFrame1mProcessNameEKeyDown
          end
        end
        inherited TMotorMoveProcessFrame1: TMotorMoveProcessFrame
          Left = 177
          Width = 540
          Height = 417
          ExplicitLeft = 177
          ExplicitWidth = 540
          ExplicitHeight = 417
          inherited PageControl1: TPageControl
            Width = 540
            Height = 417
            ExplicitWidth = 540
            ExplicitHeight = 417
            inherited TabSheet1: TTabSheet
              ExplicitWidth = 532
              ExplicitHeight = 379
              inherited MainGB: TGroupBox
                Width = 532
                Height = 379
                ExplicitWidth = 532
                ExplicitHeight = 379
              end
            end
            inherited mTriggersSheet: TTabSheet
              inherited Panel2: TPanel
                inherited Panel1: TPanel
                  ExplicitTop = 205
                end
              end
            end
          end
        end
      end
    end
  end
  object mSequenceStatusTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = mSequenceTimerTimer
    Left = 728
    Top = 560
  end
  object Actions: TActionList
    Left = 616
    Top = 40
    object addCombinedMovesProcessA: TAction
      Caption = 'Add Combined Move'
      OnExecute = addCombinedMovesProcessAExecute
    end
    object removeProcessA: TAction
      Caption = #10005
      OnExecute = removeProcessAExecute
    end
    object addTimeDelayProcess: TAction
      Caption = 'Add TimeDelay'
      OnExecute = addTimeDelayProcessExecute
    end
  end
end
