inherited PufferArduinoBoardFrame: TPufferArduinoBoardFrame
  Width = 584
  AutoSize = False
  ExplicitWidth = 584
  inherited GroupBox1: TGroupBox
    Width = 584
    Caption = 'Puffer Board'
    ExplicitWidth = 584
    inherited mSendMSGE: TSTDStringLabeledEdit
      Text = '<none>'
      Value = '<none>'
    end
    object mPufferDurationE: TIntegerLabeledEdit
      Left = 288
      Top = 72
      Width = 121
      Height = 31
      EditLabel.Width = 172
      EditLabel.Height = 23
      EditLabel.Caption = 'Puffer Duration (ms)'
      TabOrder = 5
      Text = '-1'
      OnKeyDown = updateParameter
      Value = -1
    end
    object mPufferValveSpeedE: TIntegerLabeledEdit
      Left = 288
      Top = 136
      Width = 121
      Height = 31
      EditLabel.Width = 221
      EditLabel.Height = 23
      EditLabel.Caption = 'Puffer valve speed (0-255)'
      TabOrder = 6
      Text = '-1'
      OnKeyDown = updateParameter
      Value = -1
    end
  end
  inherited Timer1: TTimer
    Left = 336
    Top = 208
  end
end
