object MotorMoveProcessFrame: TMotorMoveProcessFrame
  Left = 0
  Top = 0
  Width = 451
  Height = 304
  Align = alClient
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object MainGB: TGroupBox
    Left = 0
    Top = 0
    Width = 451
    Height = 217
    Align = alTop
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
      Top = 169
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
      Left = 120
      Top = 169
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
      Left = 240
      Top = 169
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
      Top = 108
      Width = 281
      Height = 31
      Style = csDropDownList
      TabOrder = 3
      OnChange = MotorsCBChange
    end
    object mAddTriggerBtn: TButton
      Left = 368
      Top = 49
      Width = 169
      Height = 108
      Caption = 'Add Child Action'
      TabOrder = 4
      OnClick = AddTriggerBClick
    end
    object mMoveActionNameE: TSTDStringLabeledEdit
      Left = 20
      Top = 57
      Width = 277
      Height = 31
      EditLabel.Width = 12
      EditLabel.Height = 23
      EditLabel.Caption = '  '
      TabOrder = 5
      OnKeyDown = mMoveActionNameEKeyDown
    end
  end
  object mTriggerPanel: TPanel
    Left = 0
    Top = 217
    Width = 451
    Height = 87
    Align = alClient
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 200
      Height = 85
      Align = alLeft
      Caption = 'Triggers'
      TabOrder = 0
      object mTriggersLB: TListBox
        Left = 2
        Top = 25
        Width = 196
        Height = 193
        Align = alClient
        ItemHeight = 23
        TabOrder = 0
        OnClick = TriggersLBClick
      end
      object Panel1: TPanel
        Left = 2
        Top = 23
        Width = 196
        Height = 60
        Align = alBottom
        TabOrder = 1
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
    end
  end
end
