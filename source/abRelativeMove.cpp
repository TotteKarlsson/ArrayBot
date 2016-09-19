#pragma hdrstop
#include "abRelativeMove.h"
//---------------------------------------------------------------------------


RelativeMove::RelativeMove(const string& lbl, APTMotor* mtr, double pos, double maxVel, double acc)
:
ab::Move(lbl, mtr, maxVel, acc)
//mPosition(pos),
//mPositionResolution(1.0e-3)
{}

const string RelativeMove::getTypeName() const
{
	return "relativeMove";
}



