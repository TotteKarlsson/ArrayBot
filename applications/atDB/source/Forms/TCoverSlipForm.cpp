#include <vcl.h>
#pragma hdrstop
#include "TCoverSlipForm.h"
#include "TPGCoverSlipDataModule.h"
#include "dslStringUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

using namespace dsl;


TCoverSlipForm *CoverSlipForm;

__fastcall TCoverSlipForm::TCoverSlipForm(const string& csID, TComponent* Owner)
	: TForm(Owner),
    mBarCode(csID)
{
}

//---------------------------------------------------------------------------
void __fastcall TCoverSlipForm::FormShow(TObject *Sender)
{
	//Try to select coverslip
//    csPGDM->csCDS
	initForm();
}

void TCoverSlipForm::initForm()
{
	if(mBarCode.size() && mBarCode[0] == 'C')
    {
    	mBarCode.erase(0, 1);
    }

	CoverslipIDCB->KeyValue = mBarCode.c_str();
}

void __fastcall TCoverSlipForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
    else if(Key == VK_RETURN)
    {
    	string bc(mBCBuilder.getBarCode());
    	//handle barcode
        bc = trimChars(bc,"\r \n");
        if(bc.size() == 8 && bc[0] == 'C')
        {
        	Log(lInfo) << "Current barcode is: " << bc;
			mBarCode = bc;
           	initForm();
        }
        mBCBuilder.reset();
    }
}
void __fastcall TCoverSlipForm::FormKeyPress(TObject *Sender, System::WideChar &Key)          
{
    //Check barcode from reader
    mBCBuilder.build((char) Key);	
}


