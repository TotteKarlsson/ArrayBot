#include <vcl.h>
#pragma hdrstop
#include "TStringInputDialog.h"
#include "dslVCLUtils.h"

using namespace dsl;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTStdStringLabeledEdit"
#pragma resource "*.dfm"
TStringInputDialog *StringInputDialog;
//---------------------------------------------------------------------------
__fastcall TStringInputDialog::TStringInputDialog(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
string TStringInputDialog::getText()
{
	return STDStringLabeledEdit1->getValue();
}

//---------------------------------------------------------------------------
void __fastcall TStringInputDialog::STDStringLabeledEdit1Change(TObject *Sender)
{
	mOkBtn->Enabled = (STDStringLabeledEdit1->GetTextLen() > 0) ? true : false;
}

void TStringInputDialog::setText(const string& txt)
{
	STDStringLabeledEdit1->setValue(txt);
}

void __fastcall TStringInputDialog::STDStringLabeledEdit1Click(TObject *Sender)
{
    STDStringLabeledEdit1->SelectAll();
}

//---------------------------------------------------------------------------
void __fastcall TStringInputDialog::FormShow(TObject *Sender)
{
    STDStringLabeledEdit1->SelectAll();
    ActiveControl = STDStringLabeledEdit1;
    this->Update();
}

//---------------------------------------------------------------------------
void __fastcall TStringInputDialog::STDStringLabeledEdit1KeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift)
{
	if(Key == vkReturn && STDStringLabeledEdit1->Text.Length() > 0)
    {
    	this->ModalResult = mrOk;
    }
    else if(Key == vkEscape)
    {
		this->ModalResult = mrCancel;
    }
}



