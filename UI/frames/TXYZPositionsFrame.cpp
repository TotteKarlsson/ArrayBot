#include <vcl.h>
#pragma hdrstop
#include "TXYZPositionsFrame.h"
#include "abXYZUnit.h"
#include "mtkVCLUtils.h"
#include "abAPTMotor.h"

using namespace mtk;
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
    TFrame::Name = vclstr("PosFrame_" + mtk::toString(++mFrameNr));
	PullPosTimer->Enabled = true;
    GroupBox1->Caption = vclstr(u.getName());
}

void __fastcall TXYZPositionsFrame::PullPosTimerTimer(TObject *Sender)
{
    if(mUnit.getXMotor())
    {
        mXPosL->Caption = vclstr(mtk::toString(mUnit.getXMotor()->getPosition(), "%.4g") + " mm");
    }
    else
    {
		mXPosL->Caption = "-";
    }

    if(mUnit.getYMotor())
    {
        mYPosL->Caption = vclstr(mtk::toString(mUnit.getYMotor()->getPosition()));
    }
    else
    {
		mYPosL->Caption = "-";
    }

    if(mUnit.getZMotor())
    {
        mZPosL->Caption = vclstr(mtk::toString(mUnit.getZMotor()->getPosition()));
    }
    else
    {
		mZPosL->Caption = "-";
    }

    if(mUnit.getAngleMotor())
    {
        mAnglePosL->Caption = vclstr(mtk::toString(mUnit.getAngleMotor()->getPosition()));
    }
    else
    {
		mAnglePosL->Caption = "-";
    }


}


