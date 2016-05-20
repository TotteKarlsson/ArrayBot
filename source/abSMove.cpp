#pragma hdrstop
#include "abSMove.h"

//---------------------------------------------------------------------------
SMove::SMove(ABObject* unit, const ab::Position& p, double maxVel, double acc, double dwellTime)
:
mUnit(unit),
mPosition(p),
mMaxVelocity(0),
mAcceleration(0),
mDwellTime(0)
{}
