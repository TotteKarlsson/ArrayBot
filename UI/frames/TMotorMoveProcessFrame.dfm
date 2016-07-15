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
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 451
    Height = 304
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 0
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
    object TabSheet2: TTabSheet
      Caption = 'Trigger'
      ImageIndex = 1
      inline TPositionalTriggerFrame1: TPositionalTriggerFrame
        Left = 0
        Top = 0
        Width = 443
        Height = 266
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        ExplicitWidth = 443
        ExplicitHeight = 266
        inherited MainGB: TGroupBox
          Width = 443
          Height = 266
          ExplicitWidth = 443
          ExplicitHeight = 266
          inherited GroupBox3: TGroupBox
            Width = 439
            Height = 117
            ExplicitWidth = 439
            ExplicitHeight = 117
          end
          inherited GroupBox4: TGroupBox
            Width = 439
            ExplicitWidth = 439
          end
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
