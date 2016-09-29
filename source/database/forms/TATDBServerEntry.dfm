object ATDBServerEntry: TATDBServerEntry
  Left = 0
  Top = 0
  Caption = 'ATDBServerEntry'
  ClientHeight = 312
  ClientWidth = 263
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 256
    Width = 263
    Height = 56
    Align = alBottom
    TabOrder = 0
    ExplicitWidth = 513
    DesignSize = (
      263
      56)
    object mSubmitButton: TButton
      Left = 180
      Top = 7
      Width = 68
      Height = 41
      Anchors = [akTop, akRight]
      Caption = 'Submit'
      Enabled = False
      ModalResult = 1
      TabOrder = 0
      ExplicitLeft = 415
    end
    object mCancelBtn: TButton
      Left = 101
      Top = 7
      Width = 68
      Height = 41
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
    end
  end
end
