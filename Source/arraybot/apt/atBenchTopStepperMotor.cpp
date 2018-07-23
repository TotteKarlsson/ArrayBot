#pragma hdrstop
#include <windows.h>
#include "thirdparty/thorlabs/Thorlabs.MotionControl.Benchtop.StepperMotor.h"
#include "atBenchTopStepperMotor.h"

#include "dslLogger.h"
#include "core/atExceptions.h"
#include <bitset>
using namespace std;
using namespace at;

short lChannel = 1;
//---------------------------------------------------------------------------
BenchTopStepperMotor::BenchTopStepperMotor(int serial)
: APTMotor(serial)
{
	mDeviceTypeID = (didBenchTopStepperMotor);
}

BenchTopStepperMotor::~BenchTopStepperMotor()
{
    if(isConnected())
    {
		disconnect();
    }
}

bool BenchTopStepperMotor::connect()
{
    // load the device settings
    // open the device
    int res = SBC_Open(dsl::toString(mSerial).c_str());

    mScalingFactors.position 	 = 409600.0;
    mScalingFactors.velocity 	 = 21987328.0;
	mScalingFactors.acceleration = 4506.0;

    if(res == 0)
    {
    	SBC_LoadSettings(mSerial.c_str(),lChannel);

        int en = SBC_EnableChannel(mSerial.c_str(),lChannel);
        Log(lDebug) << "Enabling Code: "<<en;

        //Set jog mode to continous
        setJogMoveMode(jmContinuous);

	    // start the device polling at 200ms intervals
    	if(!SBC_StartPolling(mSerial.c_str(),lChannel, 200))
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

bool BenchTopStepperMotor::disconnect()
{
    //Shut down message processor
    APTMotor::disconnect();
	SBC_Close(mSerial.c_str());
    mIsConnected = false;
    return true;
}

bool BenchTopStepperMotor::enable()
{
	int e = SBC_EnableChannel(mSerial.c_str(),lChannel);
    if(e)
    {
        Log(lError) <<tlError(e);
        return false;
    }
    return true;
}

bool BenchTopStepperMotor::disable()
{
	int e = SBC_DisableChannel(mSerial.c_str(),lChannel);
    if(e)
    {
        Log(lError) <<tlError(e);
        return false;
    }
    return true;
}
void BenchTopStepperMotor::setPotentiometerVelocity(double v)
{
//    //Divide the velocity by four and populate the ranges
//    //TODO: Clean this up later.. not sure how the SetPot function
//    //really are intended to work..?
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
//    short e = SBC_SetPotentiometerParams(mSerial.c_str(), 0, 0, velocity * mScalingFactors.velocity);
//    velocity += (velStep);
//    e = SBC_SetPotentiometerParams(mSerial.c_str(), 1, 32, velocity * mScalingFactors.velocity);
//    velocity += velStep;
//    e = SBC_SetPotentiometerParams(mSerial.c_str(), 2, 64, velocity * mScalingFactors.velocity);
//    velocity += velStep;
//    e = SBC_SetPotentiometerParams(mSerial.c_str(), 3, 120, velocity * mScalingFactors.velocity);

//	DWORD	vel;
//    for(int i = 0; i < 127; i++)
//    {
//    	short e = SBC_GetPotentiometerParams(mSerial.c_str(), i, &thDef, &vel);
//        Log(lInfo) <<"Pos: "<<i<<"\t"<<"Def: "<<thDef<<"\tValue: "<<vel / mScalingFactors.velocity;
//    }
}

unsigned long BenchTopStepperMotor::getStatusBits()
{
	return SBC_GetStatusBits(mSerial.c_str(),lChannel);
}

double BenchTopStepperMotor::getEncoderCounts()
{
	long cnt1, cnt2, cnt3;
    return 0;
}

HardwareInformation BenchTopStepperMotor::getHWInfo()
{
	TLI_HardwareInformation hwi;
	int e  = SBC_GetHardwareInfoBlock(mSerial.c_str(),lChannel, &hwi);
    mHWInfo.serialNumber = hwi.serialNumber;
    mHWInfo.modelNumber = hwi.modelNumber;
    mHWInfo.type = hwi.type;
    return mHWInfo;
}

bool BenchTopStepperMotor::isHomed()
{
	//Query for status bits
    unsigned long b = SBC_GetStatusBits(mSerial.c_str(),lChannel);
    bitset<32> bits(b);
    return bits.test(10);
}

bool BenchTopStepperMotor::isHoming()
{
	//Query for status bits
    unsigned long b = SBC_GetStatusBits(mSerial.c_str(),lChannel);
    bitset<32> bits(b);
    return bits.test(9);
}

bool BenchTopStepperMotor::isForwarding()
{
	//Query for status bits
    unsigned long b = SBC_GetStatusBits(mSerial.c_str(),lChannel);
    bitset<32> bits(b);
    return bits.test(5);
}

bool BenchTopStepperMotor::isReversing()
{
	//Query for status bits
    unsigned long b = SBC_GetStatusBits(mSerial.c_str(),lChannel);
    bitset<32> bits(b);
    return bits.test(4);
}

bool BenchTopStepperMotor::isActive()
{
	//Query for status bits
    unsigned long b = SBC_GetStatusBits(mSerial.c_str(),lChannel);
    bitset<32> bits(b);
    return bits.test(4) || bits.test(5) || bits.test(6) || bits.test(7) ;
}

bool BenchTopStepperMotor::isEnabled()
{
	//Query for status bits
    unsigned long b = SBC_GetStatusBits(mSerial.c_str(),lChannel);
    bitset<32> bits(b);
    return bits.test(31);
}

bool BenchTopStepperMotor::identify()
{
	SBC_Identify(mSerial.c_str());
    return true;
}

bool BenchTopStepperMotor::startPolling()
{
    return false;
}

bool BenchTopStepperMotor::stopPolling()
{
    return false;
}

void BenchTopStepperMotor::home(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcHome);
		post(cmd);
    }
    else
    {
        if(!SBC_CanHome(mSerial.c_str(),lChannel))
        {
            Log(lError) << "This device cannot be homed";
        }

        int e = SBC_Home(mSerial.c_str(),lChannel);

        if(e)
        {
            Log(lError) <<tlError(e);
        }
    }
}

void BenchTopStepperMotor::stop(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcStopHard);
		post(cmd);
    }
    else
    {
		int e = SBC_StopImmediate(mSerial.c_str(),lChannel);
        if(e)
        {
            Log(lError) <<tlError(e);
        }
		mMotorCommandsPending--;
    }
}

void BenchTopStepperMotor::stopProfiled(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcStopProfiled);
		post(cmd);
    }
    else
    {
        int e = SBC_StopProfiled(mSerial.c_str(),lChannel);
        if(e)
        {
            Log(lError) <<tlError(e);
        }
		mMotorCommandsPending--;
    }
}

double BenchTopStepperMotor::getPosition() const
{
    return SBC_GetPosition(mSerial.c_str(),lChannel) / mScalingFactors.position;
}

double BenchTopStepperMotor::getVelocity()
{
	int a(0), v(0);

	int e = SBC_GetVelParams(mSerial.c_str(),lChannel, &a, &v);

    if(e)
    {
    	Log(lError) <<tlError(e);
    }
  	return (double) v / mScalingFactors.velocity;
}

double BenchTopStepperMotor::getAcceleration()
{
	int a(0), v(0);

	int e = SBC_GetVelParams(mSerial.c_str(),lChannel, &a, &v);

    if(e)
    {
    	Log(lError) <<tlError(e);
    }
  	return (double) a / mScalingFactors.acceleration;
}

bool BenchTopStepperMotor::setVelocityParameters(double v, double a, bool inThread)
{
	if(inThread)
    {
    	//Check if motor is moving to absolute position
		MotorCommand cmd(mcSetVelocityParameters, v, a);
		post(cmd);
    }
    else
    {
     	MOT_VelocityParameters p;
        SBC_GetVelParamsBlock(mSerial.c_str(),lChannel, &p);

        if(v != 0)
        {
	        p.maxVelocity = v * mScalingFactors.velocity;
	        Log(lDebug3) << getName() << ": velocity -> "<<v;
        }

        if(a != 0.0)
        {
        	p.acceleration = a * mScalingFactors.acceleration;
	        Log(lDebug3) << getName() << ": acceleration -> "<<a;
        }

        int e = SBC_SetVelParamsBlock(mSerial.c_str(),lChannel, &p);
        mMotorCommandsPending--;

        if(e)
        {
            Log(lError) <<tlError(e);
           	return false;
        }
    }
   	return true;
}

bool BenchTopStepperMotor::setJogMoveMode(JogMoveMode jm)
{
	mJogMoveMode = jm;
	StopMode sm = getJogStopMode();
	int e = SBC_SetJogMode(mSerial.c_str(),lChannel, (MOT_JogModes) jm, (MOT_StopModes) sm);
    if(e)
    {
    	Log(lError) <<tlError(e);
        return false;
    }
  	return true;
}

bool BenchTopStepperMotor::setJogStopMode(StopMode sm)
{
	JogMoveMode jm = getJogMoveMode();
	int e = SBC_SetJogMode(mSerial.c_str(),lChannel, (MOT_JogModes) jm, (MOT_StopModes) sm);
    if(e)
    {
    	Log(lError) <<tlError(e);
        return false;
    }
  	return true;
}

JogMoveMode	BenchTopStepperMotor::getJogMoveMode()
{
    MOT_JogModes jm;
	MOT_StopModes sm;
	int e = SBC_GetJogMode(mSerial.c_str(),lChannel, &jm, &sm);
    if(e)
    {
    	Log(lError) <<tlError(e);
        return (JogMoveMode) MOT_JogModeUndefined;
    }
  	return (JogMoveMode) jm;
}

StopMode BenchTopStepperMotor::getJogStopMode()
{
	MOT_StopModes sm;
    MOT_JogModes jm;
	int e = SBC_GetJogMode(mSerial.c_str(),lChannel, &jm, &sm);
    if(e)
    {
    	Log(lError) <<tlError(e);
        return (StopMode) MOT_StopModeUndefined;
    }
  	return (StopMode) sm;
}

double BenchTopStepperMotor::getJogVelocity()
{
    int a, v;
    int e = SBC_GetJogVelParams(mSerial.c_str(),lChannel, &a, &v);
    if(e)
    {
    	Log(lError) <<tlError(e);
    }

    return v / mScalingFactors.velocity;
}

double BenchTopStepperMotor::getJogStep()
{
    int value = SBC_GetJogStepSize(mSerial.c_str(),lChannel);
	return value / mScalingFactors.position;
}

bool BenchTopStepperMotor::setJogStep(double newStep)
{
	mJogStep = newStep;
	Log(lDebug) << "Setting Jog Step: "<<newStep;
    int e = SBC_SetJogStepSize(mSerial.c_str(), lChannel, newStep * mScalingFactors.position);

    if(e)
    {
    	Log(lError) <<tlError(e);
        return false;
    }
	return true;
}

bool BenchTopStepperMotor::setJogVelocity(double newVel)
{
	mManualJogVelocity = newVel;
    int a, v;
    SBC_GetJogVelParams(mSerial.c_str(),lChannel, &a, &v);

	Log(lDebug) << "Setting Jog Velocity: "<<newVel;
    int e = SBC_SetJogVelParams(mSerial.c_str(),lChannel, a, newVel * mScalingFactors.velocity);

    if(e)
    {
    	Log(lError) <<tlError(e);
        return false;
    }
	return true;
}

bool BenchTopStepperMotor::setJogAcceleration(double newAcc)
{
    int a, v;
    SBC_GetJogVelParams(mSerial.c_str(),lChannel, &a, &v);
    int e = SBC_SetJogVelParams(mSerial.c_str(),lChannel, newAcc * mScalingFactors.acceleration, v);

    if(e)
    {
    	Log(lError) <<tlError(e);
        return false;
    }

	return true;
}

double BenchTopStepperMotor::getJogAcceleration()
{
    int a, v;
    int e = SBC_GetJogVelParams(mSerial.c_str(),lChannel, &a, &v);

    if(e)
    {
    	Log(lError) <<tlError(e);
    }

    return a  / mScalingFactors.acceleration;
}

void BenchTopStepperMotor::jogForward(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcJogForward);
		post(cmd);
    }
    else
    {
        int e = SBC_MoveJog(mSerial.c_str(),lChannel, MOT_Forwards);
        if(e)
        {
            Log(lError) <<tlError(e);
        }
		mMotorCommandsPending--;
    }
}

void BenchTopStepperMotor::jogReverse(bool inThread)
{
	if(inThread)
    {
		MotorCommand cmd(mcJogReverse);
		post(cmd);
    }
    else
    {
        //Todo: tell thorlabs about the MOT_Reverse flag name
        int e = SBC_MoveJog(mSerial.c_str(),lChannel, MOT_Reverse);
        if(e)
        {
            Log(lError) <<tlError(e);
        }
   		mMotorCommandsPending--;
    }
}

void BenchTopStepperMotor::forward(bool inThread)
{
	//TODO: use inThread logic
    if(mDesiredPosition != -1)
    {
        moveToPosition(mDesiredPosition);
    }
    else
    {
    	int e = SBC_MoveAtVelocity(mSerial.c_str(),lChannel, MOT_Forwards);
    	if(e)
    	{
        	Log(lError) <<tlError(e);
        }
    }
}

void BenchTopStepperMotor::reverse(bool inThread)
{
	//TODO: use inThread logic
    int e = SBC_MoveAtVelocity(mSerial.c_str(),lChannel, MOT_Reverse);
    if(e !=0)
    {
        Log(lError) <<tlError(e);
    }
}

bool BenchTopStepperMotor::moveToPosition(double pos, bool inThread)
{
	if(inThread)
    {
        //Set desired position here so it does not get changed in the thread
		mDesiredPosition = pos;
		MotorCommand cmd(mcMoveToPosition, pos);
		post(cmd);
    }
    else
    {
        int e = SBC_MoveToPosition(mSerial.c_str(),lChannel, pos * mScalingFactors.position );
		mMotorCommandsPending--;
        if(e)
        {
            Log(lError) <<tlError(e);
            Log(lError) <<"Tried to move to position: "<<pos<<" using the "<<getName()<<" device.";
            return false;
        }
    }
    return true;
}
