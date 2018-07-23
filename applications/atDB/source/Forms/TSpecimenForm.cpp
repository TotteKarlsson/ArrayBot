#include <vcl.h>
#pragma hdrstop
#include "TSpecimenForm.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TSpecimenForm *SpecimenForm;

//---------------------------------------------------------------------------
__fastcall TSpecimenForm::TSpecimenForm(TComponent* Owner)
	: TForm(Owner)
{}

//---------------------------------------------------------------------------
void __fastcall TSpecimenForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_ESCAPE)
    {
        CancelBtn->Click();
    }
}




