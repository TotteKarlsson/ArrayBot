#pragma hdrstop
#include "TSensorsDataModule.h"
#include "TPGDataModule.h"
#include "dslLogger.h"
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

using namespace std;
using namespace dsl;
TSensorsDataModule *sensorsDM;

//---------------------------------------------------------------------------
__fastcall TSensorsDataModule::TSensorsDataModule(TComponent* Owner)
	: TDataModule(Owner)
{}

//---------------------------------------------------------------------------
bool TSensorsDataModule::insertSensorData(WatchDogSensor& s)
{
    if(!pgDM || pgDM->SQLConnection1->Connected == false)
    {
        Log(lError) << "No DB Session...";
        return false;
    }

    static TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = pgDM->SQLConnection1;
    tq->SQLConnection->AutoClone = false;
    stringstream q;
    q <<"INSERT INTO sensordata (location, sensor_id, data1, data2, data3) VALUES ('"
                <<s.getLocationID()	<<"', '"
                <<s.getDeviceID()	<<"', '"
                <<s.getTemperature()<<"', '"
                <<s.getHumidity()	<<"', '"
                <<s.getDewPoint()
                <<"')";

    Log(lDebug) <<"Sensor Data Insertion Query: "<<q.str();
    tq->SQL->Add(q.str().c_str());
    tq->ExecSQL();
    tq->Close();
    tq->SQL->Clear();
    q.str("");

	return true;
}


