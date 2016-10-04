inherited SensorsArduinoFrame: TSensorsArduinoFrame
  Width = 270
  Height = 263
  AutoSize = False
  ExplicitWidth = 270
  ExplicitHeight = 263
  inherited GroupBox1: TGroupBox
    Width = 270
    Height = 263
    Caption = 'Sensor Board'
    ExplicitWidth = 270
    ExplicitHeight = 263
    inherited mBaudRateE: TIntegerLabeledEdit [0]
    end
    inherited mConnectBtn: TButton [1]
    end
    inherited mCommPortE: TIntegerLabeledEdit [2]
    end
    inherited mSendMSGE: TSTDStringLabeledEdit
      OnKeyDown = mSendMSGEKeyDown
    end
    inherited mSendBtn: TButton
      OnClick = mSendBtnClick
    end
  end
end
