#pragma hdrstop
//#include <System.Classes.hpp>
#include "abMotorMessageCreator.h"
#include "mtkStringUtils.h"
#include "abMotorMessageContainer.h"
#include "Poco/Mutex.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "mtkLogger.h"
#include "Poco/DateTime.h"
#include "mtkUtils.h"
//---------------------------------------------------------------------------

using Poco::Mutex;
using namespace mtk;
//----------------------------------------------------------------
MotorMessageCreator::MotorMessageCreator(const string& threadName)
:
Thread(threadName),
mRepeatRate(1)
{}

//----------------------------------------------------------------
MotorMessageCreator::~MotorMessageCreator()
{
	stop();
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
