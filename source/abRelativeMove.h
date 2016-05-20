#ifndef abRelativeMoveH
#define abRelativeMoveH
//---------------------------------------------------------------------------
#include "abExporter.h"
#include "abABObject.h"
#include "abMove.h"
//---------------------------------------------------------------------------

///A relative move moves the XYZ unit relative to its current position

class AB_CORE RelativeMove : public Move
{
    public:
        				RelativeMove(XYZUnit* unit, Position& p);
        				~RelativeMove(){}
        bool			execute();
        bool			undo();


    protected:

    private:

};
#endif
