#pragma hdrstop
#include "TATDBSensorsDataModule.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

using namespace dsl;

TatdbSensorsDM *atdbSensorsDM;

//---------------------------------------------------------------------------
__fastcall TatdbSensorsDM::TatdbSensorsDM(TComponent* Owner)
	: TDataModule(Owner)
{
}

//---------------------------------------------------------------------------
bool TatdbSensorsDM::insertSensorData(int sensorID, double val1, double val2)
{
    if(!atdbDM || atdbDM->SQLConnection1->Connected == false)
    {
        Log(lError) << "No DB Session...";
        return false;
    }

    //Create some local variables
    int sensor_id(sensorID);
	double v1(val1), v2(val2);

    //Add image to database
    //Make sure the barcode exists in the database..
    TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = atdbDM->SQLConnection1;
    tq->SQLConnection->AutoClone = false;
    stringstream q;
    q <<"INSERT INTO sensordata (sensor_id, data1, data2) VALUES ('"
                <<sensor_id<<"', '"
                <<v1<<"', '"
                <<v2
                <<"')";

    string s(q.str());
    Log(lDebug) <<"Sensor Data Insertion Query: "<<s;
    tq->SQL->Add(q.str().c_str());
    tq->ExecSQL();
    tq->Close();
    tq->SQL->Clear();
    q.str("");

//    Session& ses = *mTheSession;
//
//
//	Statement s(ses);
//    s << "INSERT INTO sensordata (sensor_id, data1, data2) VALUES(?, ?, ?)", use(sensor_id), use(v1), use(v2), now;
//    s.reset(ses);

	return true;
}


