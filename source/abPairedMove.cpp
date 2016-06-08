#pragma hdrstop
#include "abPairedMove.h"
#include "mtkBaseProperty.h"
#include "mtkMathUtils.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"

//---------------------------------------------------------------------------
using namespace mtk;

PairedMove::PairedMove(const string& name, double d, double v, double a)
:
mDistance(d),
mVelocity(v),
mAcceleration(a),
mLabel(name)
{
}

PairedMove::~PairedMove()
{}

string PairedMove::asIniRecord()
{
	stringstream s;
    s << mDistance << "," << mVelocity << ", "<< mAcceleration;
	return s.str();
}

void PairedMove::assignMotor1(APTMotor* motor)
{
	mMotor1 = motor;
}

void PairedMove::assignMotor2(APTMotor* motor)
{
	mMotor2 = motor;
}

bool PairedMove::check()
{
	if(!mMotor1 || !mMotor2)
    {
        mCheckMessage = "Motors are not assigned for the Paired move";
        return false;
    }

    if(mVelocity == 0 || mAcceleration == 0 || mDistance == 0)
    {
        mCheckMessage = "Velocity, acceleration and vertical distance need all to be non zero";
    	Log(lError) << mCheckMessage;
        return false;
    }
    //get current positions and carry out some moveTo's
	double newZ1Pos = mMotor1->getPosition() + mDistance;
	double newZ2Pos = mMotor2->getPosition() + mDistance;

    if(newZ1Pos > 25)
    {
    	stringstream s;
        s << "New position ("<<newZ2Pos<<") to big for motor with label: \""<<mMotor1->getName()<<"\"\rMax position is 25.0 mm";
    	Log(lError) << s.str();
        mCheckMessage = s.str();
        return false;
    }

    if(newZ2Pos > 25)
    {
    	stringstream s;
        s << "New position ("<<newZ2Pos<<") to big for motor with label: \""<<mMotor2->getName()<<"\"\rMax position is 25.0 mm";
    	Log(lError) << s.str();
        mCheckMessage = s.str();
        return false;
    }
}

bool PairedMove::execute()
{
	if(!check())
    {
    	return false;
    }

    //get current positions and carry out some moveTo's
	double newZ1Pos = mMotor1->getPosition() + mDistance;
	double newZ2Pos = mMotor2->getPosition() + mDistance;

	//Update motors with current parameters and start the move
    mMotor1->setJogVelocity(mVelocity);
    mMotor2->setJogAcceleration(mAcceleration);

    mMotor1->setJogVelocity(mVelocity);
    mMotor2->setJogAcceleration(mAcceleration);

    Log(lInfo) << "Moving Motor 1 to: "	<<newZ1Pos;
    Log(lInfo) << "Moving Motor 2 to: "	<<newZ2Pos;

	//Initiate the move
    mMotor1->moveAbsolute(newZ1Pos);
    mMotor2->moveAbsolute(newZ2Pos);
	return true;
}


string PairedMove::getCheckMessage()
{
	return mCheckMessage;
}

