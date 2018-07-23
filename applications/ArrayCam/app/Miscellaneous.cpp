#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "TReticlePopupForm.h"
#include "dslLogger.h"
#include "forms/TAboutForm.h"
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
		mLogLevel.setReference(&(LoggerForm->mLogLevel));
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

	if(mReticleForm.get() && mReticleForm->Visible)
    {
        mReticleForm->mReticleCenterXTB->Min = -mPB->Width/2;
        mReticleForm->mReticleCenterXTB->Max = mPB->Width/2;
        mReticleForm->mReticleCenterYTB->Min = -mPB->Height/2;
        mReticleForm->mReticleCenterYTB->Max = mPB->Height/2;
    }
}

void __fastcall	TMainForm::updateTemperature(double t)
{
}

void __fastcall	TMainForm::updateHumidity(double h)
{
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

//---------------------------------------------------------------------------
int	TMainForm::getCOMPortNumber()
{
	return mUC7ComportCB->ItemIndex + 1;
}

void __fastcall TMainForm::About1Click(TObject *Sender)
{
	TAboutForm* f = new TAboutForm(this);
    f->ShowModal();
    delete f;
}

