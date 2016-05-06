#pragma hdrstop
#include "abJoystick.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------

using namespace mtk;

JoyStick::JoyStick(int hwnd)
:
mHandle(hwnd),
mEnabled(false)
{

}

JoyStick::~JoyStick()
{
	if(mJoyStickConnected)
    {
  		joyReleaseCapture(mJoystickID);
    }
}
bool JoyStick::enable()
{
	mEnabled = true;
}

bool JoyStick::disable()
{
	mEnabled = false;
}

bool JoyStick::isEnabled()
{
	return mEnabled;
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

	//  ShowDeviceInfo(); // initialize the labels.
	//  ShowStatusInfo();

    // use joyGetDevCaps to display information from JOYCAPS structure
    // note that not all of the information from joyGetDevCaps is shown
    // here. consult the win32 SDK help file for a full description of
    // joyGetDevCaps
    joyGetDevCaps(mJoystickID, &mJoyCaps, sizeof(JOYCAPS));

    // Tell Windows we want to receive joystick events.
    // Handle = receiver, JoystickID = joystick we're using
    // 3rd arg = how often MM_JOYMOVE events happen
	if(mJoyStickConnected)
  	{
    	joySetCapture((HWND) mHandle, mJoystickID, 20*mJoyCaps.wPeriodMin,FALSE);
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
    	case 1: return mButton1;
    	case 2: return mButton2;
    	case 3: return mButton3;
    	case 4: return mButton4;
        default:
        	Log(lError) <<"We don't have that button";
            throw("Bad stuff..");
    }
}
