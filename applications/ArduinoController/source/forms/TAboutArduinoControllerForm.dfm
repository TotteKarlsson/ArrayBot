object AboutArduinoControllerForm: TAboutArduinoControllerForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'About ArduinoServer'
  ClientHeight = 552
  ClientWidth = 674
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
    Top = 505
    Width = 674
    Height = 47
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 0
    DesignSize = (
      674
      47)
    object Label1: TLabel
      Left = 127
      Top = 6
      Width = 359
      Height = 30
      Caption = 'Smith Lab.  - Allen Institute 2016-2018'
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
    object Button4: TButton
      Left = 567
      Top = 5
      Width = 90
      Height = 40
      Anchors = [akTop, akRight]
      Caption = 'Close'
      ModalResult = 1
      TabOrder = 0
      OnClick = Button4Click
    end
  end
  inline TAboutArduinoServerFrame1: TAboutArduinoServerFrame
    Left = 0
    Top = 0
    Width = 674
    Height = 505
    Align = alClient
    TabOrder = 1
    ExplicitWidth = 674
    ExplicitHeight = 505
    inherited Image1: TImage
      Width = 223
      ExplicitWidth = 223
    end
    inherited logLabel: TLabel
      Top = 216
      ExplicitTop = 216
    end
    inherited mChangeLogMemo: TMemo
      Top = 195
      Width = 674
      ExplicitTop = 195
      ExplicitWidth = 674
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
