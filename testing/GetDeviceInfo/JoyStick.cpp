#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
using namespace mtk;
using namespace std;

bool sameSign(double x, double y)
{
	return x*y >= 0.0f;
}

//---------------------------------------------------------------------------
void __fastcall TMain::JMXMove(TMessage &msg)
{
	double fullVelRange = 100.0;
    int nrOfSteps = 3;
	double step = fullVelRange / nrOfSteps;

	double scalingFactor = fullVelRange/ 65535.0;
	double pos = (msg.LParamLo * scalingFactor - fullVelRange/2.0) * 2.0;

    mRunningZAverage = (mAlpha * pos) + (1.0 - mAlpha) * mRunningZAverage;

    JoystickZPosition->Caption 	= "X Position = " + FloatToStrF(pos, ffFixed, 4,2);
    JoystickAvgZPos->Caption 	= "X Average Position = " + FloatToStrF(mRunningZAverage, ffFixed, 4,2);

	//Check if joystick value have changed more than previous command
	double vel = mRunningZAverage;
    if(fabs(vel - mValCommand) > step)
    {
        APTMotor* motor = getCurrentMotor();
        if(motor == NULL)
        {
            Log(lInfo) << "Motor object is null..";
            return;
        }

        //Did we switch direction?
        if(!sameSign(vel,mValCommand))
        {
            motor->switchDirection();
        }

        mValCommand = vel;
        if( fabs(mValCommand) <= step)
        {
	        motor->stop();
            Log(lInfo) << "Motor is stopping. ";
            return;
        }

        Log(lInfo) << "Setting jog velocity: "<<fabs(vel);
		motor->setJogVelocity(fabs(vel));
        if (vel > step)
        {
			motor->jogForward();
        }
        else
        {
			motor->jogReverse();
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::JMYMove(TMessage &msg)
{
//	double fullVelRange = 5.0;
//    int nrOfSteps = 5;
//	double step = fullVelRange / nrOfSteps;
//
//	double scalingFactor = fullVelRange/ 65535.0;
//	double pos = (msg.LParamLo * scalingFactor - fullVelRange/2.0) * 2.0;
//
//    mRunningZAverage = (mAlpha * pos) + (1.0 - mAlpha) * mRunningZAverage;
//
//    JoystickZPosition->Caption 	= "X Position = " + FloatToStrF(pos, ffFixed, 4,2);
//    JoystickAvgZPos->Caption 	= "X Average Position = " + FloatToStrF(mRunningZAverage, ffFixed, 4,2);
//
//	//Check if joystick value have changed more than previous command
//	double vel = mRunningZAverage;
//    if(fabs(vel - mValCommand) > step)
//    {
//        //Did we switch direction?
//        if(!sameSign(vel,mValCommand))
//        {
//			MotorCommand cmd(mcSwitchDirection);
//        }
//
//        mValCommand = vel;
//        if( fabs(mValCommand) <= step)
//        {
//            MotorCommand cmd(mcStopHard,  vel);
//            mMotorMessageContainer.post(cmd);
//            Log(lInfo) << "Motor is stopping. ";
//            return;
//        }
//
//        if (vel > step)
//        {
//            MotorCommand cmd(mcSetVelocityForward,  fabs(vel));
//            mMotorMessageContainer.post(cmd);
//            Log(lInfo) << "Setting forward velocity: "<<vel;
//        }
//        else
//        {
//            MotorCommand cmd(mcSetVelocityReverse,  fabs(vel));
//            mMotorMessageContainer.post(cmd);
//            Log(lInfo) << "Setting reverse velocity: "<<fabs(vel);
//        }
//    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::JMZMove(TMessage &msg)
{
//	double fullVelRange = 5.0;
//    int nrOfSteps = 5;
//	double step = fullVelRange / nrOfSteps;
//
//	double scalingFactor = fullVelRange/ 65535.0;
//	double pos = (msg.LParamLo * scalingFactor - fullVelRange/2.0) * 2.0;
//
//    mRunningZAverage = (mAlpha * pos) + (1.0 - mAlpha) * mRunningZAverage;
//
//    JoystickZPosition->Caption 	= "X Position = " + FloatToStrF(pos, ffFixed, 4,2);
//    JoystickAvgZPos->Caption 	= "X Average Position = " + FloatToStrF(mRunningZAverage, ffFixed, 4,2);
//
//	//Check if joystick value have changed more than previous command
//	double vel = mRunningZAverage;
//    if(fabs(vel - mValCommand) > step)
//    {
//        //Did we switch direction?
//        if(!sameSign(vel,mValCommand))
//        {
//			MotorCommand cmd(mcSwitchDirection);
//        }
//
//        mValCommand = vel;
//        if( fabs(mValCommand) <= step)
//        {
//            MotorCommand cmd(mcStopHard,  vel);
//            mMotorMessageContainer.post(cmd);
//            Log(lInfo) << "Motor is stopping. ";
//            return;
//        }
//
//        if (vel > step)
//        {
//            MotorCommand cmd(mcSetVelocityForward,  fabs(vel));
//            mMotorMessageContainer.post(cmd);
//            Log(lInfo) << "Setting forward velocity: "<<vel;
//        }
//        else
//        {
//            MotorCommand cmd(mcSetVelocityReverse,  fabs(vel));
//            mMotorMessageContainer.post(cmd);
//            Log(lInfo) << "Setting reverse velocity: "<<fabs(vel);
//        }
//    }
}
