object ReticlePopupForm: TReticlePopupForm
  Left = 0
  Top = 0
  AlphaBlendValue = 200
  AutoSize = True
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  ClientHeight = 178
  ClientWidth = 155
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
    Left = 0
    Top = 0
    Width = 155
    Height = 178
    Align = alTop
    Caption = 'Reticle'
    TabOrder = 0
    OnClick = GroupBox1Click
    ExplicitWidth = 161
    object mReticleRadiusTB: TTrackBar
      Left = 2
      Top = 15
      Width = 151
      Height = 33
      Hint = 'Reticle Radius'
      Align = alTop
      Anchors = []
      Max = 200
      Position = 1
      ShowSelRange = False
      TabOrder = 0
      TickStyle = tsNone
      OnChange = mReticleTBChange
      ExplicitWidth = 157
    end
    object mReticleCenterXTB: TTrackBar
      Left = 2
      Top = 48
      Width = 151
      Height = 33
      Hint = 'Reticle X Position'
      Align = alTop
      Anchors = []
      Max = 200
      Min = -200
      Position = 1
      ShowSelRange = False
      TabOrder = 1
      TickStyle = tsNone
      OnChange = mReticleTBChange
      ExplicitWidth = 157
    end
    object mReticleCenterYTB: TTrackBar
      Left = 2
      Top = 81
      Width = 151
      Height = 33
      Hint = 'Reticle Y Position'
      Align = alTop
      Anchors = []
      Max = 200
      Min = -200
      Position = 1
      ShowSelRange = False
      TabOrder = 2
      TickStyle = tsNone
      OnChange = mReticleTBChange
      ExplicitWidth = 157
    end
    object mCenterReticleBtn: TArrayBotButton
      Left = 56
      Top = 110
      Width = 75
      Height = 25
      Caption = 'Reset'
      TabOrder = 3
      OnClick = mCenterReticleBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
    object mReticleVisibilityCB: TPropertyCheckBox
      Left = 11
      Top = 150
      Width = 97
      Height = 17
      Caption = 'Visible'
      TabOrder = 4
      OnClick = mReticleVisibilityCBClick
    end
  end
  object ShowTimer: TTimer
    Enabled = False
    Interval = 4000
    OnTimer = ShowTimerTimer
    Left = 8
    Top = 104
  end
end
