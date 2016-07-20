object amFileEditor: TamFileEditor
  Left = 672
  Top = 79
  BorderStyle = bsSizeToolWin
  Caption = 'amFileEditor'
  ClientHeight = 468
  ClientWidth = 904
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 904
    Height = 468
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    object Memo1: TMemo
      Left = 1
      Top = 1
      Width = 902
      Height = 466
      Align = alClient
      Font.Charset = ANSI_CHARSET
      Font.Color = clHighlight
      Font.Height = -12
      Font.Name = 'Consolas'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 0
      WordWrap = False
    end
  end
  object ActionList1: TActionList
    Left = 368
    Top = 136
    object SaveFileAction1: TAction
      Caption = 'Save File'
      OnExecute = SaveFileAction1Execute
    end
    object SaveAsAction: TAction
      Caption = 'Save As'
      OnExecute = SaveAsActionExecute
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 376
    Top = 24
  end
end
