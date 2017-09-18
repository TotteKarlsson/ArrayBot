object HomeMotorProcessFrame: THomeMotorProcessFrame
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
    Height = 465
    Align = alTop
    Caption = 'Action Properties'
    Padding.Left = 15
    Padding.Right = 15
    TabOrder = 0
    object Panel2: TPanel
      Left = 17
      Top = 25
      Width = 368
      Height = 438
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
      object mActionInfo: TLabel
        Left = 0
        Top = 169
        Width = 368
        Height = 269
        Align = alClient
        AutoSize = False
        Caption = 
          'This move will move the Z motor to a good position for cover sli' +
          'p extraction. As Z gets above 200 mm, the x motor is triggered t' +
          'o move to a convenient position.'
        Layout = tlCenter
        WordWrap = True
        OnClick = mActionInfoClick
        ExplicitLeft = 16
        ExplicitTop = 144
        ExplicitWidth = 416
        ExplicitHeight = 333
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 368
        Height = 169
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object Label1: TLabel
          Left = 16
          Top = 15
          Width = 48
          Height = 23
          Caption = 'Motor'
        end
        object MotorsCB: TComboBox
          Left = 16
          Top = 44
          Width = 329
          Height = 31
          Style = csDropDownList
          TabOrder = 0
          OnChange = MotorsCBChange
        end
      end
    end
  end
end
