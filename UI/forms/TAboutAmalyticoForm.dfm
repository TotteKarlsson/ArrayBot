object AboutAmalyticoForm: TAboutAmalyticoForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'AboutAmalyticoForm'
  ClientHeight = 430
  ClientWidth = 832
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  inline TAboutAmalyticoFrame1: TAboutAmalyticoFrame
    Left = 0
    Top = 0
    Width = 832
    Height = 358
    Align = alClient
    AutoSize = True
    Color = clBtnFace
    ParentBackground = False
    ParentColor = False
    TabOrder = 0
    ExplicitWidth = 832
    ExplicitHeight = 358
    DesignSize = (
      832
      358)
    inherited Image1: TImage
      Left = 430
      Top = 7
      ExplicitLeft = 439
      ExplicitTop = 7
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 358
    Width = 832
    Height = 72
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 1
    object Button1: TButton
      Left = 34
      Top = 14
      Width = 125
      Height = 40
      Caption = 'Check for new version'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button3: TButton
      Left = 188
      Top = 14
      Width = 141
      Height = 40
      Action = TAboutAmalyticoFrame1.showChangeLog
      TabOrder = 1
    end
    object Button4: TButton
      Left = 708
      Top = 14
      Width = 100
      Height = 40
      Caption = 'Close'
      ModalResult = 1
      TabOrder = 2
      OnClick = Button4Click
    end
  end
  object ActionList1: TActionList
    Left = 720
    Top = 136
    object checkForUpdateA: TAction
      Caption = 'Check for Update'
      OnExecute = checkForUpdateAExecute
    end
    object retrieveChangeLogA: TAction
      Caption = 'retrieveChangeLogA'
      OnExecute = retrieveChangeLogAExecute
    end
  end
end
