object FFMPEGFrame: TFFMPEGFrame
  Left = 0
  Top = 0
  Width = 438
  Height = 241
  AutoSize = True
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 438
    Height = 241
    Caption = 'FFMPEG Thread Settings'
    TabOrder = 0
    object Label1: TLabel
      Left = 17
      Top = 126
      Width = 63
      Height = 13
      Caption = 'H.264 Preset'
    end
    object FFMPEGThreads: TIntegerLabeledEdit
      Left = 17
      Top = 95
      Width = 121
      Height = 21
      EditLabel.Width = 161
      EditLabel.Height = 13
      EditLabel.Caption = 'Threads Employed (0 => optimal)'
      TabOrder = 0
      Text = '0'
    end
    object CRFValue: TIntegerLabeledEdit
      Left = 17
      Top = 47
      Width = 121
      Height = 21
      EditLabel.Width = 82
      EditLabel.Height = 13
      EditLabel.Caption = 'CRF Value (0-51)'
      TabOrder = 1
      Text = '20'
      Value = 20
    end
    object PresetCB: TComboBox
      Left = 17
      Top = 145
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemIndex = 3
      TabOrder = 2
      Text = 'medium'
      Items.Strings = (
        'ultrafast'
        'veryfast'
        'fast'
        'medium'
        'slower'
        'veryslow')
    end
    object DeleteSourceFileCB: TPropertyCheckBox
      Left = 17
      Top = 204
      Width = 232
      Height = 17
      Caption = 'Delete Source File'
      TabOrder = 3
      OnClick = CBClick
    end
    object RenameSourceFileCB: TPropertyCheckBox
      Left = 17
      Top = 181
      Width = 224
      Height = 17
      Caption = 'Rename Source File'
      Checked = True
      State = cbChecked
      TabOrder = 4
      OnClick = CBClick
      Value = True
    end
  end
end
