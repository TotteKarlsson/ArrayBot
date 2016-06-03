#pragma hdrstop
#include "abArrayBotJoystick.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------

using namespace mtk;

ArrayBotJoyStick::ArrayBotJoyStick()
:
mEnabled(false),
mJS(14)
{
    //Associate events with buttons
    mJS.setButtonEvents(1, mButton1.down,  mButton1.up    );
    mJS.setButtonEvents(2, mButton2.down,  mButton2.up    );
    mJS.setButtonEvents(3, mButton3.down,  mButton3.up    );
    mJS.setButtonEvents(4, mButton4.down,  mButton4.up    );

    mJS.setPOVButtonEvents(1, mPOVButton1.down,  mPOVButton1.up    );
    mJS.setPOVButtonEvents(2, mPOVButton2.down,  mPOVButton2.up    );
    mJS.setPOVButtonEvents(3, mPOVButton3.down,  mPOVButton3.up    );
    mJS.setPOVButtonEvents(4, mPOVButton4.down,  mPOVButton4.up    );

	mJS.setAxisEvent(1, mX1Axis.Move);
	mJS.setAxisEvent(2, mY1Axis.Move);

	mJS.setAxisEvent(3,  mX2Axis.Move);
	mJS.setAxisEvent(4,  mY2Axis.Move);

	//Start JS poll
    mJS.enable();
}

ArrayBotJoyStick::~ArrayBotJoyStick()
{}


bool ArrayBotJoyStick::enable()
{
    mJS.enable();
	mEnabled = true;
    return true;
}

bool ArrayBotJoyStick::disable()
{
    mJS.disable();
	mEnabled = false;
    return true;
}

bool ArrayBotJoyStick::isEnabled()
{
	return mEnabled;
}

JoyStickAxis& ArrayBotJoyStick::getX1Axis()
{
	return mX1Axis;
}

JoyStickAxis& ArrayBotJoyStick::getX2Axis()
{
	return mX2Axis;
}

JoyStickAxis& ArrayBotJoyStick::getY1Axis()
{
	return mY1Axis;
}

JoyStickAxis& ArrayBotJoyStick::getY2Axis()
{
	return mY2Axis;
}

JoyStickButton& ArrayBotJoyStick::getButton(int nr)
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

JoyStickButton& ArrayBotJoyStick::getPOVButton(int nr)
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
