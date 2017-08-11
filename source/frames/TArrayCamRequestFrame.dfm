object ArrayCamRequestFrame: TArrayCamRequestFrame
  Left = 0
  Top = 0
  Width = 313
  Height = 304
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
    Height = 193
    Align = alTop
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
      TabOrder = 0
      OnCloseUp = mArrayCamRequestCBCloseUp
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
    Left = 0
    Top = 193
    Width = 313
    Height = 111
    Align = alClient
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
      EditLabel.Width = 59
      EditLabel.Height = 23
      EditLabel.Caption = 'FocusE'
      TabOrder = 0
      Text = '0'
      OnKeyDown = IntEditKeyDown
    end
    object ZoomE: TIntegerLabeledEdit
      Left = 128
      Top = 59
      Width = 105
      Height = 31
      EditLabel.Width = 58
      EditLabel.Height = 23
      EditLabel.Caption = 'ZoomE'
      TabOrder = 1
      Text = '0'
      OnKeyDown = IntEditKeyDown
    end
  end
end
