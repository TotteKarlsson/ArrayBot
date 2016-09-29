object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'ATDB Master'
  ClientHeight = 624
  ClientWidth = 825
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
  object GroupBox1: TGroupBox
    Left = 16
    Top = 200
    Width = 457
    Height = 209
    Caption = 'Users'
    TabOrder = 0
    object DBGrid1: TDBGrid
      Left = 3
      Top = 49
      Width = 390
      Height = 144
      DataSource = usersDSource
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'id'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'user_name'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'created'
          Visible = True
        end>
    end
    object AddUserBtn: TButton
      Left = 318
      Top = 18
      Width = 75
      Height = 25
      Caption = 'Add User'
      TabOrder = 1
      OnClick = AddUserBtnClick
    end
    object DBNavigator1: TDBNavigator
      Left = 16
      Top = 18
      Width = 240
      Height = 25
      DataSource = usersDSource
      VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates]
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
    end
  end
  object GroupBox2: TGroupBox
    Left = 19
    Top = 8
    Width = 310
    Height = 129
    Caption = 'MySQL Connection'
    TabOrder = 1
    object mUserNameE: TSTDStringLabeledEdit
      Left = 13
      Top = 32
      Width = 92
      Height = 21
      EditLabel.Width = 52
      EditLabel.Height = 13
      EditLabel.Caption = 'User Name'
      TabOrder = 0
      Text = 'atdb_client'
      Value = 'atdb_client'
    end
    object mPassWordE: TSTDStringLabeledEdit
      Left = 13
      Top = 72
      Width = 92
      Height = 21
      EditLabel.Width = 46
      EditLabel.Height = 13
      EditLabel.Caption = 'Password'
      TabOrder = 1
      Text = 'atdb123'
      Value = 'atdb123'
    end
    object MaskEdit1: TMaskEdit
      Left = 168
      Top = 32
      Width = 121
      Height = 21
      EditMask = '!099.099.099.099;1; '
      MaxLength = 15
      TabOrder = 2
      Text = '127.0  .0  .1  '
      OnExit = MaskEdit1Exit
    end
    object Button1: TButton
      Left = 168
      Top = 59
      Width = 121
      Height = 25
      Action = ConnectToDBA
      Caption = 'Toggle Connection'
      TabOrder = 3
    end
  end
  object mySQLC: TSQLConnection
    ConnectionName = 'MySQLConnection'
    DriverName = 'MySQL'
    KeepConnection = False
    LoadParamsOnConnect = True
    LoginPrompt = False
    Params.Strings = (
      'DriverName=MySQL'
      'HostName=localhost'
      'Database=atdb'
      'User_Name=atdb_client'
      'Password=atdb123'
      'ServerCharSet='
      'BlobSize=-1'
      'ErrorResourceFile='
      'LocaleCode=0000'
      'Compressed=False'
      'Encrypted=False'
      'ConnectTimeout=60')
    Left = 736
    Top = 40
  end
  object usersDSP: TDataSetProvider
    DataSet = usersDS
    Left = 736
    Top = 168
  end
  object usersCDS: TClientDataSet
    Active = True
    Aggregates = <>
    Params = <>
    ProviderName = 'usersDSP'
    Left = 736
    Top = 232
    object usersCDSid: TIntegerField
      FieldName = 'id'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
    end
    object usersCDSuser_name: TStringField
      FieldName = 'user_name'
      Required = True
      Size = 255
    end
    object usersCDScreated: TSQLTimeStampField
      FieldName = 'created'
    end
  end
  object usersDS: TSQLDataSet
    CommandText = 'select * from user'
    DataSource = usersDSource
    MaxBlobSize = -1
    Params = <>
    SQLConnection = mySQLC
    Left = 736
    Top = 104
    object usersDSid: TIntegerField
      FieldName = 'id'
    end
    object usersDSuser_name: TStringField
      FieldName = 'user_name'
      Required = True
      Size = 255
    end
    object usersDScreated: TSQLTimeStampField
      FieldName = 'created'
    end
  end
  object usersDSource: TDataSource
    DataSet = usersCDS
    Left = 736
    Top = 296
  end
  object ActionList1: TActionList
    Left = 592
    Top = 40
    object ConnectToDBA: TAction
      Caption = 'ToggleDbConenctionA'
      OnExecute = ConnectToDBAExecute
    end
  end
end
