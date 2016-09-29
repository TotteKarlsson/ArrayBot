#include <vcl.h>
#pragma hdrstop
#include "TMotorMoveProcessFrame.h"
#include "TPositionalTriggerFrame.h"
#include "abMove.h"
#include "apt/abAPTMotor.h"
#include "mtkVCLUtils.h"
#include "abXYZUnit.h"
#include "abArrayBot.h"
#include "abAbsoluteMove.h"
#include "abTriggerFunction.h"
#include "TTextInputDialog.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TMotorMoveProcessFrame *MotorMoveProcessFrame;

//---------------------------------------------------------------------------
__fastcall TMotorMoveProcessFrame::TMotorMoveProcessFrame(TComponent* Owner)
	: TFrame(Owner),
    mAB(NULL),
    mPosTriggerFrame(NULL)
{
	mPosTriggerFrame = new TPositionalTriggerFrame(this);
    mPosTriggerFrame->Parent = mTriggerPanel;
    mPosTriggerFrame->Align = alClient;
    mPosTriggerFrame->Visible = false;
}

void TMotorMoveProcessFrame::populate(ArrayBot* ab, AbsoluteMove* m)
{
	mAB = ab;
    MotorsCB->Clear();
	populateMotorCB();
    rePopulate(m);

    //Populate subframes
    mTriggersLB->Clear();
    if(mMove && mMove->getTrigger())
    {
	    mMove->getTrigger()->assignSubject(mMove->getUnit());
		mTriggersLB->Items->AddObject(mMove->getTrigger()->getTypeName().c_str(), (TObject*) mMove->getTrigger());
        mTriggersLB->ItemIndex = 0;
		TriggersLBClick(NULL);
        //mAddTriggerBtn->Visible	= false;
        mAddTriggerBtn->Caption = "Delete Child Action";
		mTriggerPanel->Visible 	= true;
    }
    else
    {
   		mAddTriggerBtn->Caption = "Add Child Action";
	    mPosTriggerFrame->Visible 	= false;
        mAddTriggerBtn->Visible   	= true;
		mTriggerPanel->Visible 		= false;
    }

   	mAddTriggerBtn->Enabled =  (MotorsCB->ItemIndex == -1) ? false : true;
}

void TMotorMoveProcessFrame::rePopulate(AbsoluteMove* m)
{
	if(!m)
    {
    	return;
    }

    mMove = m;
    mActionInfo->Caption = vclstr(mMove->getInfoText());

	mMovePosE->setValue(mMove->getPosition());
    mMaxVelE->setValue(mMove->getMaxVelocity());
    mAccE->setValue(mMove->getAcceleration());

    APTMotor* mtr = dynamic_cast<APTMotor*>(mMove->getUnit());
    if(!mtr)
    {
    	//Look for motor
        string unitLbl = mMove->getMotorName();
		int idx = MotorsCB->Items->IndexOf(unitLbl.c_str());
        if(idx != -1)
        {
        	//Found it, assign it
        	mMove->assignUnit( (APTMotor*) MotorsCB->Items->Objects[idx] );
			MotorsCB->ItemIndex = idx;
        }
    }
    else
    {
    	int idx = MotorsCB->Items->IndexOf(mtr->getName().c_str());
		MotorsCB->ItemIndex = idx;
    }
}

void TMotorMoveProcessFrame::populateMotorCB()
{
	vector<APTMotor*> motors = mAB->getAllMotors();
    for(int i = 0; i < motors.size(); i++)
    {
    	if(motors[i])
        {
			MotorsCB->Items->InsertObject(MotorsCB->Items->Count, motors[i]->getName().c_str(), (TObject*) motors[i]);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMotorMoveProcessFrame::MotorsCBChange(TObject *Sender)
{
	//Check if a motor is selected
    ABObject* obj = (ABObject*) MotorsCB->Items->Objects[MotorsCB->ItemIndex];
    APTMotor* motor = dynamic_cast<APTMotor*>(obj);

    if(motor && mMove)
    {
    	mMovePosE->Enabled = true;
        mAccE->Enabled = true;
        mMove->assignUnit(motor);
        mAddTriggerBtn->Enabled = true;
    }
    else
    {
    	mMovePosE->Enabled 	= false;
        mAccE->Enabled 		= false;
        mAddTriggerBtn->Enabled = false;
    }


    if(mMove && mMove->getTrigger())
    {
		mPosTriggerFrame->rePopulate(mMove->getTrigger());
    }
}

void __fastcall TMotorMoveProcessFrame::mMovePosEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key != vkReturn || mMove == NULL)
    {
    	return;
    }

    mMove->setPosition(mMovePosE->getValue());
    mMove->setMaxVelocity(mMaxVelE->getValue());
    mMove->setAcceleration(mAccE->getValue());
}

//---------------------------------------------------------------------------
void __fastcall TMotorMoveProcessFrame::TriggersLBClick(TObject *Sender)
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
       	mPosTriggerFrame->populate(*mAB, t);
	    mPosTriggerFrame->Visible = true;
    }
    else
    {
	    mPosTriggerFrame->Visible = false;
    }
}

void __fastcall TMotorMoveProcessFrame::mDeleteTriggerBClick(TObject *Sender)
{
	//delete currently selected trigger
    int indx = mTriggersLB->ItemIndex;
    if(indx != -1)
    {
    	mMove->deleteTrigger();
	    mTriggersLB->Clear();
	    mPosTriggerFrame->Visible = false;
		populate(mAB, mMove);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMotorMoveProcessFrame::AddTriggerBClick(TObject *Sender)
{
	if(mAddTriggerBtn->Caption == "Add Child Action")
    {
        //Create a new Trigger
        Trigger* t = new PositionalTrigger(NULL);
        mMove->addTrigger(t);

        //Also add a trigger function
        MoveAbsolute *tf = new MoveAbsolute(NULL);
        t->assignTriggerFunction(tf);
        populate(mAB, mMove);
    }
    else
    {
        //delete currently selected trigger
//        int indx = mTriggersLB->ItemIndex;
//        if(indx != -1)
        {
            mMove->deleteTrigger();
//            mTriggersLB->Clear();
            mPosTriggerFrame->Visible = false;
            populate(mAB, mMove);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMotorMoveProcessFrame::mActionInfoClick(TObject *Sender)
{
    if(!mMove)
    {
    	return;
    }

	//Open text edit form
	TTextInputDialog* t = new TTextInputDialog(this);

    t->Caption = "Update Action Information";
	Process* p =  mMove;

    t->setText(mMove->getInfoText());

    if(t->ShowModal() == mrOk)
    {
		//Rename the currently selected sequence
    	string newText(t->getText());
		mMove->setInfoText(newText);
		mMove->write();
        mActionInfo->Caption = vclstr(newText);
    }
    delete t;
}


