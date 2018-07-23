#pragma hdrstop
#include "atJoyStickButton.h"
#include "dslLogger.h"
#include "apt/atAPTMotor.h"
//---------------------------------------------------------------------------

using namespace dsl;
namespace at
{
    JoyStickButton::JoyStickButton()
    :
    	mIsForward(true),
        mIsEnabled(false),
        mButtonState(bsUp)
    {}

    JoyStickButton::~JoyStickButton()
    {}

    void JoyStickButton::setState(JoyStickButtonState s)
    {
    	mButtonState = s;
    }

    JoyStickButtonState JoyStickButton::getState()
    {
    	return mButtonState;
    }

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

    bool JoyStickButton::isDown()
    {
    	return (mButtonState == bsDown) ? true : false;
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
    	mButtonState = bsDown;
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
    	mButtonState = bsUp;
        Log(lDebug3) << "JSButton Up.";
        if(!mMotor || !mIsEnabled)
        {
            Log(lInfo) << "Motor object is null or JS button is disabled.";
        	return;
        }

    	mMotor->stopProfiled();
    }
}
