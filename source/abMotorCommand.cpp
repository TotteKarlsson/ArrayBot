#pragma hdrstop
#include "abMotorCommand.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;
MotorCommand::MotorCommand(MotorCommandEnum mce, double v1, double v2)
:
mCommand(mce),
mVariable1(v1),
mVariable2(v2)
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

double MotorCommand::getFirstVariable() const
{
	return mVariable1;
}

double MotorCommand::getSecondVariable() const
{
	return mVariable2;
}

string MotorCommand::asString() const
{
	stringstream s;
    s<<toString(mCommand);
    switch(mCommand)
    {
        case mcNone:                    break;
        case mcStopHard:                break;
        case mcStopProfiled:            break;
        case mcForward:                 break;
        case mcReverse:                 break;
        case mcJogForward:              break;
        case mcJogReverse:              break;
        case mcMoveDistance:			s <<" : ("<<getFirstVariable()<<")"; break;
        case mcMoveToPosition:          s <<" : ("<<getFirstVariable()<<")"; break;
        case mcSetVelocity:         	s <<" : ("<<getFirstVariable()<<", "<<getSecondVariable()<<")"; break;
        case mcSetVelocityParameters:   s <<" : ("<<getFirstVariable()<<", "<<getSecondVariable()<<")"; break;
        case mcSetVelocityForward:      s <<" : ("<<getFirstVariable()<<")"; break;
        case mcSetVelocityReverse:      s <<" : ("<<getFirstVariable()<<")"; break;
    }

	return s.str();
}

string toString(MotorCommandEnum e)
{
	switch (e)
    {
        case mcNone:                    return "none";
        case mcStopHard:                return "stop hard";
        case mcStopProfiled:            return "stop profiled";
        case mcForward:                 return "forward";
        case mcReverse:                 return "reverse";
        case mcJogForward:              return "jog forward";
        case mcJogReverse:              return "jog reverse";
        case mcMoveDistance:            return "move distance";
        case mcMoveToPosition:        	return "move to position";
        case mcSetVelocity:         	return "set velocity";
        case mcSetVelocityParameters:   return "set velocity parameters";
        case mcSetVelocityForward:      return "set velocity forward";
        case mcSetVelocityReverse:      return "set velocity reverse";
    default:
    	return "Unknown command!";
    }
}
