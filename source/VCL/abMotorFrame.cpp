#include <vcl.h>
#pragma hdrstop
#include "abMotorFrame.h"
#include "abAPTMotor.h"
#include <bitset>
#include "mtkVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "mtkFloatLabeledEdit"
#pragma link "TIntLabel"
#pragma resource "*.dfm"
TMotorFrame *MotorFrame;

using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TMotorFrame::TMotorFrame(const string& name, TComponent* Owner)
	: TFrame(Owner),
    mMotor(NULL)
{
    TFrame::Name = (vclstr("Frame_" + name));
}

//---------------------------------------------------------------------------
void TMotorFrame::assignMotor(APTMotor* m)
{
	mMotor = m;
    if(mMotor)
    {
    	MotorGB->Caption = vclstr(mMotor->getName() + " [" + mMotor->getSerial() + "]");
    	mMotorStatusTimer->Enabled = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMotorFrame::mMotorStatusTimerTimer(TObject *Sender)
{
    if(!mMotor)
    {
        return;
    }

    double p = mMotor->getPosition();
    double v = mMotor->getVelocity();
    double a = mMotor->getAcceleration();

    mMotorPositionE->SetNumber(p);

    bitset<32> bits(mMotor->getStatusBits());

    mIsActiveLabel->Caption 	= (mMotor->isActive()) 	    ? "True" : "False";
    mIsHomingLabel->Caption 	= (mMotor->isHoming()) 	    ? "True" : "False";
    mIsHomedLabel->Caption  	= (mMotor->isHomed()) 	    ? "True" : "False";
    mIsForwardingLabel->Caption = (mMotor->isForwarding()) 	? "True" : "False";
    mIsReversingLabel->Caption  = (mMotor->isReversing()) 	? "True" : "False";

    if(mMotor->isActive())
    {
        mVelocityLbl->Caption = FloatToStrF(v, ffFixed, 4,3);
    }
    else
    {
        mVelocityLbl->Caption = FloatToStrF(0,ffFixed, 4,3);
    }
}


