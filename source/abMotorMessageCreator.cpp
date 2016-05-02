#pragma hdrstop
#include <System.Classes.hpp>
#include "abMotorMessageCreator.h"
#include "mtkStringUtils.h"
#include "amlMotorMessageContainer.h"
#include "Poco/Mutex.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "mtkLogger.h"
#include "Poco/DateTime.h"
#include "amlAccount.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using Poco::Mutex;
//----------------------------------------------------------------
MotorMessageCreator::MotorMessageCreator(const string& threadName)
:
Thread(threadName),
mAccount(NULL),
mRepeatRate(1)
{}

//----------------------------------------------------------------
MotorMessageCreator::~MotorMessageCreator()
{
	stop();
}


void MotorMessageCreator::setAccount(Account* a)
{
	mAccount = a;
}
void MotorMessageCreator::setRepeatRate(int rate)
{
	mRepeatRate = rate;
}

void MotorMessageCreator::stop()
{
	//Sets time to die to true
	mtk::Thread::stop();

	if(mThread.isRunning())//The dtor will call shutdown. If already shutdown, the thread object is NULL
	{
//		mThread.join();    //Wait for worker to exit...
	}
}

void MotorMessageCreator::run()
{
	worker();
}

void MotorMessageCreator::worker()
{
	Log(lDebug)<<"Entering MotorMessageCreator Worker Function.";
	mID =  GetCurrentThreadId();

	while(mIsTimeToDie == false)
	{
		Poco::DateTime now;
		stringstream dts;
		dts <<Poco::DateTimeFormatter::format(now,"%Y-%m-%dT%H:%M:%S-%i");
		StringList motorCMD;
		motorCMD.reSize(13);
		motorCMD[0] = dts.str();
		motorCMD[1] = "Joe Doe"; //Name
		motorCMD[2] = "addr1"; 	//addr1
		motorCMD[3] = "addr2";	 //addr2
		motorCMD[4] = "The City"; // City
		motorCMD[5] = "WA"; //State or region
		motorCMD[6] = "98125"; //Postal code
		motorCMD[7] = "test@test.com";//Customer ID
		motorCMD[8] = "425 780 9655";//Phone

		motorCMD[9]  = Poco::DateTimeFormatter::format(now,"%Y-%m-%dT%H:%M:%S");
		motorCMD[10] = Poco::DateTimeFormatter::format(now,"%Y-%m-%dT%H:%M:%S");
		motorCMD[11] = mtk::toString(2);  //nr of items=
		motorCMD[12] = mtk::toString(24.45);    //motorCMD_total
		if(mAccount)
		{
			mAccount->postOrder(motorCMD.asString('|'));
		}

		sleep((long) ((double) 60*1000.0 / mRepeatRate ));
	}
	mIsFinished = true;
	mIsRunning  = false;
}

bool MotorMessageCreator::start(bool inThread)
{
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
