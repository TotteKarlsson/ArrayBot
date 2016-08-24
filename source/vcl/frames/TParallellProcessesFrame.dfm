object ParallellProcessesFrame: TParallellProcessesFrame
  Left = 0
  Top = 0
  Width = 723
  Height = 531
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object GroupBox2: TGroupBox
    Left = 0
    Top = 0
    Width = 723
    Height = 531
    Align = alClient
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 2
      Top = 113
      Width = 145
      Height = 416
      Align = alLeft
      Caption = 'Actions'
      TabOrder = 0
      object Button1: TButton
        Left = 13
        Top = 182
        Width = 118
        Height = 60
        Action = addMoveA
        TabOrder = 0
      end
      object Button2: TButton
        Left = 13
        Top = 259
        Width = 118
        Height = 60
        Action = removeMoveA
        TabOrder = 1
      end
      object mSubProcessesLB: TListBox
        Left = 13
        Top = 32
        Width = 118
        Height = 139
        ItemHeight = 23
        TabOrder = 2
        OnClick = mSubProcessesLBClick
      end
    end
    object Panel1: TPanel
      Left = 2
      Top = 25
      Width = 719
      Height = 88
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object mProcessNameE: TSTDStringLabeledEdit
        Left = 13
        Top = 32
        Width = 356
        Height = 31
        EditLabel.Width = 117
        EditLabel.Height = 23
        EditLabel.Caption = 'Process Name'
        TabOrder = 0
        OnKeyDown = mProcessNameEKeyDown
      end
      object Button3: TButton
        Left = 505
        Top = 10
        Width = 202
        Height = 72
        Action = mUpdateFinalPositionsA
        TabOrder = 1
      end
    end
    inline TMotorMoveProcessFrame1: TMotorMoveProcessFrame
      Left = 147
      Top = 113
      Width = 574
      Height = 416
      Align = alClient
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      ExplicitLeft = 147
      ExplicitTop = 113
      ExplicitWidth = 574
      ExplicitHeight = 416
      inherited MainGB: TGroupBox
        Width = 574
        Height = 171
        ExplicitWidth = 574
        ExplicitHeight = 171
        inherited mMovePosE: TFloatLabeledEdit
          TabOrder = 1
        end
        inherited mMaxVelE: TFloatLabeledEdit
          TabOrder = 2
        end
        inherited mAccE: TFloatLabeledEdit
          TabOrder = 3
        end
        inherited MotorsCB: TComboBox
          TabOrder = 0
        end
        inherited mAddTriggerBtn: TButton
          Left = 360
          Width = 201
          Caption = 'Add Child Action'
          ExplicitLeft = 360
          ExplicitWidth = 201
        end
      end
      inherited mTriggerPanel: TPanel
        Top = 171
        Width = 574
        Height = 245
        ExplicitTop = 171
        ExplicitWidth = 574
        ExplicitHeight = 245
        inherited GroupBox1: TGroupBox
          Width = 160
          Height = 243
          ExplicitWidth = 160
          ExplicitHeight = 243
          inherited mTriggersLB: TListBox
            Width = 156
            Height = 156
            ExplicitWidth = 156
            ExplicitHeight = 156
          end
          inherited Panel1: TPanel
            Top = 181
            Width = 156
            ExplicitTop = 181
            ExplicitWidth = 156
          end
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
