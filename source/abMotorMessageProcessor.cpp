#pragma hdrstop
#include "abMotorMessageProcessor.h"
#include "mtkStringUtils.h"
#include "abMotorMessageContainer.h"
#include "Poco/Mutex.h"
#include "mtkLogger.h"
#include "mtkUtils.h"
#include "abAPTMotor.h"
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
mNotifyUI(NULL),
mMotor(NULL),
mLastProcessedCommand(mcNone),
mProcessTimeDelay(150)
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

            while(mMotorMessageContainer.hasMessage() && mIsTimeToDie == false)
            {
	           	MotorCommand cmd = mMotorMessageContainer.pop();

    	        Log(lDebug) << "Processing command: "<<cmd.asString();
                if(mMotor == NULL)
                {
                	break;
                }

                switch(cmd.getCore())
                {
                    case mcNone:
		    	        Log(lWarning) << "Processing NONE command";
					break;

                    case mcStopHard:
                    	mMotor->stop(false);
//                        //Wait until motor is stopped
////                        while(mMotor->isActive())
////                        {
////                        ;
////                        }
					break;
                    case mcStopProfiled:
                    	mMotor->stopProfiled(false);
                        while(mMotor->isActive())
                        { ; }
					break;

                    case mcForward:
                    	mMotor->forward(false);
					break;

                    case mcReverse:
                    	mMotor->reverse(false);
					break;

                    case mcJogForward:
                    	mMotor->jogForward(false);
					break;

                    case mcJogReverse:
                    	mMotor->jogReverse(false);
					break;

                    case mcMoveToPosition:
                    	mMotor->moveToPosition(cmd.getFirstVariable(), false);
					break;

                    case mcSetVelocityParameters:
                    	mMotor->setVelocityParameters(cmd.getFirstVariable(), cmd.getSecondVariable(), false);
					break;

                    case mcSetVelocityForward:
                    	mMotor->setJogVelocity(cmd.getFirstVariable());
                    	mMotor->jogForward(false);
					break;

                    case mcSetVelocityReverse:
                    	mMotor->setJogVelocity(cmd.getFirstVariable());
                    	mMotor->jogReverse(false);
					break;

                    case mcSwitchDirection:
                    	mMotor->switchDirection(false);
					break;
                    default: Log(lError) << "Motor Command: "<<toString(cmd.getCore())<<" was not reckognized!";

                }
                mLastProcessedCommand = cmd.getCore();
                sleep(mProcessTimeDelay);
            }

		}//mutex
	}

    Log(lInfo) << "Motor Message Processor finished";
	mIsFinished = true;
	mIsRunning = false;
}
