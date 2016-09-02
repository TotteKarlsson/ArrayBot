object TextInputDialog: TTextInputDialog
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'TextInputDialog'
  ClientHeight = 683
  ClientWidth = 746
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  DesignSize = (
    746
    683)
  PixelsPerInch = 96
  TextHeight = 23
  object Panel1: TPanel
    Left = 0
    Top = 593
    Width = 746
    Height = 90
    Align = alBottom
    TabOrder = 0
    DesignSize = (
      746
      90)
    object mCancelBtn: TButton
      Left = 619
      Top = 16
      Width = 115
      Height = 65
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
    end
    object mOkBtn: TButton
      Left = 498
      Top = 16
      Width = 115
      Height = 65
      Anchors = [akTop, akRight]
      Caption = 'OK'
      Enabled = False
      ModalResult = 1
      TabOrder = 1
    end
  end
  object mInfoMemo: TMemo
    Left = 24
    Top = 24
    Width = 688
    Height = 548
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 1
    OnChange = mInfoMemoChange
    OnClick = mInfoMemoClick
    OnKeyDown = mInfoMemoKeyDown
  end
end
