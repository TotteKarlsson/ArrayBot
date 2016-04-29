#pragma hdrstop
#include "abTCubeDCServo.h"
#include "Thorlabs.MotionControl.TCube.BrushlessMotor.h"
//#include "Thorlabs.MotionControl.TCube.DCServo.h"
//#include "Thorlabs.MotionControl.TDIEngine.h"
#include "mtkLogger.h"
#include "abExceptions.h"
#include <bitset>         // std::bitset
using namespace std;
//---------------------------------------------------------------------------
TCubeDCServo::TCubeDCServo(int serial)
: APTMotor(serial)
{
	mDeviceTypeID = (didTCubeDCServo);

}

TCubeDCServo::~TCubeDCServo()
{}

bool TCubeDCServo::connect()
{
    // load the device settings
    // open the device
    int res = BMC_Open(toString(mSerial).c_str());

    //Find out what stage is connected

    mScalingFactors.position = 34304;
    mScalingFactors.velocity = 767367.49;
	mScalingFactors.acceleration = 261.93;

    if(res == 0)
    {
    	//BMC_LoadSettings(mSerial.c_str());
	    // start the device polling at 200ms intervals
    	if(!BMC_StartPolling(mSerial.c_str(), 200))
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

bool TCubeDCServo::disconnect()
{
    mIsConnected = false;
    return false;
}

unsigned long TCubeDCServo::getStatusBits()
{
	return BMC_GetStatusBits(mSerial.c_str());
}

double TCubeDCServo::getEncoderCounts()
{
	long cnt1, cnt2, cnt3;
	int err = BMC_GetMotorParams(mSerial.c_str(), &cnt1);
	if(!err)
    {
    	//Fill out scaling factors
        mScalingFactors.position = 34304;
        mScalingFactors.velocity = 767367.49;
		mScalingFactors.acceleration = 261.93;
    }
    return 0;
}

HardwareInformation TCubeDCServo::getHWInfo()
{
	TLI_HardwareInformation hwi;
	int err  = BMC_GetHardwareInfoBlock(mSerial.c_str(), &hwi);
    mHWInfo.serialNumber = hwi.serialNumber;
    mHWInfo.modelNumber = hwi.modelNumber;
    mHWInfo.type = hwi.type;
    return mHWInfo;
}

bool TCubeDCServo::isHomed()
{
	//Query for status bits
    unsigned long b = BMC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(10);
}

bool TCubeDCServo::isHoming()
{
	//Query for status bits
    unsigned long b = BMC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(9);
}

bool TCubeDCServo::isForwarding()
{
	//Query for status bits
    unsigned long b = BMC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(5);
}

bool TCubeDCServo::isReversing()
{
	//Query for status bits
    unsigned long b = BMC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(6);
}

bool TCubeDCServo::isActive()
{
	//Query for status bits
    unsigned long b = BMC_GetStatusBits(mSerial.c_str());

    bitset<32> bits(b);
    return bits.test(4) || bits.test(5) || bits.test(6) || bits.test(7) ;
}

bool TCubeDCServo::identify()
{
	BMC_Identify(mSerial.c_str());
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
  	if(!BMC_CanHome(mSerial.c_str()))
    {
    	Log(lError) << "This device cannot be homed";
    }

    int res = BMC_Home(mSerial.c_str());

    if(res)
    {
    	//throw
    }
}

void TCubeDCServo::stop()
{
	BMC_StopProfiled(mSerial.c_str());
}

double TCubeDCServo::getPosition()
{
    return BMC_GetPosition(mSerial.c_str()) / mScalingFactors.position;
}

double TCubeDCServo::getVelocity()
{
	int a(0);
  	int v (0);

	int err = BMC_GetVelParams(mSerial.c_str(), &a, &v);

    if(err != 0)
    {
    	Log(lError) <<tlError(err);
    }
  	return v/ mScalingFactors.velocity;
}

bool TCubeDCServo::setMaxVelocity(double vel)
{
 	MOT_VelocityParameters parameters;
    BMC_GetVelParamsBlock(mSerial.c_str(), &parameters);
    parameters.maxVelocity = vel * mScalingFactors.velocity;
    int e = BMC_SetVelParamsBlock(mSerial.c_str(), &parameters);

    if(e)
    {
	   	Log(lError) <<tlError(e);
    }

    if(isForwarding())
    {
        forward();
    }
    else if (isReversing())
    {
        reverse();
    }

	return false;
}

bool TCubeDCServo::setAcceleration(double a)
{
 	MOT_VelocityParameters parameters;
    BMC_GetVelParamsBlock(mSerial.c_str(), &parameters);
    parameters.acceleration = a * mScalingFactors.acceleration;
    BMC_SetVelParamsBlock(mSerial.c_str(), &parameters);
	return false;
}


double TCubeDCServo::getAcceleration()
{
	int a(0);
  	int v (0);

	int error = BMC_GetVelParams(mSerial.c_str(), &a, &v);

    if(error != 0)
    {
    	Log(lError) <<tlError(error);
    }
  	return a/ mScalingFactors.acceleration;
}

void TCubeDCServo::jogForward()
{
	int error = BMC_MoveJog(mSerial.c_str(), MOT_Forwards);
    if(error != 0)
    {
    	Log(lError) <<tlError(error);
    }
}

void TCubeDCServo::jogReverse()
{
	int error = BMC_MoveJog(mSerial.c_str(), MOT_Reverse);
    if(error != 0)
    {
    	Log(lError) <<tlError(error);
    }
}

void TCubeDCServo::forward()
{
	if(isReversing())
    {
    	Log(lInfo) << "Forwarding requested, but motor is in reverse..";
        stop();
    }

	int error = BMC_MoveAtVelocity(mSerial.c_str(), MOT_Forwards);
    if(error != 0)
    {
    	Log(lError) <<tlError(error);
    }
}

void TCubeDCServo::reverse()
{
	if(isForwarding())
    {
    	Log(lInfo) << "Reversing requested, but motor is forwarding..";
        stop();
    }

	int error = BMC_MoveAtVelocity(mSerial.c_str(), MOT_Reverse);
    if(error !=0)
    {
    	Log(lError) <<tlError(error);
    }
}

void TCubeDCServo::moveDistance(double distance)
{
// 	Log(lError) <<msg.str();
}



