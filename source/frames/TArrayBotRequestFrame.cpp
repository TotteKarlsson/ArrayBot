#include <vcl.h>
#pragma hdrstop
#include "TArrayBotRequestFrame.h"
#include "arraybot/process/atArrayBotRequestProcess.h"
#include "core/atArrayBotProtocol.h"
#include "dslVCLUtils.h"
#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma resource "*.dfm"

using namespace dsl;
TArrayBotRequestFrame *ArrayBotRequestFrame;
//---------------------------------------------------------------------------

int TArrayBotRequestFrame::mFrameNr = 0;

extern ArrayBotProtocol gArrayBotProtocol;
__fastcall TArrayBotRequestFrame::TArrayBotRequestFrame(ProcessSequencer& ps, TComponent* Owner)
	: TFrame(Owner),
     mProcessSequencer(ps)
{
    TFrame::Name = vclstr("ArrayBotFrame_" + dsl::toString(++mFrameNr));
	ArrayBotRequestCB->Clear();
	ArrayBotProtocol ap;
	//    string test = ap[acrStartVideoRecorder];

    //The combox items holds ArrayBot requests text and enum values
    //If new type of request is added, it have to be made available the the user here
//	ArrayBotRequestCB->Items->AddObject(vclstr(ap[acrSetMoveWhiskerForwardOn]),    	reinterpret_cast<TObject*>(acrSetMoveWhiskerForwardOn));
}

void TArrayBotRequestFrame::populate(Process* p)
{
	//Populate, update frame with data from process
    mArrayBotRequest = dynamic_cast<ArrayBotRequestProcess*>(p);
    if(!p)
    {
    	EnableDisableFrame(this, false);
        return;
    }

    NameEdit->setValue(mArrayBotRequest->getProcessName());

    //What kind of request do we have?
    for(int i = 0; i < ArrayBotRequestCB->Items->Count; i++)
    {
    	ABMessageID ar = (ABMessageID) ArrayBotRequestCB->Items->Objects[i];
		if(mArrayBotRequest->getRequest() == ar)
        {
        	ArrayBotRequestCB->ItemIndex = i;

//            if(ar == acrSetZoomAndFocus)
//            {
//                FocusE->setValue(mArrayBotRequest->getParameter1().getValue());
//                ZoomE->setValue(mArrayBotRequest->getParameter2().getValue());
//            }
//            else if (ar == acrSetLEDIntensity)
//            {
//	            LEDIntensityE->setValue(mArrayBotRequest->getParameter1().getValue());
//            }
            break;
        }
    }

    ArrayBotRequestCBCloseUp(NULL);
    FocusZoomGB->Align 	= alClient;
    LEDIntensityGB->Align 	= alClient;
  	EnableDisableFrame(this, true);
}

//---------------------------------------------------------------------------
void __fastcall TArrayBotRequestFrame::EditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkReturn)
    {
    	mArrayBotRequest->setProcessName(NameEdit->getValue());
   	    mProcessSequencer.saveCurrent();
    }
}

//---------------------------------------------------------------------------
void __fastcall TArrayBotRequestFrame::ArrayBotRequestCBCloseUp(TObject *Sender)
{
    if(mArrayBotRequest && ArrayBotRequestCB->ItemIndex >= 0)
    {
		ABMessageID r = (ABMessageID) ArrayBotRequestCB->Items->Objects[ArrayBotRequestCB->ItemIndex];
        mArrayBotRequest->setRequest(r);

       	FocusZoomGB->Visible 	= false;
       	LEDIntensityGB->Visible = false;
        switch(r)
        {
//            case acrSetZoomAndFocus:
//            	FocusZoomGB->Visible = true;
//	            FocusZoomGB->Align = alClient;
//            break;
//
//            case acrSetLEDIntensity:
//            	LEDIntensityGB->Visible = true;
//                LEDIntensityGB->Align = alClient;
//
//            break;
        }

        mProcessSequencer.saveCurrent();
    }
}

//---------------------------------------------------------------------------
void __fastcall TArrayBotRequestFrame::IntEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	TIntegerLabeledEdit* e = dynamic_cast<TIntegerLabeledEdit*>(Sender);

	if(Key == vkReturn)
    {
        if(e == FocusE)
        {
        	mArrayBotRequest->getParameter1().setValue(e->getValue());
        }

        if(e == ZoomE)
        {
        	mArrayBotRequest->getParameter2().setValue(e->getValue());
        }

        if(e == LEDIntensityE)
        {
        	mArrayBotRequest->getParameter1().setValue(e->getValue());
        }
	    mProcessSequencer.saveCurrent();
    }
}


