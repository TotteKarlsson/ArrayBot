#ifndef atMotorCommandH
#define atMotorCommandH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include <string>
#include <ostream>

using std::ostream;
using std::string;

//---------------------------------------------------------------------------

namespace at
{
    enum MotorCommandEnum
    {
    	mcNone = -1,
    	mcStopHard = 0,
        mcStopProfiled,
        mcForward,
        mcReverse,
        mcJogForward,
        mcJogReverse,
        mcSetVelocity,
        mcSetVelocityParameters,
    	mcSetVelocityForward,
    	mcSetVelocityReverse,
        mcSetAcceleration,
        mcSwitchDirection,
        mcMoveDistance,
        mcMoveToPosition,
        mcHome
    };

    string toString(MotorCommandEnum e);

    class AT_AB MotorCommand : public ATObject
    {
    	public:
    							MotorCommand(MotorCommandEnum mce, double var1 = 0, double var2 = 0);
                            	~MotorCommand();

    		string				asString() const;
            MotorCommandEnum	getCore() const;
            double				getFirstVariable() const;
            double				getSecondVariable() const;

    		AT_AB
     		friend ostream&     operator<<(ostream& stream, const MotorCommand& cmd);

        protected:
    		MotorCommandEnum	mCommand;
        	double				mVariable1;
        	double				mVariable2;
    };

}
#endif
