object ArduinoServerCommandFrame: TArduinoServerCommandFrame
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
  object mMainGB: TGroupBox
    Left = 0
    Top = 0
    Width = 451
    Height = 369
    Align = alTop
    Caption = 'Action Properties'
    Padding.Left = 15
    Padding.Right = 15
    TabOrder = 0
    object mActionInfo: TLabel
      Left = 17
      Top = 25
      Width = 417
      Height = 151
      Align = alClient
      AutoSize = False
      Caption = 'Select a command to execute as part of the process sequence.'
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
      Top = 176
      Width = 417
      Height = 191
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 15
        Width = 85
        Height = 23
        Caption = 'Command'
      end
      object mCommandCB: TComboBox
        Left = 16
        Top = 44
        Width = 353
        Height = 31
        Style = csDropDownList
        ItemIndex = 0
        TabOrder = 0
        Text = 'Activate Vaccum'
        Items.Strings = (
          'Activate Vaccum'
          'Deactivate Vaccum')
      end
    end
  end
end
