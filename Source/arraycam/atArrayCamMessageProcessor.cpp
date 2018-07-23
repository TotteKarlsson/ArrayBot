#pragma hdrstop
#include "dslStringUtils.h"
#include "dslMessageContainer.h"
#include "dslSocketClient.h"
#include "dslLogger.h"
#include "atArrayCamMessageProcessor.h"
#include "dslMessageContainer.h"
#include "Poco/Mutex.h"
#include "atArrayCamClient.h"
//----------------------------------------------------------------
using namespace dsl;

namespace at
{

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
    	onMessageReceivedCallbacks.push_back(cb);
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
    	for(int i = 0; i < onMessageReceivedCallbacks.size(); i++)
        {
    		onMessageReceivedCallbacks[i](msg);
        }

    //	if(onMessageReceivedCB1)
    //    {
    //    	onMessageReceivedCB1(msg);
    //	    Log(lDebug) << "ArrayCamMessageProcessor fired CB1: "<<msg;
    //    }
    //
    //	if(onMessageReceivedCB2)
    //    {
    //    	onMessageReceivedCB2(msg);
    //	    Log(lDebug) << "ArrayCamMessageProcessor fired CB2: "<<msg;
    //    }

    }


}
