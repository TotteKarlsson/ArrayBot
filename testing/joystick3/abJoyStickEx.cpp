#pragma hdrstop
#include "abJoyStickEx.h"
#include <directinput.hpp>
#include <bitset>
#include "mtkLogger.h"

using namespace mtk;

//---------------------------------------------------------------------------
using namespace std;

JoyStickEx::JoyStickEx()
:
mNrOfButtons(14)
{
    mJoyStickID = JOYSTICKID1; //Support only one for now

    mJoyInfo.dwSize = sizeof(JOYINFOEX);
    mJoyInfo.dwFlags  =  JOY_RETURNALL;

    mUpdateStateTimer.setInterval(20);
	mUpdateStateTimer.OnTimerC = refresh;
    readCapabilities();

    //Setup buttons
    for(int i = 0; i < mNrOfButtons; i++)
    {
    	mButtons.push_back(Button());
    }
}

bool JoyStickEx::isEnabled()
{
	return mUpdateStateTimer.isRunning();
}

bool JoyStickEx::enable()
{
	return mUpdateStateTimer.start();
}

void JoyStickEx::disable()
{
	mUpdateStateTimer.stop();
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

void JoyStickEx::setButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down)
{
	mButtons[btnNr  - 1].mEvents = ButtonEvents(up, down);
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

    //Get retrieved buttons states
    bitset<32> buttonStates(mJoyInfo.dwButtons);


    for(int i = 0; i < mNrOfButtons; i++)
    {
        if(buttonStates.at(i) && mButtons[i].mButtonState == bsUp)
        {
            if(mButtons[i].mEvents.first)
            {
                Log(lDebug5) << "Calling OnButton"<<i + 1<<"Down";
                mButtons[i].mEvents.first();
            }
            mButtons[i].mButtonState = bsDown;
        }

        else if(!buttonStates.at(i) && mButtons[i].mButtonState == bsDown)
        {
            if(mButtons[i].mEvents.second)
            {
                Log(lDebug5) << "Calling OnButton"<<i + 1<<"Up";
                mButtons[i].mEvents.second();
            }
            mButtons[i].mButtonState = bsUp;
        }

    }
}

