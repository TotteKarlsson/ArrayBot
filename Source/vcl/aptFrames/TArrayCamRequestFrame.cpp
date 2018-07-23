#include <vcl.h>
#pragma hdrstop
#include "TArrayCamRequestFrame.h"
#include "dslVCLUtils.h"
#include "core/atProcess.h"
#include "arraybot/process/atArrayCamRequestProcess.h"
#include "dslLogger.h"
#include "arraybot/atArrayBot.h"
#include "core/atArrayCamProtocol.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------


using namespace dsl;
TArrayCamRequestFrame *ArrayCamRequestFrame;
//---------------------------------------------------------------------------

int TArrayCamRequestFrame::mFrameNr = 0;

extern ArrayCamProtocol gArrayCamProtocol;
__fastcall TArrayCamRequestFrame::TArrayCamRequestFrame(ProcessSequencer& ps, TComponent* Owner)
    : TFrame(Owner),
     mProcessSequencer(ps)
{
    TFrame::Name = vclstr("ArrayCamFrame_" + dsl::toString(++mFrameNr));
    ArrayCamRequestCB->Clear();
    ArrayCamProtocol ap;
    //    string test = ap[acrStartVideoRecorder];

    //The combox items holds Arraycam requests text and enum values
    //If new type of request is added, it have to be made available the the user here
    ArrayCamRequestCB->Items->AddObject(vclstr(ap[acrStartVideoRecorder]),              reinterpret_cast<TObject*>(acrStartVideoRecorder));
    ArrayCamRequestCB->Items->AddObject(vclstr(ap[acrStopVideoRecorder]),               reinterpret_cast<TObject*>(acrStopVideoRecorder));
    ArrayCamRequestCB->Items->AddObject(vclstr(ap[acrTakeSnapShot]),                    reinterpret_cast<TObject*>(acrTakeSnapShot));
    ArrayCamRequestCB->Items->AddObject(vclstr(ap[acrEnableBarcodeScanner]),            reinterpret_cast<TObject*>(acrEnableBarcodeScanner));
    ArrayCamRequestCB->Items->AddObject(vclstr(ap[acrDisableBarcodeScanner]),           reinterpret_cast<TObject*>(acrDisableBarcodeScanner));
    ArrayCamRequestCB->Items->AddObject(vclstr(ap[acrSetZoomAndFocus]),                 reinterpret_cast<TObject*>(acrSetZoomAndFocus));
    ArrayCamRequestCB->Items->AddObject(vclstr(ap[acrStartUC7]),                        reinterpret_cast<TObject*>(acrStartUC7));
    ArrayCamRequestCB->Items->AddObject(vclstr(ap[acrStopUC7]),                         reinterpret_cast<TObject*>(acrStopUC7));
    ArrayCamRequestCB->Items->AddObject(vclstr(ap[acrSetLEDIntensity]),                 reinterpret_cast<TObject*>(acrSetLEDIntensity));
    ArrayCamRequestCB->Items->AddObject(vclstr(ap[acrSetMoveWhiskerForwardOff]),        reinterpret_cast<TObject*>(acrSetMoveWhiskerForwardOff));
    ArrayCamRequestCB->Items->AddObject(vclstr(ap[acrSetMoveWhiskerForwardOn]),         reinterpret_cast<TObject*>(acrSetMoveWhiskerForwardOn));
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

    NameEdit->setValue(mArrayCamRequest->getProcessName());

    //What kind of request do we have?
    for(int i = 0; i < ArrayCamRequestCB->Items->Count; i++)
    {
        ACMessageID ar = (ACMessageID) ArrayCamRequestCB->Items->Objects[i];
        if(mArrayCamRequest->getRequest() == ar)
        {
            ArrayCamRequestCB->ItemIndex = i;

            if(ar == acrSetZoomAndFocus)
            {
                FocusE->setValue(mArrayCamRequest->getParameter1().getValue());
                ZoomE->setValue(mArrayCamRequest->getParameter2().getValue());
            }
            else if (ar == acrSetLEDIntensity)
            {
                LEDIntensityE->setValue(mArrayCamRequest->getParameter1().getValue());
            }
            break;
        }
    }

    ArrayCamRequestCBCloseUp(NULL);
    FocusZoomGB->Align     = alClient;
    LEDIntensityGB->Align     = alClient;
      EnableDisableFrame(this, true);
}

//---------------------------------------------------------------------------
void __fastcall TArrayCamRequestFrame::EditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == vkReturn)
    {
        mArrayCamRequest->setProcessName(NameEdit->getValue());
           mProcessSequencer.saveCurrent();
    }
}

//---------------------------------------------------------------------------
void __fastcall TArrayCamRequestFrame::ArrayCamRequestCBCloseUp(TObject *Sender)
{
    if(mArrayCamRequest && ArrayCamRequestCB->ItemIndex >= 0)
    {
        ACMessageID r = (ACMessageID) ArrayCamRequestCB->Items->Objects[ArrayCamRequestCB->ItemIndex];
        mArrayCamRequest->setRequest(r);

           FocusZoomGB->Visible     = false;
           LEDIntensityGB->Visible = false;
        switch(r)
        {
            case acrSetZoomAndFocus:
                FocusZoomGB->Visible = true;
                FocusZoomGB->Align = alClient;
            break;

            case acrSetLEDIntensity:
                LEDIntensityGB->Visible = true;
                LEDIntensityGB->Align = alClient;

            break;
        }

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

        if(e == LEDIntensityE)
        {
            mArrayCamRequest->getParameter1().setValue(e->getValue());
        }
        mProcessSequencer.saveCurrent();
    }
}


