#include <vcl.h>
#pragma hdrstop
#include "TMoveCoverSlipAtAngleProcessFrame.h"
#include "TPositionalTriggerFrame.h"
#include "arraybot/apt/atMove.h"
#include "arraybot/apt/atAPTMotor.h"
#include "mtkVCLUtils.h"
#include "arraybot/atXYZUnit.h"
#include "arraybot/atArrayBot.h"
#include "arraybot/process/atMoveCoverSlipAtAngleProcess.h"
#include "arraybot/process/atTriggerFunction.h"
#include "vcl/forms/TTextInputDialog.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma link "mtkFloatLabel"
#pragma link "TPropertyCheckBox"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TMoveCoverSlipAtAngleProcessFrame *MoveCoverSlipAtAngleProcessFrame;

using namespace mtk;
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

void TMoveCoverSlipAtAngleProcessFrame::populate(MoveCoverSlipAtAngleProcess* m)
{
	//Populate the frame
	if(!m)
    {
    	return;
    }

    mMoveCoverSlipAtAngleProcess = m;
    mActionInfo->Caption = vclstr(mMoveCoverSlipAtAngleProcess->getInfoText());
	mLiftVelocityE->setValue(mMoveCoverSlipAtAngleProcess->getLiftVelocity());
	mLiftAccE->setValue(mMoveCoverSlipAtAngleProcess->getLiftAcceleration());
	mLiftAngleE->setValue(mMoveCoverSlipAtAngleProcess->getLiftAngle());
	mLiftHeightE->setValue(mMoveCoverSlipAtAngleProcess->getLiftHeight());

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

	mMoveCoverSlipAtAngleProcess->calculateLift();
	LatVelL->SetValue(mMoveCoverSlipAtAngleProcess->getLateralVelocity());
    LatAccL->SetValue(mMoveCoverSlipAtAngleProcess->getLateralAcceleration());
}

void __fastcall TMoveCoverSlipAtAngleProcessFrame::EditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key != vkReturn || mMoveCoverSlipAtAngleProcess == NULL)
    {
    	return;
    }

    mMoveCoverSlipAtAngleProcess->setLiftVelocity(mLiftVelocityE->getValue());
    mMoveCoverSlipAtAngleProcess->setLiftAcceleration(mLiftAccE->getValue());
    mMoveCoverSlipAtAngleProcess->setLiftAngle(mLiftAngleE->getValue());
    mMoveCoverSlipAtAngleProcess->setLiftHeight(mLiftHeightE->getValue());

	mProcessSequencer.saveCurrent();
    populate(mMoveCoverSlipAtAngleProcess);

}

//---------------------------------------------------------------------------
void __fastcall TMoveCoverSlipAtAngleProcessFrame::mActionInfoClick(TObject *Sender)
{
    if(!mMoveCoverSlipAtAngleProcess)
    {
    	return;
    }

	//Rename the currently selected sequence
	//Open text edit form
	TTextInputDialog* t = new TTextInputDialog(this);
    t->Caption = "Update Action Information";
	Process* p =  mMoveCoverSlipAtAngleProcess;

    t->setText(mMoveCoverSlipAtAngleProcess->getInfoText());

    if(t->ShowModal() == mrOk)
    {
    	string newText(t->getText());
		mMoveCoverSlipAtAngleProcess->setInfoText(newText);
		mMoveCoverSlipAtAngleProcess->write();
        mActionInfo->Caption = vclstr(newText);
    }
    delete t;
}


