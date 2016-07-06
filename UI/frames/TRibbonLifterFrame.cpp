#include <vcl.h>
#pragma hdrstop
#include "TRibbonLifterFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma resource "*.dfm"
TRibbonLifterFrame *RibbonLifterFrame;

bool TRibbonLifterFrame::gIsOpen = false;

//---------------------------------------------------------------------------
__fastcall TRibbonLifterFrame::TRibbonLifterFrame(ArrayBot& ab, IniFile& iniFile, TComponent* Owner)
	: TFrame(Owner),
    mRibbonLifter(ab, iniFile)
{
	//Assign ribbonlifter properties with UI elements
    mLiftLocationXE->assignExternalProperty(&(mRibbonLifter.mLiftLocationX), true);
	mLiftLocationYE->assignExternalProperty(&(mRibbonLifter.mLiftLocationY), true);

    mMoveToPickupLocationSpeedE->assignExternalProperty(&(mRibbonLifter.mMoveToLLVelocity), true);
    mMoveToPickupLocationAccE->assignExternalProperty(&(mRibbonLifter.mMoveToLLAcc), true);

    mInitialLiftSpeedZE->assignExternalProperty(&(mRibbonLifter.mLiftVelocityZ), true);
    mInitialLiftAccZE->assignExternalProperty(&(mRibbonLifter.mLiftAccZ), true);

    mInitialLiftSpeedYE->assignExternalProperty(&(mRibbonLifter.mLiftVelocityY), true);
    mInitialLiftAccYE->assignExternalProperty(&(mRibbonLifter.mLiftAccY), true);

    mWhiskerLiftOffZPositionE->assignExternalProperty(&(mRibbonLifter.mWhiskerLiftOffZPosition), true);

    mWhiskerXLiftStowPosW->assignExternalProperty(&(mRibbonLifter.mWhiskerLiftStowXPosition), true);

    gIsOpen = true;
}

__fastcall 	TRibbonLifterFrame::~TRibbonLifterFrame()
{
    gIsOpen = false;
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
void __fastcall TRibbonLifterFrame::Button2Click(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

