#pragma hdrstop
#include "mtkStringUtils.h"
#include "mtkMessageContainer.h"
#include "mtkIPCMessage.h"
#include "mtkSocketClient.h"
#include "mtkLogger.h"
#include "abArduinoMessageProcessor.h"
#include "mtkMessageContainer.h"
#include "Poco/Mutex.h"
//----------------------------------------------------------------
using namespace mtk;

ArduinoMessageProcessor::ArduinoMessageProcessor(MessageContainer& _mMessageContainer)
:
Thread("MessageProcessor"),
mAllowProcessing(true),
mMessageContainer(_mMessageContainer)
{
	//Run will start the worker thread
	Thread::run();
}

//----------------------------------------------------------------
ArduinoMessageProcessor::~ArduinoMessageProcessor()
{}

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
//    if(mParent && mParent->IsConnecting() || mAllowProcessing == false)
//        return;
//
//    if(!mSocketClient)
//        return;
//
    //Process each message in the message list
      Log(lInfo) << "Processed message: "<<msg;
}

