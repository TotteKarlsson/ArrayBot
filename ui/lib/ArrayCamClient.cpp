#pragma hdrstop
#include "mtkStringUtils.h"
#include "ArrayCamClient.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
using namespace mtk;
ArrayCamClient::ArrayCamClient()
:
mMessageProcessor(*this)
{}

ArrayCamClient::~ArrayCamClient()
{
    Log(lDebug3)<<"ArrayCam client is shutting down..";
}

bool ArrayCamClient::init(int serverPort, const string& hostname, bool connectOnInit)
{
    Log(lDebug3)<<"Setting up an ArrayCam client";
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

        //Request status
       	getServerStatus();
     	return true;
    }
    return false;
}

void ArrayCamClient::getServerStatus()
{
	request("GET_SERVER_STATUS");
}

void ArrayCamClient::assignOnMessageReceivedCallBack(OnMessageReceivedCB cb)
{
	mMessageProcessor.assignOnMessageReceivedCallBack(cb);
}

bool ArrayCamClient::isConnected()
{
	return SocketClient::isConnected();
}

bool ArrayCamClient::shutDown()
{
    Log(lDebug3)<<"Stop receiving";
	mReceiver.stop();

    Log(lDebug3)<<"Stop processing messages";
	mMessageProcessor.stop();

    Log(lDebug3)<<"Closing socket in ArrayCamClient";
	SocketClient::close();

    Log(lDebug3)<<"ArrayCamClient was shut down";
    return true;
}

bool ArrayCamClient::connect(int serverPort, const string& host)
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

bool ArrayCamClient::disConnect()
{
	mMessageProcessor.stop();
	return SocketClient::close();
}

void ArrayCamClient::postMessage(const string& msg)
{
    string socketMessage = msg;
    SocketClient::send(msg);
}

