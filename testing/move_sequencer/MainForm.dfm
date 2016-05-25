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
  Position = poDesktopCenter
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
            Left = 264
            Top = 15
            Width = 52
            Height = 13
            Caption = 'Sequences'
          end
          object GroupBox2: TGroupBox
            Left = 16
            Top = 17
            Width = 169
            Height = 206
            Caption = 'Move'
            TabOrder = 0
            object mMovePosE: TFloatLabeledEdit
              Left = 16
              Top = 59
              Width = 65
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
              Top = 107
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
              Top = 107
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
              Top = 147
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
              Top = 17
              Width = 105
              Height = 21
              TabOrder = 4
              Text = 'Select Motor'
              OnChange = MotorsCBChange
            end
          end
          object mStartBtn: TButton
            Left = 32
            Top = 296
            Width = 75
            Height = 25
            Caption = 'Start'
            TabOrder = 1
            OnClick = mStartBtnClick
          end
          object Button2: TButton
            Left = 282
            Top = 296
            Width = 75
            Height = 25
            Caption = 'Stop'
            TabOrder = 2
          end
          object Button3: TButton
            Left = 201
            Top = 296
            Width = 75
            Height = 25
            Caption = 'Pause'
            TabOrder = 3
          end
          object mMovesLB: TListBox
            Left = 264
            Top = 68
            Width = 121
            Height = 97
            ItemHeight = 13
            TabOrder = 4
            OnClick = mMovesLBClick
          end
          object mFwdBtn: TButton
            Left = 113
            Top = 296
            Width = 75
            Height = 25
            Caption = 'Fwd'
            TabOrder = 5
            OnClick = mStartBtnClick
          end
          object SequencesCB: TComboBox
            Left = 264
            Top = 34
            Width = 121
            Height = 21
            ItemIndex = 0
            TabOrder = 6
            Text = 'MoveSequence'
            OnChange = SequencesCBChange
            Items.Strings = (
              'MoveSequence')
          end
          object mSaveSequenceBtn: TButton
            Left = 262
            Top = 171
            Width = 51
            Height = 25
            Caption = 'Save'
            TabOrder = 7
            OnClick = mSaveSequenceBtnClick
          end
          object mAddMoveBtn: TButton
            Left = 194
            Top = 79
            Width = 58
            Height = 25
            Caption = 'Add Move'
            TabOrder = 8
            OnClick = mAddMoveBtnClick
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
end
