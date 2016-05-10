object MotorFrame: TMotorFrame
  Left = 0
  Top = 0
  Width = 288
  Height = 272
  TabOrder = 0
  object MotorGB: TGroupBox
    Left = 0
    Top = 0
    Width = 288
    Height = 272
    Align = alClient
    Caption = 'Motor'
    TabOrder = 0
    DesignSize = (
      288
      272)
    object StatusGB: TGroupBox
      Left = 2
      Top = 188
      Width = 284
      Height = 82
      Align = alBottom
      Caption = 'Status'
      TabOrder = 0
      object Label1: TLabel
        Left = 17
        Top = 23
        Width = 49
        Height = 13
        Caption = 'Is Active: '
      end
      object Label2: TLabel
        Left = 166
        Top = 23
        Width = 51
        Height = 13
        Caption = 'Is Homing:'
      end
      object Label3: TLabel
        Left = 17
        Top = 36
        Width = 52
        Height = 13
        Caption = 'Is Homed: '
      end
      object Label4: TLabel
        Left = 17
        Top = 49
        Width = 77
        Height = 13
        Caption = 'Velocity (mm/s):'
      end
      object Lbl: TLabel
        Left = 166
        Top = 36
        Width = 70
        Height = 13
        Caption = 'Is Forwarding:'
      end
      object Lbl2: TLabel
        Left = 166
        Top = 49
        Width = 64
        Height = 13
        Caption = 'Is Reversing:'
      end
      object mIsActiveLabel: TLabel
        Left = 107
        Top = 23
        Width = 18
        Height = 13
        Caption = 'N/A'
      end
      object mIsForwardingLabel: TLabel
        Left = 242
        Top = 36
        Width = 18
        Height = 13
        Caption = 'N/A'
      end
      object mIsHomedLabel: TLabel
        Left = 107
        Top = 36
        Width = 18
        Height = 13
        Caption = 'N/A'
      end
      object mIsHomingLabel: TLabel
        Left = 242
        Top = 23
        Width = 18
        Height = 13
        Caption = 'N/A'
      end
      object mIsReversingLabel: TLabel
        Left = 242
        Top = 49
        Width = 18
        Height = 13
        Caption = 'N/A'
      end
      object mVelocityLbl: TLabel
        Left = 107
        Top = 49
        Width = 19
        Height = 13
        Caption = '0.0 '
      end
    end
    object motorPositionE: mtkFloatLabeledEdit
      Left = 168
      Top = 29
      Width = 102
      Height = 27
      Anchors = [akTop, akRight]
      EditLabel.Width = 37
      EditLabel.Height = 13
      EditLabel.Caption = 'Position'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Text = '0.00'
    end
  end
end
