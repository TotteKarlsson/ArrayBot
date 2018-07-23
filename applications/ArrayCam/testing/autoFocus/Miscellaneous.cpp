#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "TReticlePopupForm.h"
#include "dslLogger.h"
#include "forms/TLoggerForm.h"
#include "ArrayCamUtilities.h"
//---------------------------------------------------------------------------
using namespace dsl;
extern ArrayCamUtilities acu;

static HWND gOtherAppWindow = NULL;
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
		mCamera1.exitCamera();
    	Close();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenLoggerForm1Click(TObject *Sender)
{
	if(!LoggerForm)
    {
    	LoggerForm = new TLoggerForm(acu.AppRegistryRoot, this);
        LoggerForm->Show();
    }
    else
    {
    	LoggerForm->Visible = true;
    }
}

void __fastcall TMainForm::mMainPhotoPanelResize(TObject *Sender)
{
	FitToScreenAExecute(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mToggleLogPanelClick(TObject *Sender)
{
	FitToScreenAExecute(Sender);
}

void __fastcall TMainForm::mCameraStreamPanelDblClick(TObject *Sender)
{
//	this->BorderStyle = (this->BorderStyle == bsNone) ? bsSingle : bsNone;
}



