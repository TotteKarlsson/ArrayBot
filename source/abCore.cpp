#pragma hdrstop
#include <windows.h>
#include "abCore.h"
#include "mtkStringUtils.h"
#include "mtkWin32Utils.h"
using namespace mtk;

//Module entry point..
extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

//These integers are local data in the DLL
static unsigned int WM_MOTOR_WARNING_MESSAGE = 0;

void initABCoreLib()
{
	HMODULE	handle = LoadLibraryA("abResources");
    WM_MOTOR_WARNING_MESSAGE = RegisterWindowMessage(MOTOR_WARNING_MESSAGE);
}

unsigned int getABCoreMessageID(const string& msg)
{
	if(compareStrings(msg, MOTOR_WARNING_MESSAGE))
    {
    	return WM_MOTOR_WARNING_MESSAGE;
    }
    return 0;
}





