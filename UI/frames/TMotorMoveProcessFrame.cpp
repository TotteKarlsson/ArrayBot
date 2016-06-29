#include <vcl.h>
#pragma hdrstop
#include "TMotorMoveProcessFrame.h"
#include "abLinearMove.h"
#include "abAPTMotor.h"
#include "mtkVCLUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma resource "*.dfm"
TMotorMoveProcessFrame *MotorMoveProcessFrame;

//---------------------------------------------------------------------------
__fastcall TMotorMoveProcessFrame::TMotorMoveProcessFrame(TComponent* Owner)
	: TFrame(Owner)
{}

void TMotorMoveProcessFrame::populate(LinearMove* m)
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
    	//Look for motor in the Checkbox
        string unitLbl = mMove->getMotorName();
		int idx = MotorsCB->Items->IndexOf(unitLbl.c_str());
        if(idx != -1)
        {
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

