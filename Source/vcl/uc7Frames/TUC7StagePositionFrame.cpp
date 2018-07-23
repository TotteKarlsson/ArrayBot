#include <vcl.h>
#pragma hdrstop
#include "TUC7StagePositionFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerEdit"
#pragma link "dslTIntLabel"
#pragma link "dslTIntLabel"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TUC7StagePositionFrame *UC7StagePositionFrame;

//---------------------------------------------------------------------------
__fastcall TUC7StagePositionFrame::TUC7StagePositionFrame(TComponent* Owner)
	: TFrame(Owner),
    mUC7Value(0)
{}

//---------------------------------------------------------------------------
void TUC7StagePositionFrame::setValue(unsigned int absValue)
{
   	mUC7Value = (absValue >= 100010) ? 100010 : absValue;
	AbsPosE->setValue(mUC7Value);
   	updateFromInput(AbsPosE->getValue());
}

//---------------------------------------------------------------------------
unsigned int TUC7StagePositionFrame::getValue()
{
	return mUC7Value;
}

//---------------------------------------------------------------------------
void __fastcall TUC7StagePositionFrame::AbsPosEKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift)
{
	if(Key == VK_RETURN)
    {
    	updateFromInput(AbsPosE->getValue());
    }
}

//---------------------------------------------------------------------------
void TUC7StagePositionFrame::updateFromInput(unsigned int input)
{
	mUC7Value = input;
	//update from input value
    ///Input number x 100 -> value in nm
    int nmVal = input * 100;
    int mm = (nmVal/10000000 % 10) * 10  + (nmVal/1000000 % 10);
    int um = (nmVal/100000   % 10) * 100 + (nmVal/10000   % 10) * 10 + (nmVal/1000 % 10);
	int nm = (nmVal/100 % 10) * 100;

    ValueMM->setValue(mm);
    Valueum->setValue(um);
    Valuenm->setValue(nm);
}

//---------------------------------------------------------------------------
void __fastcall TUC7StagePositionFrame::posEdit(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_RETURN)
    {
		//Updated position from edits
    	unsigned val = ValueMM->getValue() * 1e6 + Valueum->getValue() * 1e3 + Valuenm->getValue();
		setValue(val/100);
    }
}


