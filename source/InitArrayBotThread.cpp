#include <vcl.h>
#pragma hdrstop
#include <System.Classes.hpp>
#include "InitArrayBotThread.h"
#include "arraybot/atArrayBot.h"
#include "dslLogger.h"
#pragma package(smart_init)

using namespace dsl;
InitBotThread::InitBotThread()
:
mTheBot(NULL)
{}

void InitBotThread::run()
{
    if(mTheBot)
    {
        mTheBot->initialize();
        Log(lInfo) << "Finished ArrayBot Init";

        TThread::Synchronize(NULL, onFinishedInit);
    }
    mIsRunning = false;
    mIsFinished = true;
}

void InitBotThread::assingBot(ArrayBot* bot)
{
	mTheBot = bot;
}

