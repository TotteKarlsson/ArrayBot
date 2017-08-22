object StopAndResumeFrame: TStopAndResumeFrame
  Left = 0
  Top = 0
  Width = 522
  Height = 387
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
    Height = 387
    Align = alLeft
    Caption = 'StopAndResume Information'
    TabOrder = 0
    object mActionInfo: TLabel
      Left = 2
      Top = 25
      Width = 309
      Height = 360
      Align = alClient
      AutoSize = False
      Caption = 'Be really careful before running this sequence!!'
      Layout = tlCenter
      WordWrap = True
      OnClick = mActionInfoClick
      ExplicitLeft = 16
      ExplicitTop = 144
      ExplicitWidth = 416
      ExplicitHeight = 333
    end
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
      TabOrder = 0
      OnKeyDown = mEditKeyDown
    end
  end
end
