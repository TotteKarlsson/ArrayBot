object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 351
  ClientWidth = 726
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 64
    Top = 56
    Width = 97
    Height = 65
    Caption = 'Int Message'
    TabOrder = 0
  end
  object Button3: TButton
    Left = 338
    Top = 56
    Width = 141
    Height = 65
    Caption = 'SendGetStruct Message'
    TabOrder = 1
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 506
    Top = 56
    Width = 127
    Height = 65
    Caption = 'Send Text Message'
    TabOrder = 2
  end
  object Button2: TButton
    Left = 211
    Top = 56
    Width = 97
    Height = 65
    Caption = 'Struct Message'
    TabOrder = 3
  end
  object IntEdit: TEdit
    Left = 64
    Top = 157
    Width = 81
    Height = 21
    TabOrder = 4
    Text = 'IntEdit'
  end
  object StructEdit2: TEdit
    Left = 211
    Top = 168
    Width = 81
    Height = 21
    TabOrder = 5
    Text = 'Edit1'
  end
  object StructEdit1: TEdit
    Left = 211
    Top = 141
    Width = 81
    Height = 21
    TabOrder = 6
    Text = 'Edit1'
  end
  object GetStructEdit2: TEdit
    Left = 338
    Top = 168
    Width = 81
    Height = 21
    TabOrder = 7
    Text = 'Edit1'
  end
  object GetStructEdit1: TEdit
    Left = 338
    Top = 141
    Width = 81
    Height = 21
    TabOrder = 8
    Text = 'Edit1'
  end
  object TextEdit: TEdit
    Left = 506
    Top = 157
    Width = 81
    Height = 21
    TabOrder = 9
    Text = 'Edit1'
  end
end
