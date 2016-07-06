#pragma hdrstop
#include "abRibbonLifter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

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
mWhiskerLiftOffZPosition(0),
mWhiskerLiftStowXPosition(0)
{
	//Read parameters from the ini file
    mProperties.add((BaseProperty*) &mLiftLocationX.setup(		    "LIFT_LOCATION_X", 					    0));
    mProperties.add((BaseProperty*) &mLiftLocationY.setup(		    "LIFT_LOCATION_Y", 					    0));

    mProperties.add((BaseProperty*) &mMoveToLLVelocity.setup(	    "MOVE_TO_LIFT_LOCATION_VELOCITY", 	    0));
    mProperties.add((BaseProperty*) &mMoveToLLAcc.setup(		    "MOVE_TO_LIFT_LOCATION_ACC", 		    0));

    mProperties.add((BaseProperty*) &mLiftVelocityZ.setup(		    "LIFT_VELOCITY_Z", 					    0));
    mProperties.add((BaseProperty*) &mLiftAccZ.setup(			    "LIFT_ACCELERATION_Z", 				    0));

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

bool RibbonLifter::start()
{
}

bool RibbonLifter::stop()
{

}

void RibbonLifter::onTimer()
{

}
