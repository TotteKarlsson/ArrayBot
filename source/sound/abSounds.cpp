#pragma hdrstop
#include "abSounds.h"
#include <windows.h>
#include "mtkWin32Utils.h"
#include <mmsystem.h>
//---------------------------------------------------------------------------

using namespace mtk;

string getSoundResourceName(ABSound a)
{
	switch(a)
    {
    	case absMotorStop: 		return "MOTOR_STOP_SOUND";
    	case absMotorWarning: 	return "MOTOR_WARNING_SOUND";
        default: 	  			return "MOTOR_WARNING_SOUND";
    }
}

void playABSound(ABSound a, long flags)
{
	string fName(getSoundResourceName(a));
	PlayResource(fName, flags);
}

bool PlayResource(const string& resName, long flags)
{
    HINSTANCE modHandle = GetModuleHandle("abCore.dll");
    HRSRC hResInfo= FindResourceA(modHandle, resName.c_str(), RT_RCDATA);
    if(hResInfo == NULL)
    {
       return false;
    }

    HANDLE hRes = LoadResource(modHandle, hResInfo);
    if(hRes == NULL)
    {
      	return false;
    }

    LPSTR lpRes = (LPSTR) LockResource(hRes);
    if(lpRes == NULL)
    {
      	return false;
    }

//    if(PlaySound(lpRes, modHandle, SND_MEMORY | SND_ASYNC | flags)  == false)
    if(PlaySound(lpRes, modHandle, SND_MEMORY | flags)  == false)
    {
    	string error = getLastWin32Error();
    	return false;
    }

    /* Free the WAVE resource and return success or failure. */
    FreeResource(hRes);
    return true;
}

