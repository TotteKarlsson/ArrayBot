#ifndef abMotorCommandH
#define abMotorCommandH
#include "CoreExporter.h"
#include "abABObject.h"
#include <string>
#include <ostream>

using std::ostream;
using std::string;

//---------------------------------------------------------------------------
enum MotorCommandEnum
{
	mcNone = -1,
	mcStopHard = 0,
    mcStopProfiled,
    mcForward,
    mcReverse,
    mcJogForward,
    mcJogReverse,
    mcMoveDistance,
    mcSetVelocity,
	mcSetVelocityForward,
	mcSetVelocityReverse,
    mcSetAcceleration,
    mcSwitchDirection
};

string toString(MotorCommandEnum e);

class AB_CORE MotorCommand : public ABObject
{
	public:
							MotorCommand(MotorCommandEnum mce, double var=0);
                        	~MotorCommand();

		string				asString() const;
        MotorCommandEnum	getCore();
        double				getFirstVariable();

	AB_CORE
 	friend ostream&         operator<<(ostream& stream, const MotorCommand& cmd);

    protected:
		MotorCommandEnum	mCommand;
    	double				mVariable;


};
#endif
