object ParallelProcessesFrame: TParallelProcessesFrame
  Left = 0
  Top = 0
  Width = 233
  Height = 732
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
    Width = 233
    Height = 732
    Align = alLeft
    Caption = 'Actions'
    TabOrder = 0
    object mSubProcessesLB: TListBox
      Left = 2
      Top = 25
      Width = 229
      Height = 303
      Align = alClient
      ItemHeight = 23
      TabOrder = 0
      OnClick = SubProcessesLBClick
    end
    object Panel1: TPanel
      Left = 2
      Top = 328
      Width = 229
      Height = 402
      Align = alBottom
      TabOrder = 1
      DesignSize = (
        229
        402)
      object Button2: TButton
        Left = 13
        Top = 71
        Width = 200
        Height = 60
        Action = removeMoveA
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 0
      end
      object mRenameBtn: TArrayBotButton
        Left = 13
        Top = 139
        Width = 200
        Height = 60
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Rename'
        TabOrder = 1
        OnClick = mRenameBtnClick
        SoundID = 'BUTTON_CLICK_4'
      end
      object Button4: TButton
        Left = 13
        Top = 3
        Width = 200
        Height = 60
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Add Process'
        TabOrder = 2
        OnClick = addProcess
      end
    end
  end
  object ActionList1: TActionList
    Left = 72
    Top = 64
    object addMoveA: TAction
      Caption = 'Add'
      OnExecute = addMoveAExecute
    end
    object removeMoveA: TAction
      Caption = 'Remove'
      OnExecute = removeMoveAExecute
    end
    object newArrayCamRequestA: TAction
      Caption = 'Command'
      OnExecute = newArrayCamRequestAExecute
    end
    object HomeMotorA: TAction
      Caption = 'Home Motor'
      OnExecute = HomeMotorAExecute
    end
  end
end
