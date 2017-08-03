object ArrayCamRequestFrame: TArrayCamRequestFrame
  Left = 0
  Top = 0
  Width = 313
  Height = 207
  AutoSize = True
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
    Width = 313
    Height = 207
    Align = alLeft
    Caption = 'ArrayCam Request'
    TabOrder = 0
    object mNameEdit: TSTDStringLabeledEdit
      Left = 21
      Top = 64
      Width = 260
      Height = 31
      EditLabel.Width = 49
      EditLabel.Height = 23
      EditLabel.Caption = 'Name'
      Enabled = False
      ReadOnly = True
      TabOrder = 1
      OnKeyDown = mEditKeyDown
    end
    object mArrayCamRequestCB: TComboBox
      Left = 21
      Top = 128
      Width = 260
      Height = 31
      Style = csDropDownList
      ItemIndex = 0
      TabOrder = 0
      Text = 'Start Video Recorder'
      OnCloseUp = mArrayCamRequestCBCloseUp
      Items.Strings = (
        'Start Video Recorder'
        'Stop Video Recorder'
        'Take SnapShoot'
        'Enable Barcode Scanner'
        'Disable Barcode Scanner'
        'Validate Barcode')
    end
  end
end
