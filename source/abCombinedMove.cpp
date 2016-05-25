#pragma hdrstop
#include "abCombinedMove.h"
#include "mtkBaseProperty.h"
#include "mtkMathUtils.h"
//---------------------------------------------------------------------------

using namespace mtk;

CombinedMove::CombinedMove(const string& name)
:
mVerticalDistance(0),
mVerticalVelocity(0),
mVerticalAcceleration(0),
mAngle(0)
{
    mProperties.setSection(name);
    mProperties.add((BaseProperty*) &mVerticalDistance.setup("VERTICAL_DISTANCE", 			0, true));
    mProperties.add((BaseProperty*) &mVerticalVelocity.setup("VERTICAL_VELOCITY", 			0, true));
    mProperties.add((BaseProperty*) &mVerticalAcceleration.setup("VERTICAL_ACCELERATION", 		0, true));
    mProperties.add((BaseProperty*) &mAngle.setup("ANGLE", 						0, true));
}

CombinedMove::~CombinedMove()
{}

bool CombinedMove::readProperties(IniFile& i)
{
	mProperties.setIniFile(&i);
    return mProperties.read();
}

bool CombinedMove::writeProperties()
{
	return mProperties.write();
}

double CombinedMove::getHorizontalDistance()
{
	return mHorizontalDistance;
}

double CombinedMove::getHorizontalAcceleration()
{
	return mHorizontalAcceleration;
}

void CombinedMove::calculate()
{
	//Move parameters are calculated from vertical distance, angle and acceleration
    double tanTheta = tan(toRadians(mAngle));

	mHorizontalVelocity 	= mVerticalVelocity / tanTheta;
	mHorizontalAcceleration = mVerticalAcceleration / tanTheta;

}

