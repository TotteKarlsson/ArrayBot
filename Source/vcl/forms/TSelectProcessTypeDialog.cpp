#include <vcl.h>
#pragma hdrstop
#include "TSelectProcessTypeDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSelectProcessTypeDialog *SelectProcessTypeDialog;

//---------------------------------------------------------------------------
__fastcall TSelectProcessTypeDialog::TSelectProcessTypeDialog(TComponent* Owner)
	: TForm(Owner),
    mIsOpenedForParallelProcess(false)
{
}

void TSelectProcessTypeDialog::setOpenedForParallelProcess()
{
	mIsOpenedForParallelProcess =true;
}

//---------------------------------------------------------------------------
void __fastcall TSelectProcessTypeDialog::FormShow(TObject *Sender)
{
	if(!mIsOpenedForParallelProcess)
    {
    	return;
    }
    //We will need to disable some items on this form
    for (int i = 0; i < mProcTypeRG->Items->Count; i++)
    {
        TRadioButton* b = mProcTypeRG->Buttons[i];
        if(b)
        {
           if( b->Caption == "Parallel Process" ||
	           b->Caption == "Time Delay" ||
	           b->Caption == "Stop/Start Dialog"
           )
            {
                b->Enabled = false;
            }
        }
    }

	mProcTypeRG->ItemIndex = 3;
}


