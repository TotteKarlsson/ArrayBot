#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "TMemoLogger.h"
#include "mtkStringList.h"
#include "abUtilities.h"
#include "abAPTMotor.h"
#include "abTCubeDCServo.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
#include <bitset>
#include "mtkMathUtils.h"
#include "abDeviceManager.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "abXYZUnitFrame"
#pragma link "abMotorFrame"
#pragma resource "*.dfm"
TMain *Main;

extern string gLogFileLocation;
extern string gLogFileName;

using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
	TRegistryForm("Test", "MainForm", Owner),
	logMsgMethod(&logMsg),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), logMsgMethod),
    mBottomPanelHeight(100),
    mBottomPanelVisible(true),
    mTopPanelHeight(360),
    mIniFile("ArrayBot.ini", true, true)
{
	TMemoLogger::mMemoIsEnabled = false;

    mManager.connectAllDevices();

    APTDevice* d = mManager.getFirst();
    if(d)
    {
    	mMotor = dynamic_cast<APTMotor*>(d);
    }
	//Setup UI properties
    mProperties.setSection("UI");
    mProperties.add((BaseProperty*) &mBottomPanelHeight.setup("BOTTOM_PANEL_HEIGHT", 			100, true));
    mProperties.add((BaseProperty*) &mTopPanelHeight.setup("TOP_PANEL_HEIGHT", 					360, true));
    mProperties.add((BaseProperty*) &mBottomPanelVisible.setup("BOTTOM_PANEL_VISIBLE",			true, true));
	mProperties.setIniFile(&mIniFile);
    mProperties.read();
}

__fastcall TMain::~TMain()
{
	mProperties.write();
    mIniFile.save();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender)
{
	TMemoLogger::mMemoIsEnabled = true;
	mLogFileReader.start(true);

	if(mMotor)
    {
    	TMotorFrame1->assignMotor(mMotor);
    }

	//Initialize UI
}
void __fastcall TMain::ShutDownAExecute(TObject *Sender)
{
	StatusTimer->Enabled = false;

}
void __fastcall TMain::mCSAngleEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key != vkReturn)
    {
    	return;
    }
}


