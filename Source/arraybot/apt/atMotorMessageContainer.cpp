#pragma hdrstop
#include "atMotorMessageContainer.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;
namespace at
{

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
            if(msg.getCore() == mcStopProfiled || msg.getCore() == mcStopHard)
            {
    			mCommands.clear();
            }
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
        int sz = mCommands.size();
        return sz;
    }
}
