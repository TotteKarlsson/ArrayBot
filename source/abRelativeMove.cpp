#pragma hdrstop
#include "abRelativeMove.h"
#include "abXYZUnit.h"
//---------------------------------------------------------------------------

//RelativeMove::RelativeMove(ABObject* unit, Position& p)
//:
//Move(unit, p)
//{}
//
//bool RelativeMove::execute()
//{
//	XYZUnit* unit = dynamic_cast<XYZUnit*>(mUnit);
//    if(unit)
//    {
//		return unit->moveRelative(mPosition);
//    }
//
//    return false;
//}
//
//bool RelativeMove::undo()
//{
//	Position p("undo pos", mPosition.x() * -1, mPosition.y() * -1, mPosition.z() * -1);
//	XYZUnit* unit = dynamic_cast<XYZUnit*>(mUnit);
//    if(unit)
//    {
//		return unit->moveRelative(p);
//    }
//
//	return false;
//}
//

