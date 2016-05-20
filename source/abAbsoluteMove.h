#ifndef abAbsoluteMoveH
#define abAbsoluteMoveH
#include "abExporter.h"
#include "abABObject.h"
#include "abSMove.h"
//---------------------------------------------------------------------------

class AB_CORE AbsoluteMove : public SMove
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
