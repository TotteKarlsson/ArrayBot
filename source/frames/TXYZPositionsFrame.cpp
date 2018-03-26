#include <vcl.h>
#pragma hdrstop
#include "TXYZPositionsFrame.h"
#include "arraybot/atXYZUnit.h"
#include "dslVCLUtils.h"
#include "arraybot/apt/atAPTMotor.h"

using namespace dsl;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TXYZPositionsFrame *XYZPositionsFrame;

int	TXYZPositionsFrame::mFrameNr = 0;
//---------------------------------------------------------------------------
__fastcall TXYZPositionsFrame::TXYZPositionsFrame(TComponent* Owner, const XYZUnit& u)
	: TFrame(Owner),
    mUnit(u)
{
    TFrame::Name = vclstr("PosFrame_" + dsl::toString(++mFrameNr));
	PullPosTimer->Enabled = true;
    GroupBox1->Caption = vclstr(u.getName());
}

void __fastcall TXYZPositionsFrame::PullPosTimerTimer(TObject *Sender)
{
	string dblFormat("%.3f");
    if(mUnit.getXMotor())
    {
        mXPosL->Caption = vclstr(dsl::toString(mUnit.getXMotor()->getPosition(), dblFormat));
    }
    else
    {
		mXPosL->Caption = "-";
    }

    if(mUnit.getYMotor())
    {
        mYPosL->Caption = vclstr(dsl::toString(mUnit.getYMotor()->getPosition(), dblFormat));
    }
    else
    {
		mYPosL->Caption = "-";
    }

    if(mUnit.getZMotor())
    {
        mZPosL->Caption = vclstr(dsl::toString(mUnit.getZMotor()->getPosition(), dblFormat));
    }
    else
    {
		mZPosL->Caption = "-";
    }

    if(mUnit.getAngleMotor())
    {
        mAnglePosL->Caption = vclstr(dsl::toString(mUnit.getAngleMotor()->getPosition(), dblFormat));
    }
    else
    {
		mAnglePosL->Caption = "-";
    }


}


