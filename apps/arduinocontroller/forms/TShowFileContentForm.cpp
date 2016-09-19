#include <vcl.h>
#pragma hdrstop

#include "TShowFileContentForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TShowFileContentForm *ShowFileContentForm;

//---------------------------------------------------------------------------
__fastcall TShowFileContentForm::TShowFileContentForm(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TShowFileContentForm::FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

//---------------------------------------------------------------------------
void __fastcall TShowFileContentForm::Button1Click(TObject *Sender)
{
    Close();
}


