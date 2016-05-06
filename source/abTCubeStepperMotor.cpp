#pragma hdrstop
#include "abTCubeStepperMotor.h"
#include "Thorlabs.MotionControl.TCube.StepperMotor.h"
#include "mtkLogger.h"
#include "abExceptions.h"
#include "abMotorCommand.h"
#include <bitset>
using namespace std;

//---------------------------------------------------------------------------
TCubeStepperMotor::TCubeStepperMotor(int serial)
: APTMotor(serial)
{
	mDeviceTypeID = (didTCubeStepperMotor);
}

TCubeStepperMotor::~TCubeStepperMotor()
{}

bool TCubeStepperMotor::connect()
{
    // load the device settings
    // open the device
    int res = SCC_Open(toString(mSerial).c_str());

    mScalingFactors.position 	 = 2184534;
    mScalingFactors.velocity 	 = 1.1727e8;
	mScalingFactors.acceleration = 2.403e4;

    if(res == 0)
    {
    	SCC_LoadSettings(mSerial.c_str());
	    // start the device polling at 200ms intervals
    	if(!SCC_StartPolling(mSerial.c_str(), 200))
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

bool TCubeStepperMotor::disconnect()
{
    mIsConnected = false;
    return false;
}

unsigned long TCubeStepperMotor::getStatusBits()
{
	return SCC_GetStatusBits(mSerial.c_str());
}

double TCubeStepperMotor::getEncoderCounts()
{
	long stepsPerRev, gearBoxRatio;
    float pitch;
	int err = SCC_GetMotorParams(mSerial.c_str(), &stepsPerRev, &gearBoxRatio, &pitch);
	if(err)
    {
    	//Fill out scaling factors
        mScalingFactors.position = 34304;
        mScalingFactors.velocity = 767367.49;
		mScalingFactors.acceleration = 261.93;
    }
    else
    {
    	Log(lInfo) << "StepsPerRev: "<<stepsPerRev;
    	Log(lInfo) << "GearBoxRatio: "<<gearBoxRatio;
    	Log(lInfo) << "Pitch: "<<pitch;
    }
    return 0;
}

bool TCubeStepperMotor::switchDirection(bool inThread)
{
	if(isForwarding())
    {
    	reverse(inThread);
    }
    else
    {
    	forward(inThread);
    }
    return true;
}

HardwareInformation TCubeStepperMotor::getHWInfo()
{
	TLI_HardwareInformation hwi;
	int err  = SCC_GetHardwareInfoBlock(mSerial.c_str(), &hwi);
    mHWInfo.serialNumber = hwi.serialNumber;
    mHWInfo.modelNumber = hwi.modelNumber;
    mHWInfo.type = hwi.type;
    return mHWInfo;
}

bool TCubeStepperMotor::isHomed()
{
	//Query for status bits
    unsigned long b = SCC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(10);
}

bool TCubeStepperMotor::isHoming()
{
	//Query for status bits
    unsigned long b = SCC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(9);
}

bool TCubeStepperMotor::isForwarding()
{
	//Query for status bits
    unsigned long b = SCC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(5);
}

bool TCubeStepperMotor::isReversing()
{
	//Query for status bits
    unsigned long b = SCC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(4);
}

bool TCubeStepperMotor::isActive()
{
	//Query for status bits
    unsigned long b = SCC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(4) || bits.test(5) || bits.test(6) || bits.test(7) ;
}

bool TCubeStepperMotor::identify()
{
	SCC_Identify(mSerial.c_str());
    return true;
}

bool TCubeStepperMotor::startPolling()
{
    return false;
}

bool TCubeStepperMotor::stopPolling()
{
    return false;
}

void TCubeStepperMotor::home()
{
  	if(!SCC_CanHome(mSerial.c_str()))
    {
    	Log(lError) << "This device cannot be homed";
    }

    int res = SCC_Home(mSerial.c_str());

    if(res)
    {
    	//throw
    }
}

void TCubeStepperMotor::stop(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcStopHard);
		post(cmd);
    }
    else
    {
		int err = SCC_StopImmediate(mSerial.c_str());
        if(err != 0)
        {
            Log(lError) <<tlError(err);
        }
    }
}

void TCubeStepperMotor::stopProfiled(bool inThread)
{
//	if(isActive())
    {
		int err = SCC_StopProfiled(mSerial.c_str());
        if(err != 0)
        {
            Log(lError) <<tlError(err);
        }

//        while(isActive())
//        {
//            //Log(lInfo) << "Waiting ...";
//        }
    }
}

double TCubeStepperMotor::getPosition()
{
    int pos = SCC_GetPosition(mSerial.c_str());
//    Log(lDebug4) <<"Pos = "<<pos;
	return pos / mScalingFactors.position;
}

double TCubeStepperMotor::getVelocity()
{
	int a(0);
  	int v (0);

	int err = SCC_GetVelParams(mSerial.c_str(), &a, &v);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }
  	return (double) v / mScalingFactors.velocity;
}

double TCubeStepperMotor::getAcceleration()
{
	int a(0);
  	int v (0);

	int err = SCC_GetVelParams(mSerial.c_str(), &a, &v);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }
  	return (double) a / mScalingFactors.acceleration;
}

bool TCubeStepperMotor::setMaxVelocity(double vel)
{
 	MOT_VelocityParameters p;
    SCC_GetVelParamsBlock(mSerial.c_str(), &p);

    p.maxVelocity = vel * mScalingFactors.velocity;
    Log(lDebug) << "Setting velocity parameters: "<<p.acceleration<<" : "<<p.maxVelocity;
    	int e = SCC_SetVelParamsBlock(mSerial.c_str(), &p);

    if(e)
    {
        Log(lError) <<tlError(e);
    }

//        if(isForwarding())
//        {
//            forward();
//        }
//        else if (isReversing())
//        {
//            reverse();
//        }


	return true;
}

bool TCubeStepperMotor::setMaxVelocityForward(double vel)
{
	setMaxVelocity(vel);
    forward();
    return true;
}

bool TCubeStepperMotor::setMaxVelocityReverse(double vel)
{
	setMaxVelocity(vel);
    reverse();
    return true;
}

bool TCubeStepperMotor::setAcceleration(double a)
{
 	MOT_VelocityParameters parameters;
    SCC_GetVelParamsBlock(mSerial.c_str(), &parameters);

    parameters.acceleration = a * mScalingFactors.acceleration;
    SCC_SetVelParamsBlock(mSerial.c_str(), &parameters);
	Log(lDebug) << "Setting velocity parameters: "<<parameters.acceleration<<" : "<<parameters.maxVelocity;
	return false;
}

bool TCubeStepperMotor::setJogMoveMode(JogMoveMode jm)
{
	StopMode sm = getJogStopMode();
	int err = SCC_SetJogMode(mSerial.c_str(), jm, sm);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
        return false;
    }
  	return true;
}

bool TCubeStepperMotor::setJogStopMode(StopMode sm)
{
	JogMoveMode jmm = getJogMoveMode();
	int err = SCC_SetJogMode(mSerial.c_str(), jmm, sm);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
        return false;
    }
  	return true;
}

JogMoveMode	TCubeStepperMotor::getJogMoveMode()
{
    MOT_JogModes jm;
	MOT_StopModes sm;
	int err = SCC_GetJogMode(mSerial.c_str(), &jm, &sm);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
        return MOT_JogModeUndefined;
    }
  	return (JogMoveMode) jm;
}

StopMode TCubeStepperMotor::getJogStopMode()
{
	MOT_StopModes sm;
    MOT_JogModes jm;
	int err = SCC_GetJogMode(mSerial.c_str(), &jm, &sm);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
        return MOT_StopModeUndefined;
    }
  	return (StopMode) sm;
}


double TCubeStepperMotor::getJogVelocity()
{
    int a, v;
    int err = SCC_GetJogVelParams(mSerial.c_str(), &a, &v);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }

    return v / mScalingFactors.velocity;
}

bool TCubeStepperMotor::setJogVelocity(double newVel)
{
    int a, v;
    SCC_GetJogVelParams(mSerial.c_str(), &a, &v);
    int err = SCC_SetJogVelParams(mSerial.c_str(), a, newVel * mScalingFactors.velocity);
	Log(lDebug) << "Setting Jog Velocity parameters: "<<a<<" : "<<newVel * mScalingFactors.velocity;
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }
	return true;
}

bool TCubeStepperMotor::setJogAcceleration(double newAcc)
{
    int a, v;
    SCC_GetJogVelParams(mSerial.c_str(), &a, &v);
    int err = SCC_SetJogVelParams(mSerial.c_str(), newAcc * mScalingFactors.acceleration, v);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }

	return true;
}

double TCubeStepperMotor::getJogAcceleration()
{
    int a, v;
    int err = SCC_GetJogVelParams(mSerial.c_str(), &a, &v);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }

    return a  / mScalingFactors.acceleration;
}

void TCubeStepperMotor::jogForward(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcJogForward);
		post(cmd);
    }
    else
    {
        int err = SCC_MoveJog(mSerial.c_str(), MOT_Forwards);
        if(err != 0)
        {
            Log(lError) <<tlError(err);
        }
    }
}

void TCubeStepperMotor::jogReverse(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcJogReverse);
		post(cmd);
    }
    else
    {

        int err = SCC_MoveJog(mSerial.c_str(), MOT_Backwards);
        if(err != 0)
        {
            Log(lError) <<tlError(err);
        }
    }
}

void TCubeStepperMotor::forward(bool inThread)
{
//	if(isReversing())
//    {
//    	Log(lInfo) << "Forwarding requested, motor is in reverse..";
//    }

//    //Don't send command if already doing what is needed
//    if(!isForwarding())
    {
        int err = SCC_MoveAtVelocity(mSerial.c_str(), MOT_Forwards);
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

void TCubeStepperMotor::reverse(bool inThread)
{
//	if(isForwarding())
//    {
//    	Log(lInfo) << "Reversing requested, but motor is forwarding..";
////		return;
//    }

    //Don't send command if already doing what is needed
 //   if(!isReversing())
    {
        int err = SCC_MoveAtVelocity(mSerial.c_str(), MOT_Backwards);
        if(err !=0)
        {
            Log(lError) <<tlError(err);
        }
    }
}

void TCubeStepperMotor::moveDistance(double distance, bool inThread)
{
// 	Log(lError) <<msg.str();
}



