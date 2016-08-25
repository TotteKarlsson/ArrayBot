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
  object GroupBox2: TGroupBox
    Left = 0
    Top = 0
    Width = 723
    Height = 620
    Align = alClient
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 2
      Top = 113
      Width = 145
      Height = 505
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
    end
    inline TMotorMoveProcessFrame1: TMotorMoveProcessFrame
      Left = 147
      Top = 113
      Width = 574
      Height = 505
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
      ExplicitHeight = 505
      inherited MainGB: TGroupBox
        Width = 574
        ExplicitWidth = 574
      end
      inherited mTriggerPanel: TPanel
        Width = 574
        Height = 288
        ExplicitWidth = 574
        ExplicitHeight = 288
        inherited GroupBox1: TGroupBox
          Width = 160
          Height = 286
          ExplicitWidth = 160
          ExplicitHeight = 286
          inherited mTriggersLB: TListBox
            Width = 156
            Height = 199
            ExplicitWidth = 156
            ExplicitHeight = 199
          end
          inherited Panel1: TPanel
            Top = 224
            Width = 156
            ExplicitTop = 224
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
