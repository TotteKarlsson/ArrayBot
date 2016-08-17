object CombinedMoveFrame: TCombinedMoveFrame
  Left = 0
  Top = 0
  Width = 723
  Height = 526
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
    Height = 526
    Align = alClient
    Caption = 'Parallell Processes'
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 2
      Top = 109
      Width = 145
      Height = 415
      Align = alLeft
      Caption = 'Moves'
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
      Height = 415
      Align = alClient
      AutoSize = True
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
      inherited PageControl1: TPageControl
        Width = 574
        Height = 415
        ExplicitWidth = 574
        ExplicitHeight = 415
        inherited TabSheet1: TTabSheet
          ExplicitWidth = 566
          ExplicitHeight = 377
          inherited MainGB: TGroupBox
            Width = 566
            Height = 377
            ExplicitWidth = 566
            ExplicitHeight = 377
            inherited mMovePosE: TFloatLabeledEdit
              Width = 65
              ExplicitWidth = 65
            end
          end
        end
        inherited mTriggersSheet: TTabSheet
          inherited Panel2: TPanel
            inherited Panel1: TPanel
              ExplicitTop = 316
            end
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
