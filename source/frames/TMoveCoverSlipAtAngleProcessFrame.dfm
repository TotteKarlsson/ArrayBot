object MoveCoverSlipAtAngleProcessFrame: TMoveCoverSlipAtAngleProcessFrame
  Left = 0
  Top = 0
  Width = 926
  Height = 804
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 676
    Width = 926
    Height = 128
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
    object LatVelL: TFloatLabel
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
    object LatAccL: TFloatLabel
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
    Height = 676
    Align = alClient
    Caption = 'Move at Angle Parameters'
    TabOrder = 0
    object mActionInfo: TLabel
      Left = 457
      Top = 25
      Width = 467
      Height = 649
      Align = alClient
      AutoSize = False
      Caption = 'The brown fox'
      Layout = tlCenter
      WordWrap = True
      OnClick = mActionInfoClick
      ExplicitLeft = 448
      ExplicitWidth = 476
    end
    object Panel2: TPanel
      Left = 2
      Top = 25
      Width = 455
      Height = 649
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
        Top = 215
        Width = 270
        Height = 17
        Caption = 'Enable Parallel Whisker Move'
        TabOrder = 4
        OnClick = EnableParallelWhiskerMoveCBClick
      end
      object FetchAngleFromCSAngleMotorCB: TPropertyCheckBox
        Left = 19
        Top = 145
        Width = 286
        Height = 51
        Caption = 'Fetch Angle from CS Angle Motor'
        TabOrder = 5
        Visible = False
        WordWrap = True
        OnClick = FetchAngleFromCSAngleMotorCBClick
      end
      object StayAtBeachGB: TGroupBox
        Left = 19
        Top = 288
        Width = 326
        Height = 209
        Caption = 'Stay at beach'
        TabOrder = 6
        object DeltaZE: TFloatLabeledEdit
          Left = 11
          Top = 63
          Width = 121
          Height = 31
          EditLabel.Width = 112
          EditLabel.Height = 23
          EditLabel.Caption = 'Delta Z (mm)'
          TabOrder = 0
          Text = '1.00'
          OnKeyDown = EditKeyDown
          Value = 1.000000000000000000
        end
        object YMoveE: TFloatLabeledEdit
          Left = 155
          Top = 135
          Width = 121
          Height = 31
          EditLabel.Width = 113
          EditLabel.Height = 23
          EditLabel.Caption = 'Y Move (mm)'
          TabOrder = 1
          Text = '1.00'
          OnKeyDown = EditKeyDown
          Value = 1.000000000000000000
        end
        object ZMoveE: TFloatLabeledEdit
          Left = 11
          Top = 135
          Width = 121
          Height = 31
          EditLabel.Width = 113
          EditLabel.Height = 23
          EditLabel.Caption = 'Z Move (mm)'
          TabOrder = 2
          Text = '1.00'
          OnKeyDown = EditKeyDown
          Value = 1.000000000000000000
        end
      end
      object LeaveWhiskeratBeachCB: TPropertyCheckBox
        Left = 40
        Top = 248
        Width = 233
        Height = 17
        Caption = 'Stay at Beach'
        TabOrder = 7
        OnClick = LeaveWhiskeratBeachCBClick
      end
      object YMoveScalingE: TFloatLabeledEdit
        Left = 288
        Top = 108
        Width = 73
        Height = 31
        EditLabel.Width = 127
        EditLabel.Height = 23
        EditLabel.Caption = 'Y Move Scaling'
        TabOrder = 8
        Text = '1.00'
        OnKeyDown = EditKeyDown
        Value = 1.000000000000000000
      end
    end
  end
end
