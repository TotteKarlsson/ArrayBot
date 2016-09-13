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
mRibbonLengthController(*this)
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
   	notifyClients(msg.str());
}

void ArduinoServer::disableAutoPuff()
{
	mRibbonLengthController.disableAutoPuff();
    stringstream msg;
    msg <<"AUTO_PUFF=false";
   	notifyClients(msg.str());
}

void ArduinoServer::enableAutoZeroCut()
{
	mRibbonLengthController.enableAutoZeroCut();
    stringstream msg;
    msg <<"AUTO_ZERO_CUT=true";
   	notifyClients(msg.str());
}

void ArduinoServer::disableAutoZeroCut()
{
	mRibbonLengthController.disableAutoZeroCut();
    stringstream msg;
    msg <<"AUTO_ZERO_CUT=false";
   	notifyClients(msg.str());
}

void ArduinoServer::notifyClients(const string& msg)
{
	if(!msg.size())
    {
    	return;
    }

	//TODO: There might be a threading problem with this.
    //This call will update the UI
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
   	notifyClients(msg.str());

    msg.str("");
    msg <<"DESIRED_RIBBON_LENGTH="<<mRibbonLengthController.getDesiredRibbonLength();
   	notifyClients(msg.str());

    msg.str("");
    msg <<"AUTO_PUFF="<<toString(mRibbonLengthController.getAutoPuffSetting());
   	notifyClients(msg.str());

    msg.str("");
    msg <<"AUTO_ZERO_CUT="<<toString(mRibbonLengthController.getAutoZeroCutSetting());
   	notifyClients(msg.str());
}

//This is called from the arduino devices class upon receiving
//a message from the arduino thread over the serial port
//Socket clients are updated using the notifyClients funtion
void ArduinoServer::sensorMessageReceived(const string& msg)
{
	notifyClients(msg);
}

//This is called from the arduino devices class upon receiving
//a message from the arduino thread over the serial port
//Socket clients are updated using the notifyClients funtion
void ArduinoServer::pufferMessageReceived(const string& msg)
{
	Log(lDebug5) << "Handling puffer message: "<<msg;

    //Check what message we got from arduino device
    if(msg == "ArrayBot Puffer Arduino")
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
    	if(mPufferArduino.getLastCutThicknessPreset() != 1)
        {
    		mRibbonLengthController.incrementSectionCount();
        }

        mRibbonLengthController.checkProgress();

        stringstream msg;
        msg <<"SECTION_COUNT="<<mRibbonLengthController.getSectionCount();
		notifyClients(msg.str());
    }
}

//Handle incoming client requests over the socket
//These messages are handled in a thread
//Depending on the message, a response may be sent using the
//notifyClients function
bool ArduinoServer::processMessage(IPCMessage& msg)
{
    stringstream clientMessage;
    if(msg.isPacked())
    {
        msg.unPack();
    }
    if(compareStrings(msg, "RESET_SECTION_COUNT"))
    {
    	Log(lInfo) << "Resetting section counter";
        mRibbonLengthController.resetSectionCount();
	    clientMessage <<"SECTION_COUNT="<<mRibbonLengthController.getSectionCount();
    }
    else if(compareStrings(msg, "ENABLE_PUFFER"))
    {
    	Log(lInfo) << "Enabling auto puffing";
        mPufferArduino.enablePuffer();
    }
    else if(compareStrings(msg, "DISABLE_PUFFER"))
    {
    	Log(lInfo) << "Disable auto puffing";
        mPufferArduino.disablePuffer();
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
    else if(startsWith("START_NEW_RIBBON", msg))
    {
    	Log(lInfo) << "Starting new ribbon";
		mRibbonLengthController.prepareForNewRibbon();
    }
    else if(startsWith("TOGGLE_LED_LIGHT", msg))
    {
    	Log(lInfo) << "Toggling LED on/off";
        mLightsArduino.toggleLED();
    }
    else if(startsWith(msg, "TOGGLE_COAX_LIGHT"))
    {
    	Log(lInfo) << "Toggling Coax on/off";
        mLightsArduino.toggleCoax();
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
    else if(startsWith("SET_CUT_THICKNESS_PRESET", msg))
    {
        StringList sl(msg,'=');
        if(sl.size() == 2)
        {
			Log(lInfo) << "Requesting Cut Thickness Preset ("<<sl[1]<<")";
        	mPufferArduino.setCutThicknessPreset(toInt(sl[1]));
            mRibbonLengthController.setCutThicknessPreset(toInt(sl[1]));
        }
    }
    else if(startsWith("SET_DELTAY", msg))
    {
        StringList sl(msg,'=');
        if(sl.size() == 2)
        {
			Log(lInfo) << "Requesting DeltaY("<<sl[1]<<")";
        	mPufferArduino.setDeltaY(toInt(sl[1]));
        }
    }
    else if(startsWith("ENABLE_AUTO_ZERO_CUT", msg))
    {
    	Log(lInfo) << "Enabling auto zero cut";
        mRibbonLengthController.enableAutoZeroCut();
        clientMessage <<"AUTO_ZERO_CUT=true";
    }
    else if(startsWith("DISABLE_AUTO_ZERO_CUT", msg))
    {
    	Log(lInfo) << "Disabling auto zero cut";
        mRibbonLengthController.disableAutoZeroCut();
        clientMessage << "AUTO_ZERO_CUT=false";
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

   	notifyClients(clientMessage.str());
    return msg.IsProcessed();
}
