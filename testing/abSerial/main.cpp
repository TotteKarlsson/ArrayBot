#pragma hdrstop
#pragma argsused
#include "abArduinoServer.h"
#include "mtkLogger.h"
#include "mtkUtils.h"
#include "abArduinoDevice.h"
#include <signal.h>

using namespace mtk;

bool gKeepGoing(true);
void my_handler(int s)
{
	Log(lInfo) << "Caught signal: "<< s;
	gKeepGoing = false;
}

void messageCallBack(const string& msg);

int main()
{
	mtk::gLogger.setLogLevel(lDebug4);
    mtk::LogOutput::mShowLogTime  		= true;
    mtk::LogOutput::mLogToConsole  		= true;

	signal (SIGINT,my_handler);
    Serial	mSerial(3, 115200);

    while(mSerial.isConnected() && gKeepGoing)
    {
    	sleep(300);
        mSerial.assignMessageReceivedCallBack(messageCallBack);

//        while(mSerial.hasMessage())
//        {
//        	Log(lInfo) << "Message: "<< mSerial.popMessage();
//        }

        if(!mSerial.send("[HELLO]"))
        {
        	Log(lError) << "Failed to send data...";
        }
    }

    mSerial.disConnect();

    return 0;
}

void messageCallBack(const string& msg)
{
	Log(lInfo) << msg;
}

#pragma comment(lib, "mtkCommon.lib")
#pragma comment(lib, "mtkIPC.lib")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "abCore.lib")

