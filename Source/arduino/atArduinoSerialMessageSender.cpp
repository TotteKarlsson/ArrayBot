#pragma hdrstop
#include "atArduinoSerialMessageSender.h"
#include "atArduinoDevice.h"
#include "dslLogger.h"
#include "dslUtils.h"
//---------------------------------------------------------------------------
using namespace dsl;
using Poco::Mutex;

namespace at
{
    //----------------------------------------------------------------
    ArduinoSerialMessageSender::ArduinoSerialMessageSender(ArduinoDevice& d)
    :
    dsl::Thread(""),
    mProcessTimeDelay(1),
    mTheArduino(d)
    {}

    //----------------------------------------------------------------
    ArduinoSerialMessageSender::~ArduinoSerialMessageSender()
    {
    	if(mIsRunning)
        {
    		stop();
        }
    }

    //----------------------------------------------------------------
    void ArduinoSerialMessageSender::run()
    {
    	mIsRunning = true;
    	Log(lDebug)<<"Entering Arduino message sender thread for device: "<<mTheArduino.getName();
    	while(mIsTimeToDie == false)
    	{
    		{
    			Poco::ScopedLock<Poco::Mutex> lock(mTheArduino.mSendBufferMutex);
    			if(mTheArduino.mOutgoingMessagesBuffer.size() == 0)
    			{
    				Log(lDebug3) << "Waiting for messages to send to Arduino device: "<<mTheArduino.getName();
    				mTheArduino.mNewMessageToSendCondition.wait(mTheArduino.mSendBufferMutex);
    			}

                while(mTheArduino.mOutgoingMessagesBuffer.size() && mIsTimeToDie == false)
                {
                	try
                    {
                        string msg = mTheArduino.mOutgoingMessagesBuffer.front();
                        mTheArduino.mOutgoingMessagesBuffer.pop_front();

                        //Send windows message and let UI handle the message
                        if(!mTheArduino.mSerial.send(msg))
                        {
                            Log(lError) << "Sending message to Arduino \""<<mTheArduino.getName()<<"\" failed..";
                        }
                        else
                        {
                            Log(lDebug3) << "Sent message '"<<msg<<"' to device "<<mTheArduino.getName();
                        }

                        //Use a delay in case the serial devices input buffer overflows
                        sleep(mProcessTimeDelay);

                    }
                    catch(...)
                    {
                    	Log(lError) << "Exception thrown in message sender code for device: "<<mTheArduino.getName();
                    }
                }

    		}//scoped lock
    	}

        Log(lDebug) << "Arduino message sender thread finished for device: "<<mTheArduino.getName();
    	mIsFinished = true;
    	mIsRunning = false;
    }

    //----------------------------------------------------------------
    bool ArduinoSerialMessageSender::start(bool inThread)
    {
    	if(isRunning())
    	{
    		Log(lDebug3) << "Tried to start a runnning thread for device: "<<mTheArduino.getName();
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
    void ArduinoSerialMessageSender::stop()
    {
    	//Sets time to die to true
    	dsl::Thread::stop();

    	//If thread is waiting.. get it out of wait state
    	mTheArduino.mNewMessageToSendCondition.signal();
    }
}

