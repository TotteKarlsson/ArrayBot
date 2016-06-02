#pragma hdrstop
#include "abJoystick.h"
#include "mtkLogger.h"
#include <windows.h>
#include <mmsystem.h>
//---------------------------------------------------------------------------

using namespace mtk;

JoyStick::JoyStick()
:
mEnabled(false)
{}

JoyStick::~JoyStick()
{}

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

JoyStickAxis& JoyStick::getX1Axis()
{
	return mX1Axis;
}

JoyStickAxis& JoyStick::getX2Axis()
{
	return mX2Axis;
}

JoyStickAxis& JoyStick::getY1Axis()
{
	return mY1Axis;
}

JoyStickAxis& JoyStick::getY2Axis()
{
	return mY2Axis;
}

JoyStickButton& JoyStick::getButton(int nr)
{
	switch(nr)
    {
    	case 1:  return mButton1;
    	case 2:  return mButton2;
    	case 3:  return mButton3;
    	case 4:  return mButton4;
    	case 9:  return mButton9;
    	case 10: return mButton10;

        default:
        	Log(lError) <<"We don't have that button";
            throw("Bad stuff..");
    }
}

JoyStickButton& JoyStick::getPOVButton(int nr)
{
	switch(nr)
    {
    	case 1:  return mPOVButton1;
    	case 2:  return mPOVButton2;
    	case 3:  return mPOVButton3;
    	case 4:  return mPOVButton4;

        default:
        	Log(lError) <<"Don't such a button";
            throw("Bad stuff..");
    }
}
