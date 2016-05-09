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
    mMaxVelocity(0),
	mAcceleration(0),
    mIsEnabled(false),
    mZeroInMiddle(true),
	mRunningAverage(0),
	mAlpha(0.9),
    mSenseOfDirection(1)
{
}

JoyStickAxis::~JoyStickAxis()
{}

void JoyStickAxis::setSenseOfDirection(int sign)
{
	mSenseOfDirection = sign;
}

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

void JoyStickAxis::setAcceleration(double a)
{
	mAcceleration = a;
}

double JoyStickAxis::getAcceleration()
{
	return 	mAcceleration;
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
	if(!mMotor || !isEnabled())
    {
        //Log(lDebug) << "Motor object is null..";
    	return;
    }

	double fullVelRange = getMaxVelocity();
    int nrOfSteps 		= getNumberOfGears();
	double stepSize 	= fullVelRange  / nrOfSteps;

	double scalingFactor = (fullVelRange * 2.0)/ mMaxPosition;
	double newVelocity  = (newPosition - mMaxPosition/2.0) * scalingFactor;

    mRunningAverage = newVelocity * mSenseOfDirection; //(mAlpha * mCurrentPosition) + (1.0 - mAlpha) * mRunningAverage;

    if( fabs(mRunningAverage) <= stepSize)
    {
    	MotorCommandEnum c = mMotor->getLastCommand();
    	if(mMotor->isActive() &&  c != mcStopHard)
        {
        	mMotor->stop();
        }
        return;
    }
    else 	//Check if joystick value have changed more than the step
    {
    	//TODO::Write a function for this
//		if(mRunningAverage - mLastSetVelocity) < stepSize)
//        {
//        	//Do nothing
//	        return;
//        }

	    Log(lDebug) << "Axis numbers: ("<<newPosition<<","<<newVelocity<<","<<stepSize<<")";
        Log(lInfo) << "Setting jog velocity: "<<fabs(mRunningAverage);
		mMotor->setJogVelocity(fabs(mRunningAverage));
   		mLastSetVelocity = mRunningAverage;

        //Forward or reverse?
        if ((mRunningAverage > stepSize))
        {
			mMotor->jogForward();
        }
        else
        {
			mMotor->jogReverse();
        }
    }
}

