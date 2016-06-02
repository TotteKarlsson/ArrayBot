#pragma hdrstop
#include "abArrayBot.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
//---------------------------------------------------------------------------

using namespace mtk;

ArrayBot::ArrayBot(IniFile& ini)
:
mIniFile(ini),
mCoverSlip("COVERSLIP UNIT", mIniFile),
mWhisker("WHISKER UNIT", mIniFile),
mJoyStick(),
mCoverSlipAngleController("COVERSLIP ANGLE CONTROLLER", mIniFile),
mCameraAngleController("CAMERA ANGLE CONTROLLER", mIniFile),
mCSLift("COVERSLIP LIFT"),
mIsShuttingDown(false),
mJSSettings("JOYSTICK SETTINGS", mIniFile),
mJS(14)
{
	mCSLift.readProperties(mIniFile);

    //Associate functions with events

    mJS.setButtonEvents(1, mJoyStick.getButton(1).down,  mJoyStick.getButton(1).up    );
    mJS.setButtonEvents(2, mJoyStick.getButton(2).down,  mJoyStick.getButton(2).up    );
    mJS.setButtonEvents(3, mJoyStick.getButton(3).down,  mJoyStick.getButton(3).up    );
    mJS.setButtonEvents(4, mJoyStick.getButton(4).down,  mJoyStick.getButton(4).up    );

    //    mJS.setButtonEvents(5, onButton5Down,  onButton5Up    );
//    mJS.setButtonEvents(6, onButton6Down,  onButton6Up    );
//    mJS.setButtonEvents(7, onButton7Down,  onButton7Up    );
//    mJS.setButtonEvents(8, onButton8Down,  onButton8Up    );
//    mJS.setButtonEvents(9, onButton9Down,  onButton9Up    );
//    mJS.setButtonEvents(10,onButton10Down, onButton10Up	  );
//    mJS.setButtonEvents(11,onButton11Down, onButton11Up	  );
//    mJS.setButtonEvents(12,onButton12Down, onButton12Up	  );
//    mJS.setButtonEvents(13,onButton13Down, onButton13Up	  );
//    mJS.setButtonEvents(14,onButton14Down, onButton14Up	  );
//
    mJS.setPOVButtonEvents(1, mJoyStick.getPOVButton(1).down,  mJoyStick.getPOVButton(1).up    );
    mJS.setPOVButtonEvents(2, mJoyStick.getPOVButton(2).down,  mJoyStick.getPOVButton(2).up    );
    mJS.setPOVButtonEvents(3, mJoyStick.getPOVButton(3).down,  mJoyStick.getPOVButton(3).up    );
    mJS.setPOVButtonEvents(4, mJoyStick.getPOVButton(4).down,  mJoyStick.getPOVButton(4).up    );

	mJS.setAxisEvent(1, mJoyStick.getX1Axis().Move);
	mJS.setAxisEvent(2, mJoyStick.getY1Axis().Move);

	mJS.setAxisEvent(3,  mJoyStick.getX2Axis().Move);
	mJS.setAxisEvent(4,  mJoyStick.getY2Axis().Move);

	//Start JS poll
    mJS.enable();
}

ArrayBot::~ArrayBot()
{}

bool ArrayBot::isActive()
{
	return mCoverSlip.isActive() || mWhisker.isActive() || mCoverSlipAngleController.isActive() || mCameraAngleController.isActive() ||     mJS.isEnabled();
}

bool ArrayBot::isShuttingDown()
{
	return mIsShuttingDown;
}

void ArrayBot::initialize()
{
	mCoverSlip.initialize();
	mWhisker.initialize();
    mCoverSlipAngleController.initialize();
    mCameraAngleController.initialize();
}

AngleController& ArrayBot::getCoverSlipAngleController()
{
	return mCoverSlipAngleController;
}

AngleController& ArrayBot::getCameraAngleController()
{
	return mCameraAngleController;
}

//Todo: setup mechanism to check if the units were shutdown properly
bool ArrayBot::shutDown()
{
    getJoyStick().disable();
    mJS.disable();
	mCoverSlipAngleController.shutDown();
	mCameraAngleController.shutDown();
	mCoverSlip.shutDown();
	mWhisker.shutDown();
	mCSLift.writeProperties();
	mIsShuttingDown = true;
    return true;
}

void ArrayBot::stopAll()
{
    mJoyStick.disable();
    mCoverSlip.stopAll();
    mWhisker.stopAll();
	mCoverSlipAngleController.stop();
}

bool ArrayBot::applyJoyStickSetting(const string& settingName)
{
	JoyStickSetting *s = mJSSettings.getSetting(settingName);
    if(!s)
    {
    	Log(lError) <<"No joystick setting with name: "<<settingName;
        return false;
    }

	vector<double> vals = s->get();
    Log(lDebug) << "New XY jog velocity (mm/s): " <<vals[0];
    Log(lDebug) << "New XY jog acceleration (mm/(s*s)): " <<vals[1];

    getJoyStick().getX1Axis().setMaxVelocity(vals[0]);
    getJoyStick().getY1Axis().setMaxVelocity(vals[0]);

    getJoyStick().getX2Axis().setMaxVelocity(vals[0]);
    getJoyStick().getY2Axis().setMaxVelocity(vals[0]);

    Log(lDebug) << "New Z jog velocity (mm/s): " <<vals[2];
    Log(lDebug) << "New Z jog acceleration (mm/(s*s)): " <<vals[3];

    if(getCoverSlipUnit().getXMotor() && getCoverSlipUnit().getYMotor())
    {
        getCoverSlipUnit().getXMotor()->setPotentiometerVelocity(vals[0]);
        getCoverSlipUnit().getYMotor()->setPotentiometerVelocity(vals[0]);

        getCoverSlipUnit().getXMotor()->setJogAcceleration(vals[1]);
        getCoverSlipUnit().getYMotor()->setJogAcceleration(vals[1]);
    }

    if(getWhiskerUnit().getXMotor() && getWhiskerUnit().getYMotor())
    {
        getWhiskerUnit().getXMotor()->setJogAcceleration(vals[1]);
        getWhiskerUnit().getYMotor()->setJogAcceleration(vals[1]);
    }

    if(getCoverSlipUnit().getZMotor())
    {
        getCoverSlipUnit().getZMotor()->setJogVelocity(vals[2]);
        getCoverSlipUnit().getZMotor()->setJogAcceleration(vals[3]);
    }

    if(getWhiskerUnit().getZMotor())
    {
        getWhiskerUnit().getZMotor()->setJogVelocity(vals[2]);
        getWhiskerUnit().getZMotor()->setJogAcceleration(vals[3]);
    }

	return true;
}

void ArrayBot::enableJoyStick()
{
 	//enable angle motor controls
    mCoverSlipAngleController.enableJoyStick(&getJoyStick());
    mCameraAngleController.enableJoyStick(&getJoyStick());

    mCoverSlip.enableJoyStick(&getJoyStick());
    mJoyStick.getX1Axis().setSenseOfDirection(1);

	mWhisker.enableJoyStick(&getJoyStick());
    mJoyStick.getX2Axis().setSenseOfDirection(-1);

    mJoyStick.enable();
}

void ArrayBot::disableJoyStick()
{
    mCoverSlip.disableJoyStick();
    mWhisker.disableJoyStick();
    mJoyStick.disable();
}

//void ArrayBot::assignWindowHandle(int handle)
//{
//	mJoyStick.setWindowHandle(handle);
//}

JoyStick& ArrayBot::getJoyStick()
{
	return mJoyStick;
}

void ArrayBot::home()
{
	mWhisker.home();
    mCoverSlip.home();
}

void ArrayBot::initWorkingPosition()
{
	//Tell Whisker and Cover slip units to go to
    //Working position
}

void ArrayBot::stow()
{
	mWhisker.stow();
    mCoverSlip.stow();
}

XYZUnit& ArrayBot::getCoverSlipUnit()
{
	return mCoverSlip;
}

XYZUnit& ArrayBot::getWhiskerUnit()
{
	return mWhisker;
}

//void ArrayBot::onButton1Down()
//{
//	Log(lDebug5) << "Button 1 was clicked";
//}
//
//void ArrayBot::onButton1Up()
//{
//	Log(lDebug5) << "Button 1 was released";
//}


//void ArrayBot::onButton2Up()
//{
//	Button2->Caption ="UP";
//}
//
//void ArrayBot::onButton2Down()
//{
//	Button2->Caption ="DOWN";
//}

//void ArrayBot::onButton3Up()
//{
//	Log(lDebug5) << "Button 3 was clicked";
//}
//
//void ArrayBot::onButton3Down()
//{
//	Log(lDebug5) << "Button 3 was released";
//}
//



