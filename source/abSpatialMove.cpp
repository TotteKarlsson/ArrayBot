#pragma hdrstop
#include "abSpatialMove.h"
#include "abXYZUnit.h"
#include "abAPTMotor.h"
#include "abPosition.h"
using namespace ab;
//---------------------------------------------------------------------------
SpatialMove::SpatialMove(const string& lbl, ABObject* unit, MoveType type, const ab::Position& p, double maxVel, double acc, double dwellTime)
:
Process(lbl, unit),
mMoveType(type),
mPosition(p),
mMaxVelocity(0),
mAcceleration(0),
mDwellTime(0)
{
	mProcessType = (ptSpatialMove);
}

bool SpatialMove::write(IniSection* sec)
{
    IniKey* key = sec->createKey("LABEL", getLabel());

    double x = getPosition().x();
    key = sec->createKey("TYPE", 			toString(getMoveType()));
    key = sec->createKey("POSITION", 		toString(x));
    key = sec->createKey("MAX_VELOCITY", 	toString(getMaxVelocity()));
    key = sec->createKey("ACCELERATION", 	toString(getAcceleration()));
    key = sec->createKey("DWELL_TIME",   	toString(getDwellTime()));
}

bool SpatialMove::read(IniSection* sec)
{
	if(!sec)
	{
    	return false;
    }

	IniKey* key = sec->getKey("MOVE_TYPE");

    if(key)
    {
        mMoveType = toMoveType(key->mValue);;
    }

    key = sec->getKey("POSITION_NAME");
    if(key)
    {
        mPosition.setLabel(key->mValue);
    }

    key = sec->getKey("POSITION");
    if(key)
    {
	    mPosition = Position(mPosition.getLabel(), key->asFloat(), 0.0 , 0.0);
    }

    key = sec->getKey("MAX_VELOCITY", true);
    if(key)
    {
	    mMaxVelocity = key->asFloat();
    }

    key = sec->getKey("ACCELERATION", true);
    if(key)
    {
        mAcceleration = key->asFloat();
    }

    key = sec->getKey("DWELL_TIME", true);
    if (key)
    {
		mDwellTime = key->asFloat();
    }

    return true;
}

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


MoveType toMoveType(const string& mt)
{
	if(mt == "ABSOLUTE")
    {
    	return mtAbsolute;
    }

	if(mt == "RELATIVE")
    {
    	return mtRelative;
    }

    return mtUnknown;

}
