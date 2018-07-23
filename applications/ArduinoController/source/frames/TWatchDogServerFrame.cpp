#include <vcl.h>
#pragma hdrstop
#include "TWatchDogServerFrame.h"
#include "dslIniFileProperties.h"
#include "core/WatchDogSensor.h"
#include "TWatchDogSensorFrame.h"
#include "TSensorsDataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma link "dslTIntegerLabeledEdit"
#pragma resource "*.dfm"
TWatchDogServerFrame *WatchDogServerFrame;

using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TWatchDogServerFrame::TWatchDogServerFrame(TComponent* Owner)
	: TFrame(Owner),
    mWatchDogServer(NULL),
    mReadSensorsThread("c:\\usr\\bin\\snmpget.exe"),
    mSNMPWalkThread("c:\\usr\\bin\\snmpwalk.exe")
{
	mReadSensorsThread.assignCallBacks(onSensorReadStart, onSensorReadProgress, onSensorReadExit);
}

bool TWatchDogServerFrame::canClose()
{
	return (mSNMPWalkThread.isRunning() || mReadSensorsThread.isRunning()) ? false : true;
}

void TWatchDogServerFrame::shutDown()
{
	mSNMPWalkThread.stop();
    mReadSensorsThread.stop();
}

void TWatchDogServerFrame::assignWatchDogServer(WatchDogServer* s)
{
	mWatchDogServer = s;
    ServerIPE->assignExternalProperty(&mWatchDogServer->getServerIPProperty(), true);
    ServerIPE->update();

	PeriodicReadE->assignExternalProperty(&mWatchDogServer->getReadCycleTimeProperty(), true);
}

void TWatchDogServerFrame::allocateSensorFrames()
{
	for(int i = 0; i < mWatchDogServer->getNumberOfSensors(); i++)
    {
  		WatchDogSensor*  s = mWatchDogServer->getSensor(i);

        if(!s)
        {
        	continue;
        }

        Log(lInfo) << "Creating sensor frame for sensor with ID: "<<s->getDeviceID();
        TWatchDogSensorFrame* f = new TWatchDogSensorFrame(this);
        f->populate(s);
        f->Parent = SensorPanel;
        f->Align = alLeft;
        mSensorFrames.push_back(f);
    }
}

void __fastcall TWatchDogServerFrame::WalkBtnClick(TObject *Sender)
{
	//Start 'walk' thread
	mSNMPWalkThread.setWalkParameters(ServerIPE->getValue(), "1.3.6.1.4");
    mSNMPWalkThread.start(true);
}

void __fastcall TWatchDogServerFrame::ReadSensorsBtnClick(TObject *Sender)
{
	//We are to run an external executable
    mReadSensorsThread.assignServer(mWatchDogServer);
    mReadSensorsThread.start();
}

void __fastcall	TWatchDogServerFrame::onSensorReadStart(int x, int y)
{
	Log(lInfo) << "Starting sensor reads";
}

void __fastcall	TWatchDogServerFrame::onSensorReadProgress(int x, int y)
{
	string *msg (NULL);
	if(y)
    {
		msg = (string*) (y);
    }

    if(msg)
    {
	    mEnvSensorDataString = (*msg);
    	TThread::Synchronize(NULL, consumeEnvironmentSensorData);
		Log(lInfo) << "Sensor reads progressed: "<< *msg;
    }
}

void __fastcall	TWatchDogServerFrame::onSensorReadExit(int x, int y)
{
	Log(lInfo) << "Sensor reads finished";
}

void __fastcall TWatchDogServerFrame::consumeEnvironmentSensorData()
{
	//Parse the EnvSensorDataString
	StringList tokens(mEnvSensorDataString, ':');
    if(tokens.size() != 1)
    {
		Log(lError) << "Bad string format in " << __FUNC__;
        return;
    }

    StringList tok1(tokens[0],'='); //ID

    //Identify the actual sensor by its ID
    WatchDogSensor* sensor = mWatchDogServer->getSensorWithID(trim(tok1[1]));

    if(!sensor)
    {
    	Log(lError) << "Failed to identify sensor with ID: " <<trim(tok1[1]);
        return;
    }

    //Update sensor frame
    for(int i = 0; i < mSensorFrames.size(); i++)
    {
    	if(mSensorFrames[i] && mSensorFrames[i]->getSensor() == sensor)
        {
			mSensorFrames[i]->populate(sensor);
        }
    }

    //Log to database
    if(sensor->isPresent())
    {
    	sensorsDM->insertSensorData((*sensor));
    }
    else
    {
    	Log(lError) << "Sensor with ID " << sensor->getDeviceID()<<" is unavailable!";
    }
}

//---------------------------------------------------------------------------
void __fastcall TWatchDogServerFrame::EnvSensorsReadsTimerTimer(TObject *Sender)
{
	if(!mReadSensorsThread.isRunning())
    {
		//We are to run an external executable
	    mReadSensorsThread.assignServer(mWatchDogServer);
    	mReadSensorsThread.start();
    }
    else
    {
    	Log(lDebug) << "Reading sensor thread is already running";
    }
}

//---------------------------------------------------------------------------
void __fastcall TWatchDogServerFrame::StartReadsBtnClick(TObject *Sender)
{
	EnvSensorsReadsTimer->Enabled = !EnvSensorsReadsTimer->Enabled;
	EnvSensorsReadsTimer->Interval = PeriodicReadE->getValue() * 1000; //ms
	StartReadsBtn->Caption = (EnvSensorsReadsTimer->Enabled) ? "Stop Periodic Reads" : "Start Periodic Reads";
}


