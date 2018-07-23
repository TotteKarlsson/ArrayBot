#pragma hdrstop
#include <windows.h>
#include "thirdparty/thorlabs/Thorlabs.MotionControl.TCube.StepperMotor.h"
#include "atTCubeStepperMotor.h"
#include "dslLogger.h"
#include "/core/atExceptions.h"
#include "atMotorCommand.h"
#include <bitset>
using namespace std;

namespace at
{
    //---------------------------------------------------------------------------
    TCubeStepperMotor::TCubeStepperMotor(int serial)
    : APTMotor(serial)
    {
    	mDeviceTypeID = (didTCubeStepperMotor);
    }

    TCubeStepperMotor::~TCubeStepperMotor()
    {
        if(isConnected())
        {
    		disconnect();
        }
    }

    bool TCubeStepperMotor::connect()
    {
        // load the device settings
        // open the device
        int res = SCC_Open(dsl::toString(mSerial).c_str());

        mScalingFactors.position 	 = 2184533.32;
        mScalingFactors.velocity 	 = 1.1727e8;
    	mScalingFactors.acceleration = 2.403e4;

        if(res == 0)
        {
        	SCC_LoadSettings(mSerial.c_str());

            int en = SCC_EnableChannel(mSerial.c_str());
            Log(lDebug) << "Enabling Code: "<<en;

            //Set jog mode to continous
            setJogMoveMode(jmContinuous);

    	    // start the device polling at 200ms intervals
        	if(!SCC_StartPolling(mSerial.c_str(), 200))
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

    bool TCubeStepperMotor::disconnect()
    {
        //Shut down message processor
        APTMotor::disconnect();
    	SCC_Close(mSerial.c_str());
        mIsConnected = false;
        return true;
    }

    bool TCubeStepperMotor::enable()
    {
    	int e = SCC_EnableChannel(mSerial.c_str());
        if(e)
        {
            Log(lError) <<tlError(e);
            return false;
        }
        return true;
    }

    bool TCubeStepperMotor::disable()
    {
    	int e = SCC_DisableChannel(mSerial.c_str());
        if(e)
        {
            Log(lError) <<tlError(e);
            return false;
        }
        return true;
    }

    void TCubeStepperMotor::setPotentiometerVelocity(double v)
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

        short e = SCC_SetPotentiometerParams(mSerial.c_str(), 0, 0, velocity * mScalingFactors.velocity);
        velocity += (velStep);
        e = SCC_SetPotentiometerParams(mSerial.c_str(), 1, 32, velocity * mScalingFactors.velocity);
        velocity += velStep;
        e = SCC_SetPotentiometerParams(mSerial.c_str(), 2, 64, velocity * mScalingFactors.velocity);
        velocity += velStep;
        e = SCC_SetPotentiometerParams(mSerial.c_str(), 3, 120, velocity * mScalingFactors.velocity);

    //	DWORD	vel;
    //    for(int i = 0; i < 127; i++)
    //    {
    //    	short e = ISC_GetPotentiometerParams(mSerial.c_str(), i, &thDef, &vel);
    //        Log(lInfo) <<"Pos: "<<i<<"\t"<<"Def: "<<thDef<<"\tValue: "<<vel / mScalingFactors.velocity;
    //    }
    }

    unsigned long TCubeStepperMotor::getStatusBits()
    {
    	return SCC_GetStatusBits(mSerial.c_str());
    }

    double TCubeStepperMotor::getEncoderCounts()
    {
    	long cnt1, cnt2, cnt3;
        return 0;
    }

    HardwareInformation TCubeStepperMotor::getHWInfo()
    {
    	TLI_HardwareInformation hwi;
    	int e  = SCC_GetHardwareInfoBlock(mSerial.c_str(), &hwi);
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
        return bits.test(4);
    }

    bool TCubeStepperMotor::isReversing()
    {
    	//Query for status bits
        unsigned long b = SCC_GetStatusBits(mSerial.c_str());
        bitset<32> bits(b);
        return bits.test(5);
    }

    bool TCubeStepperMotor::isActive()
    {
    	//Query for status bits
        unsigned long b = SCC_GetStatusBits(mSerial.c_str());
        bitset<32> bits(b);
        return bits.test(4) || bits.test(5) || bits.test(6) || bits.test(7) ;
    }

    bool TCubeStepperMotor::isEnabled()
    {
    	//Query for status bits
        unsigned long b = SCC_GetStatusBits(mSerial.c_str());
        bitset<32> bits(b);
        return bits.test(31);
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

    void TCubeStepperMotor::home(bool inThread)
    {
    	if(inThread)
        {
    		MotorCommand cmd(mcHome);
    		post(cmd);
        }
        else
        {

            if(!SCC_CanHome(mSerial.c_str()))
            {
                Log(lError) << "This device cannot be homed";
            }

            int e = SCC_Home(mSerial.c_str());
            if(e)
            {
            	Log(lError) <<tlError(e);
            }
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
    		int e = SCC_StopImmediate(mSerial.c_str());
            mMotorCommandsPending--;
            if(e)
            {
                Log(lError) <<tlError(e);
            }
        }
    }

    void TCubeStepperMotor::stopProfiled(bool inThread)
    {
    	if(inThread)
        {
        	//Check if motor is moving to absolute position
    		MotorCommand cmd(mcStopProfiled);
    		post(cmd);
        }
        else
        {
            int e = SCC_StopProfiled(mSerial.c_str());
    		mMotorCommandsPending--;
            if(e)
            {
                Log(lError) <<tlError(e);
            }
        }
    }

    double TCubeStepperMotor::getPosition() const
    {
        return SCC_GetPosition(mSerial.c_str()) / mScalingFactors.position;
    }

    double TCubeStepperMotor::getVelocity()
    {
    	int a(0), v(0);

    	int e = SCC_GetVelParams(mSerial.c_str(), &a, &v);

        if(e)
        {
        	Log(lError) <<tlError(e);
        }
      	return (double) v / mScalingFactors.velocity;
    }

    double TCubeStepperMotor::getAcceleration()
    {
    	int a(0), v(0);

    	int e = SCC_GetVelParams(mSerial.c_str(), &a, &v);

        if(e)
        {
        	Log(lError) <<tlError(e);
        }
      	return (double) a / mScalingFactors.acceleration;
    }

    bool TCubeStepperMotor::setVelocityParameters(double v, double a, bool inThread)
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
            SCC_GetVelParamsBlock(mSerial.c_str(), &p);

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

            int e = SCC_SetVelParamsBlock(mSerial.c_str(), &p);
            mMotorCommandsPending--;

            if(e)
            {
                Log(lError) <<tlError(e);
               	return false;
            }
        }
       	return true;
    }

    double TCubeStepperMotor::getJogStep()
    {
        int value = SCC_GetJogStepSize(mSerial.c_str());
    	return value / mScalingFactors.position;
    }

    bool TCubeStepperMotor::setJogStep(double newStep)
    {
    	mJogStep = newStep;
    	Log(lDebug) << "Setting Jog Step: "<<newStep;
        int e = SCC_SetJogStepSize(mSerial.c_str(),  newStep * mScalingFactors.position);

        if(e)
        {
        	Log(lError) <<tlError(e);
            return false;
        }
    	return true;
    }

    bool TCubeStepperMotor::setJogMoveMode(JogMoveMode jm)
    {
    	mJogMoveMode = jm;
    	StopMode sm = getJogStopMode();
    	int e = SCC_SetJogMode(mSerial.c_str(), (MOT_JogModes) jm, (MOT_StopModes) sm);
        if(e)
        {
        	Log(lError) <<tlError(e);
            return false;
        }
      	return true;
    }

    bool TCubeStepperMotor::setJogStopMode(StopMode sm)
    {
    	JogMoveMode jm = getJogMoveMode();
    	int e = SCC_SetJogMode(mSerial.c_str(), (MOT_JogModes) jm, (MOT_StopModes) sm);
        if(e)
        {
        	Log(lError) <<tlError(e);
            return false;
        }
      	return true;
    }

    JogMoveMode	TCubeStepperMotor::getJogMoveMode()
    {
        MOT_JogModes jm;
    	MOT_StopModes sm;
    	int e = SCC_GetJogMode(mSerial.c_str(), &jm, &sm);
        if(e)
        {
        	Log(lError) <<tlError(e);
            return (JogMoveMode) MOT_JogModeUndefined;
        }
      	return (JogMoveMode) jm;
    }

    StopMode TCubeStepperMotor::getJogStopMode()
    {
    	MOT_StopModes sm;
        MOT_JogModes jm;
    	int e = SCC_GetJogMode(mSerial.c_str(), &jm, &sm);
        if(e)
        {
        	Log(lError) <<tlError(e);
            return (StopMode) MOT_StopModeUndefined;
        }
      	return (StopMode) sm;
    }

    double TCubeStepperMotor::getJogVelocity()
    {
        int a, v;
        int e = SCC_GetJogVelParams(mSerial.c_str(), &a, &v);
        if(e)
        {
        	Log(lError) <<tlError(e);
        }

        return v / mScalingFactors.velocity;
    }

    bool TCubeStepperMotor::setJogVelocity(double newVel)
    {
        int a, v;
        SCC_GetJogVelParams(mSerial.c_str(), &a, &v);

    	Log(lDebug) << "Setting Jog Velocity: "<<newVel;
        int e = SCC_SetJogVelParams(mSerial.c_str(), a, newVel * mScalingFactors.velocity);

        if(e)
        {
        	Log(lError) <<tlError(e);
            return false;
        }
    	return true;
    }

    bool TCubeStepperMotor::setJogAcceleration(double newAcc)
    {
        int a, v;
        SCC_GetJogVelParams(mSerial.c_str(), &a, &v);
        int e = SCC_SetJogVelParams(mSerial.c_str(), newAcc * mScalingFactors.acceleration, v);

        if(e)
        {
        	Log(lError) <<tlError(e);
            return false;
        }

    	return true;
    }

    double TCubeStepperMotor::getJogAcceleration()
    {
        int a, v;
        int e = SCC_GetJogVelParams(mSerial.c_str(), &a, &v);

        if(e)
        {
        	Log(lError) <<tlError(e);
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
            int e = SCC_MoveJog(mSerial.c_str(), MOT_Forwards);
            mMotorCommandsPending--;
            if(e)
            {
                Log(lError) <<tlError(e);
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
            //Todo: tell thorlabs about the MOT_Reverse flag name
            int e = SCC_MoveJog(mSerial.c_str(), MOT_Backwards);
            mMotorCommandsPending--;
            if(e)
            {
                Log(lError) <<tlError(e);
            }
        }
    }

    void TCubeStepperMotor::forward(bool inThread)
    {
    	//TODO: use inThread logic
        if(mDesiredPosition != -1)
        {
            moveToPosition(mDesiredPosition);
        }
        else
        {
            int e = SCC_MoveAtVelocity(mSerial.c_str(), MOT_Forwards);
            if(e)
            {
                Log(lError) <<tlError(e);
            }
        }
    }

    void TCubeStepperMotor::reverse(bool inThread)
    {
    	//TODO: use inThread logic
        int e = SCC_MoveAtVelocity(mSerial.c_str(), MOT_Backwards);
        if(e !=0)
        {
            Log(lError) <<tlError(e);
        }
    }

    bool TCubeStepperMotor::moveToPosition(double pos, bool inThread)
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
            int e = SCC_MoveToPosition(mSerial.c_str(), pos * mScalingFactors.position );
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
}
