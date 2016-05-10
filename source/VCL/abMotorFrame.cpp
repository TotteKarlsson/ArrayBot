#include <vcl.h>
#pragma hdrstop
#include "abMotorFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "mtkFloatLabeledEdit"
#pragma link "TIntLabel"
#pragma resource "*.dfm"
TMotorFrame *MotorFrame;
//---------------------------------------------------------------------------
__fastcall TMotorFrame::TMotorFrame(TComponent* Owner)
	: TFrame(Owner),
    mMotor(NULL)
{
}

//---------------------------------------------------------------------------
void TMotorFrame::assignMotor(APTMotor* m)
{
	mMotor = m;
}
