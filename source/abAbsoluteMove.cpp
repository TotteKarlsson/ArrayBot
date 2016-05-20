#pragma hdrstop
#include "abAbsoluteMove.h"
#include "abXYZUnit.h"
//---------------------------------------------------------------------------

//AbsoluteMove::AbsoluteMove(ABObject* unit, Position& p)
//:
//Move(unit, p)
//{}
//
//bool AbsoluteMove::execute()
//{
//	XYZUnit* unit = dynamic_cast<XYZUnit*>(mUnit);
//    if(unit)
//    {
//		return unit->moveAbsolute(mPosition);
//    }
//
//    return false;
//}
//
//bool AbsoluteMove::undo()
//{
//	Position p("undo pos", mPosition.x() * -1, mPosition.y() * -1, mPosition.z() * -1);
//
//	XYZUnit* unit = dynamic_cast<XYZUnit*>(mUnit);
//    if(unit)
//    {
//		return unit->moveAbsolute(p);
//    }
//
//	return false;
//}
//

