#pragma hdrstop
#include "atArduinoClient.h"
#include "dslStringUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

using namespace dsl;

namespace at
{

ArduinoClient::ArduinoClient()
:
mMessageProcessor(*this)
{}

ArduinoClient::~ArduinoClient()
{
    Log(lDebug3)<<"Arduino client is shutting down..";
}

bool ArduinoClient::init(int serverPort, const string& hostname, bool connectOnInit)
{
    Log(lDebug3)<<"Setting up an Arduino client";
	this->assignParent(this);

    if(connectOnInit)
    {
        if(!SocketClient::connect(serverPort, hostname))
        {
        	return false;
        }

       	if(!mReceiver.isRunning())
        {
            mReceiver.start(true);
        }
     	return true;
    }
    return false;
}

void ArduinoClient::getServerStatus()
{
	request("GET_SERVER_STATUS");
}

void ArduinoClient::assignOnMessageReceivedCallBack(OnMessageReceivedCB cb)
{
	mMessageProcessor.assignOnMessageReceivedCallBack(cb);
}

bool ArduinoClient::isConnected()
{
	return SocketClient::isConnected();
}

bool ArduinoClient::shutDown()
{
    Log(lDebug3)<<"Stop receiving";
	mReceiver.stop();

    Log(lDebug3)<<"Stop processing messages";
	mMessageProcessor.stop();

    Log(lDebug3)<<"Closing socket in ArduinoClient";
	SocketClient::close();

    Log(lDebug3)<<"ArduinoClient was shut down";
    return true;
}

bool ArduinoClient::connect(int serverPort, const string& host)
{
	//This should be done in a thread..
    bool res = init(serverPort, host, true);

    //Do only run the message processor if we are connected
    if(res == true && !mMessageProcessor.isRunning())
    {
        mMessageProcessor.start(true);
    }

    return res;
}

bool ArduinoClient::disConnect()
{
	mMessageProcessor.stop();
	return SocketClient::close();
}

void ArduinoClient::postMessage(const string& msg)
{
    string socketMessage = msg;
    SocketClient::send(msg);
}

}
