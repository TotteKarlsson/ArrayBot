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
IPCServer(portNumber, "ARDUINO_SERVER", createArduinoIPCReceiver)
{}

ArduinoServer::~ArduinoServer()
{}


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
