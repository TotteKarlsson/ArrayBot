#pragma hdrstop
#pragma argsused

#include <signal.h>
#include <stdio.h>
#include "abArduinoClient.h"
#include "mtkLogger.h"
#include "mtkUtils.h"

bool gKeepGoing(true);
int  gDelay = 0;
bool gSetDelay = false;

using namespace mtk;

void my_handler(int s)
{
	Log(lInfo) << "Caught signal: "<< s;
//    gSetDelay = true;
//    gDelay += 100;
	gKeepGoing = false;
}


int main()
{
	mtk::gLogger.setLogLevel(lDebug4);
    mtk::LogOutput::mShowLogTime  		= true;
    mtk::LogOutput::mLogToConsole  		= true;

	signal (SIGINT,my_handler);
	ArduinoClient ac;
    ac.connect(50000);

	try
    {
    	int count(0);
        while(ac.isConnected() && gKeepGoing)
        {
            sleep(1000);
            ac.postMessage("[Hello]");
        }

        ac.shutDown();
    }
    catch(...)
    {
    	Log(lError) << "Something bad happened";
    }

    gKeepGoing = true;
    while(gKeepGoing)
    {
		Log(lInfo) <<"...";
		sleep(400);
    }

	return 0;
}

#pragma comment(lib, "abCore.lib")
#pragma comment(lib, "mtkCommon.lib")
#pragma comment(lib, "mtkIPC.lib")
#pragma comment(lib, "poco_foundation-static.lib")

