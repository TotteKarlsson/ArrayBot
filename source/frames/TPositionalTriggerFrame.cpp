#include <vcl.h>
#pragma hdrstop
#include "TPositionalTriggerFrame.h"
#include "arraybot/apt/atMove.h"
#include "arraybot/apt/atAPTMotor.h"
#include "arraybot/atArrayBot.h"
#include "mtkVCLUtils.h"
#include "arraybot/process/atTriggerFunction.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma resource "*.dfm"

TPositionalTriggerFrame *PositionalTriggerFrame;

//---------------------------------------------------------------------------
__fastcall TPositionalTriggerFrame::TPositionalTriggerFrame(TComponent* Owner)
	: TFrame(Owner)
{}

void TPositionalTriggerFrame::populate(ArrayBot& ab, Trigger* t)
{
	mAB = &ab;
    rePopulate(t);
}

void TPositionalTriggerFrame::rePopulate(Trigger* t)
{
    mTrigger = t;
	if(!mTrigger)
    {
    	this->Enabled = false;
    	return;
    }
  	this->Enabled = true;


    APTMotor* mtr = dynamic_cast<APTMotor*>(mTrigger->getSubject());
    if(mtr)
    {
//    	MainGB->Caption = "";//"Parent Device: " + vclstr(mtr->getName());
    }

    //Setup the position
    PositionalTrigger* pt = dynamic_cast<PositionalTrigger*>(mTrigger);
    if(!pt)
    {
    	return;
    }

    mPositionE->setValue(pt->getPosition());

    //Setup the logical operator
    mOpRG->ItemIndex = (int) pt->getTestOperator();

    //Setup the object to be triggered
    mDevicesCB->Clear();
	populateDevicesCB();

    //Select the one that is to be triggered
    MoveAbsolute *tf = dynamic_cast<MoveAbsolute*>(pt->getTriggerFunction());
    if(tf)
    {
        int indexOf = mDevicesCB->Items->IndexOf(vclstr(tf->getMotorName()));
        if(indexOf != -1)
        {
            mDevicesCB->ItemIndex = indexOf;
        }

	    mNewVelE->setValue(tf->getVelocity());
	    mNewAccE->setValue(tf->getAcceleration());
	    mFinalPositionE->setValue(tf->getPosition());
    }
}

void TPositionalTriggerFrame::populateDevicesCB()
{
	mDevicesCB->Clear();
    if(!mTrigger || !mAB)
    {
    	return;
    }

    APTMotor* mtr = dynamic_cast<APTMotor*>(mTrigger->getSubject());

    if(!mtr)
    {
    	return;
    }

    vector<APTMotor*> motors = mAB->getAllMotors();
    for(int i = 0; i < motors.size(); i++)
    {
        if(motors[i] )//&& (motors[i]->getName() != mtr->getName()))
        {
        	mDevicesCB->Items->InsertObject(mDevicesCB->Items->Count, motors[i]->getName().c_str(), (TObject*) motors[i]);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TPositionalTriggerFrame::mPositionEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkReturn && mTrigger)
    {
    	PositionalTrigger* pt = dynamic_cast<PositionalTrigger*>(mTrigger);
        if(pt)
        {
            pt->setPosition(mPositionE->getValue());
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TPositionalTriggerFrame::mOpRGClick(TObject *Sender)
{
	//Capture state
	if(mTrigger)
    {
    	PositionalTrigger* pt = dynamic_cast<PositionalTrigger*>(mTrigger);
        if(pt)
        {
	    	LogicOperator lo = toLogicOperator(stdstr(mOpRG->Items->Strings[mOpRG->ItemIndex]));
		    pt->setTestOperator(lo);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TPositionalTriggerFrame::mDevicesCBChange(TObject *Sender)
{
	//Capture device
    if(mDevicesCB->ItemIndex == -1 || mTrigger == NULL)
    {
    	return;
    }

    MoveAbsolute *tf = dynamic_cast<MoveAbsolute*>(mTrigger->getTriggerFunction());
    if(tf)
    {
		tf->setMotorName(stdstr(mDevicesCB->Items->Strings[mDevicesCB->ItemIndex]));
        if(mAB)
        {
        	tf->setMotor(mAB->getMotorWithName(tf->getMotorName()));
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TPositionalTriggerFrame::mNewVelEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkReturn && mTrigger != NULL)
    {
	    MoveAbsolute *tf = dynamic_cast<MoveAbsolute*>(mTrigger->getTriggerFunction());
        if(tf)
        {
            tf->setPosition(mFinalPositionE->getValue());
     		tf->setVelocity(mNewVelE->getValue());
     		tf->setAcceleration(mNewAccE->getValue());
        }
    }
}




