#pragma hdrstop
#include "atMotorWiggler.h"
#include "apt/atAPTMotor.h"
//---------------------------------------------------------------------------

MotorWiggler::MotorWiggler(APTMotor* xmtr, APTMotor* ymtr)
:
mMaxVelocity(0),
mMaxAcceleration(0),
mAmplitude(0),
mXMotor(xmtr),
mYMotor(ymtr),
mPullRelaxVelocity(0),
mPullRelaxAcceleration(0),
mTimer(Poco::Timespan(100*Poco::Timespan::MILLISECONDS))
{
	mTimer.assignTimerFunction(onTimer);
}

MotorWiggler::~MotorWiggler(){}

void MotorWiggler::assignMotors(APTMotor* xmtr, APTMotor* ymtr)
{
	mXMotor = xmtr;
	mYMotor = ymtr;
}

bool MotorWiggler::startWiggle()
{
	if(mXMotor && mXMotor->isActive())
    {
		Log(lError) << "Can't start wiggle: motor is active";
    	return false;
    }

    mXMotor->setVelocityParameters(mMaxVelocity, mMaxAcceleration);

	mCurrentPosition = mXMotor->getPosition();
    mCenterPosition = mCurrentPosition;
    mNextPosition = mCenterPosition + mAmplitude/2.;
    mXMotor->moveToPosition(mNextPosition);
    mTimer.start();
    return true;
}

bool MotorWiggler::stopWiggle()
{
	mTimer.stop();
    return true;
}

void MotorWiggler::onTimer()
{
	if(mTimer.isTimeToDie())
    {
    	return;
    }

	mCurrentPosition = mXMotor->getPosition();
	if(fabs(mCurrentPosition - mNextPosition) < 0.1)
    {
		//Switch
        mNextPosition = (mCurrentPosition > mCenterPosition) ?
         (mCenterPosition - mAmplitude) : (mCenterPosition + mAmplitude);

	    mXMotor->moveToPosition(mNextPosition);
    }
}

bool MotorWiggler::pull(double distance)
{
	if(mYMotor)
    {
    	mYMotor->setVelocityParameters(mPullRelaxVelocity, mPullRelaxAcceleration);
		mYMotor->moveRelative(distance);
		return true;
    }
    return false;
}

bool MotorWiggler::relax(double distance)
{
	if(mYMotor)
    {
    	mYMotor->setVelocityParameters(mPullRelaxVelocity, mPullRelaxAcceleration);
		mYMotor->moveRelative(distance*(-1));
		return true;
    }

    return false;
}

