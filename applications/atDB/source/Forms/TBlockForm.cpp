#include <vcl.h>
#pragma hdrstop
#include "TBlockForm.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TBlockForm *BlockForm;

//---------------------------------------------------------------------------
__fastcall TBlockForm::TBlockForm(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TBlockForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}



