#pragma hdrstop
#include "ConnectToElloUIThread.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace dsl;

ConnectToElloUIThread::ConnectToElloUIThread(ElloUIClient& c, int p)
:
mClient(c),
mPort(p)
{}

void ConnectToElloUIThread::run()
{
	mIsRunning = true;
	Log(lDebug3) << "Trying to connect to ElloUI";
	mClient.connect(mPort);
    mIsFinished = true;
    mIsRunning = false;
}
