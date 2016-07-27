#pragma hdrstop
//#include "mtkIPCWorker.h"
#include "mtkStringUtils.h"
#include "abArduinoClient.h"

#include "mtkLogger.h"
//---------------------------------------------------------------------------

using namespace mtk;


ArduinoClient::ArduinoClient()
:
mSocketClient(),
mReceiver(mSocketClient, mIncomingMessages),
mMessageProcessor(mIncomingMessages)
{}

ArduinoClient::~ArduinoClient()
{
    Log(lDebug3)<<"Log client is shutting down..";
}

bool ArduinoClient::init(int serverPort, const string& hostname, bool connectOnInit)
{
    Log(lDebug3)<<"Setting up log client";

	mSocketClient.assignParent(this);

    if(connectOnInit)
    {
    	mSocketClient.connect(serverPort, hostname);
    }

    return true;
}

string ArduinoClient::getClientInfo()
{
    return mSocketClient.getInfo();
}

bool ArduinoClient::isConnected()
{
	return mSocketClient.isConnected();
}

bool ArduinoClient::shutDown()
{
	mReceiver.stop();

    Log(lDebug3)<<"Stop processing messages";
	mMessageProcessor.stop();

    Log(lDebug3)<<"Closing socket in ArduinoClient";
	mSocketClient.close();

    Log(lDebug3)<<"ArduinoClient was shut down";
    return true;
}

bool ArduinoClient::connect(int serverPort, const string& host)
{
    bool res = init(serverPort, host, true);
    if(isConnected())
    {
    	mReceiver.start(true);
    }
}

bool ArduinoClient::disConnect()
{
	return mSocketClient.close();
}

void ArduinoClient::postMessage(const string& msg)
{
    string socketMessage = msg;
    mSocketClient.send(msg);
}

