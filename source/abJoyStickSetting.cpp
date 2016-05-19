#pragma hdrstop
#include "abJoyStickSetting.h"
//---------------------------------------------------------------------------

JoyStickSetting::JoyStickSetting(const string& lbl, double maxXYVel, double xyAcc, double maxZVel, double zAcc)
:
mLabel(lbl),
mMaxXYVelocity(maxXYVel),
mXYAcceleration(xyAcc),
mMaxZVelocity(maxZVel),
mZAcceleration(zAcc)
{}

JoyStickSetting::~JoyStickSetting()
{}

vector<double> JoyStickSetting::get()
{
	vector<double> s(4);
    s[0] = mMaxXYVelocity;
    s[1] = mXYAcceleration;
    s[2] = mMaxZVelocity;
    s[3] = mZAcceleration;
    return s;
}

void JoyStickSetting::set(double maxXYVel, double xyAcc, double maxZVel, double zAcc)
{
    mMaxXYVelocity = maxXYVel;
    mXYAcceleration = xyAcc;
    mMaxZVelocity = maxZVel;
    mZAcceleration = zAcc;
}

