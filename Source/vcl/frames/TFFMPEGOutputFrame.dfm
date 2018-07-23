object FFMPEGOutputFrame: TFFMPEGOutputFrame
  Left = 0
  Top = 0
  Width = 510
  Height = 105
  TabOrder = 0
  object FileNameLbl: TLabel
    Left = 11
    Top = 15
    Width = 56
    Height = 13
    Caption = 'FileNameLbl'
  end
  object ProgressBar1: TProgressBar
    Left = 0
    Top = 80
    Width = 510
    Height = 25
    Align = alBottom
    TabOrder = 0
    ExplicitWidth = 327
  end
  object CompressBtn: TArrayBotButton
    Left = 0
    Top = 37
    Width = 510
    Height = 43
    Align = alBottom
    Caption = 'CompressBtn'
    TabOrder = 1
    OnClick = CompressBtnClick
    SoundID = 'BUTTON_CLICK_4'
    ExplicitWidth = 327
  end
end
