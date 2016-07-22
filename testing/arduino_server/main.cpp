#pragma hdrstop
#pragma argsused
#include "abArduinoServer.h"
#include "mtkLogger.h"
#include "mtkUtils.h"
#include "abArduinoDevice.h"
#include <signal.h>

using namespace mtk;

bool keepGoing(true);
void my_handler(int s)
{
	Log(lInfo) << "Caught signal: "<< s;
	keepGoing = false;
}

int main()
{
	mtk::gLogger.setLogLevel(lDebug5);
    mtk::LogOutput::mShowLogTime  		= true;
    mtk::LogOutput::mLogToConsole  		= true;


	signal (SIGINT,my_handler);

//	ArduinoServer s(50000);
    ArduinoDevice a1(4,  115200);
//    Serial serial(4, 115200);


	try
    {
    	int count(0);
        while(serial.isConnected() && keepGoing == true)
        {
            while(serial.hasMessage())
            {
            	string msg = serial.popMessage();
            	Log(lInfo) << msg;
            }

            count++;
	        sleep(100);
        }

        serial.disConnect();
    }
//        while(s.isRunning())
//        {
//            Log(lDebug) <<"Server HeartBeat";
//            IPCMessage msg(-1, "Server HeartBeat");
////            s.broadcast(msg);
//            sleep(5000);
//        }
//    }
    catch(...)
    {
    	Log(lError) << "Something bad happened";
    }

    return 0;
}



#pragma comment(lib, "mtkCommon.lib")
#pragma comment(lib, "mtkIPC.lib")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "abCore.lib")
