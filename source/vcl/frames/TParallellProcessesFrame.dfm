object ParallellProcessesFrame: TParallellProcessesFrame
  Left = 0
  Top = 0
  Width = 663
  Height = 489
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
    Height = 489
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
      Top = 324
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
      Top = 396
      Width = 118
      Height = 60
      Caption = 'Rename'
      TabOrder = 3
      OnClick = mRenameBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
    object Button3: TButton
      Left = 13
      Top = 248
      Width = 118
      Height = 60
      Action = addArduinoCommandA
      TabOrder = 4
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
    object addArduinoCommandA: TAction
      Caption = 'Command'
      OnExecute = addArduinoCommandAExecute
    end
  end
end
