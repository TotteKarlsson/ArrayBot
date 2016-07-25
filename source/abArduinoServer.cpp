#pragma hdrstop
#include "abArduinoServer.h"
#include "mtkLogger.h"
#include "abArduinoIPCServerReceiver.h"
#include "mtkSocketWorker.h"
#include "abArduinoUtils.h"
//---------------------------------------------------------------------------

using namespace mtk;

ArduinoServer::ArduinoServer(int portNumber)
:
IPCServer(portNumber, "ARDUINO_SERVER", createArduinoIPCReceiver),
mA1(-1)
{
	mArduinos.push_back(&mA1);

    //Assign receive callbacks
    mA1.assignMessageReceivedCallBack(messageReceived);
}

ArduinoServer::~ArduinoServer()
{}

void ArduinoServer::messageReceived(const string& msg)
{
	broadcast(msg);
}

bool ArduinoServer::shutDown()
{
    IPCServer::shutDown();
	for(int i = 0; i < 1; i++)
    {
		mArduinos[0]->disConnect();
    }
}

ArduinoDevice& ArduinoServer::getArduinoDevice(int dev)
{
	switch(dev)
    {
    	case 1: return mA1;
        defualt: return mA1;
    }
}

bool ArduinoServer::processMessage(IPCMessage& msg)
{
    if(msg.isPacked())
    {
        msg.unPack();
    }

    switch(msg.GetCommand())
    {
    	case cMakeAPuff:
        	Log(lInfo) << "Puffing....";
        break;
        default:
			IPCServer::processMessage(msg);
        break;
    }

    return msg.IsProcessed();
}
