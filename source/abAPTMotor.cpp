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
	mMotorMessageProcessor(mMotorMessageContainer)
{
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
