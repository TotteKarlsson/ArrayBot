#pragma hdrstop
#include "TestPluginWorker.h"
#include "TestPlugin.h"
#include "dslLogger.h"
#include "dslUtils.h"
//---------------------------------------------------------------------------

using namespace dsl;
TestPluginWorker::TestPluginWorker(TestPlugin& host)
:
mTheHost(host)
{}

bool TestPluginWorker::start(bool runInThread)
{
    if(runInThread)
    {
        if(mThread.isRunning())
        {
            Log(lError)<<"Tried to start a working thread!";
            return false;
        }

        //Run the worker in a thread
        mThread.start(*this);
    }
    else
    {
        run(); //Not running worker in a thread
    }
    return true;
}

bool TestPluginWorker::isRunning() const
{
    return mThread.isRunning();
}

void TestPluginWorker::run()
{
    mTheHost.mIsWorking = true;

    if(mTheHost.mWorkStartedEvent)
    {
        mTheHost.mWorkStartedEvent(mTheHost.mWorkStartedData1, NULL);
    }

    try
    {
        mTheHost.mAnInteger = mTheHost.mAnInteger * 2;

        if(mTheHost.mWorkProgressEvent)
        {
            mTheHost.mWorkProgressEvent(mTheHost.mWorkProgressData1, NULL);
	    }
    }
    catch(...)
    {
        Log(lError) << "Not good...";
    }

    if(mTheHost.mWorkFinishedEvent)
    {
        mTheHost.mWorkFinishedEvent(mTheHost.mWorkFinishedData1, &(mTheHost.mAnInteger));
    }

    mTheHost.mIsWorking = false;
    mTheHost.mTerminate = false;
}

