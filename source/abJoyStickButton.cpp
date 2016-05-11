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
	if(!mMotor || !mIsEnabled)
    {
        Log(lInfo) << "Motor object is null or JS button is disabled.";
    	return;
    }

    Log(lInfo) << "Motor moving forward.";

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
	if(!mMotor || !mIsEnabled)
    {
        Log(lInfo) << "Motor is stopping";
    	return;
    }

	mMotor->stopProfiled();
}
