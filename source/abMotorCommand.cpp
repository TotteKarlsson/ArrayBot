#pragma hdrstop
#include "abMotorCommand.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;
MotorCommand::MotorCommand(MotorCommandEnum mce, double var)
:
mCommand(mce),
mVariable(var)
{
}

MotorCommand::~MotorCommand()
{}

ostream& operator<<(ostream& stream, const MotorCommand& cmd)
{
	stream << cmd.asString();
    return stream;
}

MotorCommandEnum MotorCommand::getCore()
{
	return mCommand;
}

double MotorCommand::getFirstVariable()
{
	return mVariable;
}

string MotorCommand::asString() const
{
	stringstream s;
    s<<toString(mCommand);
	return s.str();
}

string toString(MotorCommandEnum e)
{
	switch (e)
    {
        case mcNone:
        return "none";

        case mcStopHard:
        return "stop hard";

        case mcStopProfiled:
        return "stop profiled";

        case mcForward:
        return "forward";

        case mcReverse:
        return "reverse";

        case mcJogForward:
        return "jog forward";

        case mcJogReverse:
        return "jog reverse";

        case mcMoveDistance:
        return "move distance";

        case mcMoveToPosition:
        return "move to position";

        case mcSetVelocity:
        return "set velocity";

        case mcSetVelocityForward:
        return "set velocity forward";

        case mcSetVelocityReverse:
        return "set velocity reverse";
    default:
    	return "Unknown command!";
    }
}
