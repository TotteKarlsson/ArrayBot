#pragma hdrstop
#include "abTCubeDCServo.h"
#include "Thorlabs.MotionControl.TCube.DCServo.h"
#include "mtkLogger.h"
#include "abExceptions.h"
#include <bitset>
using namespace std;

//---------------------------------------------------------------------------
TCubeDCServo::TCubeDCServo(int serial)
: APTMotor(serial)
{
	mDeviceTypeID = (didTCubeDCServo);
}

TCubeDCServo::~TCubeDCServo()
{
    if(isConnected())
    {
		disconnect();
    }
}

bool TCubeDCServo::connect()
{
    // load the device settings
    // open the device
    int res = CC_Open(toString(mSerial).c_str());

	//we need to find out what actuator is connected
    //USE THESE for ArrayBot
//    mScalingFactors.position = 1919.64;
//    mScalingFactors.velocity = 42941.66;
//	mScalingFactors.acceleration = 14.66;

    mScalingFactors.position = 34304.0;
    mScalingFactors.velocity = 767367.49;
	mScalingFactors.acceleration = 261.93;

    if(res == 0)
    {
    	CC_LoadSettings(mSerial.c_str());

        int en = CC_EnableChannel(mSerial.c_str());
        Log(lDebug) << "Enabling Code: "<<en;
        //Set jog mode to continous
        setJogMoveMode(jmContinuous);

	    // start the device polling at 200ms intervals
    	if(!CC_StartPolling(mSerial.c_str(), 200))
        {
        	Log(lError) <<"Failure in Start Polling function";
        }
        return true;
    }
    else
    {
    	Log(lError) << "Failed connecting to device: "<<mSerial;
    }
    return false;
}

bool TCubeDCServo::disconnect()
{
    //Shut down message processor
    APTMotor::disconnect();
	CC_Close(mSerial.c_str());
    mIsConnected = false;
    return true;
}

bool TCubeDCServo::enable()
{
	int err = CC_EnableChannel(mSerial.c_str());
    if(err != 0)
    {
        Log(lError) <<tlError(err);
        return false;
    }
    return true;
}

bool TCubeDCServo::disable()
{
	int err = CC_DisableChannel(mSerial.c_str());
    if(err != 0)
    {
        Log(lError) <<tlError(err);
        return false;
    }
    return true;
}

void TCubeDCServo::setPotentiometerVelocity(double v)
{
    //Divide the velocity by four and populate the ranges
    //TODO: Clean this up later.. not sure how the SetPot function
    //really are intended to work..?
//	WORD 	thDef;
//
//    mPotentiometerVelocity = v;
//    double velStep = v;// / 4.;
//	double velocity = velStep;
//
//    int fullRange = 128;
//    int nrOfRanges = 4;
//    int range = 32; //128/4
//
//    int currRange = 1;
//
//    short err = CC_SetPotentiometerParams(mSerial.c_str(), 0, 0, velocity * mScalingFactors.velocity);
//    velocity += (velStep);
//    err = CC_SetPotentiometerParams(mSerial.c_str(), 1, 32, velocity * mScalingFactors.velocity);
//    velocity += velStep;
//    err = CC_SetPotentiometerParams(mSerial.c_str(), 2, 64, velocity * mScalingFactors.velocity);
//    velocity += velStep;
//    err = CC_SetPotentiometerParams(mSerial.c_str(), 3, 120, velocity * mScalingFactors.velocity);
//
//	DWORD	vel;
//    for(int i = 0; i < 127; i++)
//    {
//    	short err = ISC_GetPotentiometerParams(mSerial.c_str(), i, &thDef, &vel);
//        Log(lInfo) <<"Pos: "<<i<<"\t"<<"Def: "<<thDef<<"\tValue: "<<vel / mScalingFactors.velocity;
//    }
}

unsigned long TCubeDCServo::getStatusBits()
{
	return CC_GetStatusBits(mSerial.c_str());
}

double TCubeDCServo::getEncoderCounts()
{
	long cnt1, cnt2, cnt3;
    return 0;
}

HardwareInformation TCubeDCServo::getHWInfo()
{
	TLI_HardwareInformation hwi;
	int err  = CC_GetHardwareInfoBlock(mSerial.c_str(), &hwi);
    mHWInfo.serialNumber = hwi.serialNumber;
    mHWInfo.modelNumber = hwi.modelNumber;
    mHWInfo.type = hwi.type;
    return mHWInfo;
}

bool TCubeDCServo::isHomed()
{
	//Query for status bits
    unsigned long b = CC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(10);
}

bool TCubeDCServo::isHoming()
{
	//Query for status bits
    unsigned long b = CC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(9);
}

bool TCubeDCServo::isForwarding()
{
	//Query for status bits
    unsigned long b = CC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(5);
}

bool TCubeDCServo::isReversing()
{
	//Query for status bits
    unsigned long b = CC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(4);
}

bool TCubeDCServo::isActive()
{
	//Query for status bits
    unsigned long b = CC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(4) || bits.test(5) || bits.test(6) || bits.test(7) ;
}

bool TCubeDCServo::isEnabled()
{
	//Query for status bits
    unsigned long b = CC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(31);
}

bool TCubeDCServo::identify()
{
	CC_Identify(mSerial.c_str());
    return true;
}

bool TCubeDCServo::startPolling()
{
    return false;
}

bool TCubeDCServo::stopPolling()
{
    return false;
}

void TCubeDCServo::home()
{
  	if(!CC_CanHome(mSerial.c_str()))
    {
    	Log(lError) << "This device cannot be homed";
    }

    int res = CC_Home(mSerial.c_str());

    if(res)
    {
    	//throw
    }
}

void TCubeDCServo::stop(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcStopHard);
		post(cmd);
    }
    else
    {
		int err = CC_StopImmediate(mSerial.c_str());
        if(err != 0)
        {
            Log(lError) <<tlError(err);
        }
    }
}

void TCubeDCServo::stopProfiled(bool inThread)
{
    int err = CC_StopProfiled(mSerial.c_str());
    if(err != 0)
    {
        Log(lError) <<tlError(err);
    }
}

double TCubeDCServo::getPosition()
{
    return CC_GetPosition(mSerial.c_str()) / mScalingFactors.position;
}

double TCubeDCServo::getVelocity()
{
	int a(0), v(0);

	int err = CC_GetVelParams(mSerial.c_str(), &a, &v);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }
  	return v / mScalingFactors.velocity;
}

double TCubeDCServo::getAcceleration()
{
	int a(0), v(0);

	int err = CC_GetVelParams(mSerial.c_str(), &a, &v);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }
  	return (double) a / mScalingFactors.acceleration;
}

bool TCubeDCServo::setVelocity(double v)
{
 	MOT_VelocityParameters p;
    CC_GetVelParamsBlock(mSerial.c_str(), &p);

    p.maxVelocity = v * mScalingFactors.velocity;
    Log(lDebug) << getName() << ": velocity -> "<<v;

    int e = CC_SetVelParamsBlock(mSerial.c_str(), &p);

    if(e)
    {
        Log(lError) <<tlError(e);
    }

	return true;
}

bool TCubeDCServo::setAcceleration(double a)
{
 	MOT_VelocityParameters parameters;
    CC_GetVelParamsBlock(mSerial.c_str(), &parameters);

    parameters.acceleration = a * mScalingFactors.acceleration;
	Log(lDebug) << getName()<< ": acceleration -> "<<a;
    CC_SetVelParamsBlock(mSerial.c_str(), &parameters);

	return false;
}

bool TCubeDCServo::setJogMoveMode(JogMoveMode jm)
{
	StopMode sm = getJogStopMode();
	int err = CC_SetJogMode(mSerial.c_str(), (MOT_JogModes) jm, (MOT_StopModes) sm);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
        return false;
    }
  	return true;
}

bool TCubeDCServo::setJogStopMode(StopMode sm)
{
	JogMoveMode jm = getJogMoveMode();
	int err = CC_SetJogMode(mSerial.c_str(), (MOT_JogModes) jm, (MOT_StopModes) sm);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
        return false;
    }
  	return true;
}

JogMoveMode	TCubeDCServo::getJogMoveMode()
{
    MOT_JogModes jm;
	MOT_StopModes sm;
	int err = CC_GetJogMode(mSerial.c_str(), &jm, &sm);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
        return (JogMoveMode) MOT_JogModeUndefined;
    }
  	return (JogMoveMode) jm;
}

StopMode TCubeDCServo::getJogStopMode()
{
	MOT_StopModes sm;
    MOT_JogModes jm;
	int err = CC_GetJogMode(mSerial.c_str(), &jm, &sm);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
        return (StopMode) MOT_StopModeUndefined;
    }
  	return (StopMode) sm;
}

double TCubeDCServo::getJogVelocity()
{
    int a, v;
    int err = CC_GetJogVelParams(mSerial.c_str(), &a, &v);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }

    return v /  mScalingFactors.velocity;
}

bool TCubeDCServo::setJogVelocity(double newVel)
{
    int a, v;
    CC_GetJogVelParams(mSerial.c_str(), &a, &v);

	Log(lDebug) << "Setting Jog Velocity: "<<newVel;
    int err = CC_SetJogVelParams(mSerial.c_str(), a, newVel * mScalingFactors.velocity);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }
	return true;
}

bool TCubeDCServo::setJogAcceleration(double newAcc)
{
    int a, v;
    CC_GetJogVelParams(mSerial.c_str(), &a, &v);
    int err = CC_SetJogVelParams(mSerial.c_str(), newAcc * mScalingFactors.acceleration, v);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }

	return true;
}

double TCubeDCServo::getJogAcceleration()
{
    int a, v;
    int err = CC_GetJogVelParams(mSerial.c_str(), &a, &v);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }

    return a  / mScalingFactors.acceleration;
}

void TCubeDCServo::jogForward(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcJogForward);
		post(cmd);
    }
    else
    {
        int err = CC_MoveJog(mSerial.c_str(), MOT_Forwards);
        if(err != 0)
        {
            Log(lError) <<tlError(err);
        }
    }
}

void TCubeDCServo::jogReverse(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcJogReverse);
		post(cmd);
    }
    else
    {
        //Todo: tell thorlabs about the MOT_Reverse flag name
        int err = CC_MoveJog(mSerial.c_str(), MOT_Backwards);
        if(err != 0)
        {
            Log(lError) <<tlError(err);
        }
    }
}

void TCubeDCServo::forward(bool inThread)
{
	//TODO: use inThread logic
    int err = CC_MoveAtVelocity(mSerial.c_str(), MOT_Forwards);
    if(err != 0)
    {
        Log(lError) <<tlError(err);
    }
}

void TCubeDCServo::reverse(bool inThread)
{
	//TODO: use inThread logic
    int err = CC_MoveAtVelocity(mSerial.c_str(), MOT_Backwards);
    if(err !=0)
    {
        Log(lError) <<tlError(err);
    }
}

bool TCubeDCServo::moveAbsolute(double pos, bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcMoveToPosition, pos);
		post(cmd);
        mMotorCommandsPending++;
    }
    else
    {
        int err = CC_MoveToPosition(mSerial.c_str(), pos * mScalingFactors.position );
		mMotorCommandsPending--;
        if(err != 0)
        {
            Log(lError) <<tlError(err);
            Log(lError) <<"Tried to move to position: "<<pos<<" using the "<<getName()<<" device.";
            return false;
        }
    }
    return true;
}



