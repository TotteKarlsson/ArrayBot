#pragma hdrstop
#include "atUC7MessageSender.h"
#include "atUC7Component.h"
#include "dslLogger.h"
#include "dslUtils.h"
//---------------------------------------------------------------------------

using namespace dsl;
using Poco::Mutex;

namespace at
{

    //----------------------------------------------------------------
    UC7MessageSender::UC7MessageSender(UC7& uc7)
    :
    dsl::Thread(""),
    mUC7(uc7),
    mProcessTimeDelay(50)
    {}

    //----------------------------------------------------------------
    UC7MessageSender::~UC7MessageSender()
    {
    	if(mIsRunning)
        {
    		stop();
        }
    }

    //----------------------------------------------------------------
    void UC7MessageSender::run()
    {
    	mIsRunning = true;
    	Log(lDebug)<<"Entering UC7 message sender thread";
    	while(mIsTimeToDie == false)
    	{
    		{
    			Poco::ScopedLock<Poco::Mutex> lock(mUC7.mSendBufferMutex);
    			if(mUC7.mOutgoingMessagesBuffer.size() == 0)
    			{
    				Log(lDebug3) << "Waiting for incoming UC7 messages.";
    				mUC7.mNewMessageToSendCondition.wait(mUC7.mSendBufferMutex);
    			}

                while(mUC7.mOutgoingMessagesBuffer.size() && mIsTimeToDie == false)
                {
                	try
                    {
                        string msg = mUC7.mOutgoingMessagesBuffer.front();
                        mUC7.mOutgoingMessagesBuffer.pop_front();

                        //Send windows message and let UI handle the message
                        if(!mUC7.mSerial.send(msg))
                        {
                            Log(lError) << "Sending a UC7 message failed..";
                        }

                        //Use a delay in case the serial devices input buffer overflows
                        sleep(mProcessTimeDelay);

                    }
                    catch(...)
                    {
                    	Log(lError) << "Exception thrown in message sender code..";
                    }
                }

    		}//scoped lock
    	}

        Log(lDebug) << "UC7 Message Sender thread finished";
    	mIsFinished = true;
    	mIsRunning = false;
    }

    //----------------------------------------------------------------
    bool UC7MessageSender::start(bool inThread)
    {
    	if(isRunning())
    	{
    		Log(lWarning) << "Tried to start a runnning thread";
    		return true;
    	}
    	if(inThread)
    	{
    		return dsl::Thread::start();
    	}
    	else
    	{
    		run();
    		return true;
    	}
    }

    //----------------------------------------------------------------
    void UC7MessageSender::stop()
    {
    	//Sets time to die to true
    	dsl::Thread::stop();

    	//If thread is waiting.. get it out of wait state
    	mUC7.mNewMessageToSendCondition.signal();
    }


}
