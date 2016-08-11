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
mAutoPuff(true),
mLEDLightONLine(3),
mLEDLightOFFLine(4),
mCoaxLightONLine(1),
mCoaxLightOFFLine(2)
{
	mArduinos.push_back(&mPufferArduino);
	mArduinos.push_back(&mSensorArduino);

    //Assign receive callbacks
    mPufferArduino.assignSerialMessageReceivedCallBack(pufferMessageReceived);
    mSensorArduino.assignSerialMessageReceivedCallBack(sensorMessageReceived);
}

ArduinoServer::~ArduinoServer()
{
    mPufferArduino.assignSerialMessageReceivedCallBack(NULL);
    mSensorArduino.assignSerialMessageReceivedCallBack(NULL);
}

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
        	if(mSectionCount >= mPuffAfterSectionCount)
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
	for(int i = 0; i < mArduinos.size(); i++)
    {
		mArduinos[i]->disConnect();
    }
    return true;
}

bool ArduinoServer::puff()
{
	return mPufferArduino.send("p");
}

bool ArduinoServer::turnLEDLightOn()
{
	return mSensorArduino.send(mLEDLightONLine);
}

bool ArduinoServer::turnLEDLightOff()
{
	return mSensorArduino.send(mLEDLightOFFLine);
}

bool ArduinoServer::turnCoaxLightOn()
{
	return mSensorArduino.send(mCoaxLightONLine);
}

bool ArduinoServer::turnCoaxLightOff()
{
	return mSensorArduino.send(mCoaxLightOFFLine);
}

bool ArduinoServer::toggleLED()
{
	static bool switcher(false);

    switcher = !switcher;
    if(switcher)
    {
		return mSensorArduino.send(mLEDLightONLine);
    }
    else
    {
		return mSensorArduino.send(mLEDLightOFFLine);
    }
}

bool ArduinoServer::toggleCoax()
{
	static bool switcher(false);

    switcher = !switcher;
    if(switcher)
    {
		return mSensorArduino.send(mCoaxLightONLine);
    }
    else
    {
		return mSensorArduino.send(mCoaxLightOFFLine);
    }
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
    else if(compareStrings(msg, "GET_STATUS"))
    {
    	Log(lInfo) << "Resetting section counter";
        broadcastStatus();
    }
    else if(compareStrings(msg, "ENABLE_AUTO_PUFF"))
    {
    	Log(lInfo) << "Enabling auto puffing";
        enableAutoPuff();
    }
    else if(compareStrings(msg, "DISABLE_AUTO_PUFF"))
    {
    	Log(lInfo) << "Disabling auto puffing";
        disableAutoPuff();
    }
    else if(startsWith(msg, "PUFF_AFTER_SECTION_COUNT"))
    {
    	Log(lInfo) << "Setting puff after section count";
		StringList l(msg,'=');
        if(l.size()==2)
        {
        	setPuffAfterSectionCount(toInt(l[1]));
        }
    }
    else if(startsWith(msg, "TOGGLE_LED_LIGHT"))
    {
    	Log(lInfo) << "Toggling LED on/off";
        toggleLED();
    }
    else if(startsWith(msg, "TOGGLE_COAX_LIGHT"))
    {
    	Log(lInfo) << "Toggling Coax on/off";
        toggleCoax();
    }
    else if(startsWith(msg, "SET_FRONTLED"))
    {
        StringList sl(msg,'=');
        if(sl.size() == 2)
        {
            stringstream s;
            s << 'f' <<sl[1];
			Log(lInfo) << "Set Front LED Intensity ("<<sl[1]<<")";
        	mSensorArduino.send(s.str());
        }
    }
    else if(startsWith(msg, "SET_BACKLED"))
    {
        StringList sl(msg,'=');
        if(sl.size() == 2)
        {
            stringstream s;
            s << 'b' <<sl[1];
			Log(lInfo) << "Set Back LED Intensity ("<<sl[1]<<")";
        	mSensorArduino.send(s.str());
        }
    }
    else if(startsWith(msg, "SET_COAX"))
    {
        StringList sl(msg,'=');
        if(sl.size() == 2)
        {
            stringstream s;
            s << 'c' <<sl[1];
			Log(lInfo) << "Set COAX Light Intensity ("<<sl[1]<<")";
        	mSensorArduino.send(s.str());
        }
    }

    return msg.IsProcessed();
}
