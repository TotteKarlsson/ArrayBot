#pragma hdrstop
#include "abAPTMotor.h"
#include "mtkLogger.h"

//---------------------------------------------------------------------------
APTMotor::APTMotor(int serialNo)
:
	APTDevice(serialNo),
    mVelocityRange(DoubleRange(0.0, 0.0)),
	mMotorMessageProcessor(mMotorMessageContainer)
{
	mMotorMessageProcessor.assignMotor(this);
	mMotorMessageProcessor.start(true);
}

APTMotor::~APTMotor()
{}

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
	return mVelocityRange.getValue();
}

//bool APTMotor::setMaxAcceleration(double a)
//{
//	mMaxAcceleration = a;
//	return true;
//}
//
//double APTMotor::getMaxAcceleration()
//{
//	return mMaxAcceleration;
//}
//
//bool APTMotor::setMaxJogVelocity(double vel)
//{
//	mMaxJogVelocity = vel;
//	return true;
//}
//
//double APTMotor::getMaxJogVelocity()
//{
//	return mMaxJogVelocity;
//}
//
//bool APTMotor::setMaxJogAcceleration(double a)
//{
//	mMaxJogAcceleration = a;
//	return true;
//}
//
//double APTMotor::getMaxJogAcceleration()
//{
//	return mMaxJogAcceleration;
//}
