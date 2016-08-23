#pragma hdrstop
#include "abAPTMotor.h"
#include "mtkLogger.h"
#include "abCore.h"

//---------------------------------------------------------------------------
APTMotor::APTMotor(int serialNo)
:
	APTDevice(serialNo),
    mPositionRange(Range<double>(0,0)),
    mPositionLimits(Range<double>(0,0)),
    mPositionLimitsEnabled(true),
    mWarningZone(10.0),
    mVelocityRange(0,0),
    mAccelerationRange(0,0),
	mManualJogVelocity(0),
	mManualJogAcceleration(0),
	mPotentiometerVelocity(0),
	mMotorMessageProcessor(mMotorMessageContainer),
    mMotorCommandsPending(0),
    mDesiredPosition(-1),
    mStatusTimer(150, onStatusTimer)
{
    mProperties.add((BaseProperty*) &mManualJogVelocity.setup(		"MANUAL_JOG_VELOCITY"		    , 			0.1,                true));
    mProperties.add((BaseProperty*) &mManualJogAcceleration.setup(	"MANUAL_JOG_ACCELERATION"	    , 			0.1,                true));
    mProperties.add((BaseProperty*) &mPotentiometerVelocity.setup(	"POTENTIOMETER_VELOCITY"	    , 			1, 					true));
    mProperties.add((BaseProperty*) &mPositionRange.setup(			"POSITION_RANGE"			    , 			Range<double>(0,0), true));
    mProperties.add((BaseProperty*) &mPositionLimits.setup(			"POSITION_LIMITS"			    , 			Range<double>(0,0), true));
    mProperties.add((BaseProperty*) &mPositionLimitsEnabled.setup(	"POSITION_LIMITS_ENABLED"       , 			false, 				true));
    mProperties.add((BaseProperty*) &mWarningZone.setup(			"POSITION_LIMIT_WARNING_ZONE"   , 			10.0, 				true));

	mMotorMessageProcessor.assignMotor(this);
	mMotorMessageProcessor.start(true);

    mStatusTimer.start();
}

APTMotor::~APTMotor()
{
	Log(lDebug) <<"Destructing motor with serial: "<<mSerial;
	mMotorMessageProcessor.stop();
    mStatusTimer.stop();

    while(mMotorMessageProcessor.isRunning() || mStatusTimer.isRunning())
    {
    	//This is not very nice...
		sleep(5);
    }

    mProperties.write();
	Log(lDebug) <<"Exiting destructor for motor with serial: "<<mSerial;
}

bool APTMotor::isInDangerZone()
{
    if(mPositionLimitsEnabled)
    {
        double pos = getPosition();
        if(pos >= mPositionLimits.getValue().getMax() * 0.9)
        {
        	return true;
        }
    }

    return false;
}

void APTMotor::onStatusTimer()
{
	if(!isActive() || isHoming())
    {
    	return;
    }

    //Check position
    if(mPositionLimitsEnabled)
    {
        double pos = getPosition();
        if(isInDangerZone() || pos >= mPositionLimits.getValue().getMax())
        {
            Log(lWarning) << "Motor \""<<getName()<<"\" has crossed the maximum position limit";

            MotorMessageData* msgData = new MotorMessageData;
			populateMotorMessageData(msgData);

            //Send windows message
            int ret = PostMessage(HWND_BROADCAST, getABCoreMessageID(MOTOR_WARNING_MESSAGE), reinterpret_cast<WPARAM> (msgData) , 0);
            if(!ret)
            {
            	Log(lError) << "Post message failed..";
            }
        }

        if(pos <= mPositionLimits.getValue().getMin())
        {
            Log(lWarning) << "Motor \""<<getName()<<"\" has crossed the minimum position limit";

        }
    }
}

void APTMotor::populateMotorMessageData(MotorMessageData* data)
{
	if(!data)
    {
    	return;
    }
    data->mSerial = mSerial;
    data->mName = getName();
    data->mCurrentPosition = getPosition();
    data->mPositionLimits = mPositionLimits;
    data->mPositionLimitsEnabled = mPositionLimitsEnabled;
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
	bool 	res1 = setJogVelocity(v);
	bool 	res2 = setJogAcceleration(a);
    return 	res1 && res2;
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
