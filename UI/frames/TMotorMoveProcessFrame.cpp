#include <vcl.h>
#pragma hdrstop
#include "TMotorMoveProcessFrame.h"
#include "abLinearMove.h"
#include "abAPTMotor.h"
#include "mtkVCLUtils.h"
#include "abXYZUnit.h"
#include "abArrayBot.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma resource "*.dfm"
TMotorMoveProcessFrame *MotorMoveProcessFrame;

//---------------------------------------------------------------------------
__fastcall TMotorMoveProcessFrame::TMotorMoveProcessFrame(TComponent* Owner)
	: TFrame(Owner),
    mAB(NULL)
{}


void TMotorMoveProcessFrame::populate(ArrayBot* ab, LinearMove* m)
{
	mAB = ab;
    MotorsCB->Clear();
	MotorsCB->Items->Add("<none>");
	populateMotorCB();
    rePopulate(m);
}

void TMotorMoveProcessFrame::rePopulate(LinearMove* m)
{
	if(!m)
    {
    	return;
    }

    mMove = m;
    MainGB->Caption = vclstr(mMove->getProcessName());
	mMovePosE->setValue(mMove->getPosition().x());
    mMaxVelE->setValue(mMove->getMaxVelocity());
    mAccE->setValue(mMove->getAcceleration());
    mPostDwellTimeE->setValue(mMove->getPostDwellTime());
    mPreDwellTimeE->setValue(mMove->getPreDwellTime());

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
        else
        {
			//Select the 'select motor' item

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
void __fastcall TMotorMoveProcessFrame::MotorsCBClick(TObject *Sender)
{
;
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
    }
    else
    {
    	mMovePosE->Enabled 	= false;
        mAccE->Enabled 		= false;
    }
}


void __fastcall TMotorMoveProcessFrame::mMovePosEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{

    if(Key != vkReturn || mMove == NULL)
    {
    	return;
    }

    ab::Position p(mMove->getPositionName(), mMovePosE->getValue(),0,0);
    mMove->setPosition(p);
    mMove->setMaxVelocity(mMaxVelE->getValue());
    mMove->setAcceleration(mAccE->getValue());
    mMove->setPostDwellTime(mPostDwellTimeE->getValue());
    mMove->setPreDwellTime(mPreDwellTimeE->getValue());

}


