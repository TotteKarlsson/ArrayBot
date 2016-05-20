#ifndef abAbsoluteMoveH
#define abAbsoluteMoveH
#include "abExporter.h"
#include "abABObject.h"
#include "abMove.h"
//---------------------------------------------------------------------------

class AB_CORE AbsoluteMove : public Move
{
    public:
        				AbsoluteMove(XYZUnit* unit, Position& p);
        				~AbsoluteMove(){}

        bool			execute();
        bool			undo();

    protected:

    private:

};
#endif
