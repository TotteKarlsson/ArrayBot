#include <vcl.h>
#pragma hdrstop
#include "TSlicesForm.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TSlicesForm *SlicesForm;

//---------------------------------------------------------------------------
__fastcall TSlicesForm::TSlicesForm(TComponent* Owner)
	: TForm(Owner)
{

}

//---------------------------------------------------------------------------
void __fastcall TSlicesForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_ESCAPE)
    {
        CancelBtn->Click();
    }
}

//---------------------------------------------------------------------------
void __fastcall TSlicesForm::DBLookupComboBoxDropDown(TObject *Sender)
{
	TDBLookupComboBox* b = dynamic_cast<TDBLookupComboBox*>(Sender);
    b->DropDownRows = 100;
}


