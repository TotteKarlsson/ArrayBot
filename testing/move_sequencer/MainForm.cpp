#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "abAPTMotor.h"
#include "abDeviceManager.h"
#include "abMove.h"
#include "abPosition.h"
#include "abTCubeDCServo.h"
#include "abUtilities.h"
#include "mtkLogger.h"
#include "mtkMathUtils.h"
#include "mtkStringList.h"
#include "mtkVCLUtils.h"
#include "TMemoLogger.h"
#include <bitset>
#include "TMoveSequencerFrame.h"
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
extern string gAppDataFolder;

using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
	TRegistryForm("Test", "MainForm", Owner),
	logMsgMethod(&logMsg),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), logMsgMethod),
    mIniFile(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", "move_sequencer.ini"), true, true), //Means we are reading ini paras on startup
    mXYZUnit("MyUnit", mIniFile),
    mMoveSequencer()
{
	TMemoLogger::mMemoIsEnabled = false;
	mXYZUnit.initialize();
	//Setup UI properties
    mProperties.setSection("UI");
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

	//Creates frames for each motor
    createMotorFrame(mXYZUnit.getXMotor());
    createMotorFrame(mXYZUnit.getYMotor());
    createMotorFrame(mXYZUnit.getZMotor());

	//Initialize UI
    TMoveSequencerFrame* sf = new TMoveSequencerFrame(&mXYZUnit, ScrollBox2);
    sf->Parent = ScrollBox2;
    sf->Align = alLeft;
}

bool TMain::createMotorFrame(APTMotor* mtr)
{
	if(!mtr)
    {
    	return false;
    }
    TMotorFrame *f = new TMotorFrame(mtr->getName(), ScrollBox1);
   	f->assignMotor(mtr);
    f->Parent = ScrollBox1;
    f->Align = alTop;
    return true;
}

void __fastcall TMain::ShutDownAExecute(TObject *Sender)
{
	StatusTimer->Enabled = false;
}


