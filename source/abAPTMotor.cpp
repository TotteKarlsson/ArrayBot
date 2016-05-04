#pragma hdrstop
#include "abAPTMotor.h"
#include "mtkLogger.h"

//---------------------------------------------------------------------------
APTMotor::APTMotor(int serialNo)
:
	APTDevice(serialNo),
	mMotorMessageProcessor(mMotorMessageContainer)
{
	mMotorMessageProcessor.start(true);
}

APTMotor::~APTMotor()
{}

void APTMotor::post(const MotorCommand& cmd)
{
	Log(lDebug) << "Command: "<<cmd<<" was posted";
	mMotorMessageContainer.post(cmd);
}


