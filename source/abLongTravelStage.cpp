#pragma hdrstop
#include "abLongTravelStage.h"
#include "Thorlabs.MotionControl.IntegratedStepperMotors.h"
#include "mtkLogger.h"
#include "abExceptions.h"
#include <bitset>
using namespace std;

//---------------------------------------------------------------------------
LongTravelStage::LongTravelStage(int serial)
: APTMotor(serial)
{
	mDeviceTypeID = (didLongTravelStage);
}

LongTravelStage::~LongTravelStage()
{
    if(isConnected())
    {
		disconnect();
    }
}

bool LongTravelStage::connect()
{
    // load the device settings
    // open the device
    int res = ISC_Open(toString(mSerial).c_str());

    mScalingFactors.position 	 = 409600.0;
    mScalingFactors.velocity 	 = 21987328.0;
	mScalingFactors.acceleration = 4506.0;

    if(res == 0)
    {
    	ISC_LoadSettings(mSerial.c_str());

        //Set jog mode to continous
        setJogMoveMode(jmContinuous);
        //setJogVelocity(1.0);
        //setJogAcceleration(1.0);

	    // start the device polling at 200ms intervals
    	if(!ISC_StartPolling(mSerial.c_str(), 200))
        {
        	Log(lError) <<"Failure in StartPolling function";
        }
        return true;
    }
    else
    {
    	Log(lError) << "Failed connecting to device: "<<mSerial;
    }
    return false;
}

bool LongTravelStage::disconnect()
{
    //Shut down message processor
    APTMotor::disconnect();
	ISC_Close(mSerial.c_str());
    mIsConnected = false;
    return false;
}

unsigned long LongTravelStage::getStatusBits()
{
	return ISC_GetStatusBits(mSerial.c_str());
}

double LongTravelStage::getEncoderCounts()
{
	long cnt1, cnt2, cnt3;
    return 0;
}

bool LongTravelStage::switchDirection(bool inThread)
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

HardwareInformation LongTravelStage::getHWInfo()
{
	TLI_HardwareInformation hwi;
	int err  = ISC_GetHardwareInfoBlock(mSerial.c_str(), &hwi);
    mHWInfo.serialNumber = hwi.serialNumber;
    mHWInfo.modelNumber = hwi.modelNumber;
    mHWInfo.type = hwi.type;
    return mHWInfo;
}

bool LongTravelStage::isHomed()
{
	//Query for status bits
    unsigned long b = ISC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(10);
}

bool LongTravelStage::isHoming()
{
	//Query for status bits
    unsigned long b = ISC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(9);
}

bool LongTravelStage::isForwarding()
{
	//Query for status bits
    unsigned long b = ISC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(5);
}

bool LongTravelStage::isReversing()
{
	//Query for status bits
    unsigned long b = ISC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(4);
}

bool LongTravelStage::isActive()
{
	//Query for status bits
    unsigned long b = ISC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(4) || bits.test(5) || bits.test(6) || bits.test(7) ;
}

bool LongTravelStage::identify()
{
	ISC_Identify(mSerial.c_str());
    return true;
}

bool LongTravelStage::startPolling()
{
    return false;
}

bool LongTravelStage::stopPolling()
{
    return false;
}

void LongTravelStage::home()
{
  	if(!ISC_CanHome(mSerial.c_str()))
    {
    	Log(lError) << "This device cannot be homed";
    }

    int res = ISC_Home(mSerial.c_str());

    if(res)
    {
    	//throw
    }
}

void LongTravelStage::stop(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcStopHard);
		post(cmd);
    }
    else
    {
		int err = ISC_StopImmediate(mSerial.c_str());
        if(err != 0)
        {
            Log(lError) <<tlError(err);
        }
    }
}

void LongTravelStage::stopProfiled(bool inThread)
{
    int err = ISC_StopProfiled(mSerial.c_str());
    if(err != 0)
    {
        Log(lError) <<tlError(err);
    }
}

double LongTravelStage::getPosition()
{
    return ISC_GetPosition(mSerial.c_str()) / mScalingFactors.position;
}

double LongTravelStage::getVelocity()
{
	int a(0), v(0);

	int err = ISC_GetVelParams(mSerial.c_str(), &a, &v);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }
  	return v / mScalingFactors.velocity;
}

double LongTravelStage::getAcceleration()
{
	int a(0), v(0);

	int err = ISC_GetVelParams(mSerial.c_str(), &a, &v);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }
  	return (double) a / mScalingFactors.acceleration;
}

bool LongTravelStage::setVelocity(double vel)
{
 	MOT_VelocityParameters p;
    ISC_GetVelParamsBlock(mSerial.c_str(), &p);

    p.maxVelocity = vel * mScalingFactors.velocity;
    Log(lDebug) << "Setting velocity parameters: "<<p.acceleration<<" : "<<p.maxVelocity;

    int e = ISC_SetVelParamsBlock(mSerial.c_str(), &p);

    if(e)
    {
        Log(lError) <<tlError(e);
    }

	return true;
}

bool LongTravelStage::setVelocityForward(double vel)
{
	setVelocity(vel);
    forward();
    return true;
}

bool LongTravelStage::setVelocityReverse(double vel)
{
	setVelocity(vel);
    reverse();
    return true;
}

bool LongTravelStage::setAcceleration(double a)
{
 	MOT_VelocityParameters parameters;
    ISC_GetVelParamsBlock(mSerial.c_str(), &parameters);

    parameters.acceleration = a * mScalingFactors.acceleration;
    ISC_SetVelParamsBlock(mSerial.c_str(), &parameters);
	Log(lDebug) << "Setting velocity parameters: "<<parameters.acceleration<<" : "<<parameters.maxVelocity;
	return false;
}

bool LongTravelStage::setJogMoveMode(JogMoveMode jm)
{
	StopMode sm = getJogStopMode();
	int err = ISC_SetJogMode(mSerial.c_str(), jm, sm);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
        return false;
    }
  	return true;
}

bool LongTravelStage::setJogStopMode(StopMode sm)
{
	JogMoveMode jmm = getJogMoveMode();
	int err = ISC_SetJogMode(mSerial.c_str(), jmm, sm);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
        return false;
    }
  	return true;
}

JogMoveMode	LongTravelStage::getJogMoveMode()
{
    MOT_JogModes jm;
	MOT_StopModes sm;
	int err = ISC_GetJogMode(mSerial.c_str(), &jm, &sm);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
        return MOT_JogModeUndefined;
    }
  	return (JogMoveMode) jm;
}

StopMode LongTravelStage::getJogStopMode()
{
	MOT_StopModes sm;
    MOT_JogModes jm;
	int err = ISC_GetJogMode(mSerial.c_str(), &jm, &sm);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
        return MOT_StopModeUndefined;
    }
  	return (StopMode) sm;
}


double LongTravelStage::getJogVelocity()
{
    int a, v;
    int err = ISC_GetJogVelParams(mSerial.c_str(), &a, &v);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }

    return v /  mScalingFactors.velocity;
}

bool LongTravelStage::setJogVelocity(double newVel)
{
    int a, v;
    ISC_GetJogVelParams(mSerial.c_str(), &a, &v);

    int err = ISC_SetJogVelParams(mSerial.c_str(), a, newVel * mScalingFactors.velocity);
	Log(lDebug) << "Setting Jog Velocity parameters: "<<a<<" : "<<newVel * mScalingFactors.velocity;
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }
	return true;
}

bool LongTravelStage::setJogAcceleration(double newAcc)
{
    int a, v;
    ISC_GetJogVelParams(mSerial.c_str(), &a, &v);
    int err = ISC_SetJogVelParams(mSerial.c_str(), newAcc * mScalingFactors.acceleration, v);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }

	return true;
}

double LongTravelStage::getJogAcceleration()
{
    int a, v;
    int err = ISC_GetJogVelParams(mSerial.c_str(), &a, &v);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }

    return a  / mScalingFactors.acceleration;
}

void LongTravelStage::jogForward(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcJogForward);
		post(cmd);
    }
    else
    {
        int err = ISC_MoveJog(mSerial.c_str(), MOT_Forwards);
        if(err != 0)
        {
            Log(lError) <<tlError(err);
        }
    }
}

void LongTravelStage::jogReverse(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcJogReverse);
		post(cmd);
    }
    else
    {
        //Todo: tell thorlabs about the MOT_Reverse flag name
        int err = ISC_MoveJog(mSerial.c_str(), MOT_Reverse);
        if(err != 0)
        {
            Log(lError) <<tlError(err);
        }
    }
}

void LongTravelStage::forward(bool inThread)
{
//	if(isReversing())
//    {
//    	Log(lInfo) << "Forwarding requested, motor is in reverse..";
//    }

//    //Don't send command if already doing what is needed
//    if(!isForwarding())
    {
        int err = ISC_MoveAtVelocity(mSerial.c_str(), MOT_Forwards);
        if(err != 0)
        {
            Log(lError) <<tlError(err);
        }
    }
//    else
//    {
//    	Log(lWarning) <<"Motor is already forwarding..";
//    }
}

void LongTravelStage::reverse(bool inThread)
{
//	if(isForwarding())
//    {
//    	Log(lInfo) << "Reversing requested, but motor is forwarding..";
////		return;
//    }

    //Don't send command if already doing what is needed
 //   if(!isReversing())
    {
        int err = ISC_MoveAtVelocity(mSerial.c_str(), MOT_Reverse);
        if(err !=0)
        {
            Log(lError) <<tlError(err);
        }
    }
}

void LongTravelStage::moveToPosition(double pos, bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcMoveToPosition, pos);
		post(cmd);
    }
    else
    {
    	setVelocity(getJogVelocity());
    	setAcceleration(getJogAcceleration());
        int err = ISC_MoveToPosition(mSerial.c_str(), pos * mScalingFactors.position );
        if(err != 0)
        {
            Log(lError) <<tlError(err);
        }
    }
}



