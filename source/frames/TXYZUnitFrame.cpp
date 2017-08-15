#include <vcl.h>
#pragma hdrstop
#include "TXYZUnitFrame.h"
#include "arraybot/atXYZUnit.h"
#include "mtkVCLUtils.h"
#include "arraybot/apt/atAPTMotor.h"
#include "TMotorFrame.h"
#include "arraybot/atWhiskerUnit.h"
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
{
    TFrame::Name = vclstr("XYZUnitFrame_" + mtk::toString(++mFrameNr));
}

//---------------------------------------------------------------------------
void TXYZUnitFrame::assignUnit(XYZUnit* u)
{
	mUnit = u;
    if(mUnit)
    {
        vector<APTMotor*> mtrs = mUnit->getAllMotors();
        int frameWidth (0);
        for(int i = 0; i < mtrs.size(); i++)
        {
            TMotorFrame* f = new TMotorFrame(mtrs[i]->getSerial(), this);
            f->SetParentComponent(this);
            f->Align = alLeft;
            f->assignMotor(mtrs[i]);
            mFrames.push_back(f);
            if(i == 0)
            {
	            frameWidth = f->Width;
            }
        }
        this->Width = mtrs.size() * frameWidth + 24;
    }
}

void TXYZUnitFrame::disable()
{
	for(int i = 0; i < mFrames.size(); i++)
    {
		mFrames[i]->MotorStatusTimer->Enabled = false;
    }
}

void TXYZUnitFrame::enable()
{
	for(int i = 0; i < mFrames.size(); i++)
    {
		mFrames[i]->MotorStatusTimer->Enabled = true;
    }
}



