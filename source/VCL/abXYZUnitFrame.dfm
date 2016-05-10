object XYZUnitFrame: TXYZUnitFrame
  Left = 0
  Top = 0
  Width = 681
  Height = 352
  TabOrder = 0
  object mainGB: TGroupBox
    Left = 0
    Top = 0
    Width = 681
    Height = 352
    Align = alClient
    Caption = 'XYZ Unit'
    TabOrder = 0
    ExplicitHeight = 279
    object Panel1: TPanel
      Left = 2
      Top = 15
      Width = 677
      Height = 41
      Align = alTop
      BevelOuter = bvLowered
      TabOrder = 0
    end
    object ScrollBox1: TScrollBox
      Left = 2
      Top = 56
      Width = 677
      Height = 294
      Align = alClient
      TabOrder = 1
      ExplicitHeight = 221
      inline TMotorFrame1: TMotorFrame
        Left = 576
        Top = 0
        Width = 288
        Height = 273
        Align = alLeft
        TabOrder = 0
        ExplicitLeft = 192
        ExplicitTop = 64
        inherited MotorGB: TGroupBox
          Height = 273
          DesignSize = (
            288
            273)
          inherited StatusGB: TGroupBox
            Top = 189
          end
        end
      end
      inline TMotorFrame3: TMotorFrame
        Left = 288
        Top = 0
        Width = 288
        Height = 273
        Align = alLeft
        TabOrder = 1
        ExplicitLeft = 112
        ExplicitTop = 64
        inherited MotorGB: TGroupBox
          Height = 273
          DesignSize = (
            288
            273)
          inherited StatusGB: TGroupBox
            Top = 189
          end
        end
      end
      inline MotorFrame2: TMotorFrame
        Left = 0
        Top = 0
        Width = 288
        Height = 273
        Align = alLeft
        TabOrder = 2
        ExplicitLeft = 56
        ExplicitTop = 96
        inherited MotorGB: TGroupBox
          Height = 273
          DesignSize = (
            288
            273)
          inherited StatusGB: TGroupBox
            Top = 189
          end
          inherited motorPositionE: mtkFloatLabeledEdit
            Left = 136
            Top = 37
            EditLabel.ExplicitLeft = 136
            EditLabel.ExplicitTop = 21
            ExplicitLeft = 136
            ExplicitTop = 37
          end
        end
      end
    end
  end
end
