object ArrayBotRequestFrame: TArrayBotRequestFrame
  Left = 0
  Top = 0
  Width = 441
  Height = 457
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 441
    Height = 193
    Align = alTop
    Caption = 'ArrayBot Request'
    TabOrder = 0
    DesignSize = (
      441
      193)
    object NameEdit: TSTDStringLabeledEdit
      Left = 21
      Top = 64
      Width = 404
      Height = 31
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 49
      EditLabel.Height = 23
      EditLabel.Caption = 'Name'
      Enabled = False
      ReadOnly = True
      TabOrder = 1
      OnKeyDown = EditKeyDown
    end
    object ArrayBotRequestCB: TComboBox
      Left = 21
      Top = 128
      Width = 404
      Height = 31
      Style = csDropDownList
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      OnCloseUp = ArrayBotRequestCBCloseUp
      Items.Strings = (
        'Start Video Recorder'
        'Stop Video Recorder'
        'Take SnapShoot'
        'Enable Barcode Scanner'
        'Disable Barcode Scanner'
        'Validate Barcode'
        'Set Camera Zoom and Focus')
    end
  end
  object FocusZoomGB: TGroupBox
    Left = 27
    Top = 209
    Width = 314
    Height = 111
    Caption = 'Parameters'
    Padding.Left = 15
    Padding.Right = 15
    TabOrder = 1
    Visible = False
    object FocusE: TIntegerLabeledEdit
      Left = 16
      Top = 59
      Width = 105
      Height = 31
      EditLabel.Width = 54
      EditLabel.Height = 23
      EditLabel.Caption = 'Focus '
      TabOrder = 0
      Text = '0'
      OnKeyDown = IntEditKeyDown
    end
    object ZoomE: TIntegerLabeledEdit
      Left = 128
      Top = 59
      Width = 105
      Height = 31
      EditLabel.Width = 47
      EditLabel.Height = 23
      EditLabel.Caption = 'Zoom'
      TabOrder = 1
      Text = '0'
      OnKeyDown = IntEditKeyDown
    end
  end
  object LEDIntensityGB: TGroupBox
    Left = 59
    Top = 349
    Width = 185
    Height = 105
    Caption = 'Parameters'
    TabOrder = 2
    Visible = False
    object LEDIntensityE: TIntegerLabeledEdit
      Left = 16
      Top = 56
      Width = 121
      Height = 31
      EditLabel.Width = 139
      EditLabel.Height = 23
      EditLabel.Caption = 'Intensity (0-255)'
      TabOrder = 0
      Text = '0'
      OnKeyDown = IntEditKeyDown
    end
  end
end
