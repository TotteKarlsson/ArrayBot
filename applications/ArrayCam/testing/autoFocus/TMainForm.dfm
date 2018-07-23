object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Array Cam 0.5'
  ClientHeight = 712
  ClientWidth = 1597
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDefault
  ShowHint = True
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 19
  object Splitter2: TSplitter
    Left = 745
    Top = 0
    Height = 509
    Align = alRight
    ExplicitLeft = 1015
    ExplicitTop = 52
    ExplicitHeight = 814
  end
  object Splitter1: TSplitter
    Left = 0
    Top = 509
    Width = 1597
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 0
    ExplicitWidth = 487
  end
  object MainContentPanel: TPanel
    Left = 748
    Top = 0
    Width = 818
    Height = 509
    Align = alRight
    Caption = 'MainContentPanel'
    Constraints.MinWidth = 786
    TabOrder = 0
    object Panel1: TPanel
      Left = 1
      Top = 1
      Width = 816
      Height = 507
      Align = alClient
      Caption = 'Panel1'
      TabOrder = 0
      DesignSize = (
        816
        507)
      object MainPC: TPageControl
        Left = 1
        Top = 1
        Width = 814
        Height = 505
        ActivePage = Main
        Align = alClient
        TabHeight = 80
        TabOrder = 0
        TabWidth = 100
        OnChange = PageControlChange
        object Main: TTabSheet
          Caption = 'Main'
          ImageIndex = 5
          object ScrollBox1: TScrollBox
            Left = 0
            Top = 0
            Width = 806
            Height = 415
            Align = alClient
            TabOrder = 0
          end
        end
        object TabSheet9: TTabSheet
          Caption = 'Navitar'
          ImageIndex = 7
          object GroupBox13: TGroupBox
            Left = 0
            Top = 0
            Width = 313
            Height = 415
            Align = alLeft
            Caption = 'Misc.'
            Color = clBtnFace
            ParentColor = False
            TabOrder = 0
            object NavitarControllerConnectBtn: TButton
              Left = 20
              Top = 24
              Width = 153
              Height = 57
              Caption = 'Connect'
              TabOrder = 0
              OnClick = NavitarControllerConnectBtnClick
            end
            object ControllerInfoGB: TGroupBox
              Left = 2
              Top = 298
              Width = 309
              Height = 115
              Align = alBottom
              Caption = 'Controller Info'
              TabOrder = 1
              object Label12: TLabel
                Left = 16
                Top = 24
                Width = 82
                Height = 19
                Caption = 'Product ID:'
                Transparent = True
              end
              object Label13: TLabel
                Left = 16
                Top = 45
                Width = 132
                Height = 19
                Caption = 'Hardware Version:'
                Transparent = True
              end
              object Label14: TLabel
                Left = 16
                Top = 66
                Width = 120
                Height = 19
                Caption = 'Software Version'
                Transparent = True
              end
              object Label15: TLabel
                Left = 16
                Top = 85
                Width = 109
                Height = 19
                Caption = 'Firmware Date:'
                Transparent = True
              end
              object ProdIdLbl: TLabel
                Left = 166
                Top = 22
                Width = 28
                Height = 19
                Caption = 'N/A'
                Transparent = True
              end
              object HWVerLbl: TLabel
                Left = 166
                Top = 43
                Width = 28
                Height = 19
                Caption = 'N/A'
                Transparent = True
              end
              object SWVerLbl: TLabel
                Left = 166
                Top = 64
                Width = 28
                Height = 19
                Caption = 'N/A'
                Transparent = True
              end
              object FirmWareDateLbl: TLabel
                Left = 166
                Top = 85
                Width = 28
                Height = 19
                Caption = 'N/A'
                Transparent = True
              end
            end
          end
          object Panel8: TPanel
            Left = 313
            Top = 0
            Width = 493
            Height = 415
            Align = alClient
            TabOrder = 1
          end
        end
        object TabSheet1: TTabSheet
          Caption = 'Settings'
          ImageIndex = 6
          object MiscPageControl: TPageControl
            Left = 0
            Top = 0
            Width = 806
            Height = 415
            ActivePage = TabSheet5
            Align = alClient
            TabOrder = 0
            OnChange = PageControlChange
            OnExit = PageControlExit
            object TabSheet5: TTabSheet
              Caption = 'ArrayCam Server'
              ImageIndex = 2
              object GroupBox1: TGroupBox
                Left = 0
                Top = 0
                Width = 798
                Height = 193
                Align = alTop
                Caption = 'Server'
                TabOrder = 0
                object NrOfArrayCamServerClients: TIntLabel
                  Left = 166
                  Top = 120
                  Width = 15
                  Height = 19
                  Caption = '-1'
                  Value = -1
                  TheFont.Charset = DEFAULT_CHARSET
                  TheFont.Color = clWindowText
                  TheFont.Height = -16
                  TheFont.Name = 'Tahoma'
                  TheFont.Style = []
                end
                object Label2: TLabel
                  Left = 16
                  Top = 120
                  Width = 134
                  Height = 19
                  Caption = 'Number of Clients:'
                end
                object ArrayCamServerPortE: TIntegerLabeledEdit
                  Left = 16
                  Top = 56
                  Width = 153
                  Height = 27
                  EditLabel.Width = 155
                  EditLabel.Height = 19
                  EditLabel.Caption = 'ArrayCam Server Port'
                  TabOrder = 0
                  Text = '0'
                end
                object SendServerStatusMessageBtn: TArrayBotButton
                  Left = 200
                  Top = 40
                  Width = 153
                  Height = 49
                  Caption = 'Broadcast Status'
                  TabOrder = 1
                  SoundID = 'BUTTON_CLICK_4'
                end
              end
            end
            object TabSheet11: TTabSheet
              Caption = 'Media'
              ImageIndex = 3
              object GroupBox6: TGroupBox
                Left = 0
                Top = 0
                Width = 798
                Height = 89
                Align = alTop
                BiDiMode = bdLeftToRight
                Caption = 'Media'
                ParentBiDiMode = False
                TabOrder = 0
                object BrowseForMediaFolderBtn: TButton
                  Left = 339
                  Top = 47
                  Width = 27
                  Height = 25
                  Caption = '...'
                  TabOrder = 0
                  OnClick = BrowseForFolderClick
                end
                object MediaFolderE: TSTDStringLabeledEdit
                  Left = 16
                  Top = 46
                  Width = 317
                  Height = 27
                  EditLabel.Width = 128
                  EditLabel.Height = 19
                  EditLabel.Caption = 'Media Root Folder'
                  TabOrder = 1
                  OnKeyDown = MediaFolderEKeyDown
                end
              end
            end
          end
        end
      end
      object Button1: TButton
        Left = 783
        Top = 1
        Width = 25
        Height = 25
        Action = ToggleMainContentPanelA
        Anchors = [akTop, akRight]
        Caption = 'x'
        TabOrder = 1
      end
    end
  end
  object LeftPanel: TPanel
    Left = 0
    Top = 0
    Width = 745
    Height = 509
    Align = alClient
    BevelEdges = []
    TabOrder = 1
    object mMainPhotoPanel: TPanel
      Left = 1
      Top = 1
      Width = 743
      Height = 507
      Margins.Left = 0
      Margins.Right = 0
      Align = alClient
      BevelEdges = []
      BevelOuter = bvNone
      TabOrder = 0
      OnResize = mMainPhotoPanelResize
      object mCamera1BackPanel: TPanel
        Left = 1
        Top = 0
        Width = 850
        Height = 673
        Margins.Left = 0
        Margins.Right = 0
        BevelOuter = bvNone
        Caption = 'No Camera...'
        TabOrder = 0
        object mPB: TPaintBox
          Left = 0
          Top = 30
          Width = 850
          Height = 643
          Margins.Left = 0
          Margins.Top = 0
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alClient
          Color = clActiveCaption
          ParentColor = False
          PopupMenu = CameraPopup
          OnClick = mPBClick
          OnMouseDown = mPBMouseDown
          OnMouseMove = mPBMouseMove
          OnMouseUp = mPBMouseUp
          ExplicitTop = 33
        end
        object CameraHC: THeaderControl
          Left = 0
          Top = 0
          Width = 850
          Height = 30
          BiDiMode = bdLeftToRight
          Sections = <
            item
              Alignment = taCenter
              BiDiMode = bdLeftToRight
              ImageIndex = -1
              ParentBiDiMode = False
              Text = 'Camera Settings'
              Width = 130
            end
            item
              Alignment = taCenter
              ImageIndex = -1
              Text = 'Reticle Settings'
              Width = 150
            end
            item
              Alignment = taCenter
              ImageIndex = -1
              Text = 'Show Reticle'
              Width = 110
            end
            item
              Alignment = taCenter
              ImageIndex = -1
              Text = 'Reset Reticle'
              Width = 110
            end
            item
              Alignment = taCenter
              ImageIndex = -1
              Text = 'Maximize Camera View'
              Width = 180
            end
            item
              ImageIndex = -1
              Text = 'Show Image Center'
              Width = 160
            end>
          OnSectionClick = CameraHCSectionClick
          ParentBiDiMode = False
          PopupMenu = CameraPopup
          StyleElements = [seFont, seClient]
        end
      end
      object MPEGPanel: TFlowPanel
        Left = 0
        Top = 0
        Width = 743
        Height = 43
        Align = alTop
        AutoSize = True
        TabOrder = 1
      end
      object Bpanel: TPanel
        Left = 0
        Top = 425
        Width = 743
        Height = 82
        Align = alBottom
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 2
        object ToolBar2: TToolBar
          Left = 1
          Top = 1
          Width = 512
          Height = 80
          Align = alLeft
          ButtonHeight = 75
          Caption = 'ToolBar2'
          TabOrder = 0
          object startAF: TArrayBotButton
            Left = 0
            Top = 0
            Width = 161
            Height = 75
            Align = alLeft
            Caption = 'Start AutoFocus'
            TabOrder = 1
            OnClick = startAFClick
            SoundID = 'BUTTON_CLICK_4'
          end
          object TakeSnapShotBtn: TArrayBotButton
            Left = 161
            Top = 0
            Width = 161
            Height = 75
            Align = alLeft
            Caption = 'Take SnapShot'
            TabOrder = 0
            OnClick = TakeSnapShotBtnClick
            SoundID = 'BUTTON_CLICK_4'
          end
        end
      end
    end
  end
  object ToggleMainContentBtn: TButton
    Left = 1566
    Top = 0
    Width = 31
    Height = 509
    Action = ToggleMainContentPanelA
    Align = alRight
    Caption = '<'
    TabOrder = 2
    Visible = False
  end
  inline TLogMemoFrame1: TLogMemoFrame
    Left = 0
    Top = 512
    Width = 1597
    Height = 200
    Align = alBottom
    TabOrder = 3
    ExplicitTop = 512
    ExplicitWidth = 1597
    ExplicitHeight = 200
    inherited Panel1: TPanel
      Width = 1597
      Height = 200
      ExplicitWidth = 1597
      ExplicitHeight = 200
      inherited GroupBox1: TGroupBox
        Width = 1595
        ExplicitWidth = 1595
        inherited ToolBar1: TToolBar
          Top = 21
          Height = 27
          ExplicitTop = 21
          ExplicitHeight = 27
        end
      end
      inherited infoMemo: TMemo
        Width = 1595
        Height = 148
        ExplicitWidth = 1595
        ExplicitHeight = 148
      end
    end
  end
  object BindingsList1: TBindingsList
    Methods = <>
    OutputConverters = <>
    Left = 148
    Top = 165
  end
  object mShutDownTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = mShutDownTimerTimer
    Left = 424
    Top = 424
  end
  object mMediaPopup: TPopupMenu
    Left = 304
    Top = 264
    object Delete1: TMenuItem
      Caption = 'Delete'
    end
    object DeleteAll1: TMenuItem
      Caption = 'Delete All'
    end
  end
  object mStartupTimer: TTimer
    Enabled = False
    Interval = 250
    OnTimer = mStartupTimerTimer
    Left = 328
    Top = 424
  end
  object CameraPopup: TPopupMenu
    Left = 120
    Top = 304
    object FittoScreen1: TMenuItem
      Action = FitToScreenA
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object N111: TMenuItem
      Action = Zoom1To1A
    end
    object N121: TMenuItem
      Action = Zoom1To2A
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object OpenSettings1: TMenuItem
      Action = OpenCameraSettingsA
    end
    object N7: TMenuItem
      Caption = '-'
    end
    object oggleControlBar1: TMenuItem
      Action = ToggleControlBar
      AutoCheck = True
    end
  end
  object ReticlePopup: TPopupMenu
    Left = 256
    Top = 128
    object Reset1: TMenuItem
      Caption = 'Reset'
    end
  end
  object MainMenu1: TMainMenu
    Left = 312
    Top = 96
    object File1: TMenuItem
      Caption = 'File'
      object Exit1: TMenuItem
        Action = FileExit1
      end
    end
    object Camera1: TMenuItem
      Caption = 'Camera'
      object FitToScreenA1: TMenuItem
        Action = FitToScreenA
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object Zoom111: TMenuItem
        Action = Zoom1To1A
      end
      object Zoom121: TMenuItem
        Action = Zoom1To2A
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object CameraSettings1: TMenuItem
        Action = OpenCameraSettingsA
      end
    end
    object Misc1: TMenuItem
      Caption = 'Options'
      object ShowHideMainContentPanel1: TMenuItem
        Action = ToggleMainContentPanelA
        AutoCheck = True
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object OpenLoggerForm1: TMenuItem
        Caption = 'Open Logger Form'
        OnClick = OpenLoggerForm1Click
      end
      object N6: TMenuItem
        Caption = '-'
      end
      object ThemesMenu: TMenuItem
        Caption = 'Theme'
      end
    end
  end
  object MenuActions: TActionList
    Left = 96
    Top = 144
    object FileExit1: TFileExit
      Category = 'File'
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
    object OpenHandWheelPositionFormA: TAction
      Category = 'File'
      Caption = 'Open Handwheel Position Form'
      Hint = 'Open Handwheel position Form'
    end
    object ToggleMainContentPanelA: TAction
      Category = 'File'
      AutoCheck = True
      Caption = 'Show/Hide Main Content Panel'
      OnExecute = ToggleMainContentPanelAExecute
    end
    object OpenCloseShortcutForm: TAction
      Category = 'File'
      Caption = 'Open Actions'
    end
    object ToggleControlBar: TAction
      Category = 'Misc'
      AutoCheck = True
      Caption = 'Toggle ControlBar'
    end
    object BrowseForFolder1: TBrowseForFolder
      Category = 'File'
      Caption = '...'
      DialogCaption = 'BrowseForFolder1'
      BrowseOptions = [bifEditBox, bifNewDialogStyle, bifUseNewUI]
      BrowseOptionsEx = []
    end
  end
  object CameraActions: TActionList
    Left = 56
    Top = 192
    object FitToScreenA: TAction
      Category = 'Camera'
      Caption = 'Fit to Screen'
      Hint = 'Fit To Screen'
      OnExecute = FitToScreenAExecute
    end
    object Zoom1To1A: TAction
      Category = 'Camera'
      Caption = 'Zoom 1:1'
      Hint = 'Zoom 1:1'
      OnExecute = Zoom1To1AExecute
    end
    object Zoom1To2A: TAction
      Category = 'Camera'
      Caption = 'Zoom 1:2'
      Hint = 'Zoom 1:2'
      OnExecute = Zoom1To2AExecute
    end
    object OpenCameraSettingsA: TAction
      Category = 'Camera'
      Caption = 'More Settings'
      Hint = 'Open Camera settings form'
      OnExecute = OpenCameraSettingsAExecute
    end
  end
  object BindingsList2: TBindingsList
    Methods = <>
    OutputConverters = <>
    Left = 416
    Top = 24
  end
  object AutoFocusTimer: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = AutoFocusTimerTimer
    Left = 578
    Top = 425
  end
end
