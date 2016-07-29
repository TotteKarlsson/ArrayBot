#pragma hdrstop
#include "abArduinoServer.h"
#include "mtkLogger.h"
#include "abArduinoIPCServerReceiver.h"
#include "mtkSocketWorker.h"
#include "abArduinoUtils.h"
#include "mtkStringUtils.h"

//---------------------------------------------------------------------------
using namespace mtk;

ArduinoServer::ArduinoServer(int portNumber)
:
IPCServer(portNumber, "ARDUINO_SERVER", createArduinoIPCReceiver),
mPufferArduino(-1),
mSensorArduino(-1),
mSectionCount(0),
mPuffAfterSectionCount(10),
mAutoPuff(true)

{
	mArduinos.push_back(&mPufferArduino);
	mArduinos.push_back(&mSensorArduino);

    //Assign receive callbacks
    mPufferArduino.assignSerialMessageReceivedCallBack(pufferMessageReceived);
    mSensorArduino.assignSerialMessageReceivedCallBack(sensorMessageReceived);
}

ArduinoServer::~ArduinoServer()
{}

void ArduinoServer::enableAutoPuff()
{
	mAutoPuff = true;

    stringstream msg;
    msg <<"AUTO_PUFF="<<toString(mAutoPuff);
   	updateClients(msg.str());
}

void ArduinoServer::disableAutoPuff()
{
	mAutoPuff = false;
    stringstream msg;
    msg <<"AUTO_PUFF="<<toString(mAutoPuff);
   	updateClients(msg.str());
}

void ArduinoServer::broadcastStatus()
{
	//These are all status messages possible
    //A client typically call this one once, to sync their UI
    stringstream msg;
    msg <<"SECTION_COUNT="<<mSectionCount;
   	updateClients(msg.str());

    msg.str("");
    msg <<"PUFF_AFTER_SECTION_COUNT="<<mPuffAfterSectionCount;
   	updateClients(msg.str());

    msg.str("");
    msg <<"AUTO_PUFF="<<toString(mAutoPuff);
   	updateClients(msg.str());
}

void ArduinoServer::resetSectionCount()
{
	mSectionCount = 0;
    stringstream msg;
    msg <<"SECTION_COUNT="<<mSectionCount;
	updateClients(msg.str());
}

//This is called from the arduino devices receive thread
void ArduinoServer::pufferMessageReceived(const string& msg)
{
    //Check what message we got from arduino device
    if(msg == "ArrayBot Puffer Init")
    {
        //Setup variables
        //Puffer duration etc..
        if(mPufferArduino.init)
        {
            mPufferArduino.init();
        }
    }
    else if (msg == "HALL_SENSOR=HIGH")
    {
        mSectionCount++;
    	if(mAutoPuff)
    	{
        	if(mSectionCount > mPuffAfterSectionCount)
        	{
        		puff();
				mSectionCount = 0;
            }
        }

        stringstream msg;
        msg <<"SECTION_COUNT="<<mSectionCount;
		updateClients(msg.str());
    }
}

void ArduinoServer::updateClients(const string msg)
{
    if(onMessageUpdateCB)
    {
        onMessageUpdateCB(msg);
    }
    broadcast(msg);
}

void ArduinoServer::setPuffAfterSectionCount(int val)
{
	mPuffAfterSectionCount = val;

    stringstream msg;
    msg <<"PUFF_AFTER_SECTION_COUNT="<<mPuffAfterSectionCount;
	updateClients(msg.str());
}

void ArduinoServer::sensorMessageReceived(const string& msg)
{
	updateClients(msg);
}

bool ArduinoServer::shutDown()
{
    IPCServer::shutDown();
	for(int i = 0; i < 1; i++)
    {
		mArduinos[i]->disConnect();
    }
    return true;
}

bool ArduinoServer::puff()
{
	return mPufferArduino.send("p");
}

//Handle simple text messages over the socket
bool ArduinoServer::processMessage(IPCMessage& msg)
{
    if(msg.isPacked())
    {
        msg.unPack();
    }

    if(compareStrings(msg, "RESET_SECTION_COUNT"))
    {
    	Log(lInfo) << "Resetting section counter";
        resetSectionCount();
    }

    if(compareStrings(msg, "GET_STATUS"))
    {
    	Log(lInfo) << "Resetting section counter";
        broadcastStatus();
    }

    if(compareStrings(msg, "ENABLE_AUTO_PUFF"))
    {
    	Log(lInfo) << "Enabling auto puffing";
        enableAutoPuff();
    }

    if(compareStrings(msg, "DISABLE_AUTO_PUFF"))
    {
    	Log(lInfo) << "Disabling auto puffing";
        disableAutoPuff();
    }

    if(startsWith(msg, "PUFF_AFTER_SECTION_COUNT"))
    {
    	Log(lInfo) << "Setting puff after section count";
		StringList l(msg,'=');
        if(l.size()==2)
        {
        	setPuffAfterSectionCount(toInt(l[1]));
        }

    }
    return msg.IsProcessed();
}
