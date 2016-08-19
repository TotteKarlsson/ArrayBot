#pragma hdrstop
#include "abArrayBotJoystick.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------

using namespace mtk;

ArrayBotJoyStick::ArrayBotJoyStick(int& joyStickID)
:
mEnabled(false),
mCoverSlipAxesEnabled(false),
mWhiskerAxesEnabled(false),
mCoverSlipZButtonsEnabled(false),
mWhiskerZButtonsEnabled(false),
mJoyStickID(joyStickID),
mJSMessageDispatcher(*this, 14, mJoyStickID)
{
    //Associate events with buttons
    mJSMessageDispatcher.setButtonEvents(1, mButton1.down,  mButton1.up);
    														//!Z- down
    mJSMessageDispatcher.setButtonEvents(2, mButton2.down,  mButton2.up);

    mJSMessageDispatcher.setButtonEvents(3, mButton3.down,  mButton3.up);

    														//!Z-up
    mJSMessageDispatcher.setButtonEvents(4, mButton4.down,  mButton4.up);

    mJSMessageDispatcher.setButtonEvents(5, mButton5.down,  mButton5.up);
    mJSMessageDispatcher.setButtonEvents(6, mButton6.down,  mButton6.up);

    mJSMessageDispatcher.setButtonEvents(7, mButton7.down,  mButton7.up);
    mJSMessageDispatcher.setButtonEvents(8, mButton8.down,  mButton8.up);

    mJSMessageDispatcher.setPOVButtonEvents(1, mPOVButton1.down,  mPOVButton1.up);
    mJSMessageDispatcher.setPOVButtonEvents(2, mPOVButton2.down,  mPOVButton2.up);
    mJSMessageDispatcher.setPOVButtonEvents(3, mPOVButton3.down,  mPOVButton3.up);
    mJSMessageDispatcher.setPOVButtonEvents(4, mPOVButton4.down,  mPOVButton4.up);

	mJSMessageDispatcher.setAxisEvent(1, mX1Axis.Move);
	mJSMessageDispatcher.setAxisEvent(2, mY1Axis.Move);

	mJSMessageDispatcher.setAxisEvent(3,  mX2Axis.Move);
	mJSMessageDispatcher.setAxisEvent(4,  mY2Axis.Move);

	//Start JS poll
    mJSMessageDispatcher.enable(joyStickID);
}

ArrayBotJoyStick::~ArrayBotJoyStick()
{}

bool ArrayBotJoyStick::isValid()
{
	return mJSMessageDispatcher.isValid();
}

bool ArrayBotJoyStick::enableJoyStickWithID(int id)
{
	mJoyStickID = id;
	mEnabled = mJSMessageDispatcher.enable(id);
    return mEnabled;
}

bool ArrayBotJoyStick::setAxesMaxVelocity(double maxV)
{
    mX1Axis.setMaxVelocity(maxV);
    mX2Axis.setMaxVelocity(maxV);

    mY1Axis.setMaxVelocity(maxV);
    mY2Axis.setMaxVelocity(maxV);
    return true;
}

void ArrayBotJoyStick::setButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down)
{
	mJSMessageDispatcher.setButtonEvents(btnNr, up, down);
}

void ArrayBotJoyStick::setPOVButtonEvents(int btnNr, JoyStickEvent up, JoyStickEvent down)
{
	mJSMessageDispatcher.setPOVButtonEvents(btnNr, up, down);
}

void ArrayBotJoyStick::setAxisEvent(int axis, JoyStickAxisEvent move)
{
	mJSMessageDispatcher.setAxisEvent(axis, move);
}

bool ArrayBotJoyStick::disableCoverSlipAxes()
{
	mCoverSlipAxesEnabled = false;
    return true;
}

bool ArrayBotJoyStick::enableCoverSlipAxes()
{
	mCoverSlipAxesEnabled = true;
    return true;
}

bool ArrayBotJoyStick::disableWhiskerAxes()
{
	mWhiskerAxesEnabled = false;
    return true;
}

bool ArrayBotJoyStick::enableWhiskerAxes()
{
	mWhiskerAxesEnabled = true;
    return true;
}

bool ArrayBotJoyStick::enableCoverSlipZButtons()
{
	mCoverSlipZButtonsEnabled = true;
    return true;
}

bool ArrayBotJoyStick::enableWhiskerZButtons()
{
	mWhiskerZButtonsEnabled = true;
    return true;
}

bool ArrayBotJoyStick::disableCoverSlipZButtons()
{
	mCoverSlipZButtonsEnabled = false;
    return true;
}

bool ArrayBotJoyStick::disableWhiskerZButtons()
{
	mWhiskerZButtonsEnabled = false;
    return true;
}

bool ArrayBotJoyStick::enable()
{
    mEnabled = mJSMessageDispatcher.enable(mJoyStickID);
    if(mEnabled)
    {
		mCoverSlipAxesEnabled = true;
		mWhiskerAxesEnabled = true;
        mCoverSlipZButtonsEnabled = true;
        mWhiskerZButtonsEnabled = true;
    }
    else
    {
		mCoverSlipAxesEnabled = false;
		mWhiskerAxesEnabled = false;
        mCoverSlipZButtonsEnabled = false;
        mWhiskerZButtonsEnabled = false;
    }

    return mEnabled;
}

bool ArrayBotJoyStick::disable()
{
    mJSMessageDispatcher.disable();
	mCoverSlipAxesEnabled = false;
	mWhiskerAxesEnabled = false;
    mCoverSlipZButtonsEnabled = false;
    mWhiskerZButtonsEnabled = false;

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

    	case 7:  return mButton7;
    	case 8:  return mButton8;

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

unsigned long ArrayBotJoyStick::getButtonBits()
{
	return mJSMessageDispatcher.getButtonBits();
}

unsigned long ArrayBotJoyStick::getPOVBits()
{
	return mJSMessageDispatcher.getPOVBits();
}

unsigned long ArrayBotJoyStick::getX1Pos()
{
	return mJSMessageDispatcher.getX1Pos();
}

unsigned long ArrayBotJoyStick::getY1Pos()
{
	return mJSMessageDispatcher.getY1Pos();
}

unsigned long ArrayBotJoyStick::getZ1Pos()
{
	return mJSMessageDispatcher.getZ1Pos();
}

unsigned long ArrayBotJoyStick::getX2Pos()
{
	return mJSMessageDispatcher.getX2Pos();
}

unsigned long ArrayBotJoyStick::getY2Pos()
{
	return mJSMessageDispatcher.getY2Pos();
}

unsigned long ArrayBotJoyStick::getZ2Pos()
{
	return mJSMessageDispatcher.getZ2Pos();
}

