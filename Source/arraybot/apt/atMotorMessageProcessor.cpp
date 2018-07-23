#pragma hdrstop
#include "atMotorMessageProcessor.h"
#include "dslStringUtils.h"
#include "atMotorMessageContainer.h"
#include "Poco/Mutex.h"
#include "dslLogger.h"
#include "dslUtils.h"
#include "atAPTMotor.h"
//---------------------------------------------------------------------------

using Poco::Mutex;
using namespace dsl;

namespace at
{

    //----------------------------------------------------------------
    MotorMessageProcessor::MotorMessageProcessor(MotorMessageContainer& messageContainer,  const string& threadName)
    :
    dsl::Thread(threadName),
    mAllowProcessing(true),
    mMotorMessageContainer(messageContainer),
    mProcessedCount(0),
    mNotifyUI(NULL),
    mMotor(NULL),
    mLastProcessedCommand(mcNone),
    mProcessTimeDelay(50)
    {}

    //----------------------------------------------------------------
    MotorMessageProcessor::~MotorMessageProcessor()
    {
    	if(mIsRunning)
        {
    		stop();
        }
    }

    void MotorMessageProcessor::assignMotor(APTMotor* motor)
    {
    	mMotor = motor;
    }

    MotorCommandEnum MotorMessageProcessor::getLastProcessedMessage()
    {
    	return mLastProcessedCommand;
    }

    bool MotorMessageProcessor::start(bool inThread)
    {
    	if(isRunning())
    	{
    		Log(lDebug3) << "Tried to start a runnning thread";
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
    	dsl::Thread::stop();

    	//If thread is waiting.. get it out of wait state
    	mMotorMessageContainer.mNewCommandCondition.signal();
    }

    void MotorMessageProcessor::run()
    {
    	worker();
    }

    void MotorMessageProcessor::worker()
    {
    	Log(lDebug)<<"Entering Command Processor Worker Function.";
    	while(mIsTimeToDie == false)
    	{
    		{
    			Poco::ScopedLock<Poco::Mutex> lock(mMotorMessageContainer.mListMutex);
    			if(mMotorMessageContainer.count() == 0)
    			{
    				Log(lDebug3) << "Waiting for motor commands.";
    				mMotorMessageContainer.mNewCommandCondition.wait(mMotorMessageContainer.mListMutex);
    			}

               	MotorCommand cmd = mMotorMessageContainer.pop();
                //while(mMotorMessageContainer.hasMessage() && mIsTimeToDie == false)
                {


        	        Log(lDebug) << "Processing command: "<<cmd.asString();
                    if(mMotor == NULL)
                    {
                    	break;
                    }

                    switch(cmd.getCore())
                    {
                        case mcNone: Log(lWarning) << "Processing NONE command";                                                                        break;
                        case mcStopHard: 		        mMotor->stop(false);                                                                            break;
                        case mcForward: 		        mMotor->forward(false);                                                                         break;
                        case mcReverse: 		        mMotor->reverse(false);                                                                         break;
                        case mcJogForward:		        mMotor->jogForward(false);                                                                      break;
                        case mcJogReverse: 		        mMotor->jogReverse(false);                                                                      break;
                        case mcHome: 			        mMotor->home(false);   		                                                                    break;
                        case mcMoveToPosition: 	        mMotor->moveToPosition(cmd.getFirstVariable(), false);                                          break;
                        case mcSetVelocityParameters: 	mMotor->setVelocityParameters(cmd.getFirstVariable(), cmd.getSecondVariable(), false);          break;
                        case mcSwitchDirection: 		mMotor->switchDirection(false);                                                                 break;

                        case mcStopProfiled:
                        	mMotor->stopProfiled(false);
                            while(mMotor->isActive())
                            { ; }
    					break;

                        case mcSetVelocityForward:
                        	mMotor->setJogVelocity(cmd.getFirstVariable());
                        	mMotor->jogForward(false);
    					break;

                        case mcSetVelocityReverse:
                        	mMotor->setJogVelocity(cmd.getFirstVariable());
                        	mMotor->jogReverse(false);
    					break;

                        default: Log(lError) << "Motor Command: "<<toString(cmd.getCore())<<" was not reckognized!";                            break;

                    }
                    mLastProcessedCommand = cmd.getCore();
                }

    		}//mutex
            sleep(mProcessTimeDelay);
    	}

        Log(lInfo) << "Motor Message Processor finished";
    	mIsFinished = true;
    	mIsRunning = false;
    }

}
