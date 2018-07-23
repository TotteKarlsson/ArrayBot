#pragma hdrstop
#include "atJoystickAxis.h"
#include "dslLogger.h"
#include "apt/atAPTMotor.h"
#include "dslUtils.h"

using namespace dsl;

namespace at
{
    JoyStickAxis::JoyStickAxis()
    :
    	mMaxPosition(65535),
        mNumberOfGears(25),
        mMaxVelocity(0),
    	mAcceleration(0),
        mIsEnabled(false),
        mZeroInMiddle(true),
    	mMotorVelocity(0),
    	mAlpha(1),
        mSenseOfDirection(1),
        mMotor(NULL),
        mLeftDeadZone(0),
        mRightDeadZone(0)
    {}

    JoyStickAxis::~JoyStickAxis()
    {}

    void JoyStickAxis::setup(APTMotor* motor, double vel, double acc)
    {
        assignMotor(motor);
        setMaxVelocity(vel);
        setAcceleration(acc);
    }

    void JoyStickAxis::setDeadZones(double leftDZ, double rightDZ)
    {
    	mLeftDeadZone = leftDZ;
        mRightDeadZone = rightDZ;
    }

    void JoyStickAxis::setSenseOfDirection(int sign)
    {
    	mSenseOfDirection = sign;
    }

    void JoyStickAxis::enable()
    {
    	mIsEnabled = true;
    }

    void JoyStickAxis::disable()
    {
    	mIsEnabled = false;
    }

    bool JoyStickAxis::isEnabled()
    {
    	return mIsEnabled;
    }

    void JoyStickAxis::setNumberOfGears(int g)
    {
    	mNumberOfGears = g;
    }

    int JoyStickAxis::getNumberOfGears()
    {
    	return 	mNumberOfGears;
    }

    void JoyStickAxis::setMaxVelocity(double vel)
    {
    	mMaxVelocity = vel;
    }

    double JoyStickAxis::getMaxVelocity()
    {
    	return 	mMaxVelocity;
    }

    void JoyStickAxis::setAcceleration(double a)
    {
    	mAcceleration = a;
    }

    double JoyStickAxis::getAcceleration()
    {
    	return 	mAcceleration;
    }

    void JoyStickAxis::assignMotor(APTMotor* motor)
    {
    	mMotor = motor;
    }

    double JoyStickAxis::getCurrentVelocity()
    {
    	return mLastSetVelocity;
    }


    //The move function is where the joystick axis position
    //is translated to a move command
    void JoyStickAxis::Move(int newPosition)
    {
    	if(!mMotor || !isEnabled())
        {
    		//    	Log(lError) << "Tried to move a NULL or disabled motor";
        	return;
        }

        //Scale the incoming position to be in the motors velocity range,
        double scaledPosition 	= ((newPosition)  - mMaxPosition/2.0 ); //-32767.5 -> +32767.5
        scaledPosition 			= (scaledPosition/mMaxPosition) * 2.0; //-1 -> +1

        //Accomodate for deadzones
        MotorCommandEnum lastCommand = mMotor->getLastCommand();
        bool stopMotor(false);
        if(scaledPosition < 0) //Negative
        {
            if(scaledPosition > mLeftDeadZone)
            {
            	stopMotor = true;
            }
        }
        else
        {
            if(scaledPosition < mRightDeadZone)
            {
            	stopMotor = true;
            }
        }

        if(stopMotor)
        {
            if(mMotor->isActive() &&  lastCommand != mcStopHard)
            {
            	if(lastCommand != mcStopProfiled)
                {

                	mMotor->stopProfiled();
                }
            }
            return;
        }

        int    nrOfSteps = getNumberOfGears();
    	double stepSize  = mMaxVelocity  / nrOfSteps;

        mMotorVelocity = pow(scaledPosition, 3.0) * mSenseOfDirection;
       	mMotorVelocity *= mMaxVelocity;
    //    if(fabs(mMotorVelocity) <= stepSize)
    //    {
    //    	MotorCommandEnum c = mMotor->getLastCommand();
    //    	if(mMotor->isActive() &&  c != mcStopHard)
    //        {
    //        	//Bring down velocity manually to zero
    //            double v = mMotor->getJogVelocity();
    //       		mMotor->stopProfiled();
    //        }
    //    }
    //    else
        {
    	    Log(lDebug3) << "Axis numbers: ("<<newPosition<<","<<scaledPosition<<","<<stepSize<<")";
            Log(lDebug3) << "Setting jog velocity: "<<fabs(mMotorVelocity);

    		mMotor->setJogVelocity(fabs(mMotorVelocity));
       		mLastSetVelocity = mMotorVelocity;

            //Forward or reverse?
            if (mMotorVelocity > 0)
            {
    			mMotor->jogForward();
            }
            else
            {
    			mMotor->jogReverse();
            }
        }
    }

}
