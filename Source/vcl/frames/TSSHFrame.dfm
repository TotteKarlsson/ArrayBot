object SSHFrame: TSSHFrame
  Left = 0
  Top = 0
  Width = 521
  Height = 70
  AutoSize = True
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 521
    Height = 70
    Caption = 'Connection'
    TabOrder = 0
    object ConnectBtn: TButton
      Left = 380
      Top = 21
      Width = 121
      Height = 35
      Caption = 'Connect'
      TabOrder = 4
      OnClick = ConnectBtnClick
    end
    object edSSHHost: TSTDStringLabeledEdit
      Left = 16
      Top = 34
      Width = 105
      Height = 21
      EditLabel.Width = 44
      EditLabel.Height = 13
      EditLabel.Caption = 'SSH Host'
      TabOrder = 0
      Text = 'atbigdawg'
      Value = 'atbigdawg'
    end
    object seSSHPort: TIntegerLabeledEdit
      Left = 127
      Top = 34
      Width = 65
      Height = 21
      EditLabel.Width = 20
      EditLabel.Height = 13
      EditLabel.Caption = 'Port'
      TabOrder = 1
      Text = '22'
      Value = 22
    end
    object edSSHUserName: TSTDStringLabeledEdit
      Left = 198
      Top = 34
      Width = 105
      Height = 21
      EditLabel.Width = 52
      EditLabel.Height = 13
      EditLabel.Caption = 'User Name'
      TabOrder = 2
      Text = 'totte'
      Value = 'totte'
    end
    object edSSHPassword: TSTDStringLabeledEdit
      Left = 309
      Top = 34
      Width = 65
      Height = 21
      EditLabel.Width = 46
      EditLabel.Height = 13
      EditLabel.Caption = 'Password'
      PasswordChar = '*'
      TabOrder = 3
      Text = 'lacket47'
      Value = 'lacket47'
    end
  end
  object ScFileStorage: TScFileStorage
    Password = 'lacket47'
    Left = 48
    Top = 224
  end
  object ScSSHShell1: TScSSHShell
    Client = ScSSHClient
    NonBlocking = True
    OnAsyncError = ScSSHShell1AsyncError
    Left = 176
    Top = 240
  end
  object ScSSHChannel: TScSSHChannel
    Client = ScSSHClient
    Left = 120
    Top = 256
  end
  object ScSSHClient: TScSSHClient
    HostName = 'atbigdawg'
    User = 'totte'
    Password = 'lacket47'
    KeyStorage = ScFileStorage
    AfterConnect = ScSSHClientAfterConnect
    BeforeConnect = ScSSHClientBeforeConnect
    AfterDisconnect = ScSSHClientAfterDisconnect
    OnServerKeyValidate = ScSSHClientServerKeyValidate
    Left = 80
    Top = 280
  end
end
