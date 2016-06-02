#pragma hdrstop
#include "abJoyStickButton.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
//---------------------------------------------------------------------------

using namespace mtk;
JoyStickButton::JoyStickButton()
:
	mIsForward(true),
    mIsEnabled(false)
{}

JoyStickButton::~JoyStickButton()
{}


void JoyStickButton::assignMotor(APTMotor* motor)
{
	mMotor = motor;
}

void JoyStickButton::enable()
{
	mIsEnabled = true;
}

void JoyStickButton::disable()
{
	mIsEnabled = false;
}

void JoyStickButton::setForward()
{
	mIsForward = true;
}

void JoyStickButton::setReverse()
{
	mIsForward = false;
}

void JoyStickButton::down()
{
    Log(lDebug3) << "JSButton Down.";
	if(!mMotor || !mIsEnabled)
    {
        Log(lInfo) << "Motor object is null or JS button is disabled.";
    	return;
    }

	if(mIsForward)
    {
    	mMotor->jogForward();
    }
    else
    {
    	mMotor->jogReverse();
    }
}

void JoyStickButton::up()
{
    Log(lDebug3) << "JSButton Up.";
    if(!mMotor || !mIsEnabled)
    {
        Log(lInfo) << "Motor object is null or JS button is disabled.";
    	return;
    }

	mMotor->stopProfiled();
}
