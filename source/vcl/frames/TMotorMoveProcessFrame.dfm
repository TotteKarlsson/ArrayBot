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
  object mMainGB: TGroupBox
    Left = 0
    Top = 0
    Width = 451
    Height = 417
    Align = alTop
    Caption = 'Action Properties'
    Padding.Left = 15
    Padding.Right = 15
    TabOrder = 1
    object mActionInfo: TLabel
      Left = 17
      Top = 25
      Width = 417
      Height = 199
      Align = alClient
      AutoSize = False
      Caption = 
        'This move will move the Z motor to a good position for cover sli' +
        'p extraction. As Z gets above 200 mm, the x motor is triggered t' +
        'o move to a convenient position.'
      Layout = tlCenter
      WordWrap = True
      OnClick = mActionInfoClick
      ExplicitLeft = 1
      ExplicitTop = 24
      ExplicitWidth = 426
      ExplicitHeight = 182
    end
    object Panel2: TPanel
      Left = 17
      Top = 224
      Width = 417
      Height = 191
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 15
        Width = 48
        Height = 23
        Caption = 'Motor'
      end
      object mAccE: TFloatLabeledEdit
        Left = 240
        Top = 121
        Width = 81
        Height = 31
        EditLabel.Width = 101
        EditLabel.Height = 23
        EditLabel.Caption = 'Acceleration'
        TabOrder = 3
        Text = '0.0'
        OnKeyDown = mMovePosEKeyDown
      end
      object mMaxVelE: TFloatLabeledEdit
        Left = 120
        Top = 121
        Width = 89
        Height = 31
        EditLabel.Width = 103
        EditLabel.Height = 23
        EditLabel.Caption = 'Max Velocity'
        TabOrder = 2
        Text = '0.0'
        OnKeyDown = mMovePosEKeyDown
      end
      object mMovePosE: TFloatLabeledEdit
        Left = 16
        Top = 121
        Width = 89
        Height = 31
        EditLabel.Width = 63
        EditLabel.Height = 23
        EditLabel.Caption = 'Position'
        TabOrder = 1
        Text = '0.0'
        OnKeyDown = mMovePosEKeyDown
      end
      object MotorsCB: TComboBox
        Left = 16
        Top = 44
        Width = 281
        Height = 31
        Style = csDropDownList
        TabOrder = 0
        OnChange = MotorsCBChange
      end
      object mAddTriggerBtn: TArrayBotButton
        Left = 351
        Top = 44
        Width = 169
        Height = 108
        Caption = 'Add Child Action'
        ParentDoubleBuffered = True
        TabOrder = 4
        OnClick = AddTriggerBClick
        SoundID = 'BUTTON_CLICK_4'
      end
    end
  end
  object mTriggerPanel: TPanel
    Left = 0
    Top = 417
    Width = 451
    Height = 266
    Align = alClient
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 200
      Height = 264
      Align = alLeft
      Caption = 'Triggers'
      TabOrder = 0
      object mTriggersLB: TListBox
        Left = 2
        Top = 25
        Width = 196
        Height = 177
        Align = alClient
        ItemHeight = 23
        TabOrder = 0
        OnClick = TriggersLBClick
      end
      object Panel1: TPanel
        Left = 2
        Top = 202
        Width = 196
        Height = 60
        Align = alBottom
        TabOrder = 1
        ExplicitTop = 230
        object mDeleteTriggerB: TArrayBotButton
          Left = 1
          Top = 1
          Width = 90
          Height = 58
          Align = alLeft
          Caption = 'Delete'
          ParentDoubleBuffered = True
          TabOrder = 0
          OnClick = mDeleteTriggerBClick
          SoundID = 'BUTTON_CLICK_4'
        end
      end
    end
  end
end
