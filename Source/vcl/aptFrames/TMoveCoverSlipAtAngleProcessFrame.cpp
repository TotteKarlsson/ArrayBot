#include <vcl.h>
#pragma hdrstop
#include "TMoveCoverSlipAtAngleProcessFrame.h"
#include "TPositionalTriggerFrame.h"
#include "arraybot/apt/atMove.h"
#include "arraybot/apt/atAPTMotor.h"
#include "dslVCLUtils.h"
#include "arraybot/atXYZUnit.h"
#include "arraybot/atArrayBot.h"
#include "arraybot/process/atMoveCoverSlipAtAngleProcess.h"
#include "arraybot/process/atTriggerFunction.h"
#include "vcl/forms/TTextInputDialog.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma link "dslTFloatLabel"
#pragma link "dslTPropertyCheckBox"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TMoveCoverSlipAtAngleProcessFrame *MoveCoverSlipAtAngleProcessFrame;

using namespace dsl;
using namespace at;
static int frameNr = 1;

//---------------------------------------------------------------------------
__fastcall TMoveCoverSlipAtAngleProcessFrame::TMoveCoverSlipAtAngleProcessFrame(ProcessSequencer& ps, TComponent* Owner)
	: TFrame(Owner),
    mProcessSequencer(ps),
    mAB(ps.getArrayBot()),
	mMoveCoverSlipAtAngleProcess(NULL),
    mPosTriggerFrame(NULL)
{
    this->Name = this->Name + IntToStr(frameNr++);
}

//---------------------------------------------------------------------------
void TMoveCoverSlipAtAngleProcessFrame::populate(MoveCoverSlipAtAngleProcess* m)
{
	if(!m)
    {
    	return;
    }

    mMoveCoverSlipAtAngleProcess = m;
    mActionInfo->Caption = vclstr(	mMoveCoverSlipAtAngleProcess->getInfoText());
	mLiftVelocityE->setValue(	    mMoveCoverSlipAtAngleProcess->getLiftVelocity());
	mLiftAccE->setValue(		    mMoveCoverSlipAtAngleProcess->getLiftAcceleration());
	mLiftAngleE->setValue(		    mMoveCoverSlipAtAngleProcess->getLiftAngle());
	mLiftHeightE->setValue(		    mMoveCoverSlipAtAngleProcess->getLiftHeight());

	DeltaZE->setValue(				mMoveCoverSlipAtAngleProcess->getLWBBDeltaZ());
	YMoveE->setValue( 				mMoveCoverSlipAtAngleProcess->getLWBB_Y_Move());
	ZMoveE->setValue( 				mMoveCoverSlipAtAngleProcess->getLWBB_Z_Move());
	YMoveScalingE->setValue(   		mMoveCoverSlipAtAngleProcess->getYMoveScaling());

    EnableParallelWhiskerMoveCB->Checked 	= mMoveCoverSlipAtAngleProcess->getMoveWhiskerInParallel();
	LeaveWhiskeratBeachCB->Checked	 		= mMoveCoverSlipAtAngleProcess->getLeaveWhiskerByBeach();

    //Validate motors
    if(!mAB.getCoverSlipUnit().getZMotor() || !mAB.getCoverSlipUnit().getYMotor() || !mAB.getWhiskerUnit().getZMotor() || !mAB.getWhiskerUnit().getYMotor())
    {
    	string msg("Not all motors for carrying out lift at angle are present. Process will be disabled");
    	Log(lError) << msg;
        MessageDlg(msg.c_str(), mtError, TMsgDlgButtons() << mbOK, 0);
    }
    else
    {
    	string msg("All motors for carrying out lift at angle are present.");
    	Log(lInfo) << msg;
    }

	mMoveCoverSlipAtAngleProcess->calculateLift(mAB);
	LatVelL->SetValue(mMoveCoverSlipAtAngleProcess->getLateralVelocity());
    LatAccL->SetValue(mMoveCoverSlipAtAngleProcess->getLateralAcceleration());

    //Stay at beach?
	if(EnableParallelWhiskerMoveCB->Checked)
    {
	    LeaveWhiskeratBeachCB->Enabled = true;
		if(LeaveWhiskeratBeachCB->Checked)
    	{
    		enableDisableGroupBox(StayAtBeachGB, true);
        }
        else
        {
    		enableDisableGroupBox(StayAtBeachGB, false);
        }
    }
    else
    {
	    LeaveWhiskeratBeachCB->Enabled 		= false;
    	enableDisableGroupBox(StayAtBeachGB, false);
    }

    if(FetchAngleFromCSAngleMotorCB->Checked)
    {
	    mLiftAngleE->Enabled = false;
        if(mAB.getCoverSlipAngleController())
        {
        	mLiftAngleE->setValue(mAB.getCoverSlipAngleController()->getPosition());
        }
    }
    else
    {
	    mLiftAngleE->Enabled = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMoveCoverSlipAtAngleProcessFrame::EditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key != vkReturn || mMoveCoverSlipAtAngleProcess == NULL)
    {
    	return;
    }

    mMoveCoverSlipAtAngleProcess->setLiftVelocity(		mLiftVelocityE->getValue());
    mMoveCoverSlipAtAngleProcess->setLiftAcceleration(	mLiftAccE->getValue());
    mMoveCoverSlipAtAngleProcess->setLiftAngle(         mLiftAngleE->getValue());
    mMoveCoverSlipAtAngleProcess->setLiftHeight(        mLiftHeightE->getValue());
	mMoveCoverSlipAtAngleProcess->setLWBBDeltaZ(        DeltaZE->getValue());
	mMoveCoverSlipAtAngleProcess->setLWBB_Y_Move(       YMoveE->getValue());
	mMoveCoverSlipAtAngleProcess->setLWBB_Z_Move(       ZMoveE->getValue());
	mMoveCoverSlipAtAngleProcess->setYMoveScaling(      YMoveScalingE->getValue());

    populate(mMoveCoverSlipAtAngleProcess);
	mProcessSequencer.saveCurrent();
}

//---------------------------------------------------------------------------
void __fastcall TMoveCoverSlipAtAngleProcessFrame::mActionInfoClick(TObject *Sender)
{
	Process* p =  mMoveCoverSlipAtAngleProcess;
    if(!p)
    {
    	return;
    }

	//Rename the currently selected sequence
	//Open text edit form
	TTextInputDialog* t = new TTextInputDialog(this);
    t->Caption = "Update Action Information";

    t->setText(p->getInfoText());

    if(t->ShowModal() == mrOk)
    {
    	string newText(t->getText());
		p->setInfoText(newText);
		p->write();
        mActionInfo->Caption = vclstr(newText);
    }
    delete t;
	mProcessSequencer.saveCurrent();
}

//---------------------------------------------------------------------------
void __fastcall TMoveCoverSlipAtAngleProcessFrame::EnableParallelWhiskerMoveCBClick(TObject *Sender)
{
	mMoveCoverSlipAtAngleProcess->setMoveWhiskerInParallel(EnableParallelWhiskerMoveCB->Checked);
    populate(mMoveCoverSlipAtAngleProcess);
	mProcessSequencer.saveCurrent();
}

//---------------------------------------------------------------------------
void __fastcall TMoveCoverSlipAtAngleProcessFrame::FetchAngleFromCSAngleMotorCBClick(TObject *Sender)
{
	mMoveCoverSlipAtAngleProcess->setFetchAngleFromCSAngleMotor(FetchAngleFromCSAngleMotorCB->Checked);
	mProcessSequencer.saveCurrent();

    if(FetchAngleFromCSAngleMotorCB->Checked)
    {
	    mLiftAngleE->Enabled = false;
        if(mAB.getCoverSlipAngleController())
        {
        	mLiftAngleE->setValue(mAB.getCoverSlipAngleController()->getPosition());
        }
    }
    else
    {
	    mLiftAngleE->Enabled = true;
    }
    populate(mMoveCoverSlipAtAngleProcess);
	mProcessSequencer.saveCurrent();
}

//---------------------------------------------------------------------------
void __fastcall TMoveCoverSlipAtAngleProcessFrame::LeaveWhiskeratBeachCBClick(TObject *Sender)
{
	mMoveCoverSlipAtAngleProcess->setLeaveWhiskerByBeach(LeaveWhiskeratBeachCB->Checked);
    populate(mMoveCoverSlipAtAngleProcess);
	mProcessSequencer.saveCurrent();
}


