object ParallellProcessesFrame: TParallellProcessesFrame
  Left = 0
  Top = 0
  Width = 723
  Height = 620
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
    Width = 145
    Height = 620
    Align = alLeft
    Caption = 'Actions'
    TabOrder = 0
    ExplicitLeft = 2
    ExplicitTop = 25
    ExplicitHeight = 593
    object Button1: TButton
      Left = 13
      Top = 182
      Width = 118
      Height = 60
      Action = addMoveA
      Caption = 'New'
      TabOrder = 0
    end
    object Button2: TButton
      Left = 13
      Top = 253
      Width = 118
      Height = 60
      Action = removeMoveA
      TabOrder = 1
    end
    object mSubProcessesLB: TListBox
      Left = 13
      Top = 37
      Width = 118
      Height = 139
      ItemHeight = 23
      TabOrder = 2
      OnClick = mSubProcessesLBClick
    end
    object mRenameBtn: TArrayBotButton
      Left = 13
      Top = 325
      Width = 118
      Height = 60
      Caption = 'Rename'
      TabOrder = 3
      OnClick = mRenameBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
  end
  inline TMotorMoveProcessFrame1: TMotorMoveProcessFrame
    Left = 145
    Top = 0
    Width = 578
    Height = 620
    Align = alClient
    AutoSize = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    ExplicitLeft = 2
    ExplicitTop = 25
    ExplicitWidth = 574
    ExplicitHeight = 593
    inherited mMainGB: TGroupBox
      Width = 578
      Height = 401
      ExplicitWidth = 578
      ExplicitHeight = 401
      inherited mActionInfo: TLabel
        Width = 544
        Height = 183
        ExplicitWidth = 570
        ExplicitHeight = 183
      end
      inherited Panel2: TPanel
        Top = 208
        Width = 544
        ExplicitTop = 208
        ExplicitWidth = 544
        inherited Label1: TLabel
          Top = 33
          ExplicitTop = 33
        end
        inherited mAccE: TFloatLabeledEdit
          Top = 126
          EditLabel.ExplicitLeft = 240
          EditLabel.ExplicitTop = 100
          EditLabel.ExplicitWidth = 101
          ExplicitTop = 126
        end
        inherited mMaxVelE: TFloatLabeledEdit
          Top = 126
          EditLabel.ExplicitLeft = 120
          EditLabel.ExplicitTop = 100
          EditLabel.ExplicitWidth = 103
          ExplicitTop = 126
        end
        inherited mMovePosE: TFloatLabeledEdit
          Top = 126
          EditLabel.ExplicitLeft = 16
          EditLabel.ExplicitTop = 100
          EditLabel.ExplicitWidth = 63
          ExplicitTop = 126
        end
        inherited MotorsCB: TComboBox
          Top = 62
          ExplicitTop = 62
        end
      end
    end
    inherited mTriggerPanel: TPanel
      Top = 401
      Width = 578
      Height = 219
      ExplicitTop = 401
      ExplicitWidth = 578
      ExplicitHeight = 219
      inherited GroupBox1: TGroupBox
        Width = 160
        Height = 217
        ExplicitWidth = 160
        ExplicitHeight = 217
        inherited mTriggersLB: TListBox
          Width = 156
          Height = 130
          ExplicitWidth = 156
          ExplicitHeight = 130
        end
        inherited Panel1: TPanel
          Top = 155
          Width = 156
          ExplicitTop = 155
          ExplicitWidth = 156
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 240
    Top = 40
    object addMoveA: TAction
      Caption = 'Add'
      OnExecute = addMoveAExecute
    end
    object removeMoveA: TAction
      Caption = 'Remove'
      OnExecute = removeMoveAExecute
    end
    object mUpdateFinalPositionsA: TAction
      Caption = 'Update Final Positions'
      OnExecute = mUpdateFinalPositionsAExecute
    end
  end
end
