#ifndef abSMoveH
#define abSMoveH
#include "abExporter.h"
#include "abABObject.h"
#include "abPosition.h"
//---------------------------------------------------------------------------

////class XYZUnit;
//
/////The move baseclass contain the general logic for a move of
////a XYZ unit
class AB_CORE SMove : public ABObject
{
////    public:
////        				Move(ABObject* unit, Position& p);
////
////    	virtual			~Move(){}
////        virtual bool	execute() = 0;
////        virtual	bool	undo() = 0;
////
////    protected:
////    	ABObject* 		mUnit;
////
////        				//!The exact meaning of the position attribute is
////                        //made clear in derived classes
////        Position        mPosition;
};
//
#endif
