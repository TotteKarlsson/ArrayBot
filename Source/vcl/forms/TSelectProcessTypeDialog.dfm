object SelectProcessTypeDialog: TSelectProcessTypeDialog
  Left = 0
  Top = 0
  Caption = 'Select New Process/Event Type'
  ClientHeight = 357
  ClientWidth = 672
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 23
  object Panel1: TPanel
    Left = 0
    Top = 267
    Width = 672
    Height = 90
    Align = alBottom
    TabOrder = 0
    DesignSize = (
      672
      90)
    object Button1: TButton
      Left = 545
      Top = 16
      Width = 115
      Height = 65
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 0
    end
    object mOkBtn: TButton
      Left = 424
      Top = 16
      Width = 115
      Height = 65
      Anchors = [akTop, akRight]
      Caption = 'OK'
      ModalResult = 1
      TabOrder = 1
    end
  end
  object mProcTypeRG: TRadioGroup
    AlignWithMargins = True
    Left = 40
    Top = 40
    Width = 592
    Height = 187
    Margins.Left = 40
    Margins.Top = 40
    Margins.Right = 40
    Margins.Bottom = 40
    Align = alClient
    Caption = 'Available Processes/Events'
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      'Parallel Process'
      'Time Delay'
      'Stop/Start Dialog'
      'ArrayCam Request'
      'Absolute Move'
      'Lift at Angle'
      'Home Motor')
    TabOrder = 1
  end
end
