#pragma hdrstop
#include "dslStringUtils.h"
#include "dslMessageContainer.h"
#include "dslSocketClient.h"
#include "dslLogger.h"
#include "atArrayBotMessageProcessor.h"
#include "dslMessageContainer.h"
#include "Poco/Mutex.h"
#include "atArrayBotClient.h"
//----------------------------------------------------------------
using namespace dsl;

namespace at
{
    ArrayBotMessageProcessor::ArrayBotMessageProcessor(ArrayBotClient& client)
    :
    Thread("MessageProcessor"),
    mAllowProcessing(true),
    mMessageContainer(client.mIncomingMessages),
    mClient(client)
    {}

    //----------------------------------------------------------------
    ArrayBotMessageProcessor::~ArrayBotMessageProcessor()
    {}

    void ArrayBotMessageProcessor::assignOnMessageReceivedCallBack(OnMessageReceivedCB cb)
    {
    	onMessageReceivedCallbacks.push_back(cb);
    }

    bool ArrayBotMessageProcessor::start(bool inThread)
    {
        return Thread::start();
    }

    void ArrayBotMessageProcessor::stop()
    {
        Thread::stop();
        mMessageContainer.mGotMessage.broadcast();
    }

    void ArrayBotMessageProcessor::run()
    {
        worker();
    }

    void ArrayBotMessageProcessor::worker()
    {
    	mIsRunning = true;
        Log(lDebug)<<"Entering ArrayBotMessageProcessor Worker Function.";
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

        Log(lInfo) << "Exiting ArrayBot message processor.";
        mIsFinished = true;
       	mIsRunning = false;
    }

    void ArrayBotMessageProcessor::processMessage(const string& msg)
    {
    	for(int i = 0; i < onMessageReceivedCallbacks.size(); i++)
        {
    		onMessageReceivedCallbacks[i](msg);
        }

    //	if(onMessageReceivedCB1)
    //    {
    //    	onMessageReceivedCB1(msg);
    //	    Log(lDebug) << "ArrayBotMessageProcessor fired CB1: "<<msg;
    //    }
    //
    //	if(onMessageReceivedCB2)
    //    {
    //    	onMessageReceivedCB2(msg);
    //	    Log(lDebug) << "ArrayBotMessageProcessor fired CB2: "<<msg;
    //    }

    }
}

