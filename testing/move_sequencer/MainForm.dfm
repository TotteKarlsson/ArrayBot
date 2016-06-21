object Main: TMain
  Left = 0
  Top = 0
  Caption = 'Move Sequencer Version 0.1'
  ClientHeight = 567
  ClientWidth = 884
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Btnpanel: TPanel
    Left = 757
    Top = 0
    Width = 127
    Height = 567
    Align = alRight
    TabOrder = 0
    object Button7: TButton
      Left = 1
      Top = 444
      Width = 125
      Height = 60
      Action = stopAllA
      Align = alBottom
      BiDiMode = bdLeftToRight
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 0
    end
    object Button5: TButton
      Left = 1
      Top = 504
      Width = 125
      Height = 62
      Action = FileExit1
      Align = alBottom
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
  end
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 757
    Height = 567
    Align = alClient
    Constraints.MinHeight = 348
    Constraints.MinWidth = 670
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 755
      Height = 565
      ActivePage = TabSheet4
      Align = alClient
      TabHeight = 60
      TabOrder = 0
      TabWidth = 100
      object TabSheet4: TTabSheet
        Caption = 'The Bot'
        object GroupBox1: TGroupBox
          Left = 312
          Top = 3
          Width = 393
          Height = 390
          Caption = 'Move Sequencer'
          TabOrder = 0
          object Label1: TLabel
            Left = 16
            Top = 26
            Width = 52
            Height = 13
            Caption = 'Sequences'
          end
          object GroupBox2: TGroupBox
            Left = 207
            Top = 26
            Width = 169
            Height = 207
            Caption = 'Move'
            TabOrder = 0
            object Label2: TLabel
              Left = 16
              Top = 20
              Width = 28
              Height = 13
              Caption = 'Motor'
            end
            object mMovePosE: TFloatLabeledEdit
              Left = 16
              Top = 79
              Width = 49
              Height = 21
              EditLabel.Width = 37
              EditLabel.Height = 13
              EditLabel.Caption = 'Position'
              TabOrder = 0
              Text = '0.0'
              OnKeyDown = moveParEdit
            end
            object mMaxVelE: TFloatLabeledEdit
              Left = 16
              Top = 127
              Width = 65
              Height = 21
              EditLabel.Width = 60
              EditLabel.Height = 13
              EditLabel.Caption = 'Max Velocity'
              TabOrder = 1
              Text = '0.0'
              OnKeyDown = moveParEdit
            end
            object mAccE: TFloatLabeledEdit
              Left = 87
              Top = 127
              Width = 65
              Height = 21
              EditLabel.Width = 59
              EditLabel.Height = 13
              EditLabel.Caption = 'Acceleration'
              TabOrder = 2
              Text = '0.0'
              OnKeyDown = moveParEdit
            end
            object mDwellTimeE: TFloatLabeledEdit
              Left = 15
              Top = 167
              Width = 65
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'Dwell Time (ms)'
              TabOrder = 3
              Text = '0.0'
              OnKeyDown = moveParEdit
            end
            object MotorsCB: TComboBox
              Left = 16
              Top = 39
              Width = 105
              Height = 21
              TabOrder = 4
              Text = 'Select Motor'
              OnChange = MotorsCBChange
            end
            object mMovePositionLabel: TSTDStringLabeledEdit
              Left = 71
              Top = 79
              Width = 90
              Height = 21
              EditLabel.Width = 67
              EditLabel.Height = 13
              EditLabel.Caption = 'Position Name'
              TabOrder = 5
              Text = 'PositionName'
              OnKeyDown = moveParEdit
              Value = 'PositionName'
            end
          end
          object mStartBtn: TButton
            Left = 16
            Top = 264
            Width = 75
            Height = 25
            Caption = 'Start'
            TabOrder = 1
            OnClick = mStartBtnClick
          end
          object mMovesLB: TListBox
            Left = 16
            Top = 105
            Width = 121
            Height = 97
            ItemHeight = 13
            TabOrder = 2
            OnClick = mMovesLBClick
          end
          object mSequencesCB: TComboBox
            Left = 16
            Top = 78
            Width = 121
            Height = 21
            Style = csDropDownList
            ItemIndex = 0
            TabOrder = 3
            Text = 'MoveSequence'
            OnChange = SequencesCBChange
            Items.Strings = (
              'MoveSequence')
          end
          object mSaveSequenceBtn: TButton
            Left = 16
            Top = 208
            Width = 41
            Height = 25
            Caption = 'Save'
            TabOrder = 4
            OnClick = mSaveSequenceBtnClick
          end
          object mAddMoveBtn: TButton
            Left = 143
            Top = 111
            Width = 58
            Height = 25
            Caption = 'Add Move'
            TabOrder = 5
            OnClick = mAddMoveBtnClick
          end
          object mDeleteSequenceBtn: TButton
            Left = 63
            Top = 44
            Width = 41
            Height = 28
            Caption = 'Delete'
            TabOrder = 6
            OnClick = mDeleteSequenceClick
          end
          object mAddSeqBtn: TButton
            Left = 16
            Top = 44
            Width = 41
            Height = 28
            Caption = 'Add'
            TabOrder = 7
            OnClick = mAddSeqBtnClick
          end
          object mDeleteMoveBtn: TButton
            Left = 143
            Top = 142
            Width = 58
            Height = 25
            Caption = 'Del Move'
            TabOrder = 8
            OnClick = deleteMove
          end
        end
        object ScrollBox1: TScrollBox
          Left = 0
          Top = 0
          Width = 306
          Height = 495
          Align = alLeft
          TabOrder = 1
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'Logging'
        ImageIndex = 4
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object BottomPanel: TPanel
          Left = 0
          Top = 0
          Width = 747
          Height = 495
          Align = alClient
          TabOrder = 0
          object infoMemo: TMemo
            Left = 1
            Top = 51
            Width = 745
            Height = 443
            Align = alClient
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ScrollBars = ssVertical
            TabOrder = 0
            WordWrap = False
          end
          object ToolBar1: TToolBar
            Left = 1
            Top = 1
            Width = 745
            Height = 50
            ButtonHeight = 44
            Caption = 'ToolBar1'
            TabOrder = 1
            object BitBtn2: TBitBtn
              Left = 0
              Top = 0
              Width = 75
              Height = 44
              Caption = 'Clear'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
              OnClick = BitBtn3Click
            end
          end
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 304
    Top = 648
    object checkForDevices: TAction
      Caption = 'Devices Check'
      OnExecute = checkForDevicesExecute
    end
    object addDevicesToListBox: TAction
      Caption = 'Connect All'
    end
    object identifyCurrent: TAction
      Caption = 'Identify'
    end
    object homeDevice: TAction
      Caption = 'Home'
    end
    object jogForward: TAction
      Caption = 'Fwd'
    end
    object jogBackwards: TAction
      Caption = 'Rev'
    end
    object moveForward: TAction
      Caption = 'Forward'
    end
    object moveBackward: TAction
      Caption = 'Backward'
    end
    object stopAllA: TAction
      Caption = 'Stop All'
      OnExecute = stopAllAExecute
    end
    object initBotA: TAction
      Caption = 'Initialize'
    end
    object ShutDownA: TAction
      Caption = 'ShutDown'
      OnExecute = ShutDownAExecute
    end
    object FileExit1: TFileExit
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = ShutDownTimerTimer
    Left = 32
    Top = 648
  end
  object StatusTimer: TTimer
    Enabled = False
    Interval = 500
    Left = 120
    Top = 648
  end
  object mSequenceTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = mSequenceTimerTimer
    Left = 456
    Top = 320
  end
end
