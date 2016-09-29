#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{}

//---------------------------------------------------------------------------
void __fastcall TForm1::AddUserBtnClick(TObject *Sender)
{
   usersCDS->Append();
   usersCDS->FieldValues["user_name"] = "New User";

   usersCDS->Post();
   usersCDS->ApplyUpdates(-1);
   usersCDS->Refresh();
   usersDS->Refresh();
}


//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
}


