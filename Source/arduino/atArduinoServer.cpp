#pragma hdrstop
#include "atArduinoServer.h"
#include "dslLogger.h"
#include "atArduinoIPCServerReceiver.h"
#include "dslSocketWorker.h"
#include "atArduinoUtils.h"
#include "dslStringUtils.h"

//---------------------------------------------------------------------------
using namespace dsl;

namespace at
{
    ArduinoServer::ArduinoServer(int portNumber)
    :
    IPCServer(portNumber, "ARDUINO_SERVER", createArduinoIPCReceiver),
    mLightsArduino(-1)
    {
    	mArduinos.push_back(&mLightsArduino);

        //Assign receive callbacks
        mLightsArduino.assignSerialMessageReceivedCallBack(lightsArduinoMessageReceived);
    }

    ArduinoServer::~ArduinoServer()
    {
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

    void ArduinoServer::notifyClients(const string& msg)
    {
    	if(!msg.size())
        {
        	return;
        }

        if(onMessageUpdateCB)
        {
        	//This one is synchronized
            onMessageUpdateCB(msg);
        }

    //    broadcast(msg);
    }

    void ArduinoServer::broadcastStatus()
    {
        stringstream msg;
       	notifyClients(msg.str());
    }

    //This is called from the arduino devices class upon receiving
    //a message from the arduino thread over the serial port
    //Socket clients are updated using the notifyClients funtion
    void ArduinoServer::lightsArduinoMessageReceived(const string& msg)
    {
    	notifyClients(msg);
    }

    //Handle incoming client requests over the socket
    //These messages are handled in a thread
    //Depending on the message, a response may be sent using the
    //notifyClients function
    bool ArduinoServer::processRequest(IPCMessage& msg)
    {
        stringstream clientMessage;
        if(msg.isPacked())
        {
            msg.unPack();
        }

        //LIGHTS ARDUINO MESSAGES ******************************************
        if(startsWith("TURN_ON_LED_LIGHTS", msg))
        {
        	Log(lInfo) << "Turn on LED lights";
            mLightsArduino.turnLEDLightsOn();
        }

        else if(startsWith("TURN_OFF_LED_LIGHTS", msg))
        {
        	Log(lInfo) << "Turn off LED lights";
            mLightsArduino.turnLEDLightsOff();
        }

        else if(startsWith("TOGGLE_LED_LIGHT", msg))
        {
        	Log(lInfo) << "Toggling LED on/off";
            mLightsArduino.toggleLED();
        }

        else if(startsWith("SET_FRONT_LED", msg))
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

        else if(startsWith("GET_LIGHTS_ARDUINO_STATUS", msg))
        {
    		Log(lInfo) << "Requesting lights arduino status";
            mLightsArduino.getStatus();
        }

        else if(startsWith("LIGHTS_CUSTOM_MESSAGE", msg))
        {
        	StringList l(msg,'=');
            if(l.size() == 2)
            {
    	    	Log(lInfo) << "Sending custom message to Lights Arduino: "<<l[1];
    	        mLightsArduino.send(l[1]);
            }
        }

        else if(compareStrings(msg, "GET_SERVER_STATUS"))
        {
        	Log(lInfo) << "Broadcast server status";
            request("GET_LIGHTS_ARDUINO_STATUS");
            broadcastStatus();
        }

        else
        {
        	Log(lError) << "UNHANDLED ARDUINO SERVER MESSAGE: "<<msg;
        }

        if(clientMessage.str().size())
        {
       		notifyClients(clientMessage.str());
        }
        return msg.IsProcessed();
    }
}
