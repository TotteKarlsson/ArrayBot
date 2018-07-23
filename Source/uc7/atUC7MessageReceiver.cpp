#pragma hdrstop
#include "atUC7MessageReceiver.h"
#include "dslStringUtils.h"
#include "Poco/Mutex.h"
#include "dslLogger.h"
#include "dslUtils.h"
#include "atUC7Component.h"
#include "atUC7ApplicationMessages.h"
#include "atUC7DataStructures.h"
//---------------------------------------------------------------------------

using Poco::Mutex;
using namespace dsl;
namespace at
{

    //----------------------------------------------------------------
    UC7MessageReceiver::UC7MessageReceiver(UC7& messageContainer,  HWND__ *h, const string& threadName)
    :
    dsl::Thread(threadName),
    mAllowProcessing(true),
    mUC7(messageContainer),
    mProcessedCount(0),
    mProcessTimeDelay(50),
    mHandle(h)
    {}

    //----------------------------------------------------------------
    UC7MessageReceiver::~UC7MessageReceiver()
    {
    	if(mIsRunning)
        {
    		stop();
        }
    }

    bool UC7MessageReceiver::start(bool inThread)
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
    		worker();
    		return true;
    	}
    }

    void UC7MessageReceiver::pauseProcessing()
    {
    	mAllowProcessing = false;
    }

    void UC7MessageReceiver::resumeProcessing()
    {
    	mAllowProcessing = true;
    }

    void UC7MessageReceiver::stop()
    {
    	//Sets time to die to true
    	dsl::Thread::stop();

    	//If thread is waiting.. get it out of wait state
    	mUC7.mNewReceivedMessageCondition.signal();
    }

    void UC7MessageReceiver::run()
    {
    	worker();
    }

    void UC7MessageReceiver::worker()
    {
    	Log(lDebug)<<"Entering Command Processor Worker Function.";
    	while(mIsTimeToDie == false)
    	{
    		{
    			Poco::ScopedLock<Poco::Mutex> lock(mUC7.mReceiveBufferMutex);
    			if(mUC7.mIncomingMessagesBuffer.size() == 0)
    			{
    				Log(lDebug3) << "Waiting for UC7 message.";
    				mUC7.mNewReceivedMessageCondition.wait(mUC7.mReceiveBufferMutex);
    			}

                while(mUC7.hasMessage() && mIsTimeToDie == false)
                {
                	try
                    {
                        //Message is deleted in main thread
                        UC7Message* msg = new UC7Message;
                        (*msg) = mUC7.mIncomingMessagesBuffer.front();

                        mUC7.mIncomingMessagesBuffer.pop_front();
                        if(!msg->check())
                        {
                            Log(lError) << "Corrupted message";
                        }
                        else
                        {
                            //Send windows message and let UI handle the message
                            if(!PostMessage(mHandle, UWM_UC7_MESSAGE, 1, (long) msg))
                            {
                                Log(lError) << "Post message failed in UC7 Message receiver.";
                            }
                        }

                        sleep(mProcessTimeDelay);
                    }
                    catch(...)
                    {
                    	Log(lError) << "Bad stuff in message consumer..";
                    }
                }

    		}//scoped lock
    	}

        Log(lInfo) << "UC7 Message Processor finished";
    	mIsFinished = true;
    	mIsRunning = false;
    }

}
