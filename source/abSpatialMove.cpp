#pragma hdrstop
#include "abSpatialMove.h"

//---------------------------------------------------------------------------
SpatialMove::SpatialMove(ABObject* unit, const ab::Position& p, double maxVel, double acc, double dwellTime)
:
mUnit(unit),
mPosition(p),
mMaxVelocity(0),
mAcceleration(0),
mDwellTime(0)
{}
