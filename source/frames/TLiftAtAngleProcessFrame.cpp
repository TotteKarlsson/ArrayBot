#include <vcl.h>
#pragma hdrstop
#include "TLiftAtAngleProcessFrame.h"
#include "TPositionalTriggerFrame.h"
#include "arraybot/apt/atMove.h"
#include "arraybot/apt/atAPTMotor.h"
#include "mtkVCLUtils.h"
#include "arraybot/atXYZUnit.h"
#include "arraybot/atArrayBot.h"
#include "arraybot/process/atLiftAtAngleProcess.h"
#include "arraybot/process/atTriggerFunction.h"
#include "vcl/forms/TTextInputDialog.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TLiftAtAngleProcessFrame *LiftAtAngleProcessFrame;

static int frameNr = 1;
//---------------------------------------------------------------------------
__fastcall TLiftAtAngleProcessFrame::TLiftAtAngleProcessFrame(ProcessSequencer& ps, TComponent* Owner)
	: TFrame(Owner),
    mProcessSequencer(ps),
    mAB(ps.getArrayBot()),
    mPosTriggerFrame(NULL)
{
	mPosTriggerFrame = new TPositionalTriggerFrame(this);
    mPosTriggerFrame->Parent = mTriggerPanel;
    mPosTriggerFrame->Align = alClient;
    mPosTriggerFrame->Visible = false;

    this->Name = this->Name + IntToStr(frameNr++);
}

void TLiftAtAngleProcessFrame::populate(LiftAtAngleProcess* m)
{
    MotorsCB->Clear();
	populateMotorCB();
    rePopulate(m);

    //Populate subframes
    mTriggersLB->Clear();
//    if(mProcess && mProcess->getTrigger())
//    {
//	    mProcess->getTrigger()->assignSubject(mProcess->getUnit());
//		mTriggersLB->Items->AddObject(mProcess->getTrigger()->getTypeName().c_str(), (TObject*) mProcess->getTrigger());
//        mTriggersLB->ItemIndex = 0;
//		TriggersLBClick(NULL);
//        //mAddTriggerBtn->Visible	= false;
//        mAddTriggerBtn->Caption = "Delete Child Action";
//		mTriggerPanel->Visible 	= true;
//    }
//    else
//    {
//   		mAddTriggerBtn->Caption = "Add Child Action";
//	    mPosTriggerFrame->Visible 	= false;
//        mAddTriggerBtn->Visible   	= true;
//		mTriggerPanel->Visible 		= false;
//    }

   	mAddTriggerBtn->Enabled =  (MotorsCB->ItemIndex == -1) ? false : true;
}

void TLiftAtAngleProcessFrame::rePopulate(LiftAtAngleProcess* m)
{
	if(!m)
    {
    	return;
    }

    mProcess = m;
    mActionInfo->Caption = vclstr(mProcess->getInfoText());

//	mMovePosE->setValue(mProcess->getPosition());
//    mMaxVelE->setValue(mProcess->getMaxVelocity());
//    mAccE->setValue(mProcess->getAcceleration());

//    APTMotor* mtr = dynamic_cast<APTMotor*>(mProcess->getUnit());
//    if(!mtr)
//    {
//    	//Look for motor
//        string unitLbl = mProcess->getMotorName();
//		int idx = MotorsCB->Items->IndexOf(unitLbl.c_str());
//        if(idx != -1)
//        {
//        	//Found it, assign it
//        	mProcess->assignUnit( (APTMotor*) MotorsCB->Items->Objects[idx] );
//			MotorsCB->ItemIndex = idx;
//        }
//    }
//    else
//    {
//    	int idx = MotorsCB->Items->IndexOf(mtr->getName().c_str());
//		MotorsCB->ItemIndex = idx;
//    }
}

//Motor objects are stored in the checkbox list property
void TLiftAtAngleProcessFrame::populateMotorCB()
{
	vector<APTMotor*> motors = mAB.getAllMotors();
    for(int i = 0; i < motors.size(); i++)
    {
    	if(motors[i])
        {
			MotorsCB->Items->InsertObject(MotorsCB->Items->Count, motors[i]->getName().c_str(), (TObject*) motors[i]);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TLiftAtAngleProcessFrame::MotorsCBChange(TObject *Sender)
{
//	//Check if a motor is selected
//    ATObject* obj = (ATObject*) MotorsCB->Items->Objects[MotorsCB->ItemIndex];
//    APTMotor* motor = dynamic_cast<APTMotor*>(obj);
//
//    if(motor && mProcess)
//    {
//    	mProcessPosE->Enabled = true;
//        mAccE->Enabled = true;
//        mProcess->assignUnit(motor);
//        mAddTriggerBtn->Enabled = true;
//    }
//    else
//    {
//    	mProcessPosE->Enabled 	= false;
//        mAccE->Enabled 		= false;
//        mAddTriggerBtn->Enabled = false;
//    }
//
//    if(mProcess && mProcess->getTrigger())
//    {
//		mPosTriggerFrame->rePopulate(mProcess->getTrigger());
//    }
//	mProcessSequencer.saveCurrent();
}

void __fastcall TLiftAtAngleProcessFrame::mMovePosEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
//    if(Key != vkReturn || mProcess == NULL)
//    {
//    	return;
//    }
//
//    mProcess->setPosition(mProcessPosE->getValue());
//    mProcess->setMaxVelocity(mMaxVelE->getValue());
//    mProcess->setAcceleration(mAccE->getValue());
//
//	mProcessSequencer.saveCurrent();
}

//---------------------------------------------------------------------------
void __fastcall TLiftAtAngleProcessFrame::TriggersLBClick(TObject *Sender)
{
	//Retrive selected trigger
    int indx = mTriggersLB->ItemIndex;
    if(indx == -1)
    {
       	mAddTriggerBtn->Enabled 	= false;
    	return;
    }

   	mAddTriggerBtn->Enabled = true;

    Trigger* t = (Trigger*) mTriggersLB->Items->Objects[indx];
    if(t)
    {
		//Check what kind of trigger
       	mPosTriggerFrame->populate(mAB, t);
	    mPosTriggerFrame->Visible = true;
    }
    else
    {
	    mPosTriggerFrame->Visible = false;
    }
}

void __fastcall TLiftAtAngleProcessFrame::mDeleteTriggerBClick(TObject *Sender)
{
	//delete currently selected trigger
//    int indx = mTriggersLB->ItemIndex;
//    if(indx != -1)
//    {
//    	mProcess->deleteTrigger();
//	    mTriggersLB->Clear();
//	    mPosTriggerFrame->Visible = false;
//		populate(mProcess);
//    }
}

//---------------------------------------------------------------------------
void __fastcall TLiftAtAngleProcessFrame::AddTriggerBClick(TObject *Sender)
{
//	if(mAddTriggerBtn->Caption == "Add Child Action")
//    {
//        //Create a new Trigger
//        Trigger* t = new PositionalTrigger(NULL);
//        mProcess->addTrigger(t);
//
//        //Also add a trigger function
//        MoveAbsolute *tf = new MoveAbsolute(NULL);
//        t->assignTriggerFunction(tf);
//        populate(mProcess);
//    }
//    else
//    {
//        //delete currently selected trigger
////        int indx = mTriggersLB->ItemIndex;
////        if(indx != -1)
//        {
//            mProcess->deleteTrigger();
////            mTriggersLB->Clear();
//            mPosTriggerFrame->Visible = false;
//            populate(mProcess);
//        }
//    }
}

//---------------------------------------------------------------------------
void __fastcall TLiftAtAngleProcessFrame::mActionInfoClick(TObject *Sender)
{
    if(!mProcess)
    {
    	return;
    }

	//Open text edit form
	TTextInputDialog* t = new TTextInputDialog(this);

    t->Caption = "Update Action Information";
	Process* p =  mProcess;

    t->setText(mProcess->getInfoText());

    if(t->ShowModal() == mrOk)
    {
		//Rename the currently selected sequence
    	string newText(t->getText());
		mProcess->setInfoText(newText);
		mProcess->write();
        mActionInfo->Caption = vclstr(newText);
    }
    delete t;
}


