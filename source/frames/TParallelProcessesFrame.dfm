object ParallelProcessesFrame: TParallelProcessesFrame
  Left = 0
  Top = 0
  Width = 233
  Height = 593
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
    Height = 593
    Align = alLeft
    Caption = 'Actions'
    TabOrder = 0
    object mSubProcessesLB: TListBox
      Left = 2
      Top = 25
      Width = 229
      Height = 199
      Align = alClient
      ItemHeight = 23
      TabOrder = 0
      OnClick = SubProcessesLBClick
    end
    object Panel1: TPanel
      Left = 2
      Top = 224
      Width = 229
      Height = 367
      Align = alBottom
      TabOrder = 1
      DesignSize = (
        229
        367)
      object Button1: TButton
        Left = 13
        Top = 22
        Width = 200
        Height = 60
        Action = addMoveA
        Anchors = [akLeft, akTop, akRight]
        Caption = 'New Move'
        TabOrder = 0
      end
      object Button2: TButton
        Left = 13
        Top = 224
        Width = 200
        Height = 60
        Action = removeMoveA
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 1
      end
      object Button3: TButton
        Left = 13
        Top = 157
        Width = 200
        Height = 60
        Action = newArrayCamRequestA
        Anchors = [akLeft, akTop, akRight]
        Caption = 'ArrayCam Request'
        TabOrder = 2
      end
      object mRenameBtn: TArrayBotButton
        Left = 13
        Top = 292
        Width = 200
        Height = 60
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Rename'
        TabOrder = 3
        OnClick = mRenameBtnClick
        SoundID = 'BUTTON_CLICK_4'
      end
      object ArrayBotButton1: TArrayBotButton
        Left = 13
        Top = 89
        Width = 200
        Height = 60
        Action = HomeMotorA
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Home Motor'
        TabOrder = 4
        SoundID = 'BUTTON_CLICK_4'
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
