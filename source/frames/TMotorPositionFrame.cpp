#include <vcl.h>
#pragma hdrstop
#include "TMotorPositionFrame.h"
#include "mtkVCLUtils.h"
#include "arraybot/apt/atAPTMotor.h"

using namespace mtk;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMotorPositionFrame *MotorPositionFrame;

int	TMotorPositionFrame::mFrameNr = 0;
//---------------------------------------------------------------------------
__fastcall TMotorPositionFrame::TMotorPositionFrame(TComponent* Owner, const APTMotor* mtr)
	: TFrame(Owner),
    mMotor(mtr)
{
    TFrame::Name = vclstr("PosFrame_" + mtk::toString(++mFrameNr));
	PullPosTimer->Enabled = true;
    MotorPositionGB->Caption = vclstr(mtr->getName());
}

void TMotorPositionFrame::assignMotor(APTMotor* m)
{
	mMotor = m;
	PullPosTimer->Enabled = true;
}

void __fastcall TMotorPositionFrame::PullPosTimerTimer(TObject *Sender)
{
	string dblFormat("%.3f");
    if(mMotor)
    {
        mPosL->Caption = vclstr(mtk::toString(mMotor->getPosition(), dblFormat));
    }
    else
    {
		mPosL->Caption = "-";
    }
}


