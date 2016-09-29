#include <vcl.h>
#pragma hdrstop
#include "TSlotFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSlotFrame *SlotFrame;
//---------------------------------------------------------------------------
__fastcall TSlotFrame::TSlotFrame(TComponent* Owner)
	: TFrame(Owner)
{
}

