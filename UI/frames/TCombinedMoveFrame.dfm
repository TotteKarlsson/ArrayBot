object CombinedMoveFrame: TCombinedMoveFrame
  Left = 0
  Top = 0
  Width = 530
  Height = 520
  AutoSize = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  inline TMotorMoveProcessFrame1: TMotorMoveProcessFrame
    Left = 145
    Top = 0
    Width = 385
    Height = 520
    Align = alLeft
    AutoSize = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    ExplicitLeft = 137
    ExplicitHeight = 207
    inherited MainGB: TGroupBox
      Height = 520
      Align = alLeft
      ExplicitHeight = 207
      inherited mMovePosE: TFloatLabeledEdit
        Top = 115
        EditLabel.ExplicitTop = 89
        ExplicitTop = 115
      end
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 145
    Height = 520
    Align = alLeft
    Caption = 'Moves'
    TabOrder = 1
    object Button1: TButton
      Left = 13
      Top = 177
      Width = 118
      Height = 60
      Action = addMoveA
      TabOrder = 0
    end
    object Button2: TButton
      Left = 13
      Top = 243
      Width = 118
      Height = 60
      Action = removeMoveA
      TabOrder = 1
    end
    object mMoveLB: TListBox
      Left = 13
      Top = 32
      Width = 118
      Height = 139
      ItemHeight = 23
      TabOrder = 2
      OnClick = mMoveLBClick
    end
  end
  object ActionList1: TActionList
    Left = 32
    Top = 64
    object addMoveA: TAction
      Caption = 'Add'
      OnExecute = addMoveAExecute
    end
    object removeMoveA: TAction
      Caption = 'Remove'
      OnExecute = removeMoveAExecute
    end
  end
end
