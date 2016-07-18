object MotorMoveProcessFrame: TMotorMoveProcessFrame
  Left = 0
  Top = 0
  Width = 623
  Height = 338
  Align = alClient
  AutoSize = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  ExplicitWidth = 451
  ExplicitHeight = 304
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 623
    Height = 338
    ActivePage = mTriggersSheet
    Align = alClient
    TabOrder = 0
    ExplicitWidth = 451
    ExplicitHeight = 304
    object TabSheet1: TTabSheet
      Caption = 'Move Parameters'
      object MainGB: TGroupBox
        Left = 0
        Top = 0
        Width = 801
        Height = 417
        Caption = 'MotorMove Process'
        TabOrder = 0
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
          Left = 16
          Top = 199
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
          Left = 216
          Top = 199
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
      end
    end
    object mTriggersSheet: TTabSheet
      Caption = 'Triggers'
      ImageIndex = 1
      ExplicitWidth = 443
      ExplicitHeight = 266
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 185
        Height = 300
        Align = alLeft
        Caption = 'Panel2'
        TabOrder = 0
        ExplicitHeight = 266
        object Panel1: TPanel
          Left = 1
          Top = 239
          Width = 183
          Height = 60
          Align = alBottom
          TabOrder = 0
          ExplicitTop = 205
          object mDeleteTriggerB: TButton
            Left = 91
            Top = 1
            Width = 90
            Height = 58
            Align = alLeft
            Caption = 'Delete'
            TabOrder = 0
            OnClick = mDeleteTriggerBClick
            ExplicitLeft = 1
          end
          object mAddTriggerB: TButton
            Left = 1
            Top = 1
            Width = 90
            Height = 58
            Align = alLeft
            Caption = 'Add'
            TabOrder = 1
            OnClick = mAddTriggerBClick
            ExplicitLeft = -5
            ExplicitTop = 6
          end
        end
        object mTriggersLB: TListBox
          Left = 1
          Top = 1
          Width = 183
          Height = 238
          Align = alClient
          ItemHeight = 23
          TabOrder = 1
          OnClick = TriggersLBClick
          ExplicitHeight = 204
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Misc'
      ImageIndex = 2
      object GroupBox1: TGroupBox
        Left = 24
        Top = 38
        Width = 185
        Height = 100
        Caption = 'Dwell Times (ms)'
        TabOrder = 0
        object mPostDwellTimeE: TFloatLabeledEdit
          Left = 96
          Top = 52
          Width = 65
          Height = 31
          EditLabel.Width = 34
          EditLabel.Height = 23
          EditLabel.Caption = 'Post'
          Enabled = False
          TabOrder = 0
          Text = '0.0'
          OnKeyDown = mMovePosEKeyDown
        end
        object mPreDwellTimeE: TFloatLabeledEdit
          Left = 16
          Top = 52
          Width = 65
          Height = 31
          EditLabel.Width = 27
          EditLabel.Height = 23
          EditLabel.Caption = 'Pre'
          Enabled = False
          TabOrder = 1
          Text = '0.0'
          OnKeyDown = mMovePosEKeyDown
        end
      end
    end
  end
end
