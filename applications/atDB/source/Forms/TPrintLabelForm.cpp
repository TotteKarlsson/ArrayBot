#include <vcl.h>
#pragma hdrstop
#include "TPrintLabelForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma resource "*.dfm"
TPrintLabelForm *PrintLabelForm;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TPrintLabelForm::TPrintLabelForm(TComponent* Owner)
	: TForm(Owner)
{
	if(!mLabelPrinter.load("TSCLIB.dll"))
    {
    	Log(lError) << "Failed to load mTSC library..";
    }
}

//---------------------------------------------------------------------------
void __fastcall TPrintLabelForm::mPrintButtonClick(TObject *Sender)
{
	//Just print label content
    if(!mLabelPrinter.isLoaded())
    {
    	MessageDlg("The printer is not loaded..!\nThis is a bad ERROR. A DLL is missing.", mtWarning, TMsgDlgButtons() << mbOK, 0);
    }

	mLabelPrinter.printFreshBatchLabel(stdstr(mLblToPrint->Caption), mCopiesLbl->getValue());
}

void __fastcall TPrintLabelForm::setup(const string& lbl)
{
	mLblToPrint->Caption = vclstr(lbl);
}

void __fastcall TPrintLabelForm::FormShow(TObject *Sender)
{
	;
}

//---------------------------------------------------------------------------
void __fastcall TPrintLabelForm::Button1Click(TObject *Sender)
{
	Close();
}


