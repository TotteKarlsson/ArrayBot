#include <vcl.h>
#pragma hdrstop
#include "TXYZUnitFrame.h"
#include "abXYZUnit.h"
#include "mtkVCLUtils.h"
#include "abAPTMotor.h"
#include "TMotorFrame.h"
#include "abWhiskerUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TSTDStringLabeledEdit"
#pragma link "TMotorFrame"
#pragma resource "*.dfm"

TXYZUnitFrame *XYZUnitFrame;

using namespace mtk;
int TXYZUnitFrame::mFrameNr = 0;
//---------------------------------------------------------------------------
__fastcall TXYZUnitFrame::TXYZUnitFrame(TComponent* Owner)
	: TFrame(Owner),
    mUnit(NULL)
//    mXMotorFrame(NULL),
//    mYMotorFrame(NULL),
//    mZMotorFrame(NULL),
//    mAngleMotorFrame(NULL)
{
    TFrame::Name = vclstr("XYZUnitFrame_" + mtk::toString(++mFrameNr));
}

//---------------------------------------------------------------------------
void TXYZUnitFrame::assignUnit(XYZUnit* u)
{
	mUnit = u;

    if(mUnit)
    {
        mainGB->Caption = vclstr(mUnit->getName());

        vector<APTMotor*> mtrs = mUnit->getAllMotors();

        for(int i = 0; i < mtrs.size(); i++)
        {
            TMotorFrame* f = new TMotorFrame(mtrs[i]->getSerial(), this);
            f->SetParentComponent(ScrollBox1);
            f->Align = alLeft;
            f->assignMotor(mtrs[i]);
            mFrames.push_back(f);
        }
    }
}

void TXYZUnitFrame::disable()
{
	for(int i = 0; i < mFrames.size(); i++)
    {
		mFrames[i]->mMotorStatusTimer->Enabled = false;
    }

//	if(mXMotorFrame)
//    {
//    	mXMotorFrame->mMotorStatusTimer->Enabled = false;
//    }
//
//	if(mYMotorFrame)
//    {
//    	mYMotorFrame->mMotorStatusTimer->Enabled = false;
//    }
//
//	if(mZMotorFrame)
//    {
//    	mZMotorFrame->mMotorStatusTimer->Enabled = false;
//    }
//
//	if(mAngleMotorFrame)
//    {
//    	mAngleMotorFrame->mMotorStatusTimer->Enabled = false;
//    }
}


