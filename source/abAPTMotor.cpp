#pragma hdrstop
#include "abAPTMotor.h"
#include "mtkLogger.h"

//---------------------------------------------------------------------------
APTMotor::APTMotor(int serialNo)
:
	APTDevice(serialNo),
    mPositionRange(Range<double>(0,0)),
    mVelocityRange(0,0),
    mAccelerationRange(0,0),
	mManualJogVelocity(0),
	mManualJogAcceleration(0),
	mPotentiometerVelocity(0),
	mMotorMessageProcessor(mMotorMessageContainer),
    mMotorCommandsPending(0),
    mDesiredPosition(-1)
{
    mProperties.add((BaseProperty*) &mManualJogVelocity.setup(		"MANUAL_JOG_VELOCITY"		, 			0.1,                true));
    mProperties.add((BaseProperty*) &mManualJogAcceleration.setup(	"MANUAL_JOG_ACCELERATION"	, 			0.1,                true));
    mProperties.add((BaseProperty*) &mPotentiometerVelocity.setup(	"POTENTIOMETER_VELOCITY"	, 			1, 					true));
    mProperties.add((BaseProperty*) &mPositionRange.setup(			"POSITION_RANGE"			, 			Range<double>(0,0), true));

	mMotorMessageProcessor.assignMotor(this);
	mMotorMessageProcessor.start(true);
}

APTMotor::~APTMotor()
{
	mMotorMessageProcessor.stop();
    while(mMotorMessageProcessor.isRunning())
    {
		sleep(5);
    }
	Log(lDebug) <<"Destructing motor with serial: "<<mSerial;
    mProperties.write();
}

bool APTMotor::isMotorCommandPending()
{
	return (mMotorCommandsPending >= 1) ? true : false;
}

bool APTMotor::isAtDesiredPosition()
{
	return isEqual(mDesiredPosition, getPosition(), 1.e-3);
}

double APTMotor::getMaxPosition()
{
	return mPositionRange.getValue().getMax();
}

bool APTMotor::applyProperties()
{
	setJogVelocity(mManualJogVelocity);
	setJogAcceleration(mManualJogAcceleration);
    setPotentiometerVelocity(mPotentiometerVelocity);
    return true;
}

bool APTMotor::setJogMoveParameters(double v, double a)
{
	bool res1 = setJogVelocity(v);
	bool res2 = setJogAcceleration(a);
    return res1 && res2;
}

bool APTMotor::moveAbsolute(double position, double v, double a)
{
	setVelocityParameters(v, a);
    return moveToPosition(position, true);
}

bool APTMotor::switchDirection(bool inThread)
{
	//The forward/reverse bits don't work so this function is disabled until they do

//	if(isForwarding())
//    {
//    	reverse(inThread);
//    }
//    else
//    {
//    	forward(inThread);
//    }
	return false;
}

bool APTMotor::moveRelative(double position, bool inThread)
{
	double curr_pos = getPosition();
    return moveToPosition(curr_pos + position);
}

double APTMotor::getManualJogVelocity()
{
	return mManualJogVelocity;
}

double APTMotor::getManualJogAcceleration()
{
	return mManualJogAcceleration;
}

void APTMotor::setManualJogVelocity(double v)
{
	mManualJogVelocity = v;
}

void APTMotor::setManualJogAcceleration(double a)
{
	mManualJogAcceleration = a;
}

double APTMotor::getPotentiometerVelocity()
{
	return mPotentiometerVelocity;
}

bool APTMotor::setVelocityForward(double vel)
{
	setVelocityParameters(vel);
    forward();
    return true;
}

bool APTMotor::setVelocityReverse(double vel)
{
	setVelocityParameters(vel);
    reverse();
    return true;
}

bool APTMotor::disconnect()
{
	mMotorMessageProcessor.stop();
    return true;
}

void APTMotor::post(const MotorCommand& cmd)
{
	mMotorMessageContainer.post(cmd);
}

MotorCommandEnum APTMotor::getLastCommand()
{
	return mMotorMessageProcessor.getLastProcessedMessage();
}

bool APTMotor::setVelocityRange(DoubleRange vel)
{
	mVelocityRange = vel;
	return true;
}

DoubleRange APTMotor::getVelocityRange()
{
	return mVelocityRange;
}
