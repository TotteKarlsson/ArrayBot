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
#include "abPosition.h"
#include "abSpatialMove.h"

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
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "move_sequencer", gLogFileName), logMsgMethod),
    mBottomPanelHeight(100),
    mBottomPanelVisible(true),
    mTopPanelHeight(360),
    mIniFile("move_sequencer.ini", true, true), //Means we are reading ini paras on startup
    mXYZUnit("MyUnit", mIniFile)
{
	TMemoLogger::mMemoIsEnabled = false;

//    mManager.connectAllDevices();
	mXYZUnit.initialize();
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

	//Creates frames for each motor
    createMotorFrame(mXYZUnit.getXMotor());
    createMotorFrame(mXYZUnit.getYMotor());
    createMotorFrame(mXYZUnit.getZMotor());

	//Initialize UI
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

//---------------------------------------------------------------------------
void __fastcall TMain::mAddMoveBtnClick(TObject *Sender)
{
	//Create and add a move to the sequencer
    ab::Position pos("", 0.0, 0.0, 0.0);
//	SpatialMove *move = new SpatialMove("", mMotor, mtAbsolute, pos);
//
//    mProcessSequencer.addProcess(move);
//
//    //Update LB
//    if(move->getPositionName() == "")
//    {
//    	string lbl = "Pos: " + mtk::toString(mMovesLB->Count + 1);
//        move->setPositionName(lbl);
//    }
//    mMovesLB->Items->AddObject(move->getPositionName().c_str(), (TObject*) move);
}

//---------------------------------------------------------------------------
void __fastcall TMain::mStartBtnClick(TObject *Sender)
{
	TButton* btn = (TButton*)Sender;
    if(btn==mStartBtn)
    {
		mProcessSequencer.start(true);
		seqtimer->Enabled = true;
    }
    else if(btn==mFwdBtn)
    {
    	mProcessSequencer.forward();
		seqtimer->Enabled = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::seqtimerTimer(TObject *Sender)
{
	//Check what the sequencer is doing
	if(mProcessSequencer.isRunning())
    {
    	runLbl->Caption = "Is Running";
    }
    else
    {
      	runLbl->Caption = "Idle";
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mSaveSequenceBtnClick(TObject *Sender)
{
	//Save Current Sequence
    mProcessSequencer.save();
}

//---------------------------------------------------------------------------
void __fastcall TMain::SequencesCBChange(TObject *Sender)
{
//	//Load the sequence
//    int index = SequencesCB->ItemIndex;
//    if(index == -1)
//    {
//    	return;
//    }
//    string fName(stdstr(SequencesCB->Items->Strings[index]) + ".moves");
//
//	if(mProcessSequencer.load(fName))
//    {
//    	//Fill out listbox
//		ProcessSequence& seq = mProcessSequencer.getSequence();
//
//        Process* move = seq.getFirst();
//        while(move)
//        {
//    		mMovesLB->Items->AddObject(move->getLabel().c_str(), (TObject*) move);
//            move = seq.getNext();
//        }
//    }
//    mProcessSequencer.assignUnit(mMotor);
}

//---------------------------------------------------------------------------
void __fastcall TMain::mMovesLBClick(TObject *Sender)
{
	//Retrieve current move and populate UI
    int i = mMovesLB->ItemIndex;
    if(i == -1)
    {
    	return;
    }

    SpatialMove* move = (SpatialMove*) mMovesLB->Items->Objects[i];

    if(move)
    {
    	mMovePosE->setValue(move->getPosition().x());
        mMaxVelE->setValue(move->getMaxVelocity());
        mAccE->setValue(move->getAcceleration());
        mDwellTimeE->setValue(move->getDwellTime());
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::moveParEdit(TObject *Sender, WORD &Key, TShiftState Shift)
{
    int i = mMovesLB->ItemIndex;
    if(i == -1 || Key != vkReturn)
    {
    	return;
    }

    SpatialMove* move = (SpatialMove*) mMovesLB->Items->Objects[i];
	TFloatLabeledEdit* e = dynamic_cast<TFloatLabeledEdit*>(Sender);

//    if(e == mMovePosE)
    {
    	ab::Position p(move->getPositionName(), mMovePosE->getValue(),0,0);
		move->setPosition(p);
    }

//    if(e == mMaxVelE)
    {
		move->setMaxVelocity(mMaxVelE->getValue());
    }

//    if(e == mAccE)
    {
		move->setAcceleration(mAccE->getValue());
    }

//    if(e == mDwellTimeE)
    {
		move->setDwellTime(mDwellTimeE->getValue());
    }

}

void __fastcall TMain::stopAllAExecute(TObject *Sender)
{
;
}


