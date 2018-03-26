#include <vcl.h>
#pragma hdrstop
#include "TStopAndResumeFrame.h"
#include "dslVCLUtils.h"
#include "core/atProcess.h"
#include "arraybot/process/atStopAndResumeProcess.h"
#include "dslLogger.h"
#include "arraybot/atArrayBot.h"
#include "vcl/forms/TTextInputDialog.h"

#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"

using namespace dsl;

TStopAndResumeFrame *StopAndResumeFrame;
//---------------------------------------------------------------------------

__fastcall TStopAndResumeFrame::TStopAndResumeFrame(TComponent* Owner)
	: TFrame(Owner)
{}

void TStopAndResumeFrame::populate(Process* p)
{
	rePopulate(p);
}

void TStopAndResumeFrame::rePopulate(Process* p)
{
	//Populate, update frame with data from process
    mStopAndResume = dynamic_cast<StopAndResumeProcess*>(p);
    if(!p)
    {
    	EnableDisableFrame(this, false);
        return;
    }

    mNameEdit->setValue(mStopAndResume->getProcessName());
    mActionInfo->Caption = mStopAndResume->getInfoText().c_str();
  	EnableDisableFrame(this, true);
}

//---------------------------------------------------------------------------
void __fastcall TStopAndResumeFrame::mEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkReturn && mStopAndResume != NULL)
    {
    	mStopAndResume->setProcessName(mNameEdit->getValue());
    }
}

//---------------------------------------------------------------------------
void __fastcall TStopAndResumeFrame::mActionInfoClick(TObject *Sender)
{
    if(!mStopAndResume)
    {
    	return;
    }

	//Open text edit form
	TTextInputDialog* t = new TTextInputDialog(this);

    t->Caption = "Update Action Information";
	Process* p =  mStopAndResume;

    t->setText(mStopAndResume->getInfoText());

    if(t->ShowModal() == mrOk)
    {
		//Rename the currently selected sequence
    	string newText(t->getText());
		mStopAndResume->setInfoText(newText);
		mStopAndResume->write();
        mActionInfo->Caption = vclstr(newText);
    }
    delete t;
}


