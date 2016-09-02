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
    object Button1: TButton
      Left = 13
      Top = 182
      Width = 118
      Height = 60
      Action = addMoveA
      Caption = 'New'
      TabOrder = 1
    end
    object Button2: TButton
      Left = 13
      Top = 253
      Width = 118
      Height = 60
      Action = removeMoveA
      TabOrder = 2
    end
    object mSubProcessesLB: TListBox
      Left = 13
      Top = 37
      Width = 118
      Height = 139
      ItemHeight = 23
      TabOrder = 0
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
    ExplicitLeft = 145
    ExplicitWidth = 578
    ExplicitHeight = 620
    inherited mMainGB: TGroupBox
      Width = 578
      Height = 297
      TabOrder = 0
      ExplicitWidth = 578
      ExplicitHeight = 297
      inherited mActionInfo: TLabel
        Width = 544
        Height = 131
        ExplicitLeft = 17
        ExplicitTop = 25
        ExplicitWidth = 542
        ExplicitHeight = 69
      end
      inherited Panel2: TPanel
        Top = 156
        Width = 544
        Height = 139
        ExplicitTop = 134
        ExplicitWidth = 544
        ExplicitHeight = 139
        inherited Label1: TLabel
          Left = 0
          Top = 7
          ExplicitLeft = 0
          ExplicitTop = 7
        end
        inherited mAccE: TFloatLabeledEdit
          Left = 224
          Top = 100
          EditLabel.ExplicitLeft = 224
          EditLabel.ExplicitTop = 74
          EditLabel.ExplicitWidth = 101
          ExplicitLeft = 224
          ExplicitTop = 100
        end
        inherited mMaxVelE: TFloatLabeledEdit
          Left = 112
          Top = 100
          EditLabel.ExplicitLeft = 112
          EditLabel.ExplicitTop = 74
          EditLabel.ExplicitWidth = 63
          ExplicitLeft = 112
          ExplicitTop = 100
        end
        inherited mMovePosE: TFloatLabeledEdit
          Left = 0
          Top = 100
          EditLabel.ExplicitTop = 74
          EditLabel.ExplicitWidth = 108
          ExplicitLeft = 0
          ExplicitTop = 100
        end
        inherited MotorsCB: TComboBox
          Left = 0
          Top = 36
          ExplicitLeft = 0
          ExplicitTop = 36
        end
        inherited mAddTriggerBtn: TArrayBotButton
          Left = 359
          Top = 18
          ExplicitLeft = 359
          ExplicitTop = 18
        end
      end
    end
    inherited mTriggerPanel: TPanel
      Top = 297
      Width = 578
      Height = 323
      TabOrder = 1
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
          Height = 190
          ExplicitWidth = 156
          ExplicitHeight = 190
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
