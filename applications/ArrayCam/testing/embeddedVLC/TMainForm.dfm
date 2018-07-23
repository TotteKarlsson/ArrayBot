object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'MainForm'
  ClientHeight = 950
  ClientWidth = 1189
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1189
    Height = 950
    Align = alClient
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 1
      Top = 660
      Width = 1187
      Height = 86
      Align = alBottom
      Caption = 'BitBtn1'
      TabOrder = 0
      OnClick = BitBtn1Click
    end
    object ProgressBar1: TProgressBar
      Left = 1
      Top = 746
      Width = 1187
      Height = 17
      Align = alBottom
      TabOrder = 2
    end
    object infoMemo: TMemo
      Left = 1
      Top = 763
      Width = 1187
      Height = 186
      Align = alBottom
      Lines.Strings = (
        'infoMemo')
      ScrollBars = ssVertical
      TabOrder = 1
      WordWrap = False
    end
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 240
      Height = 659
      Align = alLeft
      TabOrder = 3
      inline THDMIStreamerFrame1: THDMIStreamerFrame
        Left = 1
        Top = 1
        Width = 238
        Height = 247
        Align = alTop
        AutoSize = True
        TabOrder = 0
        ExplicitLeft = 1
        ExplicitTop = 1
        ExplicitWidth = 238
        inherited SettingsGB: TGroupBox
          Width = 238
          ExplicitWidth = 238
        end
        inherited StartRecordingBtn: TArrayBotButton
          Width = 238
          ExplicitWidth = 238
        end
      end
    end
    object VLCPlugin21: TVLCPlugin2
      Left = 241
      Top = 1
      Width = 947
      Height = 659
      Align = alClient
      TabOrder = 4
      OnMediaPlayerPlaying = VLCPlugin21MediaPlayerPlaying
      OnMediaPlayerTimeChanged = VLCPlugin21MediaPlayerTimeChanged
      OnMediaPlayerLengthChanged = VLCPlugin21MediaPlayerLengthChanged
      ExplicitLeft = 552
      ExplicitTop = 136
      ExplicitWidth = 320
      ExplicitHeight = 240
      ControlData = {
        07000000280043006F0075006E007400290003000D0000000800000041007500
        74006F004C006F006F0070000B000000080000004100750074006F0050006C00
        610079000B00FFFF090000004200610063006B0043006F006C006F0072000300
        00000000070000004200610073006500550052004C0008000000000008000000
        4200720061006E00640069006E0067000B00FFFF0C0000004500780074006500
        6E00740048006500690067006800740003001C4400000B000000450078007400
        65006E007400570069006400740068000300E061000011000000460075006C00
        6C00730063007200650065006E0045006E00610062006C00650064000B00FFFF
        030000004D0052004C0008000000000009000000530074006100720074005400
        69006D0065000300000000000700000054006F006F006C006200610072000B00
        FFFF07000000560069007300690062006C0065000B00FFFF0600000056006F00
        6C0075006D006500030064000000}
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = ShutDownTimerTimer
    Left = 344
    Top = 160
  end
end
