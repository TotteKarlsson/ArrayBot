#pragma hdrstop
#include "abMotorMessageProcessor.h"
#include "mtkStringUtils.h"
#include "abMotorMessageContainer.h"
#include "Poco/Mutex.h"
#include "mtkLogger.h"

#include "mtkUtils.h"
//---------------------------------------------------------------------------

using Poco::Mutex;
using namespace mtk;

//----------------------------------------------------------------
MotorMessageProcessor::MotorMessageProcessor(MotorMessageContainer& messageContainer,  const string& threadName)
:
mtk::Thread(threadName),
mAllowProcessing(true),
mMotorMessageContainer(messageContainer),
mProcessedCount(0),
mNotifyUI(NULL)
{}

//----------------------------------------------------------------
MotorMessageProcessor::~MotorMessageProcessor()
{
	if(mIsRunning)
    {
		stop();
    }
}

bool MotorMessageProcessor::start(bool inThread)
{
	if(isRunning())
	{
		Log(lWarning) << "Tried to start a runnning thread";
		return true;
	}
	if(inThread)
	{
		return mtk::Thread::start();
	}
	else
	{
		worker();
		return true;
	}
}

void MotorMessageProcessor::pauseProcessing()
{
	mAllowProcessing = false;
}

void MotorMessageProcessor::resumeProcessing()
{
	mAllowProcessing = true;
}

void MotorMessageProcessor::stop()
{
	//Sets time to die to true
	mtk::Thread::stop();

	//If thread is waiting.. get it out of wait state
	mMotorMessageContainer.mNewCommandCondition.signal();
}

void MotorMessageProcessor::run()
{
	worker();
}

void MotorMessageProcessor::worker()
{
	Log(lDebug)<<"Entering Order Processor Worker Function.";
	while(mIsTimeToDie == false)
	{
		{
			Poco::ScopedLock<Poco::Mutex> lock(mMotorMessageContainer.mListMutex);
			if(mMotorMessageContainer.count() == 0)
			{
				Log(lDebug3) << "Waiting for motor commands.";
				mMotorMessageContainer.mNewCommandCondition.wait(mMotorMessageContainer.mListMutex);
			}

            while(mMotorMessageContainer.hasMessage())
            {
	           	string cmd = mMotorMessageContainer.pop();
    	        Log(lInfo) << "Processing command: "<<cmd;
            }

		}//mutex
	}

	mIsFinished = true;
	mIsRunning = false;
    Log(lInfo) << "Motor Message Processor finished";
}


