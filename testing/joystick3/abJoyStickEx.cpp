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
mNrOfButtons(14),
mMoveResolution(1000)
{
    mJoyStickID = JOYSTICKID1; //Support only one for now

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

void JoyStickEx::setAxisEvent(int axis, JoyStickAxisEvent move)
{
    switch(axis)
    {
    	case 1:
			mX1Axis.mEvent = move;
		break;

        case 2:
			mY1Axis.mEvent = move;
		break;

    	case 3:
			mX2Axis.mEvent = move;
		break;

        case 4:
			mY2Axis.mEvent = move;
		break;

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

    //Check X1 Axis
    if(abs((int) (mX1Axis.mPosition - mJoyInfo.dwXpos)) > mMoveResolution)
    {
    	if(mX1Axis.mEvent)
        {
	        Log(lDebug5) << "Calling X1 AxisEvent";
            mX1Axis.mEvent(mJoyInfo.dwXpos);
        }
        mX1Axis.mPosition = mJoyInfo.dwXpos;
    }

    //Check Y1 Axis
    if(abs((int) (mY1Axis.mPosition - mJoyInfo.dwYpos)) > mMoveResolution)
    {
    	if(mY1Axis.mEvent)
        {
	        Log(lDebug5) << "Calling Y1 AxisEvent";
            mY1Axis.mEvent(mJoyInfo.dwYpos);
        }
        mY1Axis.mPosition = mJoyInfo.dwYpos;
    }

    //Check X2 Axis  (Z - axis in API struc)
    if(abs((int) (mX2Axis.mPosition - mJoyInfo.dwZpos)) > mMoveResolution)
    {
    	if(mX2Axis.mEvent)
        {
	        Log(lDebug5) << "Calling X2 AxisEvent";
            mX2Axis.mEvent(mJoyInfo.dwZpos);
        }
        mX2Axis.mPosition = mJoyInfo.dwZpos;
    }

    //Check Y2 Axis (
    if(abs((int) (mY2Axis.mPosition - mJoyInfo.dwRpos)) > mMoveResolution)
    {
    	if(mY2Axis.mEvent)
        {
	        Log(lDebug5) << "Calling Y2 AxisEvent";
            mY2Axis.mEvent(mJoyInfo.dwRpos);
        }
        mY2Axis.mPosition = mJoyInfo.dwRpos;
    }

    //Process retrieved buttons states
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

