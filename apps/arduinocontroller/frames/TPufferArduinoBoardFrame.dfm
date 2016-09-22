inherited PufferArduinoBoardFrame: TPufferArduinoBoardFrame
  Width = 496
  AutoSize = False
  ExplicitWidth = 496
  inherited GroupBox1: TGroupBox
    Width = 496
    Caption = 'Puffer Board'
    ExplicitWidth = 496
    object mPufferDurationE: TIntegerLabeledEdit [0]
      Left = 259
      Top = 72
      Width = 121
      Height = 31
      EditLabel.Width = 172
      EditLabel.Height = 23
      EditLabel.Caption = 'Puffer Duration (ms)'
      TabOrder = 4
      Text = '-1'
      OnKeyDown = updateParameter
      Value = -1
    end
    inherited mSendMSGE: TSTDStringLabeledEdit
      Text = '<none>'
      OnKeyDown = mSendMSGEKeyDown
      Value = '<none>'
    end
    inherited mSendBtn: TButton
      Top = 131
      TabOrder = 5
      OnClick = mSendBtnClick
      ExplicitTop = 131
    end
  end
  inherited mCheckConnectionTimer: TTimer
    Left = 336
    Top = 208
  end
end
