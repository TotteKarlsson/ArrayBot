object ActionsForm: TActionsForm
  Left = 0
  Top = 0
  AutoSize = True
  BorderStyle = bsToolWindow
  Caption = 'Robot Actions'
  ClientHeight = 125
  ClientWidth = 150
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnMouseDown = FormMouseDown
  PixelsPerInch = 96
  TextHeight = 13
  object ArrayBotButton1: TArrayBotButton
    Left = 0
    Top = 0
    Width = 150
    Height = 125
    Action = StopAtTopA
    Caption = 'Stop at Top'
    TabOrder = 0
    SoundID = 'BUTTON_CLICK_4'
  end
  object ActionList1: TActionList
    Left = 112
    Top = 96
    object StopAtTopA: TAction
      Caption = 'Stop at Top'
      OnExecute = StopAtTopAExecute
    end
  end
end
