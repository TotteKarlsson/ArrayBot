#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{}

//---------------------------------------------------------------------------
void __fastcall TMainForm::AddUserBtnClick(TObject *Sender)
{
   usersCDS->Append();
   usersCDS->FieldValues["user_name"] = "New User";

   usersCDS->Post();
   usersCDS->ApplyUpdates(-1);
//   usersCDS->Refresh();
   usersDS->Refresh();
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
}


void __fastcall TMainForm::MaskEdit1Exit(TObject *Sender)
{
	// Extract the net and host address from the IP.
  	String IP = MaskEdit1->Text;
  	int net1 = IP.SubString(0, 3).TrimRight().ToInt();
  	int net2 = IP.SubString(5, 3).TrimRight().ToInt();
  	int host1 = IP.SubString(9, 3).TrimRight().ToInt();
  	int host2 = IP.SubString(13, 3).TrimRight().ToInt();

  // A range test that you cannot validate through edit masks
  if (net1 < 0 	|| net1 > 255 ||  net2 < 0 || net2 > 255 ||
      host1 < 0 || host1 > 255 || host2 < 0 || host2 > 255)
      {
    throw(Exception("Not a valid IP address."));
    }

}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ConnectToDBAExecute(TObject *Sender)
{
	if(mySQLC->Connected == false)
    {
   		mySQLC->Connected = true;
		ConnectToDBA->Caption = "Disconnect" ;
    }
    else
    {
		mySQLC->Connected = false;
		ConnectToDBA->Caption = "Connect";
    }
}


