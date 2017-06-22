#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "arraybot/apt/atAPTMotor.h"
//---------------------------------------------------------------------------
void __fastcall TMain::mWiggleBtnClick(TObject *Sender)
{
	//Start/Stop wiggle timer
    if(!mTheWiggler.isRunning())
    {
        mAB.disableJoyStickAxes();
        Log(lInfo) << "Wiggler Center Position: "<<mTheWiggler.getCenterPosition();
        mTheWiggler.startWiggle();
		mWiggleBtn->Caption = "Stop Wiggle";
    }
    else
    {
        mTheWiggler.stopWiggle();
	    mAB.getWhiskerUnit().getXMotor()->stop();
        mAB.enableJoyStickAxes();
    	mWiggleBtn->Caption = "Start Wiggle";
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mWiggleSpinButtonDownClick(TObject *Sender)
{
	mWigglerAmplitudeE->setValue(mWigglerAmplitudeE->getValue() - mWigglerAmplitudeStepE->getValue());
    if(mWigglerAmplitudeE->getValue() < 0)
    {
		mWigglerAmplitudeE->setValue(0.0);
    }

    mWigglerAmplitudeE->update();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mWiggleSpinButtonUpClick(TObject *Sender)
{
	mWigglerAmplitudeE->setValue(mWigglerAmplitudeE->getValue() + mWigglerAmplitudeStepE->getValue());
    mWigglerAmplitudeE->update();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mPullRibbonBtnClick(TObject *Sender)
{

    int ii = mPullCB->ItemIndex;
	if(mPullCB->ItemIndex == -1)
    {
    	return;
    }

	double step = mPullCB->Items->Strings[ii].ToDouble();

    TArrayBotButton* b = dynamic_cast<TArrayBotButton*>(Sender);

    mAB.disableJoyStickAxes();
    if(b == mPullRibbonBtn)
    {
    	mTheWiggler.pull(step);
    }
    else
    {
    	mTheWiggler.relax(step);
    }
}
