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

void MotorMessageContainer::post(const MotorCommand& msg)
{
    //The list of motorCMDs are accessed by child threads
    {
        Poco::ScopedLock<Poco::Mutex> lock(mListMutex);
        mCommands.push_back(msg);
        mNewCommandCondition.signal();
        Log(lDebug) << "Command posted to message list: "<<msg.asString();
    }
}

void  MotorMessageContainer::wakeUpWatchers()
{
	Log(lDebug) << "Wake up processors waiting for motorCMDs";
	mNewCommandCondition.signal();
}

MotorCommand MotorMessageContainer::pop()
{
    MotorCommand cmd(mcNone);

    //Scoped lock
    {
        Poco::ScopedLock<Poco::Mutex> lock(mListMutex);
        if(mCommands.size())
        {
            cmd = mCommands.front();
            mCommands.pop_front();
        }
    }

    return cmd;
}

MotorCommand MotorMessageContainer::peek()
{
    MotorCommand cmd(mcNone);

    //Scoped lock
    {
        Poco::ScopedLock<Poco::Mutex> lock(mListMutex);
        if(mCommands.size())
        {
            cmd = mCommands.front();
        }
    }

    return cmd;
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

