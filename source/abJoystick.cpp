#pragma hdrstop
#include "abJoystick.h"
#include "mtkLogger.h"
#include <windows.h>
#include <mmsystem.h>
//---------------------------------------------------------------------------

using namespace mtk;

JoyStick::JoyStick(int hwnd)
:
mHandle(hwnd),
mEnabled(false),
mMessageRate(20)
{}

JoyStick::~JoyStick()
{
	if(mJoyStickConnected)
    {
  		joyReleaseCapture(mJoystickID);
    }
}

void JoyStick::setWindowHandle(int handle)
{
	mHandle = handle;
}

bool JoyStick::enable()
{
	mEnabled = true;
    return true;
}

bool JoyStick::disable()
{
	mEnabled = false;
    return true;
}

bool JoyStick::isEnabled()
{
	return mEnabled;
}

bool JoyStick::setMessageRate(int rate)
{
	mMessageRate = rate;
    return true;
}

int JoyStick::getMessageRate()
{
	return mMessageRate;
}

bool JoyStick::connect()
{
    mJoyStickConnected = false;
    MMRESULT  	JoyResult;
    JOYINFO 	JoyInfo;

    // the joystick could be disconnected even if the driver is
    // loaded. use joyGetPos to detect if a joystick is connected
    // it returns JOYERR_NOERROR if the joystick is plugged in
	// find out how many joysticks the driver supports
  	mJoyStickDriverCount = joyGetNumDevs();

  	if(mJoyStickDriverCount == 0)    // can any joysticks be supported
  	{
		return false;
  	}
    // test for joystick1
    JoyResult = joyGetPos(JOYSTICKID1,&JoyInfo);
    if(JoyResult != JOYERR_UNPLUGGED)
    {
      mJoyStickConnected = true;
      mJoystickID = JOYSTICKID1;
    }
    else if(JoyResult == MMSYSERR_INVALPARAM)
    {
    	// INVALIDPARAM means something is bad. quit now without
	    // checking for joystick 2
      	Log(lError) << "An error occured while calling joyGetPosEx";
		return false;
    }
    else if((JoyResult=joyGetPos(JOYSTICKID2,&JoyInfo)) == JOYERR_NOERROR)
    {
      // if joystick1 is unconnected, check for joystick2
      mJoyStickConnected = true;
      mJoystickID = JOYSTICKID2;
    }

    // use joyGetDevCaps to display information from JOYCAPS structure
    // note that not all of the information from joyGetDevCaps is shown
    // here. consult the win32 SDK help file for a full description of
    // joyGetDevCaps
    JOYCAPS 			        mJoyCaps;
    joyGetDevCaps(mJoystickID, &mJoyCaps, sizeof(JOYCAPS));

    // Tell Windows we want to receive joystick events.
    // Handle = receiver, JoystickID = joystick that we're using
    // 3rd arg = how often MM_JOYMOVE events happen
	if(mJoyStickConnected)
  	{
    	joySetCapture((HWND) mHandle, mJoystickID, mMessageRate*mJoyCaps.wPeriodMin,FALSE);
  	}
	return mJoyStickConnected;
}

JoyStickAxis& JoyStick::getXAxis()
{
	return mXAxis;
}

JoyStickAxis& JoyStick::getYAxis()
{
	return mYAxis;
}

JoyStickAxis& JoyStick::getZAxis()
{
	return mZAxis;
}

JoyStickButton& JoyStick::getButton(int nr)
{
	switch(nr)
    {
    	case 1:  return mButton1;
    	case 2:  return mButton2;
    	case 3:  return mButton3;
    	case 4:  return mButton4;
    	case 5:  return mButton5;
    	case 6:  return mButton6;
    	case 7:  return mButton7;
    	case 8:  return mButton8;
    	case 9:  return mButton9;
    	case 10: return mButton10;

        default:
        	Log(lError) <<"We don't have that button";
            throw("Bad stuff..");
    }
}
