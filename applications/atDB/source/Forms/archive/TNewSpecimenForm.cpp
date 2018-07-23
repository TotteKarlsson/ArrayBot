#include <vcl.h>
#pragma hdrstop
#include "TNewSpecimenForm.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TNewSpecimenForm *NewSpecimenForm;

//---------------------------------------------------------------------------
__fastcall TNewSpecimenForm::TNewSpecimenForm(TComponent* Owner)
	: TForm(Owner)
{

}


//---------------------------------------------------------------------------
void __fastcall TNewSpecimenForm::FormShow(TObject *Sender)
{
//	DBEdit1->
	DBEdit1->Refresh();
}


//---------------------------------------------------------------------------
void __fastcall TNewSpecimenForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_ESCAPE)
    {
        CancelBtn->Click();
    }
}



