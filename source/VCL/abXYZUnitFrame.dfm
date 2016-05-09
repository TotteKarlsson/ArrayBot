object XYZUnitFrame: TXYZUnitFrame
  Left = 0
  Top = 0
  Width = 681
  Height = 619
  TabOrder = 0
  object mainGB: TGroupBox
    Left = 0
    Top = 0
    Width = 681
    Height = 619
    Align = alClient
    Caption = 'XYZ Unit'
    TabOrder = 0
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
      Height = 561
      Align = alClient
      TabOrder = 1
      inline TMotorFrame1: TMotorFrame
        Left = 0
        Top = 0
        Width = 656
        Height = 272
        Align = alTop
        TabOrder = 0
        ExplicitLeft = 304
        ExplicitTop = 224
        inherited MotorGB: TGroupBox
          Width = 656
          inherited StatusGB: TGroupBox
            Width = 652
          end
        end
      end
      inline MotorFrame1: TMotorFrame
        Left = 0
        Top = 272
        Width = 656
        Height = 272
        Align = alTop
        TabOrder = 1
        ExplicitLeft = 240
        ExplicitTop = 400
        inherited MotorGB: TGroupBox
          Width = 656
          inherited StatusGB: TGroupBox
            Width = 652
          end
        end
      end
      inline MotorFrame2: TMotorFrame
        Left = 0
        Top = 544
        Width = 656
        Height = 272
        Align = alTop
        TabOrder = 2
        ExplicitLeft = 200
        ExplicitTop = 552
        inherited MotorGB: TGroupBox
          Width = 656
          inherited StatusGB: TGroupBox
            Width = 652
          end
        end
      end
    end
  end
end
