#pragma hdrstop
#include "abArrayBotJoystick.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------

using namespace mtk;

JoyStick::JoyStick()
:
mEnabled(false),
mJS(14)
{
    //Associate events with buttons
    mJS.setButtonEvents(1, this->getButton(1).down,  this->getButton(1).up    );
    mJS.setButtonEvents(2, this->getButton(2).down,  this->getButton(2).up    );
    mJS.setButtonEvents(3, this->getButton(3).down,  this->getButton(3).up    );
    mJS.setButtonEvents(4, this->getButton(4).down,  this->getButton(4).up    );

    mJS.setPOVButtonEvents(1, this->getPOVButton(1).down,  this->getPOVButton(1).up    );
    mJS.setPOVButtonEvents(2, this->getPOVButton(2).down,  this->getPOVButton(2).up    );
    mJS.setPOVButtonEvents(3, this->getPOVButton(3).down,  this->getPOVButton(3).up    );
    mJS.setPOVButtonEvents(4, this->getPOVButton(4).down,  this->getPOVButton(4).up    );

	mJS.setAxisEvent(1, this->getX1Axis().Move);
	mJS.setAxisEvent(2, this->getY1Axis().Move);

	mJS.setAxisEvent(3,  this->getX2Axis().Move);
	mJS.setAxisEvent(4,  this->getY2Axis().Move);

	//Start JS poll
    mJS.enable();
}

JoyStick::~JoyStick()
{}


bool JoyStick::enable()
{
    mJS.enable();
	mEnabled = true;
    return true;
}

bool JoyStick::disable()
{
    mJS.disable();
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
