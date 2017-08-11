#include <vcl.h>
#pragma hdrstop
#include "TArrayCamRequestFrame.h"
#include "mtkVCLUtils.h"
#include "core/atProcess.h"
#include "arraybot/process/atArrayCamRequestProcess.h"
#include "mtkLogger.h"
#include "arraybot/atArrayBot.h"
#include "arraycam/atArrayCamProtocol.h"
#pragma package(smart_init)
#pragma link "TSTDStringLabeledEdit"
#pragma link "TFloatLabeledEdit"
#pragma link "TIntegerLabeledEdit"
#pragma resource "*.dfm"

using namespace mtk;
TArrayCamRequestFrame *ArrayCamRequestFrame;
//---------------------------------------------------------------------------

int TArrayCamRequestFrame::mFrameNr = 0;

extern ArrayCamProtocol gArrayCamProtocol;
__fastcall TArrayCamRequestFrame::TArrayCamRequestFrame(ProcessSequencer& ps, TComponent* Owner)
	: TFrame(Owner),
     mProcessSequencer(ps)
{
    TFrame::Name = vclstr("ArrayCamFrame_" + mtk::toString(++mFrameNr));
	mArrayCamRequestCB->Clear();
	ArrayCamProtocol ap;
	//    string test = ap[acrStartVideoRecorder];

    //The combox items holds Arraycam requests text and enum values
    //If new type of request is added, it have to be made available the the user here
	mArrayCamRequestCB->Items->AddObject(vclstr(ap[acrStartVideoRecorder]),		reinterpret_cast<TObject*>(acrStartVideoRecorder));
	mArrayCamRequestCB->Items->AddObject(vclstr(ap[acrStopVideoRecorder]), 		reinterpret_cast<TObject*>(acrStopVideoRecorder));
	mArrayCamRequestCB->Items->AddObject(vclstr(ap[acrTakeSnapShot]), 			reinterpret_cast<TObject*>(acrTakeSnapShot));
	mArrayCamRequestCB->Items->AddObject(vclstr(ap[acrEnableBarcodeScanner]), 	reinterpret_cast<TObject*>(acrEnableBarcodeScanner));
	mArrayCamRequestCB->Items->AddObject(vclstr(ap[acrDisableBarcodeScanner]), 	reinterpret_cast<TObject*>(acrDisableBarcodeScanner));
	mArrayCamRequestCB->Items->AddObject(vclstr(ap[acrSetZoomAndFocus]), 		reinterpret_cast<TObject*>(acrSetZoomAndFocus));
}

void TArrayCamRequestFrame::populate(Process* p)
{
	//Populate, update frame with data from process
    mArrayCamRequest = dynamic_cast<ArrayCamRequestProcess*>(p);
    if(!p)
    {
    	EnableDisableFrame(this, false);
        return;
    }

    mNameEdit->setValue(mArrayCamRequest->getProcessName());

    //What kind of request do we have?
    for(int i = 0; i < mArrayCamRequestCB->Items->Count; i++)
    {
    	ACMessageID ar = (ACMessageID) mArrayCamRequestCB->Items->Objects[i];

		if(mArrayCamRequest->getRequest() == ar)
        {
        	mArrayCamRequestCB->ItemIndex = i;

            if(ar == acrSetZoomAndFocus)
            {
	           	FocusZoomGB->Visible = true;
                FocusE->setValue(mArrayCamRequest->getParameter1().getValue());
                ZoomE->setValue(mArrayCamRequest->getParameter2().getValue());
            }
            else
            {
	           	FocusZoomGB->Visible = false;
            }
            break;
        }
    }

  	EnableDisableFrame(this, true);
}

//---------------------------------------------------------------------------
void __fastcall TArrayCamRequestFrame::mEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkReturn)
    {
    	mArrayCamRequest->setProcessName(mNameEdit->getValue());
    }
}

//---------------------------------------------------------------------------
void __fastcall TArrayCamRequestFrame::mArrayCamRequestCBCloseUp(TObject *Sender)
{
    if(mArrayCamRequest)
    {
		ACMessageID r = (ACMessageID) mArrayCamRequestCB->Items->Objects[mArrayCamRequestCB->ItemIndex];
        mArrayCamRequest->setRequest(r);
       	FocusZoomGB->Visible = r == acrSetZoomAndFocus ? true : false;
        mProcessSequencer.saveCurrent();
    }
}

//---------------------------------------------------------------------------
void __fastcall TArrayCamRequestFrame::IntEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	TIntegerLabeledEdit* e = dynamic_cast<TIntegerLabeledEdit*>(Sender);

	if(Key == vkReturn)
    {
        if(e == FocusE)
        {
        	mArrayCamRequest->getParameter1().setValue(e->getValue());
        }

        if(e == ZoomE)
        {
        	mArrayCamRequest->getParameter2().setValue(e->getValue());
        }
    }
}


