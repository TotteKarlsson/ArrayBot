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

    mScalingFactors.position 	 = 7471102; //52297717.00 / 7.0;
    mScalingFactors.velocity 	 = 7471102; //52297717.00 / 7.0;
	mScalingFactors.acceleration = 7471102; //52297717.00 / 7.0;

    if(res == 0)
    {
    	//SCC_LoadSettings(mSerial.c_str());
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

bool TCubeStepperMotor::switchDirection()
{
	if(isForwarding())
    {
    	reverse();
    }
    else
    {
    	forward();
    }
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

void TCubeStepperMotor::stop()
{
//	if(isActive())
    {
//		int err = SCC_StopProfiled(mSerial.c_str());
		int err = SCC_StopImmediate(mSerial.c_str());

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

void TCubeStepperMotor::stopProfiled()
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
    return SCC_GetPosition(mSerial.c_str()) / mScalingFactors.position;
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
  	return v / mScalingFactors.velocity;
}


bool TCubeStepperMotor::setMaxVelocity(double vel)
{
 	MOT_VelocityParameters p;
    SCC_GetVelParamsBlock(mSerial.c_str(), &p);

//    //Check difference
//    if(fabs(vel - parameters.maxVelocity) < 1.0)
//    {
//    	Log(lInfo) <<"velocity change to small..";
//    }
//    else
    {
    	p.maxVelocity = vel * mScalingFactors.velocity;
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
    }

	return false;
}

bool TCubeStepperMotor::setMaxVelocityForward(double vel)
{
	setMaxVelocity(vel);
    forward();
}

bool TCubeStepperMotor::setMaxVelocityReverse(double vel)
{
	setMaxVelocity(vel);
    reverse();
}

bool TCubeStepperMotor::setAcceleration(double a)
{
 	MOT_VelocityParameters parameters;
    SCC_GetVelParamsBlock(mSerial.c_str(), &parameters);

    parameters.acceleration = a * mScalingFactors.acceleration;

    SCC_SetVelParamsBlock(mSerial.c_str(), &parameters);
	return false;
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
  	return a / mScalingFactors.acceleration;
}

bool TCubeStepperMotor::setJogMode(JogModes jm, StopModes sm)
{
	int err = SCC_SetJogMode(mSerial.c_str(), jm, sm);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
        return false;
    }
  	return true;
}

bool TCubeStepperMotor::setJogVelocity(double v)
{
    int acceleration;
    int velocity;
    SCC_GetJogVelParams(mSerial.c_str(), &acceleration, &velocity);
    int err = SCC_SetJogVelParams(mSerial.c_str(), acceleration, v * mScalingFactors.velocity);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }
	return true;
}

double TCubeStepperMotor::getJogVelocity()
{
    int a, v;
    int err = SCC_GetJogVelParams(mSerial.c_str(), &a, &v);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }

    return v /  mScalingFactors.velocity;
}

bool TCubeStepperMotor::setJogAcceleration(double newAcc)
{
    int a;
    int v;
    SCC_GetJogVelParams(mSerial.c_str(), &a, &v);
    int err = SCC_SetJogVelParams(mSerial.c_str(), v, newAcc * mScalingFactors.acceleration);

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
		MotorCommand cmd(mcForward);
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

void TCubeStepperMotor::jogReverse()
{
	int err = SCC_MoveJog(mSerial.c_str(), MOT_Backwards);
    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }
}

void TCubeStepperMotor::forward()
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

void TCubeStepperMotor::reverse()
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

void TCubeStepperMotor::moveDistance(double distance)
{
// 	Log(lError) <<msg.str();
}



