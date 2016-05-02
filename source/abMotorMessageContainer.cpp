#pragma hdrstop
#include "abMotorMessageContainer.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace mtk;
MotorMessageContainer::MotorMessageContainer()
:
mNrOfProcessedCommands(0)
{}

MotorMessageContainer::~MotorMessageContainer()
{}

void MotorMessageContainer::post(const string& msg)
{
    //The list of motorCMDs are accessed by child threads
    {
        Poco::ScopedLock<Poco::Mutex> lock(mListMutex);
        mCommands.push_back(msg);
        mNewCommandCondition.signal();
        Log(lDebug) << "A new motorCMD was posted to internal list";
    }
}

void  MotorMessageContainer::wakeUpWatchers()
{
	Log(lDebug) << "Wake up processors waiting for motorCMDs";
	mNewCommandCondition.signal();
}

string MotorMessageContainer::pop()
{
    string msg = "";

    //Scoped lock
    {
        Poco::ScopedLock<Poco::Mutex> lock(mListMutex);
        if(mCommands.size())
        {
            msg = mCommands.front();
            mCommands.pop_front();
        }
    }

    return msg;
}

string MotorMessageContainer::peek()
{
    string msg = "";

    //Scoped lock
    {
        Poco::ScopedLock<Poco::Mutex> lock(mListMutex);
        if(mCommands.size())
        {
            msg = mCommands.front();
        }
    }

    return msg;
}

bool MotorMessageContainer::hasMessage()
{
    return count() > 0  ? true : false;
}

int MotorMessageContainer::count()
{
//    mListMutex.lock();
    int sz = mCommands.size();
//    mListMutex.unlock();
    return sz;
}

