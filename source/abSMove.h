#ifndef abSMoveH
#define abSMoveH
#include "abExporter.h"
#include "abABObject.h"
#include "abPosition.h"
//---------------------------------------------------------------------------

//!The move baseclass contain the general logic for a 'move' of
//any type of object
class AB_CORE SMove : public ABObject
{
    public:
        				SMove(ABObject* unit, Position& p);

    	virtual			~SMove(){}
        virtual bool	execute() = 0;
        virtual	bool	undo() = 0;

    protected:
    					//!Making object for moving abstract allow us
                        //to move 'any' object. Just specialize in the
                        //execute function..
    	ABObject* 		mUnit;

        				//!The exact meaning of the position attribute is
                        //made clear in derived classes
        Position        mPosition;
};

#endif
