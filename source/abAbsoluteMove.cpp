#pragma hdrstop
#include "abAbsoluteMove.h"
#include "abXYZUnit.h"
//---------------------------------------------------------------------------

AbsoluteMove::AbsoluteMove(XYZUnit* unit, Position& p)
:
Move(unit, p)
{}

bool AbsoluteMove::execute()
{
	return mUnit->moveRelative(mPosition);
}

bool AbsoluteMove::undo()
{
	Position p("undo pos", mPosition.x() * -1, mPosition.y() * -1, mPosition.z() * -1);
	return mUnit->moveRelative(p);
}


