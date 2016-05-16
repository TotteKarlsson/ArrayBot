#ifndef abMotorCommandH
#define abMotorCommandH
#include "abExporter.h"
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
    mcSetVelocity,
	mcSetVelocityForward,
	mcSetVelocityReverse,
    mcSetAcceleration,
    mcSwitchDirection,
    mcMoveDistance,
    mcMoveToPosition
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
