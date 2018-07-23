#ifndef TSensorsDataModuleH
#define TSensorsDataModuleH
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <string>
#include "WatchDogSensor.h"
//---------------------------------------------------------------------------

using std::string;


class PACKAGE TSensorsDataModule : public TDataModule
{
    __published:
        TSQLDataSet *SensorDataDS;
        TDataSetProvider *SensorDataProvider;
        TClientDataSet *SensorDataCDS;

	private:

    public:
                        __fastcall 	TSensorsDataModule(TComponent* Owner);
        bool 						insertSensorData(WatchDogSensor& s);
};


extern PACKAGE TSensorsDataModule *sensorsDM;
#endif
