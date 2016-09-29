#ifndef abRelativeMoveH
#define abRelativeMoveH
#include "abExporter.h"
#include "abABObject.h"
#include "abMove.h"
//---------------------------------------------------------------------------
class APTMotor;

class AB_CORE RelativeMove : public ab::Move
{
    public:
    								RelativeMove( const string& lbl, APTMotor* mtr = NULL, double pos = 0, double maxVel = 1, double acc = 1);
									~RelativeMove(){}
		const string 				getTypeName() const;


    protected:

    private:

};
#endif
