object MoveCoverSlipAtAngleProcessFrame: TMoveCoverSlipAtAngleProcessFrame
  Left = 0
  Top = 0
  Width = 926
  Height = 600
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 272
    Width = 926
    Height = 328
    Align = alBottom
    Caption = 'Info'
    TabOrder = 1
    object A: TLabel
      Left = 21
      Top = 40
      Width = 132
      Height = 23
      Caption = 'Lateral Velocity:'
    end
    object Label1: TLabel
      Left = 21
      Top = 69
      Width = 170
      Height = 23
      Caption = 'Lateral Acceleration:'
    end
    object LatVelL: mtkFloatLabel
      Left = 224
      Top = 40
      Width = 26
      Height = 23
      Caption = '0.0'
      ValueString = '0.0'
      NrOfDecimals = 1
      TheFont.Charset = DEFAULT_CHARSET
      TheFont.Color = clWindowText
      TheFont.Height = -19
      TheFont.Name = 'Tahoma'
      TheFont.Style = []
    end
    object LatAccL: mtkFloatLabel
      Left = 224
      Top = 69
      Width = 26
      Height = 23
      Caption = '0.0'
      ValueString = '0.0'
      NrOfDecimals = 1
      TheFont.Charset = DEFAULT_CHARSET
      TheFont.Color = clWindowText
      TheFont.Height = -19
      TheFont.Name = 'Tahoma'
      TheFont.Style = []
    end
  end
  object GroupBox4: TGroupBox
    Left = 0
    Top = 0
    Width = 926
    Height = 272
    Align = alClient
    Caption = 'Move at Angle Parameters'
    TabOrder = 0
    object mActionInfo: TLabel
      Left = 337
      Top = 25
      Width = 587
      Height = 245
      Align = alClient
      AutoSize = False
      Caption = 'The brown fox'
      Layout = tlCenter
      WordWrap = True
      OnClick = mActionInfoClick
      ExplicitLeft = 312
      ExplicitWidth = 612
      ExplicitHeight = 173
    end
    object Panel2: TPanel
      Left = 2
      Top = 25
      Width = 335
      Height = 245
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
      object mLiftAccE: TFloatLabeledEdit
        Left = 155
        Top = 36
        Width = 105
        Height = 31
        EditLabel.Width = 151
        EditLabel.Height = 23
        EditLabel.Caption = 'Move Acceleration'
        TabOrder = 1
        Text = '0.0'
        OnKeyDown = EditKeyDown
      end
      object mLiftAngleE: TFloatLabeledEdit
        Left = 19
        Top = 108
        Width = 105
        Height = 31
        EditLabel.Width = 47
        EditLabel.Height = 23
        EditLabel.Caption = 'Angle'
        TabOrder = 2
        Text = '0.0'
        OnKeyDown = EditKeyDown
      end
      object mLiftHeightE: TFloatLabeledEdit
        Left = 155
        Top = 108
        Width = 105
        Height = 31
        EditLabel.Width = 86
        EditLabel.Height = 23
        EditLabel.Caption = 'Lift Height'
        TabOrder = 3
        Text = '0.0'
        OnKeyDown = EditKeyDown
      end
      object mLiftVelocityE: TFloatLabeledEdit
        Left = 19
        Top = 36
        Width = 105
        Height = 31
        EditLabel.Width = 113
        EditLabel.Height = 23
        EditLabel.Caption = 'Move Velocity'
        TabOrder = 0
        Text = '0.0'
        OnKeyDown = EditKeyDown
      end
      object EnableParallelWhiskerMoveCB: TPropertyCheckBox
        Left = 19
        Top = 168
        Width = 270
        Height = 17
        Caption = 'Enable Parallel Whisker Move'
        TabOrder = 4
        OnClick = EnableParallelWhiskerMoveCBClick
      end
    end
  end
end
