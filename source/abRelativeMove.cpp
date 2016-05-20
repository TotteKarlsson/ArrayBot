#pragma hdrstop
#include "abRelativeMove.h"
#include "abXYZUnit.h"
//---------------------------------------------------------------------------

RelativeMove::RelativeMove(XYZUnit* unit, Position& p)
:
Move(unit, p)
{}

bool RelativeMove::execute()
{
	return mUnit->moveRelative(mPosition);
}

bool RelativeMove::undo()
{
	Position p("undo pos", mPosition.x() * -1, mPosition.y() * -1, mPosition.z() * -1);
	return mUnit->moveRelative(p);
}


