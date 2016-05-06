#pragma hdrstop
#include "abJoystickAxis.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
#include "mtkUtils.h"

using namespace mtk;

JoyStickAxis::JoyStickAxis()
:
	mMaxPosition(65535),
    mNumberOfGears(10),
    mMaxVelocity(1),
    mIsEnabled(false),
    mZeroInMiddle(true),
	mRunningAverage(0),
	mAlpha(0.9)
{
}

JoyStickAxis::~JoyStickAxis()
{}

void JoyStickAxis::enable()
{
	mIsEnabled = true;
}

void JoyStickAxis::disable()
{
	mIsEnabled = false;
}

bool JoyStickAxis::isEnabled()
{
	return mIsEnabled;
}

void JoyStickAxis::setNumberOfGears(int g)
{
	mNumberOfGears = g;
}

int JoyStickAxis::getNumberOfGears()
{
	return 	mNumberOfGears;
}

void JoyStickAxis::setMaxVelocity(double vel)
{
	mMaxVelocity = vel;
}

double JoyStickAxis::getMaxVelocity()
{
	return 	mMaxVelocity;
}

void JoyStickAxis::assignMotor(APTMotor* motor)
{
	mMotor = motor;
}

double JoyStickAxis::getCurrentVelocity()
{
	return mLastSetVelocity;
}

void JoyStickAxis::Move(double newPosition)
{
	if(!mMotor)
    {
        Log(lInfo) << "Motor object is null..";
    	return;
    }
    if(!isEnabled())
    {
    	return;
    }

	double fullVelRange = getMaxVelocity();
    int nrOfSteps 		= getNumberOfGears();
	double stepSize = fullVelRange  / nrOfSteps;

	double scalingFactor = (fullVelRange * 2.0)/ mMaxPosition;
	double newVelocity  = (newPosition - mMaxPosition/2.0) * scalingFactor;

    mRunningAverage = newVelocity; //(mAlpha * mCurrentPosition) + (1.0 - mAlpha) * mRunningAverage;

    if( fabs(mRunningAverage) < stepSize)
    {
    	MotorCommandEnum c = mMotor->getLastCommand();
    	if(mMotor->isActive() &&  c != mcStopHard)
        {
        	mMotor->stop();
        }
        return;
    }

	//Check if joystick value have changed more than the step
    else
    {
    	//TODO::Write a function for this
//		if(mRunningAverage - mLastSetVelocity) < stepSize)
//        {
//        	//Do nothing
//	        return;
//        }

	    Log(lDebug) << "Axis numbers: ("<<newPosition<<","<<newVelocity<<","<<stepSize<<")";
//        //Did we switch direction?
//        if(!sameSign(vel,mLastVelocity))
//        {
//            mMotor->switchDirection();
//        }

        Log(lInfo) << "Setting jog velocity: "<<fabs(mRunningAverage);
		mMotor->setJogVelocity(fabs(mRunningAverage));
   		mLastSetVelocity = mRunningAverage;
        if (mRunningAverage > stepSize)
        {
			mMotor->jogForward();
        }
        else
        {
			mMotor->jogReverse();
        }
    }
}

