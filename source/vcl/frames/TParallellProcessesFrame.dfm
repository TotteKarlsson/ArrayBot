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
    Caption = 'Sub Processes'
    TabOrder = 0
    ExplicitHeight = 526
    object GroupBox1: TGroupBox
      Left = 2
      Top = 109
      Width = 145
      Height = 420
      Align = alLeft
      Caption = 'Processes'
      TabOrder = 0
      ExplicitHeight = 415
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
    object Panel1: TPanel
      Left = 2
      Top = 25
      Width = 719
      Height = 84
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object mProcessNameE: TSTDStringLabeledEdit
        Left = 13
        Top = 35
        Width = 197
        Height = 31
        EditLabel.Width = 49
        EditLabel.Height = 23
        EditLabel.Caption = 'Name'
        TabOrder = 0
        OnKeyDown = mProcessNameEKeyDown
      end
    end
    inline TMotorMoveProcessFrame1: TMotorMoveProcessFrame
      Left = 147
      Top = 109
      Width = 574
      Height = 420
      Align = alClient
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      ExplicitLeft = 147
      ExplicitTop = 109
      ExplicitWidth = 574
      ExplicitHeight = 415
      inherited MainGB: TGroupBox
        Width = 574
        Height = 171
        ExplicitWidth = 574
        ExplicitHeight = 171
        inherited mMovePosE: TFloatLabeledEdit
          TabOrder = 1
        end
        inherited mMaxVelE: TFloatLabeledEdit
          EditLabel.ExplicitLeft = 0
          EditLabel.ExplicitTop = -26
          EditLabel.ExplicitWidth = 86
          TabOrder = 2
        end
        inherited mAccE: TFloatLabeledEdit
          EditLabel.ExplicitLeft = 0
          EditLabel.ExplicitTop = -26
          EditLabel.ExplicitWidth = 56
          TabOrder = 3
        end
        inherited MotorsCB: TComboBox
          TabOrder = 0
        end
        inherited mAddTriggerBtn: TButton
          Left = 360
          Top = 49
          Height = 108
          ExplicitLeft = 360
          ExplicitTop = 49
          ExplicitHeight = 108
        end
      end
      inherited mTriggerPanel: TPanel
        Top = 171
        Width = 574
        Height = 249
        inherited GroupBox1: TGroupBox
          Width = 160
          Height = 247
          ExplicitWidth = 160
          ExplicitHeight = 247
          inherited mTriggersLB: TListBox
            Width = 156
            Height = 160
          end
          inherited Panel1: TPanel
            Top = 185
            Width = 156
            ExplicitLeft = 2
            ExplicitTop = 22
            ExplicitWidth = 196
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
  end
end
