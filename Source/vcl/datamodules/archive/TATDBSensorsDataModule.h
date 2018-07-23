#ifndef TATDBSensorsDataModuleH
#define TATDBSensorsDataModuleH
#include <System.Classes.hpp>
#include "TATDBDataModule.h"
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
//---------------------------------------------------------------------------


class TatdbSensorsDM : public TDataModule
{
    __published:
        TSQLDataSet *SensorDataDS;
        TDataSetProvider *SensorDataProvider;
        TClientDataSet *SensorDataCDS;

	private:

    public:
                        __fastcall 	TatdbSensorsDM(TComponent* Owner);
        bool 						insertSensorData(int sensorID, double val1, double val2);
};


extern PACKAGE TatdbSensorsDM *atdbSensorsDM;
#endif
