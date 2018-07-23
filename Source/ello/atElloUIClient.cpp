#pragma hdrstop
#include "dslStringUtils.h"
#include "atElloUIClient.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

using namespace dsl;

namespace at
{

    ElloUIClient::ElloUIClient()
    :
    mMessageProcessor(*this)
    {}

    ElloUIClient::~ElloUIClient()
    {
        Log(lDebug3)<<"ElloUI client is shutting down..";
    }

    bool ElloUIClient::init(int serverPort, const string& hostname, bool connectOnInit)
    {
        Log(lDebug3)<<"Setting up an ElloUI client";
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

    bool ElloUIClient::connect(int serverPort, const string& host)
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

    void ElloUIClient::run()
    {
    	request("RUN");
    }

    void ElloUIClient::assignOnMessageReceivedCallBack(OnMessageReceivedCB cb)
    {
    	mMessageProcessor.assignOnMessageReceivedCallBack(cb);
    }

    bool ElloUIClient::isConnected()
    {
    	return SocketClient::isConnected();
    }

    bool ElloUIClient::shutDown()
    {
        Log(lDebug3)<<"Stop receiving";
    	mReceiver.stop();

        Log(lDebug3)<<"Stop processing messages";
    	mMessageProcessor.stop();

        Log(lDebug3)<<"Closing socket in ElloUIClient";
    	SocketClient::close();

        Log(lDebug3)<<"ElloUIClient was shut down";
        return true;
    }

    bool ElloUIClient::disConnect()
    {
    	mMessageProcessor.stop();
    	return SocketClient::close();
    }

    void ElloUIClient::postMessage(const string& msg)
    {
        string socketMessage = msg;
        SocketClient::send(msg);
    }

}

