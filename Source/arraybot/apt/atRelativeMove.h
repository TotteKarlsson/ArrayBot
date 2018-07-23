#ifndef atRelativeMoveH
#define atRelativeMoveH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include "atMove.h"
//---------------------------------------------------------------------------
class APTMotor;

namespace at
{
    class AT_AB RelativeMove : public at::Move
    {
        public:
        								RelativeMove( const string& lbl, APTMotor* mtr = NULL, double pos = 0, double maxVel = 1, double acc = 1);
    									~RelativeMove(){}
    		const string 				getTypeName() const;


        protected:

        private:

    };
}
#endif
