#pragma hdrstop
#include "abAbsoluteMove.h"
#include "abXYZUnit.h"
#include "abAPTMotor.h"
//---------------------------------------------------------------------------

using ab::Position;
AbsoluteMove::AbsoluteMove(ABObject* unit, const Position& p)
:
SpatialMove(unit, p)
{}

bool AbsoluteMove::execute()
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

bool AbsoluteMove::undo()
{
	Position p("undo pos", mPosition.x() * -1, mPosition.y() * -1, mPosition.z() * -1);

	XYZUnit* unit = dynamic_cast<XYZUnit*>(mUnit);
    if(unit)
    {
		return unit->moveAbsolute(p);
    }

	return false;
}

bool AbsoluteMove::achievedPosition()
{
	APTMotor* o = dynamic_cast<APTMotor*>(mUnit);
    if(o)
    {
    	double p = o->getPosition();
    	return (isEqual(p,mPosition.x(), 5.0e-6)) ? true : false;
    }

    return false;
}

bool AbsoluteMove::isActive()
{
	APTMotor* o = dynamic_cast<APTMotor*>(mUnit);
    if(o)
    {
    	return o->isActive();
    }

    return false;
}
