object MainForm: TMainForm
  Left = 0
  Top = 0
  ActiveControl = mPortNr
  Caption = 'iBot - Version 0.1'
  ClientHeight = 409
  ClientWidth = 647
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 24
    Top = 24
    Width = 241
    Height = 161
    Caption = 'MosaicPlanner'
    TabOrder = 0
    object mPortNr: TIntegerLabeledEdit
      Left = 16
      Top = 40
      Width = 105
      Height = 21
      EditLabel.Width = 20
      EditLabel.Height = 13
      EditLabel.Caption = 'Port'
      TabOrder = 0
      Text = '50000'
      Value = 50000
    end
    object Button1: TButton
      Left = 136
      Top = 38
      Width = 75
      Height = 25
      Caption = 'Connect'
      TabOrder = 1
      OnClick = Button1Click
    end
    object mSendStr: mtkSTDStringEdit
      Left = 16
      Top = 112
      Width = 105
      Height = 21
      EditLabel.Width = 54
      EditLabel.Height = 13
      EditLabel.Caption = 'Send string'
      TabOrder = 2
      Text = '[GET_VERSION]'
      Value = '[GET_VERSION]'
    end
    object Button2: TButton
      Left = 136
      Top = 110
      Width = 75
      Height = 25
      Caption = 'Send'
      TabOrder = 3
      OnClick = Button2Click
    end
  end
  object infoMemo: TMemo
    Left = 0
    Top = 272
    Width = 647
    Height = 137
    Align = alBottom
    TabOrder = 1
  end
  object ClientSocket1: TClientSocket
    Active = False
    Address = 'localhost'
    ClientType = ctNonBlocking
    Host = 'localhost'
    Port = 50000
    OnConnecting = ClientSocket1Connecting
    OnConnect = ClientSocket1Connect
    OnDisconnect = ClientSocket1Disconnect
    OnRead = ClientSocket1Read
    OnWrite = ClientSocket1Write
    OnError = ClientSocket1Error
    Left = 216
    Top = 88
  end
end
