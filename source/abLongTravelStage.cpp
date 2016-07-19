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

        int en = ISC_EnableChannel(mSerial.c_str());
        Log(lDebug) << "Enabling Code: "<<en;
        //Set jog mode to continous
        setJogMoveMode(jmContinuous);

	    // start the device polling at 200ms intervals
    	if(!ISC_StartPolling(mSerial.c_str(), 200))
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

bool LongTravelStage::disconnect()
{
    //Shut down message processor
    APTMotor::disconnect();
	ISC_Close(mSerial.c_str());
    mIsConnected = false;
    return true;
}

bool LongTravelStage::enable()
{
	int e = ISC_EnableChannel(mSerial.c_str());
    if(e != 0)
    {
        Log(lError) <<tlError(e);
        return false;
    }
    return true;
}

bool LongTravelStage::disable()
{
	int e = ISC_DisableChannel(mSerial.c_str());
    if(e != 0)
    {
        Log(lError) <<tlError(e);
        return false;
    }
    return true;
}
void LongTravelStage::setPotentiometerVelocity(double v)
{
    //Divide the velocity by four and populate the ranges
    //TODO: Clean this up later.. not sure how the SetPot function
    //really are intended to work..?
	WORD 	thDef;

    mPotentiometerVelocity = v;
    double velStep = v;// / 4.;
	double velocity = velStep;

    int fullRange = 128;
    int nrOfRanges = 4;
    int range = 32; //128/4

    int currRange = 1;

    short e = ISC_SetPotentiometerParams(mSerial.c_str(), 0, 0, velocity * mScalingFactors.velocity);
    velocity += (velStep);
    e = ISC_SetPotentiometerParams(mSerial.c_str(), 1, 32, velocity * mScalingFactors.velocity);
    velocity += velStep;
    e = ISC_SetPotentiometerParams(mSerial.c_str(), 2, 64, velocity * mScalingFactors.velocity);
    velocity += velStep;
    e = ISC_SetPotentiometerParams(mSerial.c_str(), 3, 120, velocity * mScalingFactors.velocity);

//	DWORD	vel;
//    for(int i = 0; i < 127; i++)
//    {
//    	short e = ISC_GetPotentiometerParams(mSerial.c_str(), i, &thDef, &vel);
//        Log(lInfo) <<"Pos: "<<i<<"\t"<<"Def: "<<thDef<<"\tValue: "<<vel / mScalingFactors.velocity;
//    }
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

HardwareInformation LongTravelStage::getHWInfo()
{
	TLI_HardwareInformation hwi;
	int e  = ISC_GetHardwareInfoBlock(mSerial.c_str(), &hwi);
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

bool LongTravelStage::isEnabled()
{
	//Query for status bits
    unsigned long b = ISC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(31);
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
		int e = ISC_StopImmediate(mSerial.c_str());
        if(e != 0)
        {
            Log(lError) <<tlError(e);
        }
    }
}

void LongTravelStage::stopProfiled(bool inThread)
{
    int e = ISC_StopProfiled(mSerial.c_str());
    if(e != 0)
    {
        Log(lError) <<tlError(e);
    }
}

double LongTravelStage::getPosition()
{
    return ISC_GetPosition(mSerial.c_str()) / mScalingFactors.position;
}

double LongTravelStage::getVelocity()
{
	int a(0), v(0);

	int e = ISC_GetVelParams(mSerial.c_str(), &a, &v);

    if(e != 0)
    {
    	Log(lError) <<tlError(e);
    }
  	return (double) v / mScalingFactors.velocity;
}

double LongTravelStage::getAcceleration()
{
	int a(0), v(0);

	int e = ISC_GetVelParams(mSerial.c_str(), &a, &v);

    if(e != 0)
    {
    	Log(lError) <<tlError(e);
    }
  	return (double) a / mScalingFactors.acceleration;
}

bool LongTravelStage::setVelocityParameters(double v, double a, bool inThread)
{
	if(inThread)
    {
    	//Check if motor is moving to absolute position
		MotorCommand cmd(mcSetVelocityParameters, v, a);
		post(cmd);
        mMotorCommandsPending++;
    }
    else
    {
     	MOT_VelocityParameters p;
        ISC_GetVelParamsBlock(mSerial.c_str(), &p);

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

        int e = ISC_SetVelParamsBlock(mSerial.c_str(), &p);
        mMotorCommandsPending--;

        if(e)
        {
            Log(lError) <<tlError(e);
           	return false;
        }
    }
   	return true;
}

bool LongTravelStage::setJogMoveMode(JogMoveMode jm)
{
	StopMode sm = getJogStopMode();
	int e = ISC_SetJogMode(mSerial.c_str(), (MOT_JogModes) jm, (MOT_StopModes) sm);
    if(e)
    {
    	Log(lError) <<tlError(e);
        return false;
    }
  	return true;
}

bool LongTravelStage::setJogStopMode(StopMode sm)
{
	JogMoveMode jm = getJogMoveMode();
	int e = ISC_SetJogMode(mSerial.c_str(), (MOT_JogModes) jm, (MOT_StopModes) sm);
    if(e != 0)
    {
    	Log(lError) <<tlError(e);
        return false;
    }
  	return true;
}

JogMoveMode	LongTravelStage::getJogMoveMode()
{
    MOT_JogModes jm;
	MOT_StopModes sm;
	int e = ISC_GetJogMode(mSerial.c_str(), &jm, &sm);
    if(e != 0)
    {
    	Log(lError) <<tlError(e);
        return (JogMoveMode) MOT_JogModeUndefined;
    }
  	return (JogMoveMode) jm;
}

StopMode LongTravelStage::getJogStopMode()
{
	MOT_StopModes sm;
    MOT_JogModes jm;
	int e = ISC_GetJogMode(mSerial.c_str(), &jm, &sm);
    if(e != 0)
    {
    	Log(lError) <<tlError(e);
        return (StopMode) MOT_StopModeUndefined;
    }
  	return (StopMode) sm;
}

double LongTravelStage::getJogVelocity()
{
    int a, v;
    int e = ISC_GetJogVelParams(mSerial.c_str(), &a, &v);
    if(e != 0)
    {
    	Log(lError) <<tlError(e);
    }

    return v / mScalingFactors.velocity;
}

bool LongTravelStage::setJogVelocity(double newVel)
{
    int a, v;
    ISC_GetJogVelParams(mSerial.c_str(), &a, &v);

	Log(lDebug) << "Setting Jog Velocity: "<<newVel;
    int e = ISC_SetJogVelParams(mSerial.c_str(), a, newVel * mScalingFactors.velocity);

    if(e != 0)
    {
    	Log(lError) <<tlError(e);
        return false;
    }
	return true;
}

bool LongTravelStage::setJogAcceleration(double newAcc)
{
    int a, v;
    ISC_GetJogVelParams(mSerial.c_str(), &a, &v);
    int e = ISC_SetJogVelParams(mSerial.c_str(), newAcc * mScalingFactors.acceleration, v);

    if(e != 0)
    {
    	Log(lError) <<tlError(e);
        return false;
    }

	return true;
}

double LongTravelStage::getJogAcceleration()
{
    int a, v;
    int e = ISC_GetJogVelParams(mSerial.c_str(), &a, &v);

    if(e)
    {
    	Log(lError) <<tlError(e);
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
        int e = ISC_MoveJog(mSerial.c_str(), MOT_Forwards);
        if(e != 0)
        {
            Log(lError) <<tlError(e);
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
        int e = ISC_MoveJog(mSerial.c_str(), MOT_Reverse);
        if(e != 0)
        {
            Log(lError) <<tlError(e);
        }
    }
}

void LongTravelStage::forward(bool inThread)
{
	//TODO: use inThread logic
    if(mDesiredPosition != -1)
    {
        moveToPosition(mDesiredPosition);
    }
    else
    {
    	int e = ISC_MoveAtVelocity(mSerial.c_str(), MOT_Forwards);
    	if(e != 0)
    	{
        	Log(lError) <<tlError(e);
        }
    }
}

void LongTravelStage::reverse(bool inThread)
{
	//TODO: use inThread logic
    int e = ISC_MoveAtVelocity(mSerial.c_str(), MOT_Reverse);
    if(e !=0)
    {
        Log(lError) <<tlError(e);
    }
}

bool LongTravelStage::moveToPosition(double pos, bool inThread)
{
	if(inThread)
    {
        //Set desired position here so it does not get changed in the thread
		mDesiredPosition = pos;
		MotorCommand cmd(mcMoveToPosition, pos);
		post(cmd);
        mMotorCommandsPending++;
    }
    else
    {
        int e = ISC_MoveToPosition(mSerial.c_str(), pos * mScalingFactors.position );
		mMotorCommandsPending--;
        if(e != 0)
        {
            Log(lError) <<tlError(e);
            Log(lError) <<"Tried to move to position: "<<pos<<" using the "<<getName()<<" device.";
            return false;
        }
    }
    return true;
}
