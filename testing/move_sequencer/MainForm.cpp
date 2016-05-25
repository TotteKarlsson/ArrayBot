#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "abAPTMotor.h"
#include "abDeviceManager.h"
#include "abLinearMove.h"
#include "abPosition.h"
#include "abTCubeDCServo.h"
#include "abUtilities.h"
#include "mtkLogger.h"
#include "mtkMathUtils.h"
#include "mtkStringList.h"
#include "mtkVCLUtils.h"
#include "TMemoLogger.h"
#include <bitset>
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
    mIniFile("move_sequencer.ini", true, true), //Means we are reading ini paras on startup
    mXYZUnit("MyUnit", mIniFile)
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
    //Fill out sequencer frame
	if(mXYZUnit.getXMotor())
    {
    	MotorsCB->Items->InsertObject(MotorsCB->Items->Count, mXYZUnit.getXMotor()->getName().c_str(), (TObject*) mXYZUnit.getXMotor() );
    }

	if(mXYZUnit.getYMotor())
    {
    	MotorsCB->Items->InsertObject(MotorsCB->Items->Count, mXYZUnit.getYMotor()->getName().c_str(), (TObject*) mXYZUnit.getYMotor() );
    }

	if(mXYZUnit.getZMotor())
    {
    	MotorsCB->Items->InsertObject(MotorsCB->Items->Count, mXYZUnit.getZMotor()->getName().c_str(), (TObject*) mXYZUnit.getZMotor() );
    }


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
	if(MotorsCB->ItemIndex == -1)
    {
    	Log(lError) << "No motor is selected. can't create move";
    	return;
    }

    APTMotor* motor = (APTMotor*) MotorsCB->Items->Objects[MotorsCB->ItemIndex];
    if(!motor)
    {
    	Log(lError) << "No motor is selected. can't create move";
    	return;
    }

	LinearMove *move = new LinearMove("", motor, mtAbsolute, pos);

    mMoveSequencer.addProcess(move);

    //Update LB
    if(move->getPositionName() == "")
    {
    	string lbl = "MOVE " + mtk::toString(mMovesLB->Count + 1);
        move->setPositionName(lbl);
    }
    mMovesLB->Items->AddObject(move->getPositionName().c_str(), (TObject*) move);
}

//---------------------------------------------------------------------------
void __fastcall TMain::mStartBtnClick(TObject *Sender)
{
	TButton* btn = (TButton*)Sender;
    if(btn==mStartBtn)
    {
		mMoveSequencer.start(true);
    }
    else if(btn==mFwdBtn)
    {
    	mMoveSequencer.forward();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mSaveSequenceBtnClick(TObject *Sender)
{
	//Save Current Sequence
    mMoveSequencer.save();
}

//---------------------------------------------------------------------------
void __fastcall TMain::SequencesCBChange(TObject *Sender)
{
	//Load the sequence
    int index = SequencesCB->ItemIndex;
    if(index == -1)
    {
    	return;
    }
    string fName(stdstr(SequencesCB->Items->Strings[index]) + ".moves");

	if(mMoveSequencer.load(fName))
    {
    	//Fill out listbox
		ProcessSequence& seq = mMoveSequencer.getSequence();

        Process* move = seq.getFirst();
        while(move)
        {
    		mMovesLB->Items->AddObject(move->getLabel().c_str(), (TObject*) move);
            move = seq.getNext();
        }
    }

    mMoveSequencer.assignUnit(&mXYZUnit);
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

    LinearMove* move = (LinearMove*) mMovesLB->Items->Objects[i];

    if(move)
    {
    	mMovePosE->setValue(move->getPosition().x());
        mMaxVelE->setValue(move->getMaxVelocity());
        mAccE->setValue(move->getAcceleration());
        mDwellTimeE->setValue(move->getDwellTime());

        APTMotor* mtr = dynamic_cast<APTMotor*>(move->getUnit());
        if(mtr)
        {
        	int idx = MotorsCB->Items->IndexOf(mtr->getName().c_str());
			MotorsCB->ItemIndex = idx;
        }
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

    LinearMove* move = (LinearMove*) mMovesLB->Items->Objects[i];
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



//---------------------------------------------------------------------------
void __fastcall TMain::MotorsCBChange(TObject *Sender)
{
	//Check if a motor is selected
    APTMotor* motor = (APTMotor*) MotorsCB->Items->Objects[MotorsCB->ItemIndex];
    if(motor)
    {
    	mMovePosE->Enabled = true;
        mAccE->Enabled = true;
    }
    else
    {
    	mMovePosE->Enabled = false;
        mAccE->Enabled = false;
    }
}


