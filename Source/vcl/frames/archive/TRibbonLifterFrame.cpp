#include <vcl.h>
#pragma hdrstop
#include "TRibbonLifterFrame.h"
#include "dslLogger.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTFloatLabeledEdit"
#pragma resource "*.dfm"
TRibbonLifterFrame *RibbonLifterFrame;

using namespace dsl;

bool TRibbonLifterFrame::gIsFrameOpen = false;

//---------------------------------------------------------------------------
__fastcall TRibbonLifterFrame::TRibbonLifterFrame(ArrayBot& ab, IniFile& iniFile, TComponent* Owner)
	: TFrame(Owner),
    mRibbonLifter(ab, iniFile)
{
	//Assign ribbonlifter properties with UI elements
    mLiftLocationXE->assignExternalProperty(&(mRibbonLifter.mLiftLocationX), true);
	mLiftLocationYE->assignExternalProperty(&(mRibbonLifter.mLiftLocationY), true);

	mLiftDistanceCSE->assignExternalProperty(&(mRibbonLifter.mLiftDistanceCS), true);

    mMoveToPickupLocationSpeedE->assignExternalProperty(&(mRibbonLifter.mMoveToLLVelocity), true);
    mMoveToPickupLocationAccE->assignExternalProperty(&(mRibbonLifter.mMoveToLLAcc), true);

    mInitialLiftSpeedZE->assignExternalProperty(&(mRibbonLifter.mLiftVelocityZ), true);
    mInitialLiftAccZE->assignExternalProperty(&(mRibbonLifter.mLiftAccZ), true);

    mInitialLiftSpeedYE->assignExternalProperty(&(mRibbonLifter.mLiftVelocityY), true);
    mInitialLiftAccYE->assignExternalProperty(&(mRibbonLifter.mLiftAccY), true);

    mWhiskerLiftOffZPositionE->assignExternalProperty(&(mRibbonLifter.mWhiskerLiftOffZPosition), true);

    mWhiskerXLiftStowPosW->assignExternalProperty(&(mRibbonLifter.mWhiskerLiftStowXPosition), true);

    gIsFrameOpen = true;
}

__fastcall 	TRibbonLifterFrame::~TRibbonLifterFrame()
{
    gIsFrameOpen = false;
}

void __fastcall TRibbonLifterFrame::WndProc(TMessage &Message)
{
    if (Message.Msg == CM_RELEASE)
    {
        delete this;
        return;
    }

    TFrame::WndProc(Message);
}

bool TRibbonLifterFrame::init()
{
	return true;
}

bool TRibbonLifterFrame::close()
{
	// CM_RELEASE is defined in Controls.hpp
    PostMessage(Handle, CM_RELEASE, 0, 0);
    return true;
}

//---------------------------------------------------------------------------
void __fastcall TRibbonLifterFrame::mMove1BtnClick(TObject *Sender)
{
	if(mRibbonLifter.isRunning())
    {
    	mRibbonLifter.stop();
        return;
    }
	//Get Whisker X and Y distances
    if(!mRibbonLifter.setupMove1())
    {
    	Log(lError) << "There was a problem setting up Move 1";
    }

	mMoveTimer->Enabled = true;
    mRibbonLifter.executeMove1();
}

//---------------------------------------------------------------------------
void __fastcall TRibbonLifterFrame::mMoveTimerTimer(TObject *Sender)
{
	if(mRibbonLifter.isRunning())
    {
		mRunningLbl->Caption = "Running..";
        mMove1Btn->Caption = "Stop";
	    mMove2Btn->Caption = "Stop";
    }
    else
    {
        mMove1Btn->Caption = "Start";
        mMove2Btn->Caption = "Start";
		mRunningLbl->Caption = "Not running..";
        mMoveTimer->Enabled = false;
    }
}

//---------------------------------------------------------------------------
void __fastcall TRibbonLifterFrame::mMove2BtnClick(TObject *Sender)
{
	if(mRibbonLifter.isRunning())
    {
    	mRibbonLifter.stop();
        return;
    }

	//Get Whisker X and Y distances
    if(!mRibbonLifter.setupMove2())
    {
    	Log(lError) << "There was a problem setting up Move 1";
    }

	mMoveTimer->Enabled = true;
    mRibbonLifter.executeMove2();
}

