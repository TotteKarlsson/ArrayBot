//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TMotorMoveProcessFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma resource "*.dfm"
TMotorMoveProcessFrame *MotorMoveProcessFrame;

//---------------------------------------------------------------------------
__fastcall TMotorMoveProcessFrame::TMotorMoveProcessFrame(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
