#pragma hdrstop
#include "dslStringUtils.h"
#include "dslMessageContainer.h"
#include "dslSocketClient.h"
#include "dslLogger.h"
#include "atElloUIMessageProcessor.h"
#include "dslMessageContainer.h"
#include "Poco/Mutex.h"
#include "atElloUIClient.h"
//----------------------------------------------------------------
using namespace dsl;

namespace at
{

    ElloUIMessageProcessor::ElloUIMessageProcessor(ElloUIClient& client)
    :
    Thread("MessageProcessor"),
    mAllowProcessing(true),
    mMessageContainer(client.mIncomingMessages),
    mClient(client)
    {}

    //----------------------------------------------------------------
    ElloUIMessageProcessor::~ElloUIMessageProcessor()
    {}

    void ElloUIMessageProcessor::assignOnMessageReceivedCallBack(OnMessageReceivedCB cb)
    {
    	onMessageReceivedCB = cb;
    }

    bool ElloUIMessageProcessor::start(bool inThread)
    {
        return Thread::start();
    }

    void ElloUIMessageProcessor::stop()
    {
        Thread::stop();
        mMessageContainer.mGotMessage.broadcast();
    }

    void ElloUIMessageProcessor::run()
    {
        worker();
    }

    void ElloUIMessageProcessor::worker()
    {
    	mIsRunning = true;
        Log(lDebug)<<"Entering ElloUIMessageProcessor Worker Function.";
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

    void ElloUIMessageProcessor::processMessage(const string& msg)
    {
    	if(onMessageReceivedCB)
        {
        	onMessageReceivedCB(msg);
    	    Log(lDebug) << "ELLO UI message processor processed message: "<<msg;
        }
    }


}
