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
    Align = alTop
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
    Align = alTop
    TabOrder = 1
    inline TTimeDelayFrame1: TTimeDelayFrame
      Left = 233
      Top = 1
      Width = 767
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
      ExplicitLeft = 233
      ExplicitTop = 1
      ExplicitWidth = 767
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
      Width = 232
      Height = 528
      Align = alLeft
      TabOrder = 1
      object GroupBox1: TGroupBox
        Left = 1
        Top = 129
        Width = 230
        Height = 398
        Align = alClient
        Caption = 'Sequence'
        TabOrder = 0
        object mDeleteMoveBtn: TButton
          Left = 13
          Top = 199
          Width = 200
          Height = 50
          Action = removeProcessA
          TabOrder = 0
        end
        object mProcessesLB: TListBox
          Left = 13
          Top = 91
          Width = 200
          Height = 102
          ItemHeight = 23
          TabOrder = 1
          OnClick = mProcessesLBClick
        end
        object mSequenceNameE: mtkSTDStringEdit
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
          Top = 255
          Width = 200
          Height = 50
          Action = addTimeDelayProcess
          TabOrder = 3
        end
        object mAddMoveBtn: TButton
          Left = 13
          Top = 317
          Width = 200
          Height = 50
          Action = addCombinedMovesProcessA
          TabOrder = 4
        end
      end
      object GroupBox2: TGroupBox
        Left = 1
        Top = 1
        Width = 230
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
      Left = 233
      Top = 1
      Width = 767
      Height = 528
      Align = alClient
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      ExplicitLeft = 233
      ExplicitTop = 1
      ExplicitWidth = 767
      ExplicitHeight = 528
      inherited GroupBox2: TGroupBox
        Width = 767
        Height = 528
        ExplicitWidth = 767
        ExplicitHeight = 528
        inherited GroupBox1: TGroupBox
          Height = 417
          ExplicitHeight = 417
        end
        inherited Panel1: TPanel
          Width = 763
          ExplicitWidth = 763
          inherited mProcessNameE: TSTDStringLabeledEdit
            OnKeyDown = TCombinedMoveFrame1mProcessNameEKeyDown
          end
        end
        inherited TMotorMoveProcessFrame1: TMotorMoveProcessFrame
          Width = 618
          Height = 417
          ExplicitWidth = 618
          ExplicitHeight = 417
          inherited PageControl1: TPageControl
            Width = 618
            Height = 417
            ExplicitWidth = 618
            ExplicitHeight = 417
            inherited mTriggersSheet: TTabSheet
              ExplicitWidth = 610
              ExplicitHeight = 379
              inherited Panel2: TPanel
                Height = 379
                ExplicitHeight = 379
                inherited Panel1: TPanel
                  Top = 318
                  ExplicitTop = 318
                  ExplicitWidth = 183
                  inherited mDeleteTriggerB: TButton
                    ExplicitLeft = 91
                  end
                  inherited mAddTriggerB: TButton
                    ExplicitLeft = 1
                    ExplicitTop = 1
                  end
                end
                inherited mTriggersLB: TListBox
                  Height = 317
                  ExplicitHeight = 317
                end
              end
            end
            inherited TabSheet3: TTabSheet
              ExplicitWidth = 443
              ExplicitHeight = 266
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
