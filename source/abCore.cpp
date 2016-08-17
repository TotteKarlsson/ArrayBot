#pragma hdrstop
#include <windows.h>
#include "abCore.h"
#include "mtkStringUtils.h"
#include <Mmsystem.h>
using namespace mtk;

static UINT WM_MOTOR_WARNING_MESSAGE = 0;

string 	getSoundResourceName(ABSound a);
bool PlayResource(const string& resName, long flags = 0);

unsigned int getABCoreMessageID(const string& msg)
{
	if(compareStrings(msg, MOTOR_WARNING_MESSAGE))
    {
    	return WM_MOTOR_WARNING_MESSAGE;
    }
    return 0;
}

extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

string getSoundResourceName(ABSound a)
{
	switch(a)
    {
    	case absMotorStop: return "MOTOR_STOP_SOUND";
    }
}

void initABCoreLib()
{
    WM_MOTOR_WARNING_MESSAGE = RegisterWindowMessage(MOTOR_WARNING_MESSAGE);
}

void playABSound(ABSound a, long flags)
{
	string fName(getSoundResourceName(a));
	PlayResource(fName, flags);
}


bool PlayResource(const string& resName, long flags)
{
    HINSTANCE Nl = NULL;

    HRSRC hResInfo= FindResourceA(Nl, resName.c_str(), RT_RCDATA);
    if(hResInfo == NULL)
    {
       return false;
    }

    HANDLE hRes = LoadResource(Nl,hResInfo);
    if(hRes == NULL)
    {
      	return false;
    }

    LPSTR lpRes = (LPSTR) LockResource(hRes);
    if(lpRes == NULL)
    {
      	return false;
    }

    if(sndPlaySound(lpRes, SND_MEMORY | SND_ASYNC | flags)  == NULL)
    {
    	return false;
    }

    /* Free the WAVE resource and return success or failure. */
    FreeResource(hRes);
    return true;
}



#if defined DSL_STATIC
	#pragma comment(lib, "mtkCommon-static.lib")
	#pragma comment(lib, "mtkMath-static.lib")
	#pragma comment(lib, "mtkIPC-static.lib")
#else
	#pragma comment(lib, "mtkCommon.lib")
	#pragma comment(lib, "mtkMath.lib")
	#pragma comment(lib, "mtkIPC.lib")
#endif

#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")

//Thorlabs
#pragma comment(lib, "Thorlabs.MotionControl.TDIEngineB.lib")

//Motors
#pragma comment(lib, "Thorlabs.MotionControl.TCube.StepperMotorB.lib")
#pragma comment(lib, "Thorlabs.MotionControl.IntegratedStepperMotorsB.lib")
#pragma comment(lib, "Thorlabs.MotionControl.TCube.DCServoB.lib")
#pragma comment(lib, "Thorlabs.MotionControl.TCube.BrushlessMotorB.lib")

