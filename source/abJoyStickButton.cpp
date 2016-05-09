#pragma hdrstop
#include "abJoyStickButton.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
//---------------------------------------------------------------------------

using namespace mtk;
JoyStickButton::JoyStickButton()
:
	mIsForward(true)
{}

JoyStickButton::~JoyStickButton()
{}


void JoyStickButton::assignMotor(APTMotor* motor)
{
	mMotor = motor;
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
	if(!mMotor)
    {
        Log(lInfo) << "Motor object is null..";
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
	if(!mMotor)
    {
        Log(lInfo) << "Motor is stopping";
    	return;
    }

	mMotor->stopProfiled();
}


