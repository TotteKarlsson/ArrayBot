//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TPositionalTriggerFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma resource "*.dfm"
TPositionalTriggerFrame *PositionalTriggerFrame;
//---------------------------------------------------------------------------
__fastcall TPositionalTriggerFrame::TPositionalTriggerFrame(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
