object AboutArrayBotForm: TAboutArrayBotForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'About ArrayBot'
  ClientHeight = 296
  ClientWidth = 571
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
  object Panel1: TPanel
    Left = 0
    Top = 249
    Width = 571
    Height = 47
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 0
    DesignSize = (
      571
      47)
    object Label1: TLabel
      Left = 127
      Top = 6
      Width = 312
      Height = 30
      Caption = 'Smith Lab.  - Allen Institute 2016'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -21
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsItalic]
      ParentColor = False
      ParentFont = False
      StyleElements = [seClient, seBorder]
    end
    object Button3: TButton
      Left = 20
      Top = 5
      Width = 101
      Height = 40
      Caption = 'Change Log'
      TabOrder = 0
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 464
      Top = 5
      Width = 90
      Height = 40
      Anchors = [akTop, akRight]
      Caption = 'Close'
      ModalResult = 1
      TabOrder = 1
      OnClick = Button4Click
    end
  end
  inline TAboutArrayBotFrame1: TAboutArrayBotFrame
    Left = 0
    Top = 0
    Width = 571
    Height = 249
    Align = alClient
    TabOrder = 1
    ExplicitWidth = 571
    ExplicitHeight = 249
    inherited Image1: TImage
      Width = 120
      ExplicitWidth = 120
    end
    inherited logLabel: TLabel
      Top = 216
      ExplicitTop = 216
    end
    inherited Image2: TImage
      Width = 571
      Height = 249
      ExplicitWidth = 571
      ExplicitHeight = 249
    end
  end
  object ActionList1: TActionList
    Left = 160
    Top = 144
    object checkForUpdateA: TAction
      Caption = 'Check for Update'
    end
    object retrieveChangeLogA: TAction
      Caption = 'retrieveChangeLogA'
    end
  end
end
