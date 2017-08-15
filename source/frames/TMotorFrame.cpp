#include <vcl.h>
#pragma hdrstop
#include "TMotorFrame.h"
#include "arraybot/apt/atAPTMotor.h"
#include <bitset>
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
#include "mtkStringUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TIntLabel"
#pragma link "mtkFloatLabel"
#pragma link "TPropertyCheckBox"
#pragma resource "*.dfm"
TMotorFrame *MotorFrame;

using namespace mtk;
int TMotorFrame::mFrameNr = 0;
//---------------------------------------------------------------------------
__fastcall TMotorFrame::TMotorFrame(const string& name, TComponent* Owner)
	: TFrame(Owner),
    mMotor(NULL)
{
    TFrame::Name = vclstr("Frame_" + replaceCharacter('-', '_', name) + mtk::toString(++mFrameNr));
}

//---------------------------------------------------------------------------
void TMotorFrame::assignMotor(APTMotor* m)
{
	mMotor = m;
    if(mMotor)
    {
    	MotorGB->Caption = vclstr(mMotor->getName() + " [" + mMotor->getSerial() + "]");

        switch(mMotor->getJogMoveMode())
        {
        	case jmContinuous: 			JogModeRG->ItemIndex = 0; break;
        	case jmSingleStep: 			JogModeRG->ItemIndex = 1; break;
        	case jmJogModeUndefined: 	JogModeRG->ItemIndex = -1; break;
        }

        mJogStepE->setValue(mMotor->getJogStep());
        mJogVelocity->setValue(mMotor->getManualJogVelocity());
        mJogAcc->setValue(mMotor->getManualJogAcceleration());
	    mPotentiometerSettingE->setValue(mMotor->getPotentiometerVelocity());

        //Tie UI elements to underlying motor properties
        mPositionRangeMaxE->setReference(m->mPositionRange.getReference().getMaxReference());

		mMinPositionLimitE->setReference(m->mPositionLimits.getReference().getMinReference());
        mMaxPositionLimitE->setReference(m->mPositionLimits.getReference().getMaxReference());


		mEnableDisableLimits->setReference(m->mPositionLimitsEnabled.getReference());
    	EnableDisableFrame(this, true);
    }
    else
    {
    	MotorStatusTimer->Enabled = false;
    	EnableDisableFrame(this, false);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMotorFrame::MotorStatusTimerTimer(TObject *Sender)
{
    if(!mMotor)
    {
        return;
    }

    double p 	= mMotor->getPosition();
    double v 	= mMotor->getJogVelocity();
    double a 	= mMotor->getJogAcceleration();
    double vp 	= mMotor->getPotentiometerVelocity();

    mMotorPositionE->setValue(p);
    mJogVelLbl->SetValue(v);
	mJogAccLbl->SetValue(a);

    bitset<32> bits(mMotor->getStatusBits());

    mIsActiveLabel->Caption 	= (mMotor->isActive()) 	    ? "True" : "False";
    mIsHomingLabel->Caption 	= (mMotor->isHoming()) 	    ? "True" : "False";
    mIsHomedLabel->Caption  	= (mMotor->isHomed()) 	    ? "True" : "False";
    mIsForwardingLabel->Caption = (mMotor->isForwarding()) 	? "True" : "False";
    mIsReversingLabel->Caption  = (mMotor->isReversing()) 	? "True" : "False";
    mIsEnabledLbl->Caption  	= (mMotor->isEnabled()) 	? "True" : "False";

    EnableDisableBtn->Caption 	= (mMotor->isEnabled())    	? "Disable" : "Enable";
    mIsHomedLabel->Font->Color 	= (mIsHomedLabel->Caption == "False") ?  clRed : clGreen;
}

//---------------------------------------------------------------------------
void __fastcall TMotorFrame::identifyExecute(TObject *Sender)
{
    if(mMotor)
    {
    	mMotor->identify();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMotorFrame::homeExecute(TObject *Sender)
{
    if(mMotor)
    {
    	mMotor->home();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMotorFrame::BtnDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	TButton* btn = (TButton*)(Sender);
    if(btn == mFwdBtn)
    {
        double vel = mJogVelocity->getValue();
        mMotor->setJogVelocity(vel);
        double a = mJogAcc->getValue();
        mMotor->setJogAcceleration(a);
      	mMotor->jogForward();
    }

    if(btn == mRewBtn)
    {
        double vel = mJogVelocity->getValue();
        mMotor->setJogVelocity(vel);
        double a = mJogAcc->getValue();
        mMotor->setJogAcceleration(a);
      	mMotor->jogReverse();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMotorFrame::BtnUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	TButton* btn = (TButton*)(Sender);
    if(btn == mFwdBtn || btn == mRewBtn)
    {
  		mMotor->stop();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMotorFrame::DevEdit(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key != vkReturn)
    {
    	return;
    }

    if(!mMotor)
    {
    	Log(lError) << "No motor to set values for";
        return;
    }

	TFloatLabeledEdit* e = dynamic_cast<TFloatLabeledEdit*>(Sender);
    double value = e->getValue();
    if(e == mJogVelocity)
    {
        Log(lDebug) << "New JOG velocity (mm/s): " <<value;
		mMotor->setManualJogVelocity(value);
        mMotor->setJogVelocity(value);
        mMotor->setPotentiometerVelocity(value);
    }
    else if(e == mJogAcc)
    {
        Log(lDebug) << "New JOG acceleration (mm/(s*s)): " <<value;
		mMotor->setManualJogAcceleration(value);
        mMotor->setJogAcceleration(value);
    }
    else if(e == mPotentiometerSettingE)
    {
        Log(lDebug) << "New Pot vel (mm/(s)): " <<value;
		mMotor->setPotentiometerVelocity(value);
    }
    else if(e == mJogStepE)
    {
        Log(lDebug) << "Setting JogStep: (mm): " <<value;
        mMotor->setJogStep(value);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMotorFrame::mMotorPositionEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	MotorStatusTimer->Enabled = false;
	if(Key != vkReturn)
    {
    	return;
    }

    if(mMotor)
    {
		mMotor->moveToPosition(mMotorPositionE->getValue());
    }
}

//---------------------------------------------------------------------------
void __fastcall TMotorFrame::mMotorPositionEKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkReturn)
    {
		MotorStatusTimer->Enabled = true;
    	return;
    }
}


void __fastcall TMotorFrame::EnableDisableBtnClick(TObject *Sender)
{
	if(!mMotor)
    {
    	return;
    }

    if(mMotor->isEnabled())
    {
        mMotor->disable();
    }
    else
    {
        mMotor->enable();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMotorFrame::StopBtnClick(TObject *Sender)
{
	if(mMotor)
    {
		mMotor->stop();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMotorFrame::mEnableDisableLimitsClick(TObject *Sender)
{
	mEnableDisableLimits->OnClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TMotorFrame::JogModeRGClick(TObject *Sender)
{
	if(!mMotor)
    {
    	return;
    }

	//Setup jogmode
	int itemIndex =JogModeRG->ItemIndex;
    switch(itemIndex)
    {
    	case 0:
        	mMotor->setJogMoveMode(jmContinuous);
        break;

        case 1:
        	mMotor->setJogMoveMode(jmSingleStep);
        break;
    }
}


