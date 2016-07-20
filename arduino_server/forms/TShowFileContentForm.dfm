object ShowFileContentForm: TShowFileContentForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'ShowFileContentForm'
  ClientHeight = 510
  ClientWidth = 670
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 670
    Height = 510
    Align = alClient
    Lines.Strings = (
      'Memo1')
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
    WordWrap = False
    ExplicitWidth = 609
    ExplicitHeight = 617
  end
end
