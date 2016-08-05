#pragma hdrstop
#include "mtkStringUtils.h"
#include "abArduinoClient.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------

using namespace mtk;

ArduinoClient::ArduinoClient()
:
mReceiver(*this, mIncomingMessages),
mMessageProcessor(*this)
{}

ArduinoClient::~ArduinoClient()
{
    Log(lDebug3)<<"Arduino client is shutting down..";
}

bool ArduinoClient::init(int serverPort, const string& hostname, bool connectOnInit)
{
    Log(lDebug3)<<"Setting up client";
	this->assignParent(this);

    if(connectOnInit)
    {
    	SocketClient::connect(serverPort, hostname);
    }

    return true;
}

void ArduinoClient::getStatus()
{
	request("GET_STATUS");
}

void ArduinoClient::resetSectionCounter()
{
	request("RESET_SECTION_COUNT");
}

void ArduinoClient::setPuffAfterSectionCount(int count)
{
	stringstream msg;
    msg <<"PUFF_AFTER_SECTION_COUNT="<<count;
	request(msg.str());
}

void ArduinoClient::enableAutoPuff()
{
	stringstream msg;
    msg <<"ENABLE_AUTO_PUFF";
	request(msg.str());
}

void ArduinoClient::disableAutoPuff()
{
	stringstream msg;
    msg <<"DISABLE_AUTO_PUFF";
	request(msg.str());
}

void ArduinoClient::toggleLED()
{
	stringstream msg;
    msg <<"TOGGLE_LED_LIGHT";
	request(msg.str());
}

void ArduinoClient::toggleCoax()
{
	stringstream msg;
    msg <<"TOGGLE_COAX_LIGHT";
	request(msg.str());
}

void ArduinoClient::assignOnMessageReceivedCallBack(OnMessageReceivedCB cb)
{
	mMessageProcessor.assignOnMessageReceivedCallBack(cb);
}

string ArduinoClient::getClientInfo()
{
    return SocketClient::getInfo();
}

bool ArduinoClient::isConnected()
{
	return SocketClient::isConnected();
}

bool ArduinoClient::shutDown()
{
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

    if(!mMessageProcessor.isRunning())
    {
        mMessageProcessor.start(true);
    }

    if(isConnected())
    {
    	return mReceiver.start(true);
    }
    return false;
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

