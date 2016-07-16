#pragma hdrstop
#include "abTriggerFunction.h"
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
	return true;
}

