#pragma hdrstop
#include "abSpatialMove.h"
#include "abXYZUnit.h"
#include "abAPTMotor.h"
#include "abPosition.h"
using namespace ab;
//---------------------------------------------------------------------------
SpatialMove::SpatialMove(ABObject* unit, MoveType type, const ab::Position& p, double maxVel, double acc, double dwellTime)
:
Process(unit),
mMoveType(type),
mPosition(p),
mMaxVelocity(0),
mAcceleration(0),
mDwellTime(0)
{}

bool SpatialMove::execute()
{
	XYZUnit* o = dynamic_cast<XYZUnit*>(mUnit);
    if(o)
    {
		return o->moveAbsolute(mPosition);
    }

	APTMotor* m = dynamic_cast<APTMotor*>(mUnit);
    if(m)
    {
    	m->setJogVelocity(mMaxVelocity);
        m->setJogAcceleration(mAcceleration);
        return m->moveAbsolute(mPosition.x());
    }

    return false;
}

bool SpatialMove::undo()
{
	Position p("undo pos", mPosition.x() * -1, mPosition.y() * -1, mPosition.z() * -1);

	XYZUnit* unit = dynamic_cast<XYZUnit*>(mUnit);
    if(unit)
    {
		return unit->moveAbsolute(p);
    }

	return false;
}

bool SpatialMove::achievedPosition()
{
	APTMotor* o = dynamic_cast<APTMotor*>(mUnit);
    if(o)
    {
    	double p = o->getPosition();
    	return (isEqual(p,mPosition.x(), 5.0e-6)) ? true : false;
    }

    return false;
}

bool SpatialMove::isActive()
{
	APTMotor* o = dynamic_cast<APTMotor*>(mUnit);
    if(o)
    {
    	return o->isActive();
    }

    return false;
}
