#pragma hdrstop
#include "abLongTravelStage.h"
#include "Thorlabs.MotionControl.TCube.BrushlessMotor.h"
//#include "Thorlabs.MotionControl.TCube.DCServo.h"
//#include "Thorlabs.MotionControl.TDIEngine.h"
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
{}

bool LongTravelStage::connect()
{
    // load the device settings
    // open the device
    int res = BMC_Open(toString(mSerial).c_str());

    //Find out what stage is connected

//    mScalingFactors.position = 34304;
//    mScalingFactors.velocity = 767367.49;
//	mScalingFactors.acceleration = 261.93;

    mScalingFactors.position = 1919.64;
    mScalingFactors.velocity = 42941.66;
	mScalingFactors.acceleration = 14.66;

    if(res == 0)
    {
    	//BMC_LoadSettings(mSerial.c_str());
	    // start the device polling at 200ms intervals
    	if(!BMC_StartPolling(mSerial.c_str(), 250))
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
    mIsConnected = false;
    return false;
}

unsigned long LongTravelStage::getStatusBits()
{
	return BMC_GetStatusBits(mSerial.c_str());
}

double LongTravelStage::getEncoderCounts()
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

bool LongTravelStage::switchDirection()
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

HardwareInformation LongTravelStage::getHWInfo()
{
	TLI_HardwareInformation hwi;
	int err  = BMC_GetHardwareInfoBlock(mSerial.c_str(), &hwi);
    mHWInfo.serialNumber = hwi.serialNumber;
    mHWInfo.modelNumber = hwi.modelNumber;
    mHWInfo.type = hwi.type;
    return mHWInfo;
}

bool LongTravelStage::isHomed()
{
	//Query for status bits
    unsigned long b = BMC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(10);
}

bool LongTravelStage::isHoming()
{
	//Query for status bits
    unsigned long b = BMC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(9);
}

bool LongTravelStage::isForwarding()
{
	//Query for status bits
    unsigned long b = BMC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(5);
}

bool LongTravelStage::isReversing()
{
	//Query for status bits
    unsigned long b = BMC_GetStatusBits(mSerial.c_str());
    bitset<32> bits(b);
    return bits.test(4);
}

bool LongTravelStage::isActive()
{
	//Query for status bits
    unsigned long b = BMC_GetStatusBits(mSerial.c_str());

    bitset<32> bits(b);
    return bits.test(4) || bits.test(5) || bits.test(6) || bits.test(7) ;
}

bool LongTravelStage::identify()
{
	BMC_Identify(mSerial.c_str());
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

void LongTravelStage::stop()
{
//	if(isActive())
    {
//		int error = BMC_StopProfiled(mSerial.c_str());
		int error = BMC_StopImmediate(mSerial.c_str());

        if(error != 0)
        {
            Log(lError) <<tlError(error);
        }

//        while(isActive())
//        {
//            //Log(lInfo) << "Waiting ...";
//        }
    }
}

void LongTravelStage::stopProfiled()
{
//	if(isActive())
    {
		int error = BMC_StopProfiled(mSerial.c_str());
        if(error != 0)
        {
            Log(lError) <<tlError(error);
        }

//        while(isActive())
//        {
//            //Log(lInfo) << "Waiting ...";
//        }
    }
}

double LongTravelStage::getPosition()
{
    return BMC_GetPosition(mSerial.c_str()) / mScalingFactors.position;
}

double LongTravelStage::getVelocity()
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


bool LongTravelStage::setMaxVelocity(double vel)
{
 	MOT_VelocityParameters parameters;
    BMC_GetVelParamsBlock(mSerial.c_str(), &parameters);

    //Check difference
    if(fabs(vel - parameters.maxVelocity) < 1.0)
    {
    	Log(lInfo) <<"velocity change to small..";
    }
    else
    {
    	parameters.maxVelocity = vel * mScalingFactors.velocity;
    	int e = BMC_SetVelParamsBlock(mSerial.c_str(), &parameters);

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

bool LongTravelStage::setMaxVelocityForward(double vel)
{
	setMaxVelocity(vel);
    forward();
}

bool LongTravelStage::setMaxVelocityReverse(double vel)
{
	setMaxVelocity(vel);
    reverse();
}

bool LongTravelStage::setAcceleration(double a)
{
 	MOT_VelocityParameters parameters;
    BMC_GetVelParamsBlock(mSerial.c_str(), &parameters);
    parameters.acceleration = a * mScalingFactors.acceleration;
    BMC_SetVelParamsBlock(mSerial.c_str(), &parameters);
	return false;
}

double LongTravelStage::getAcceleration()
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

void LongTravelStage::jogForward()
{
	int error = BMC_MoveJog(mSerial.c_str(), MOT_Forwards);
    if(error != 0)
    {
    	Log(lError) <<tlError(error);
    }
}

void LongTravelStage::jogReverse()
{
	int error = BMC_MoveJog(mSerial.c_str(), MOT_Reverse);
    if(error != 0)
    {
    	Log(lError) <<tlError(error);
    }
}

void LongTravelStage::forward()
{
//	if(isReversing())
//    {
//    	Log(lInfo) << "Forwarding requested, motor is in reverse..";
//    }

//    //Don't send command if already doing what is needed
//    if(!isForwarding())
    {
        int error = BMC_MoveAtVelocity(mSerial.c_str(), MOT_Forwards);
        if(error != 0)
        {
            Log(lError) <<tlError(error);
        }
    }
//    else
//    {
//    	Log(lWarning) <<"Motor is already forwarding..";
//    }
}

void LongTravelStage::reverse()
{
//	if(isForwarding())
//    {
//    	Log(lInfo) << "Reversing requested, but motor is forwarding..";
////		return;
//    }

    //Don't send command if already doing what is needed
 //   if(!isReversing())
    {
        int error = BMC_MoveAtVelocity(mSerial.c_str(), MOT_Reverse);
        if(error !=0)
        {
            Log(lError) <<tlError(error);
        }
    }
}

void LongTravelStage::moveDistance(double distance)
{
// 	Log(lError) <<msg.str();
}



