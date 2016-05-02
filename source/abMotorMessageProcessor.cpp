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
	stop();
//	mDB.close();
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

bool MotorMessageProcessor::openDataBase(const string& db)
{
//	if(!fileExists(db))
//	{
//		return false;
//	}
//
//	bool res = mDB.open(db);
//	if(!res)
//	{
//		Log(lError) << "Order Processor failed opening database";
//	}
//	return res;
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
				Log(lDebug3) << "Waiting for motorCMDs.";
				mMotorMessageContainer.mNewCommandCondition.wait(mMotorMessageContainer.mListMutex);
			}

            //Allow the processor to import all pending motorCMDs before updating stats in the UI
			{
//				Poco::ScopedLock<Poco::Mutex> lock(mDB.mDBMutex);
//				while(mMotorMessageContainer.count() && mIsTimeToDie == false)
//				{
//					string motorCMDLine = mMotorMessageContainer.pop();
//					StringList motorCMD(motorCMDLine,'|');
//
//					try
//					{
//						if(importOrderData(motorCMD))
//						{
//							importCustomerData(motorCMD);
//							importStateOrRegionData(motorCMD);
//							Log(lInfo) << "Importing Order: "<<(motorCMD[0]);
//						}
//						else
//						{
//							Log(lError) << "Failed importing motorCMD";
//						}
//					}
//					catch(const mtk::SQLiteException& e)
//					{
//						switch(e.errorCode())
//						{
//							case 5: 	Log(lDebug2) << "Database is locked or busy. Failed to import motorCMD: "<<motorCMD[0];               break;
//							case 19:	Log(lDebug2) << "Order already imported: "<<motorCMD[0];                                         break;
//							default:  	Log(lDebug2) << "An unhandled SQLite exception: "<<motorCMD[0]<<" Message was: " << e.what();    break;
//						}
//					}
//					catch(const mtk::MoleculixException& e)
//					{
//						Log(lDebug2) << "Exception: "<<e.what();
//					}
//				}
//			   mDB.createStatistics();
			} //DBMutex

//			if(mNotifyUI && mIsTimeToDie == false)
//			{
//				TThread::Synchronize(NULL, mNotifyUI);
//			}
		}//Order container mutex
	}

	mIsFinished = true;
	mIsRunning = false;
}


