#ifndef abAbsoluteMoveH
#define abAbsoluteMoveH
#include "abExporter.h"
#include "abABObject.h"
#include "abSpatialMove.h"
//---------------------------------------------------------------------------

class AB_CORE AbsoluteMove : public SpatialMove
{
    public:
        				AbsoluteMove(ABObject* unit, const ab::Position& p);
        				~AbsoluteMove(){}
        virtual string	getType(){return "ABSOLUTE";}
        virtual bool	isActive();
        virtual bool	achievedPosition();
        bool			execute();
        bool			undo();

    protected:

    private:

};
#endif
