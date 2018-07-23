#pragma hdrstop
#include "dslStringUtils.h"
#include "dslMessageContainer.h"
#include "dslSocketClient.h"
#include "dslLogger.h"
#include "atArduinoMessageProcessor.h"
#include "dslMessageContainer.h"
#include "Poco/Mutex.h"
#include "atArduinoClient.h"
//----------------------------------------------------------------
using namespace dsl;

namespace at
{
ArduinoMessageProcessor::ArduinoMessageProcessor(ArduinoClient& client)
:
Thread("MessageProcessor"),
mAllowProcessing(true),
mMessageContainer(client.mIncomingMessages),
mClient(client)
{}

//----------------------------------------------------------------
ArduinoMessageProcessor::~ArduinoMessageProcessor()
{}

void ArduinoMessageProcessor::assignOnMessageReceivedCallBack(OnMessageReceivedCB cb)
{
	onMessageReceivedCB = cb;
}

bool ArduinoMessageProcessor::start(bool inThread)
{
    return Thread::start();
}

void ArduinoMessageProcessor::stop()
{
    Thread::stop();
    mMessageContainer.mGotMessage.broadcast();
}

void ArduinoMessageProcessor::run()
{
    worker();
}

void ArduinoMessageProcessor::worker()
{
	mIsRunning = true;
    Log(lDebug)<<"Entering ArduinoMessageProcessor Worker Function.";
    mID =  GetCurrentThreadId();

    //Wait for conditional varible, regarding messages and
    //then, when set, process messages...
    while(!mIsTimeToDie)
    {
        {
            Poco::ScopedLock<Poco::Mutex> lock(mMessageContainer.mListMutex);
            if(mMessageContainer.count() == 0)
            {
                mIsStarted = true;
                mMessageContainer.mGotMessage.wait(mMessageContainer.mListMutex);
            }
        }

        while(mMessageContainer.count())
        {
            processMessage(mMessageContainer.pop());
            if(mIsTimeToDie)
            {
            	break;
            }
        }
    }

    Log(lInfo) << "Exiting Arduino message processor.";
    mIsFinished = true;
}

void ArduinoMessageProcessor::processMessage(const string& msg)
{
	if(onMessageReceivedCB)
    {
    	onMessageReceivedCB(msg);
	    Log(lDebug) << "Processed message: "<<msg;
    }
}

}
