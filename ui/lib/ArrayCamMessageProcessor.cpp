#pragma hdrstop
#include "mtkStringUtils.h"
#include "mtkMessageContainer.h"
#include "mtkSocketClient.h"
#include "mtkLogger.h"
#include "ArrayCamMessageProcessor.h"
#include "mtkMessageContainer.h"
#include "Poco/Mutex.h"
#include "ArrayCamClient.h"
//----------------------------------------------------------------
using namespace mtk;

ArrayCamMessageProcessor::ArrayCamMessageProcessor(ArrayCamClient& client)
:
Thread("MessageProcessor"),
mAllowProcessing(true),
mMessageContainer(client.mIncomingMessages),
mClient(client)
{}

//----------------------------------------------------------------
ArrayCamMessageProcessor::~ArrayCamMessageProcessor()
{}

void ArrayCamMessageProcessor::assignOnMessageReceivedCallBack(OnMessageReceivedCB cb)
{
	onMessageReceivedCB = cb;
}

bool ArrayCamMessageProcessor::start(bool inThread)
{
    return Thread::start();
}

void ArrayCamMessageProcessor::stop()
{
    Thread::stop();
    mMessageContainer.mGotMessage.broadcast();
}

void ArrayCamMessageProcessor::run()
{
    worker();
}

void ArrayCamMessageProcessor::worker()
{
	mIsRunning = true;
    Log(lDebug)<<"Entering ArrayCamMessageProcessor Worker Function.";
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

    Log(lInfo) << "Exiting ArrayCam message processor.";
    mIsFinished = true;
   	mIsRunning = false;
}

void ArrayCamMessageProcessor::processMessage(const string& msg)
{
	if(onMessageReceivedCB)
    {
    	onMessageReceivedCB(msg);
	    Log(lDebug) << "Processed message: "<<msg;
    }
}

