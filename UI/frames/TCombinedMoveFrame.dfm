object CombinedMoveFrame: TCombinedMoveFrame
  Left = 0
  Top = 0
  Width = 362
  Height = 207
  AutoSize = True
  TabOrder = 0
  inline TMotorMoveProcessFrame1: TMotorMoveProcessFrame
    Left = 137
    Top = 0
    Width = 225
    Height = 207
    Align = alLeft
    AutoSize = True
    TabOrder = 0
    ExplicitLeft = 137
    inherited MainGB: TGroupBox
      Align = alLeft
      inherited mMovePosE: TFloatLabeledEdit
        Top = 83
        EditLabel.ExplicitLeft = 16
        EditLabel.ExplicitTop = 67
        EditLabel.ExplicitWidth = 89
        ExplicitTop = 83
      end
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 137
    Height = 207
    Align = alLeft
    Caption = 'Combined Processes'
    TabOrder = 1
    object Button1: TButton
      Left = 13
      Top = 165
      Width = 58
      Height = 25
      Action = addMoveA
      TabOrder = 0
    end
    object Button2: TButton
      Left = 77
      Top = 165
      Width = 54
      Height = 25
      Action = removeMoveA
      TabOrder = 1
    end
    object mMoveLB: TListBox
      Left = 13
      Top = 20
      Width = 118
      Height = 139
      ItemHeight = 13
      TabOrder = 2
      OnClick = mMoveLBClick
    end
  end
  object ActionList1: TActionList
    Left = 32
    Top = 64
    object addMoveA: TAction
      Caption = 'Add Move'
      OnExecute = addMoveAExecute
    end
    object removeMoveA: TAction
      Caption = 'Remove'
      OnExecute = removeMoveAExecute
    end
  end
end
