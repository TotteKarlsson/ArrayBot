object AboutArrayBotForm: TAboutArrayBotForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'About ArrayBot'
  ClientHeight = 335
  ClientWidth = 714
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
  inline TAboutArrayBotFrame1: TAboutArrayBotFrame
    Left = 0
    Top = 0
    Width = 714
    Height = 288
    Align = alClient
    AutoSize = True
    Color = clBtnFace
    ParentBackground = False
    ParentColor = False
    TabOrder = 0
    ExplicitWidth = 832
    ExplicitHeight = 358
    DesignSize = (
      714
      288)
    inherited Image1: TImage
      Left = 523
      Top = 16
      ExplicitLeft = 437
      ExplicitTop = 16
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 288
    Width = 714
    Height = 47
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 1
    ExplicitWidth = 614
    DesignSize = (
      714
      47)
    object Button3: TButton
      Left = 20
      Top = 5
      Width = 101
      Height = 40
      Action = TAboutArrayBotFrame1.showChangeLog
      TabOrder = 0
    end
    object Button4: TButton
      Left = 607
      Top = 5
      Width = 90
      Height = 40
      Anchors = [akTop, akRight]
      Caption = 'Close'
      ModalResult = 1
      TabOrder = 1
      OnClick = Button4Click
      ExplicitLeft = 507
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
