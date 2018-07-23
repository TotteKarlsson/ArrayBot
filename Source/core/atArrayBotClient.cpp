#pragma hdrstop
#include "dslStringUtils.h"
#include "atArrayBotClient.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;

namespace at
{
    ArrayBotClient::ArrayBotClient()
    :
    mMessageProcessor(*this)
    {}

    ArrayBotClient::~ArrayBotClient()
    {
        Log(lDebug3)<<"ArrayBot client is shutting down..";
    }

    bool ArrayBotClient::init(int serverPort, const string& hostname, bool connectOnInit)
    {
        Log(lDebug3)<<"Setting up an ArrayBot client";
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

    void ArrayBotClient::getServerStatus()
    {
    	request("GET_SERVER_STATUS");
    }

    void ArrayBotClient::assignOnMessageReceivedCallBack(OnMessageReceivedCB cb)
    {
    	mMessageProcessor.assignOnMessageReceivedCallBack(cb);
    }

    bool ArrayBotClient::isConnected()
    {
    	return SocketClient::isConnected();
    }

    bool ArrayBotClient::shutDown()
    {
        Log(lDebug3)<<"Stop receiving";
    	mReceiver.stop();

        Log(lDebug3)<<"Stop processing messages";
    	mMessageProcessor.stop();

        Log(lDebug3)<<"Closing socket in ArrayBotClient";
    	SocketClient::close();

        Log(lDebug3)<<"ArrayBotClient was shut down";
        return true;
    }

    bool ArrayBotClient::connect(int serverPort, const string& host)
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

    bool ArrayBotClient::disConnect()
    {
    	mMessageProcessor.stop();
    	return SocketClient::close();
    }

    bool ArrayBotClient::postRequest(const string& msg)
    {
        return SocketClient::request(msg);
    }

    bool ArrayBotClient::postRequest(const string& msg, int p1)
    {
    	stringstream m;
        m << msg << ", " << p1;

        return SocketClient::request(m.str());
    }

    bool ArrayBotClient::postRequest(const string& msg, int p1, int p2)
    {
    	stringstream m;
        m << msg << ", " << p1 << ", " << p2;

        return SocketClient::request(m.str());
    }


    //bool ArrayBotClient::startVideo()							{return postRequest(mProtocol[acrStartVideoRecorder])						 		;}

}
