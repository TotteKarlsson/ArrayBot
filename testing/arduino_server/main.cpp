#pragma hdrstop
#pragma argsused
#include "abArduinoServer.h"
#include "mtkLogger.h"
#include "mtkUtils.h"

using namespace mtk;


int main()
{
	mtk::gLogger.setLogLevel(lDebug5);
    mtk::LogOutput::mShowLogTime  = true;
    mtk::LogOutput::mLogToConsole  = true;

	ArduinoServer s(50000);
	try
    {
        while(s.isRunning())
        {
            Log(lDebug) <<"Server HeartBeat";
            IPCMessage msg(-1, "Server HeartBeat");
            s.broadcast(msg);
            sleep(10000);

        }
    }
    catch(...)
    {
    	Log(lError) << "Something bad happened";
    }
	return 0;
}



#pragma comment(lib, "mtkCommon.lib")
#pragma comment(lib, "mtkIPC.lib")
#pragma comment(lib, "poco_foundation-static.lib")
