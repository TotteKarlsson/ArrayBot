object StringInputDialog: TStringInputDialog
  Left = 0
  Top = 0
  AutoSize = True
  BorderStyle = bsDialog
  Caption = 'String InputDialog'
  ClientHeight = 166
  ClientWidth = 746
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  DesignSize = (
    746
    166)
  PixelsPerInch = 96
  TextHeight = 23
  object Panel1: TPanel
    Left = 0
    Top = 76
    Width = 746
    Height = 90
    Align = alBottom
    TabOrder = 0
    DesignSize = (
      746
      90)
    object Button1: TButton
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
  object STDStringLabeledEdit1: TSTDStringLabeledEdit
    Left = 24
    Top = 26
    Width = 688
    Height = 31
    Anchors = [akLeft, akTop, akRight, akBottom]
    EditLabel.Width = 89
    EditLabel.Height = 23
    EditLabel.Caption = 'New Value'
    TabOrder = 1
    OnChange = STDStringLabeledEdit1Change
    OnClick = STDStringLabeledEdit1Click
    OnKeyDown = STDStringLabeledEdit1KeyDown
  end
end