#pragma hdrstop
#include "abTriggerFunction.h"
#include "abAPTMotor.h"
//---------------------------------------------------------------------------


MoveAbsolute::MoveAbsolute(APTMotor* mtr, double pos, double v, double a)
:
mMotor(mtr),
mPosition(pos),
mVelocity(v),
mAcceleration(a)
{}


bool MoveAbsolute::execute()
{
	if(mMotor)
    {
    	mMotor->moveAbsolute(mPosition, mVelocity, mAcceleration);
        Log(lInfo) << "Move absolute trigger executed";
    }
    else
    {
        Log(lError) << "Move absolute trigger executed with NULL motor";
    }

	return true;
}

