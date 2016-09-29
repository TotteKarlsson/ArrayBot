#pragma hdrstop
#include "abJoyStickSetting.h"
#include <sstream>
//---------------------------------------------------------------------------
using namespace std;

JoyStickSetting::JoyStickSetting(const string& lbl, double maxXYVel, double xyAcc, double maxZVel, double zAcc, double angleVel, double angleAcc)
:
mLabel(lbl),
mXYVelocity(maxXYVel),
mXYAcceleration(xyAcc),
mZVelocity(maxZVel),
mZAcceleration(zAcc),
mAngleControllerVelocity(angleVel),
mAngleControllerAccleration(angleAcc)
{}

JoyStickSetting::~JoyStickSetting()
{}

vector<double> JoyStickSetting::get()
{
	vector<double> s(6);
    s[0] = mXYVelocity;
    s[1] = mXYAcceleration;
    s[2] = mZVelocity;
    s[3] = mZAcceleration;
    s[4] = mAngleControllerVelocity;
    s[5] = mAngleControllerAccleration;
    return s;
}

void JoyStickSetting::set(double maxXYVel, double xyAcc, double maxZVel, double zAcc, double angleVelocity, double angleAcc)
{
    mXYVelocity 	= maxXYVel;
    mXYAcceleration = xyAcc;
    mZVelocity 		= maxZVel;
    mZAcceleration 	= zAcc;
	mAngleControllerVelocity = angleVelocity;
    mAngleControllerAccleration = angleAcc;
}

string	JoyStickSetting::asIniRecord()
{
	stringstream s;
    s<<mXYVelocity << "," << mXYAcceleration<<","<<
       mZVelocity  << "," << mZAcceleration<<","<<
       mAngleControllerVelocity<< "," << mAngleControllerAccleration;
	return s.str();
}

