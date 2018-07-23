#include <vcl.h>
#pragma hdrstop
#include "TNewCaseForm.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TNewCaseForm *NewCaseForm;

//---------------------------------------------------------------------------
__fastcall TNewCaseForm::TNewCaseForm(TComponent* Owner)
	: TForm(Owner)
{

}

//---------------------------------------------------------------------------
void __fastcall TNewCaseForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_ESCAPE)
    {
        CancelBtn->Click();
    }
}



