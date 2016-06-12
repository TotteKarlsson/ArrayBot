object OptionsForm: TOptionsForm
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'OptionsForm'
  ClientHeight = 414
  ClientWidth = 646
  Color = clBtnFace
  Constraints.MinHeight = 453
  Constraints.MinWidth = 660
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 646
    Height = 373
    Align = alClient
    TabOrder = 0
    object mTree: TTreeView
      Left = 1
      Top = 1
      Width = 128
      Height = 371
      Align = alLeft
      HideSelection = False
      Indent = 19
      ReadOnly = True
      RowSelect = True
      TabOrder = 0
      OnClick = mTreeClick
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 373
    Width = 646
    Height = 41
    Align = alBottom
    TabOrder = 1
    object Button1: TButton
      Left = 481
      Top = 6
      Width = 75
      Height = 25
      Action = OKAction
      ModalResult = 1
      TabOrder = 0
    end
    object CancelBtn: TButton
      Left = 562
      Top = 6
      Width = 75
      Height = 25
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
      OnClick = CancelBtnClick
    end
  end
  object ActionList1: TActionList
    Left = 552
    Top = 72
    object OKAction: TAction
      Caption = 'OK'
      Enabled = False
      OnExecute = OKActionExecute
    end
  end
end
