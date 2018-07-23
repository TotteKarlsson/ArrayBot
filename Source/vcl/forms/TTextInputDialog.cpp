#include <vcl.h>
#pragma hdrstop
#include "TTextInputDialog.h"
#include "dslVCLUtils.h"

using namespace dsl;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTStdStringLabeledEdit"
#pragma resource "*.dfm"
TTextInputDialog *TextInputDialog;
//---------------------------------------------------------------------------
__fastcall TTextInputDialog::TTextInputDialog(TComponent* Owner)
	: TForm(Owner),
    mProcessReturn(true)
{
}

//---------------------------------------------------------------------------
string TTextInputDialog::getText()
{
	StringList strs;
    for(int i = 0; i < mInfoMemo->Lines->Count; i++)
    {
    	strs.append(stdstr(mInfoMemo->Lines->Strings[i]));
    }
	return strs.asString();
}

//---------------------------------------------------------------------------
void __fastcall TTextInputDialog::mInfoMemoChange(TObject *Sender)
{
	mOkBtn->Enabled = (mInfoMemo->Modified) ? true : false;
}

void TTextInputDialog::setText(const string& txt)
{
	StringList sl(txt, '\n');
    mInfoMemo->Clear();
    for(int i = 0; i < sl.size(); i++)
    {
		mInfoMemo->Lines->Add(vclstr(sl[i]));
    }

    mInfoMemo->SelStart = 0;//Memo1->GetTextLen();
    mInfoMemo->Perform(EM_SCROLLCARET, 0, 0);
}

void __fastcall TTextInputDialog::mInfoMemoClick(TObject *Sender)
{
//    STDStringLabeledEdit1->SelectAll();
}

//---------------------------------------------------------------------------
void __fastcall TTextInputDialog::FormShow(TObject *Sender)
{
//    STDStringLabeledEdit1->SelectAll();
    ActiveControl = mInfoMemo;
    this->Update();
}

//---------------------------------------------------------------------------
void __fastcall TTextInputDialog::mInfoMemoKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift)
{

//	if(!mProcessReturn)
//    {
//    	return;
//    }
//
//	if(Key == vkReturn && STDStringLabeledEdit1->Text.Length() > 0)
//    {
//    	this->ModalResult = mrOk;
//    }
}


void __fastcall TTextInputDialog::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == vkEscape)
    {
     	this->ModalResult = mrCancel;
    }
}


