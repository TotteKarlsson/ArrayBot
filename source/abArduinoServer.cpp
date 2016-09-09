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
mLightsArduino(-1),
mRibbonLengthController(*this),
mLEDLightONLine(3),
mLEDLightOFFLine(4),
mCoaxLightONLine(1),
mCoaxLightOFFLine(2)
{
	mArduinos.push_back(&mPufferArduino);
	mArduinos.push_back(&mLightsArduino);

    //Assign receive callbacks
    mPufferArduino.assignSerialMessageReceivedCallBack(pufferMessageReceived);
    mLightsArduino.assignSerialMessageReceivedCallBack(sensorMessageReceived);
}

ArduinoServer::~ArduinoServer()
{
    mPufferArduino.assignSerialMessageReceivedCallBack(NULL);
    mLightsArduino.assignSerialMessageReceivedCallBack(NULL);
}

void ArduinoServer::assignOnUpdateCallBack(OnMessageUpdateCB cb)
{
	onMessageUpdateCB = cb;
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

void ArduinoServer::enableAutoPuff()
{
	mRibbonLengthController.enableAutoPuff();
    stringstream msg;
    msg <<"AUTO_PUFF=true";
   	updateClients(msg.str());
}

void ArduinoServer::disableAutoPuff()
{
	mRibbonLengthController.disableAutoPuff();
    stringstream msg;
    msg <<"AUTO_PUFF=false";
   	updateClients(msg.str());
}

void ArduinoServer::enableAutoZeroCut()
{
	mRibbonLengthController.enableAutoZeroCut();
    stringstream msg;
    msg <<"AUTO_ZERO_CUT=true";
   	updateClients(msg.str());
}

void ArduinoServer::disableAutoZeroCut()
{
	mRibbonLengthController.disableAutoZeroCut();
    stringstream msg;
    msg <<"AUTO_ZERO_CUT=false";
   	updateClients(msg.str());
}

void ArduinoServer::updateClients(const string& msg)
{
	//TODO: There is a problem with this...
    if(onMessageUpdateCB)
    {
        onMessageUpdateCB(msg);
    }

    broadcast(msg);
}

void ArduinoServer::broadcastStatus()
{
	//These are all status messages possible
    //A client may call this one in order to sync their UI
    stringstream msg;
    msg <<"SECTION_COUNT="<<mRibbonLengthController.getSectionCount();
   	updateClients(msg.str());

    msg.str("");
    msg <<"DESIRED_RIBBON_LENGTH="<<mRibbonLengthController.getDesiredRibbonLength();
   	updateClients(msg.str());

    msg.str("");
    msg <<"AUTO_PUFF="<<toString(mRibbonLengthController.getAutoPuffSetting());
   	updateClients(msg.str());

    msg.str("");
    msg <<"AUTO_ZERO_CUT="<<toString(mRibbonLengthController.getAutoZeroCutSetting());
   	updateClients(msg.str());
}

void ArduinoServer::sensorMessageReceived(const string& msg)
{
	updateClients(msg);
}

//This is called from the arduino devices class upon receiving
//a message from the arduino thread over the serial port
//Socket clients are updated using the updateClients funtion
void ArduinoServer::pufferMessageReceived(const string& msg)
{
	Log(lDebug5) << "Handling puffer message: "<<msg;

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
        mRibbonLengthController.check();
    	mRibbonLengthController.incrementSectionCount();

        stringstream msg;
        msg <<"SECTION_COUNT="<<mRibbonLengthController.getSectionCount();
		updateClients(msg.str());
    }
}

//void ArduinoServer::setPuffAfterSectionCount(int val)
//{
//	mDesiredRibbonLength = val;
//    stringstream msg;
//    msg <<"DESIRED_RIBBON_LENGTH="<<mDesiredRibbonLength;
//	updateClients(msg.str());
//}
//
//bool ArduinoServer::setZeroCut()
//{
//	Log(lInfo) << "Requesting Zero Cut";
//	bool res;
//	IPCMessage msg(-1, "SET_CUT_PRESET=1");
//
//    res = postIPCMessage(msg);
//	return res;
//}
//

bool ArduinoServer::turnLEDLightOn()
{
	Log(lInfo) << "Turning on LEDs";
	return mLightsArduino.send(mLEDLightONLine);
}

bool ArduinoServer::turnLEDLightOff()
{
	Log(lInfo) << "Turning off LEDs";
	return mLightsArduino.send(mLEDLightOFFLine);
}

bool ArduinoServer::turnCoaxLightOn()
{
	Log(lInfo) << "Turning on Coax light";
	return mLightsArduino.send(mCoaxLightONLine);
}

bool ArduinoServer::turnCoaxLightOff()
{
	Log(lInfo) << "Turning off Coax light";
	return mLightsArduino.send(mCoaxLightOFFLine);
}

bool ArduinoServer::toggleLED()
{
	static bool switcher(false);

    switcher = !switcher;
    if(switcher)
    {
		return mLightsArduino.send(mLEDLightONLine);
    }
    else
    {
		return mLightsArduino.send(mLEDLightOFFLine);
    }
}

bool ArduinoServer::toggleCoax()
{
	static bool switcher(false);

    switcher = !switcher;
    if(switcher)
    {
		return mLightsArduino.send(mCoaxLightONLine);
    }
    else
    {
		return mLightsArduino.send(mCoaxLightOFFLine);
    }
}

//Handle incoming client requests over the socket
//These messages are handled in a thread
//Depending on message, a response may be sent using the
//updateClients function
bool ArduinoServer::processMessage(IPCMessage& msg)
{
    if(msg.isPacked())
    {
        msg.unPack();
    }

    if(compareStrings(msg, "RESET_SECTION_COUNT"))
    {
    	Log(lInfo) << "Resetting section counter";
        mRibbonLengthController.resetSectionCount();
	    stringstream smsg;
	    smsg <<"SECTION_COUNT="<<mRibbonLengthController.getSectionCount();
		updateClients(smsg.str());
    }
    else if(compareStrings(msg, "ENABLE_PUFFER"))
    {
    	Log(lInfo) << "Enabling auto puffing";
        mPufferArduino.enablePuffer();
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
    else if(startsWith("SET_DESIRED_RIBBON_LENGTH", msg))
    {
    	Log(lInfo) << "Setting desired ribbon length";
		StringList l(msg,'=');
        if(l.size() == 2)
        {
        	mRibbonLengthController.setDesiredRibbonLength(toInt(l[1]));
        }
    }
    else if(startsWith("PUFF", msg))
    {
    	Log(lInfo) << "Executing puffer";
	    mRibbonLengthController.manualPuff();
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
        	mLightsArduino.send(s.str());
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
        	mLightsArduino.send(s.str());
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
        	mLightsArduino.send(s.str());
        }
    }
    else if(startsWith("SET_CUT_PRESET", msg))
    {
        StringList sl(msg,'=');
        if(sl.size() == 2)
        {
			Log(lInfo) << "Request Cut Preset ("<<sl[1]<<")";
        	mPufferArduino.setCutPreset(toInt(sl[1]));
        }
    }
    else if(startsWith("SET_DELTAY", msg))
    {
        StringList sl(msg,'=');
        if(sl.size() == 2)
        {
			Log(lInfo) << "Request DeltaY("<<sl[1]<<")";
        	mPufferArduino.setDeltaY(toInt(sl[1]));
        }
    }
    else if(compareStrings(msg, "GET_STATUS"))
    {
    	Log(lInfo) << "Broadcast status";
        broadcastStatus();
    }
    else
    {
    	Log(lError) << "UNHANDLED ARDUINO SERVER MESSAGE: "<<msg;
    }

    return msg.IsProcessed();
}
