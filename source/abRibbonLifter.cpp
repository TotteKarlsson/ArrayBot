#pragma hdrstop
#include "abRibbonLifter.h"
#include "abAPTMotor.h"
#include "abAbsoluteMove.h"
//---------------------------------------------------------------------------


RibbonLifter::RibbonLifter(ArrayBot& ab, IniFile& ini)
:
mIniFile(ini),
mProperties(&ini, "RIBBON_LIFTER"),
mArrayBot(ab),
mLiftLocationX(0),
mLiftLocationY(0),
mMoveToLLVelocity(0),
mMoveToLLAcc(0),
mLiftVelocityZ(0),
mLiftAccZ(0),
mLiftVelocityY(0),
mLiftAccY(0),
mLiftDistanceCS(0),
mWhiskerLiftOffZPosition(0),
mWhiskerLiftStowXPosition(0),
mMove1("RibbonLifterMove1"),
mMove2("RibbonLifterMove2"),
mSequencer(ab, ""),
mLiftSequence(ab),
mProcessTimer(Poco::Timespan(100*Poco::Timespan::MILLISECONDS))

{
	//Read parameters from the ini file
    mProperties.add((BaseProperty*) &mLiftLocationX.setup(		    "LIFT_LOCATION_X", 					    0));
    mProperties.add((BaseProperty*) &mLiftLocationY.setup(		    "LIFT_LOCATION_Y", 					    0));

    mProperties.add((BaseProperty*) &mMoveToLLVelocity.setup(	    "MOVE_TO_LIFT_LOCATION_VELOCITY", 	    0));
    mProperties.add((BaseProperty*) &mMoveToLLAcc.setup(		    "MOVE_TO_LIFT_LOCATION_ACC", 		    0));

    mProperties.add((BaseProperty*) &mLiftVelocityZ.setup(		    "LIFT_VELOCITY_Z", 					    0));
    mProperties.add((BaseProperty*) &mLiftAccZ.setup(			    "LIFT_ACCELERATION_Z", 				    0));
    mProperties.add((BaseProperty*) &mLiftDistanceCS.setup(		    "LIFT_DISTANCE_COVERSLIP",			    0));

    mProperties.add((BaseProperty*) &mLiftVelocityY.setup(			"LIFT_VELOCITY_Y", 					    0));
    mProperties.add((BaseProperty*) &mLiftAccY.setup(				"LIFT_ACCELERATION_Y", 				    0));

    mProperties.add((BaseProperty*) &mWhiskerLiftOffZPosition.setup("WHISKER_LIFT_OFF_Z_POS",				0));
    mProperties.add((BaseProperty*) &mWhiskerLiftStowXPosition.setup("WHISKER_LIFT_STOW_X_POS",    			0));

    //Assumes that the inifile is already loaded
    mProperties.read();

	mProcessTimer.assignTimerFunction(onTimer);
}

RibbonLifter::~RibbonLifter()
{
    mProperties.write();
}

bool RibbonLifter::isRunning()
{
	return mSequencer.isRunning();
}

bool RibbonLifter::setupMove1()
{
	mMove1.clear();
    mLiftSequence.clear();

	//Scale these velocities
	AbsoluteMove* xMove = new AbsoluteMove("xMove1", ab::Position("middle_x", mLiftLocationX, 0, 0),  	mMoveToLLVelocity, mMoveToLLAcc);
	AbsoluteMove* yMove = new AbsoluteMove("yMove1", ab::Position("middle_y", mLiftLocationY, 0, 0), mMoveToLLVelocity, mMoveToLLAcc);

    xMove->assignUnit(mArrayBot.getWhiskerUnit().getXMotor());
    yMove->assignUnit(mArrayBot.getWhiskerUnit().getYMotor());

	mMove1.addMove(xMove);
	mMove1.addMove(yMove);

    mLiftSequence.add(&mMove1);
    mSequencer.addSequence(&mLiftSequence);
    return true;
}

bool RibbonLifter::executeMove1()
{
	mProcessTimer.start();
	mArrayBot.disableJoyStickAxes();
	mSequencer.start();
    return true;
}

bool RibbonLifter::setupMove2()
{
	mMove2.clear();
    mLiftSequence.clear();

//	//Scale these velocities
//	ab::Move whiskerZMove("xMove1", ab::mtAbsolute, ab::Position("middle_x", mLiftLocationX, 0, 0),  	mMoveToLLVelocity, mMoveToLLAcc);
//	ab::Move yMove("yMove1", ab::mtAbsolute, ab::Position("middle_y", mLiftLocationY/2., 0, 0), mMoveToLLVelocity, mMoveToLLAcc);
//
//    xMove.assignUnit(mArrayBot.getWhiskerUnit().getXMotor());
//    yMove.assignUnit(mArrayBot.getWhiskerUnit().getYMotor());
//
//	mMove1.addMove(xMove);
//	mMove1.addMove(yMove);
//
//    mLiftSequence.add(&mMove1);
//    mSequencer.addSequence(&mLiftSequence);
    return true;
}

bool RibbonLifter::executeMove2()
{
	mProcessTimer.start();
	mArrayBot.disableJoyStickAxes();
	mSequencer.start();
    return true;
}

bool RibbonLifter::start()
{
	return true;
}

bool RibbonLifter::stop()
{
	mSequencer.stop();
    return true;
}

void RibbonLifter::onTimer()
{
	if(!isRunning())
    {
	    mProcessTimer.stop();
		mArrayBot.enableJoyStickAxes();
    }
}
