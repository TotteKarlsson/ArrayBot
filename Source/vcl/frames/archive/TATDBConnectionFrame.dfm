object ATDBConnectionFrame: TATDBConnectionFrame
  Left = 0
  Top = 0
  Width = 286
  Height = 201
  AutoSize = True
  TabOrder = 0
  object GBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 286
    Height = 201
    Caption = 'ATDB Connection'
    TabOrder = 0
    object mServerIPE: TSTDStringLabeledEdit
      Left = 16
      Top = 40
      Width = 121
      Height = 21
      EditLabel.Width = 74
      EditLabel.Height = 13
      EditLabel.Caption = 'Server Address'
      TabOrder = 0
      Text = '127.0.0.1'
      Value = '127.0.0.1'
    end
    object mDBUserE: TSTDStringLabeledEdit
      Left = 16
      Top = 89
      Width = 121
      Height = 21
      EditLabel.Width = 22
      EditLabel.Height = 13
      EditLabel.Caption = 'User'
      TabOrder = 1
      Text = 'atdb-client'
      Value = 'atdb-client'
    end
    object mPasswordE: TSTDStringLabeledEdit
      Left = 146
      Top = 89
      Width = 121
      Height = 21
      EditLabel.Width = 46
      EditLabel.Height = 13
      EditLabel.Caption = 'Password'
      TabOrder = 2
      Text = 'atdb123'
      Value = 'atdb123'
    end
    object mDatabaseE: TSTDStringLabeledEdit
      Left = 146
      Top = 40
      Width = 121
      Height = 21
      EditLabel.Width = 46
      EditLabel.Height = 13
      EditLabel.Caption = 'Database'
      TabOrder = 3
      Text = 'atdb'
      Value = 'atdb'
    end
    object ArrayBotButton1: TArrayBotButton
      Left = 88
      Top = 128
      Width = 113
      Height = 41
      Action = ConnectA
      Caption = 'Connect'
      TabOrder = 4
      SoundID = 'BUTTON_CLICK_4'
    end
  end
  object ActionList1: TActionList
    Left = 32
    Top = 136
    object ConnectA: TAction
      Caption = 'Connect'
      OnExecute = ConnectAExecute
    end
  end
end
