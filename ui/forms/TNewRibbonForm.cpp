#include <vcl.h>
#pragma hdrstop
#include "TNewRibbonForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNewRibbonForm *NewRibbonForm;
//---------------------------------------------------------------------------
__fastcall TNewRibbonForm::TNewRibbonForm(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TNewRibbonForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == vkEscape)
    {
    	Close();
    }
}

void __fastcall TNewRibbonForm::FormCloseQuery(TObject *Sender, bool &CanClose)

{
	Visible = false;
    CanClose = false;
}
//---------------------------------------------------------------------------
