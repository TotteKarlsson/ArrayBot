#pragma hdrstop
#include "abAPTMotor.h"
#include "mtkLogger.h"

//---------------------------------------------------------------------------
APTMotor::APTMotor(int serialNo)
:
	APTDevice(serialNo),
    mPositionRange(0,0),
    mVelocityRange(0,0),
    mAccelerationRange(0,0),
	mManualJogVelocity(0),
	mManualJogAcceleration(0),
	mMotorMessageProcessor(mMotorMessageContainer)
{
    mProperties.add((BaseProperty*) &mManualJogVelocity.setup("MANUAL_JOG_VELOCITY", 			0.0, true));
    mProperties.add((BaseProperty*) &mManualJogAcceleration.setup("MANUAL_JOG_ACCELERATION", 			0.0, true));

	mMotorMessageProcessor.assignMotor(this);
	mMotorMessageProcessor.start(true);
}

APTMotor::~APTMotor()
{
	mMotorMessageProcessor.stop();
    while(mMotorMessageProcessor.isRunning())
    {
		Log(lDebug) << "...";
    }
	Log(lDebug) <<"Destructing Motor with serial: "<<mSerial;
    mProperties.write();
}

bool APTMotor::applyProperties()
{
	setJogVelocity(mManualJogVelocity);
	setJogAcceleration(mManualJogAcceleration);
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

bool APTMotor::disconnect()
{
	mMotorMessageProcessor.stop();
    return true;
}

void APTMotor::post(const MotorCommand& cmd)
{
	Log(lDebug) << "Command: "<<cmd<<" was posted";
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
