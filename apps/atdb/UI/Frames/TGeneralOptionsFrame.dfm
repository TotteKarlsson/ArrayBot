object GeneralOptionsFrame: TGeneralOptionsFrame
  Left = 0
  Top = 0
  Width = 451
  Height = 304
  Align = alClient
  TabOrder = 0
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 451
    Height = 304
    Align = alClient
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 449
      Height = 112
      Align = alTop
      Caption = 'History'
      TabOrder = 0
      object mNrOfHistoryItems: TIntegerLabeledEdit
        Left = 16
        Top = 36
        Width = 49
        Height = 21
        EditLabel.Width = 140
        EditLabel.Height = 13
        EditLabel.Caption = 'Max Number of History Items'
        TabOrder = 0
        Text = '12'
        OnKeyDown = mNrOfHistoryItemsKeyDown
        Value = 12
      end
      object Button1: TButton
        Left = 16
        Top = 72
        Width = 75
        Height = 25
        Action = ClearHistoryA
        TabOrder = 1
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 113
      Width = 449
      Height = 48
      Align = alTop
      Caption = 'Splash Screen'
      TabOrder = 1
      object ShowSplashOnStartupCB: TPropertyCheckBox
        Left = 16
        Top = 23
        Width = 145
        Height = 17
        Caption = 'Show on Startup'
        TabOrder = 0
        OnClick = CheckBoxClick
      end
    end
  end
  object ActionList1: TActionList
    Left = 128
    Top = 56
    object ClearHistoryA: TAction
      Caption = 'Clear History'
      OnExecute = ClearHistoryAExecute
    end
  end
end
