object SequencerButtonsFrame: TSequencerButtonsFrame
  Left = 0
  Top = 0
  Width = 669
  Height = 123
  TabOrder = 0
  OnEnter = FrameEnter
  object mSequenceStatusTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = mSequenceStatusTimerTimer
    Left = 463
    Top = 39
  end
end
