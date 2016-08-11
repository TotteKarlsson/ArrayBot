object MotorMoveProcessFrame: TMotorMoveProcessFrame
  Left = 0
  Top = 0
  Width = 451
  Height = 304
  Align = alClient
  AutoSize = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 451
    Height = 304
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Move Parameters'
      object MainGB: TGroupBox
        Left = 0
        Top = 0
        Width = 443
        Height = 266
        Align = alClient
        Caption = 'MotorMove Process'
        TabOrder = 0
        object mHaveTriggerLabel: TLabel
          Left = 272
          Top = 176
          Width = 6
          Height = 23
        end
        object mMovePosE: TFloatLabeledEdit
          Left = 16
          Top = 126
          Width = 89
          Height = 31
          EditLabel.Width = 63
          EditLabel.Height = 23
          EditLabel.Caption = 'Position'
          TabOrder = 0
          Text = '0.0'
          OnKeyDown = mMovePosEKeyDown
        end
        object mMaxVelE: TFloatLabeledEdit
          Left = 144
          Top = 126
          Width = 89
          Height = 31
          EditLabel.Width = 103
          EditLabel.Height = 23
          EditLabel.Caption = 'Max Velocity'
          TabOrder = 1
          Text = '0.0'
          OnKeyDown = mMovePosEKeyDown
        end
        object mAccE: TFloatLabeledEdit
          Left = 272
          Top = 126
          Width = 81
          Height = 31
          EditLabel.Width = 101
          EditLabel.Height = 23
          EditLabel.Caption = 'Acceleration'
          TabOrder = 2
          Text = '0.0'
          OnKeyDown = mMovePosEKeyDown
        end
        object MotorsCB: TComboBox
          Left = 16
          Top = 49
          Width = 281
          Height = 31
          Style = csDropDownList
          TabOrder = 3
          OnChange = MotorsCBChange
          OnClick = MotorsCBClick
        end
        object mAddTriggerB: TButton
          Left = 16
          Top = 176
          Width = 137
          Height = 58
          Caption = 'Add Trigger'
          TabOrder = 4
          OnClick = AddTriggerBClick
        end
      end
    end
    object mTriggersSheet: TTabSheet
      Caption = 'Triggers'
      ImageIndex = 1
      TabVisible = False
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 185
        Height = 266
        Align = alLeft
        Caption = 'Panel2'
        TabOrder = 0
        object Panel1: TPanel
          Left = 1
          Top = 205
          Width = 183
          Height = 60
          Align = alBottom
          TabOrder = 0
          ExplicitTop = 337
          object mDeleteTriggerB: TButton
            Left = 1
            Top = 1
            Width = 90
            Height = 58
            Align = alLeft
            Caption = 'Delete'
            TabOrder = 0
            OnClick = mDeleteTriggerBClick
          end
        end
        object mTriggersLB: TListBox
          Left = 1
          Top = 1
          Width = 183
          Height = 204
          Align = alClient
          ItemHeight = 23
          TabOrder = 1
          OnClick = TriggersLBClick
        end
      end
    end
  end
end
