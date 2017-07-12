#include <vcl.h>
#pragma hdrstop
#include "TTimeDelayFrame.h"
#include "mtkVCLUtils.h"
#include "core/atProcess.h"
#include "arraybot/process/atTimeDelay.h"
#include "mtkLogger.h"
#include "arraybot/atArrayBot.h"

#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TIntegerLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"

using namespace mtk;

TTimeDelayFrame *TimeDelayFrame;
//---------------------------------------------------------------------------

__fastcall TTimeDelayFrame::TTimeDelayFrame(TComponent* Owner)
	: TFrame(Owner)
{}

void TTimeDelayFrame::populate(Process* p)
{
	rePopulate(p);
}

void TTimeDelayFrame::rePopulate(Process* p)
{
	//Populate, update frame with data from process
    mTimeDelay = dynamic_cast<TimeDelay*>(p);
    if(!p)
    {
    	EnableDisableFrame(this, false);
        return;
    }

    long val = mTimeDelay->getTimeDelay().totalMilliseconds();
   	mTimeDelayE->setValue(val);
    mNameEdit->setValue(mTimeDelay->getProcessName());

  	EnableDisableFrame(this, true);
}

//---------------------------------------------------------------------------
void __fastcall TTimeDelayFrame::mEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkReturn && mTimeDelay != NULL)
    {
        mTimeDelay->setTimeDelay(mTimeDelayE->getValue()*Poco::Timespan::MILLISECONDS);
    	mTimeDelay->setProcessName(mNameEdit->getValue());
    }
}


