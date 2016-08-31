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
mDesiredRibbonLength(10),
mAutoPuff(false),
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
    msg <<"DESIRED_RIBBON_LENGTH="<<mDesiredRibbonLength;
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

void ArduinoServer::sensorMessageReceived(const string& msg)
{
	updateClients(msg);
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
        	if(mSectionCount == mDesiredRibbonLength - 3)
            {
                stringstream msg;
        		msg <<"GET_READY_FOR_ZERO_CUT_1";
				updateClients(msg.str());
            }

        	if(mSectionCount == mDesiredRibbonLength - 2)
            {
                stringstream msg;
        		msg <<"GET_READY_FOR_ZERO_CUT_2";
				updateClients(msg.str());
            }

        	if(mSectionCount == mDesiredRibbonLength - 1)
            {
                stringstream msg;
        		msg <<"SET_ZERO_CUT";
				updateClients(msg.str());
            }

        	if(mSectionCount >= mDesiredRibbonLength)
        	{
            	try
                {
        			enablePuffer();
                }catch(...)
                {
                	Log(lError) << "SuperError";
                }
				mSectionCount = 0;
                stringstream msg;

        		msg <<"RESTORE_FROM_ZERO_CUT";
				updateClients(msg.str());
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
	mDesiredRibbonLength = val;

    stringstream msg;
    msg <<"DESIRED_RIBBON_LENGTH="<<mDesiredRibbonLength;
	updateClients(msg.str());
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
	Log(lInfo) << "Sending puff command";
    bool res = mPufferArduino.send("p");
    if(res)
    {
    	resetSectionCount();
    }
	return res;
}

bool ArduinoServer::enablePuffer()
{
	Log(lInfo) << "Sending puffer enabled command";
	return mPufferArduino.send("e");
}

bool ArduinoServer::turnLEDLightOn()
{
	Log(lInfo) << "Turning on LEDs";
	return mSensorArduino.send(mLEDLightONLine);
}

bool ArduinoServer::turnLEDLightOff()
{
	Log(lInfo) << "Turning off LEDs";
	return mSensorArduino.send(mLEDLightOFFLine);
}

bool ArduinoServer::turnCoaxLightOn()
{
	Log(lInfo) << "Turning on Coax light";
	return mSensorArduino.send(mCoaxLightONLine);
}

bool ArduinoServer::turnCoaxLightOff()
{
	Log(lInfo) << "Turning off Coax light";
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
    else if(compareStrings(msg, "ENABLE_PUFFER"))
    {
    	Log(lInfo) << "Enabling auto puffing";
        enablePuffer();
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
    else if(startsWith("DESIRED_RIBBON_LENGTH", msg))
    {
    	Log(lInfo) << "Setting puff after section count";
		StringList l(msg,'=');
        if(l.size()==2)
        {
        	setPuffAfterSectionCount(toInt(l[1]));
        }
    }
    else if(startsWith("PUFF", msg))
    {
    	Log(lInfo) << "Executing puffer";
	    puff();
    }

    else if(startsWith("TOGGLE_LED_LIGHT", msg))
    {
    	Log(lInfo) << "Toggling LED on/off";
        toggleLED();
    }
    else if(startsWith(msg, "TOGGLE_COAX_LIGHT"))
    {
    	Log(lInfo) << "Toggling Coax on/off";
        toggleCoax();
    }
    else if(startsWith("SET_FRONTLED", msg))
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
    else if(startsWith("SET_BACKLED", msg))
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
    else if(startsWith("SET_COAX", msg))
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
    else
    {
    	Log(lError) << "UNHANDLED ARDUINO MESSAGE: "<<msg;
    }

    return msg.IsProcessed();
}
