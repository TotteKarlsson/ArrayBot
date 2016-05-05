#pragma hdrstop
#include "abJoystickAxis.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
#include "mtkUtils.h"

using namespace mtk;

JoyStickAxis::JoyStickAxis()
:
	mMaxPosition(65535),
    mNumberOfGears(3),
    mMaxVelocity(1),
    mIsEnabled(false),
    mZeroInMiddle(true),
	mRunningZAverage(0),
	mAlpha(0.9)
{
}

JoyStickAxis::~JoyStickAxis()
{}

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

void JoyStickAxis::Move(double newPosition)
{
	if(!mMotor)
    {
        Log(lInfo) << "Motor object is null..";
    	return;
    }

	double fullVelRange = getMaxVelocity();
    int nrOfSteps = getNumberOfGears();
	double step = fullVelRange / nrOfSteps;

	double scalingFactor = fullVelRange/ mMaxPosition;
	double pos = (newPosition * scalingFactor - fullVelRange/2.0) * 2.0;

    mRunningZAverage = (mAlpha * pos) + (1.0 - mAlpha) * mRunningZAverage;

	//Check if joystick value have changed more than previous command
	double vel = mRunningZAverage;
    if(fabs(vel - mValCommand) > step)
    {
        //Did we switch direction?
        if(!sameSign(vel,mValCommand))
        {
            mMotor->switchDirection();
        }

        mValCommand = vel;
        if( fabs(mValCommand) <= step)
        {
	        mMotor->stop();
            Log(lInfo) << "Motor is stopping. ";
            return;
        }

        Log(lInfo) << "Setting jog velocity: "<<fabs(vel);
		mMotor->setJogVelocity(fabs(vel));
        if (vel > step)
        {
			mMotor->jogForward();
        }
        else
        {
			mMotor->jogReverse();
        }
    }

}

