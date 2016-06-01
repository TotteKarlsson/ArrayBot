#pragma hdrstop
#include "abJoyStickEx.h"
#include <directinput.hpp>
#include <bitset>
#include "mtkLogger.h"

using namespace mtk;

//---------------------------------------------------------------------------
using namespace std;

JoyStickEx::JoyStickEx()
: OnButton1Down(NULL)
{
    mJoyStickID = JOYSTICKID1; //Support only one for now

    mJoyInfo.dwSize = sizeof(JOYINFOEX);
    mJoyInfo.dwFlags  =  JOY_RETURNALL;

    readCapabilities();
}

void JoyStickEx::readCapabilities()
{
    if (mJoyStickID == -1)
    {
    	return;
    }

    int res = joyGetDevCaps(mJoyStickID, &mCapabilities, sizeof(JOYCAPS));
    if(res != JOYERR_NOERROR)
    {
		throw("Failed getting joystick capablities");
    }
}

//---------------------------------------------------------------------------
void JoyStickEx::refresh()
{
    if (mJoyStickID == -1)
    {
	    return;
    }

    mJoyInfo.dwSize  =  sizeof(JOYINFOEX);
    mJoyInfo.dwFlags = JOY_RETURNALL;
    int res = joyGetPosEx(mJoyStickID, &mJoyInfo);
    if(res != JOYERR_NOERROR)
    {
		throw("Failed getting joystick status");
    }

    bitset<32> buttons(mJoyInfo.dwButtons);
    if(buttons.at(0) && OnButton1Down)
    {
    	Log(lInfo) << "Calling OnButton1Down";
		OnButton1Down();
    }

    if(!buttons.at(0) && OnButton1Up)
    {
    	Log(lInfo) << "Calling OnButton1Up";
		OnButton1Up();
    }

}

