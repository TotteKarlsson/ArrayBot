#pragma hdrstop
#pragma argsused
#include "abArduinoServer.h"
#include "dslLogger.h"
#include "dslUtils.h"
#include "dslRandom.h"
#include <signal.h>

using namespace dsl;

bool gKeepGoing(true);
int  gDelay = 0;
bool gSetDelay = false;


void my_handler(int s)
{
	Log(lInfo) << "Caught signal: "<< s;
//    gSetDelay = true;
//    gDelay += 100;
//	gKeepGoing = true;
}

int main()
{
	dsl::gLogger.setLogLevel(lDebug4);
    dsl::LogOutput::mShowLogTime  		= true;
    dsl::LogOutput::mLogToConsole  		= true;

	signal (SIGINT,my_handler);

    ArduinoServer s(50000);
    ArduinoDevice& a1 = s.getArduinoDevice(1);

	a1.connect(4, 250000);

	try
    {
	    Random rnd(1,100);
    	int count(0);

        while(s.isRunning() && gKeepGoing)
        {
            sleep(1);
	        if(gSetDelay)
            {
            	stringstream msg;
                msg<<"[s:"<<gDelay<<"]";
            	a1.send(msg.str());
                gSetDelay = false;
            }
        }

        s.shutDown();
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

#pragma comment(lib, "dslCommon.lib")
#pragma comment(lib, "dslIPC.lib")
#pragma comment(lib, "dslMath.lib")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "abCore.lib")

