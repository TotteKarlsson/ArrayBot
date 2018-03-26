#include <vcl.h>
#pragma hdrstop
#include "TMotorPositionFrame.h"
#include "dslVCLUtils.h"
#include "arraybot/apt/atAPTMotor.h"

using namespace dsl;
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
    TFrame::Name = vclstr("PosFrame_" + dsl::toString(++mFrameNr));
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
        mPosL->Caption = vclstr(dsl::toString(mMotor->getPosition(), dblFormat));
    }
    else
    {
		mPosL->Caption = "-";
    }
}


