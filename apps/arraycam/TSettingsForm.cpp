#include <vcl.h>
#pragma hdrstop
#include "TSettingsForm.h"
#include <sstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "TPropertyCheckBox"
#pragma resource "*.dfm"
TSettingsForm *SettingsForm;

using namespace std;
//---------------------------------------------------------------------------
__fastcall TSettingsForm::TSettingsForm(TMainForm& mf)
	: TForm(&mf),
    mMainForm(mf)
{
	UIUpdateTimer->Enabled = true;

    //Bind properties
    mAutoGainCB->setReference(mMainForm.mAutoGain.getReference());
	mAutoGainCB->Update();

    mAutoExposureCB->setReference(mMainForm.mAutoExposure.getReference());
	mAutoExposureCB->Update();

    mVerticalMirrorCB->setReference(mMainForm.mVerticalMirror.getReference());
	mVerticalMirrorCB->Update();

    mHorizontalMirrorCB->setReference(mMainForm.mHorizontalMirror.getReference());
	mHorizontalMirrorCB->Update();
}

//---------------------------------------------------------------------------
void __fastcall TSettingsForm::mASStartBtnClick(TObject *Sender)
{
	if(mASStartBtn->Caption == "Start")
    {
    	mMainForm.mLightsArduinoClient.connect(mArduinoServerPortE->getValue());
        mASStartBtn->Caption == "Connecting";
        mMainForm.mLightsArduinoClient.getStatus();
    }
    else
    {
    	mMainForm.mLightsArduinoClient.disConnect();
    }
}

//--------------------------------------------------------------------------
void __fastcall TSettingsForm::UIUpdateTimerTimer(TObject *Sender)
{
   	mASStartBtn->Caption 			= mMainForm.mLightsArduinoClient.isConnected()	? "Stop" : "Start";
	mArduinoServerPortE->Enabled 	= !mMainForm.mLightsArduinoClient.isConnected();
}

//---------------------------------------------------------------------------
void __fastcall TSettingsForm::mVerticalMirrorCBClick(TObject *Sender)
{
    HCAM hCam = mMainForm.mCamera.GetCameraHandle();
	if(mVerticalMirrorCB->Checked)
    {
		is_SetRopEffect (hCam, IS_SET_ROP_MIRROR_LEFTRIGHT, 1, 0);
    }
    else
    {
		is_SetRopEffect (hCam, IS_SET_ROP_MIRROR_LEFTRIGHT, 0, 0);
    }
	mVerticalMirrorCB->OnClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TSettingsForm::mHorizontalMirrorCBClick(TObject *Sender)
{
    HCAM hCam = mMainForm.mCamera.GetCameraHandle();
	if(mHorizontalMirrorCB->Checked)
    {
		is_SetRopEffect (hCam, IS_SET_ROP_MIRROR_UPDOWN, 1, 0);
    }
    else
    {
		is_SetRopEffect (hCam, IS_SET_ROP_MIRROR_UPDOWN, 0, 0);
    }
	mHorizontalMirrorCB->OnClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TSettingsForm::AutoParaCBClick(TObject *Sender)
{
    HCAM hCam = mMainForm.mCamera.GetCameraHandle();
    TCheckBox* cb = dynamic_cast<TCheckBox*>(Sender);

    double dEnable;
	int ret;
    if(cb)
    {
    	dEnable = cb->Checked ? 1 : 0;
    }

    if(cb == mAutoGainCB)
    {
	    mAutoGainCB->OnClick(Sender);
	    //Enable auto gain control:
	    ret = is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_GAIN, &dEnable, 0);
    }
    else if (cb == mAutoExposureCB)
    {
	    mAutoExposureCB->OnClick(Sender);
	    //Enable auto gain control:
	    ret = is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_SHUTTER, &dEnable, 0);
    }

    //Check return value;

    //Set brightness setpoint to 128:
    double nominal = 128;
    ret = is_SetAutoParameter (hCam, IS_SET_AUTO_REFERENCE, &nominal, 0);

//    //Return shutter control limit:
//    double maxShutter;
//    ret = is_SetAutoParameter (hCam, IS_GET_AUTO_SHUTTER_MAX, &maxShutter, 0);
}


void __fastcall TSettingsForm::Button1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------



void __fastcall TSettingsForm::FormClose(TObject *Sender, TCloseAction &Action)

{
	UIUpdateTimer->Enabled = false;
}
//---------------------------------------------------------------------------

