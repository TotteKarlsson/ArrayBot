object SensorsDataModule: TSensorsDataModule
  OldCreateOrder = False
  Height = 348
  Width = 450
  object SensorDataDS: TSQLDataSet
    CommandText = 'SELECT * from sensordata order by date_time'
    MaxBlobSize = -1
    Params = <>
    SQLConnection = pgDM.SQLConnection1
    Left = 48
    Top = 88
  end
  object SensorDataProvider: TDataSetProvider
    DataSet = SensorDataDS
    Left = 168
    Top = 88
  end
  object SensorDataCDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'SensorDataProvider'
    Left = 288
    Top = 88
  end
end
