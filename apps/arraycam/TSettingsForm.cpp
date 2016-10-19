#include <vcl.h>
#pragma hdrstop
#include "TSettingsForm.h"
#include <sstream>
#include "mtkVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "TPropertyCheckBox"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TSettingsForm *SettingsForm;

using namespace std;
using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TSettingsForm::TSettingsForm(TMainForm& mf)
	: TForm(&mf),
    mMainForm(mf)
{
    //Bind properties
    mAutoGainCB->setReference(mMainForm.mAutoGain.getReference());
	mAutoGainCB->Update();

    mAutoExposureCB->setReference(mMainForm.mAutoExposure.getReference());
	mAutoExposureCB->Update();

    mVerticalMirrorCB->setReference(mMainForm.mVerticalMirror.getReference());
	mVerticalMirrorCB->Update();

    mHorizontalMirrorCB->setReference(mMainForm.mHorizontalMirror.getReference());
	mHorizontalMirrorCB->Update();

    mPairLEDsCB->setReference(mMainForm.mPairLEDs.getReference());
    mPairLEDsCB->Update();

    mPhotoOutputBaseFolder->setReference(mMainForm.mSnapShotFolder.getReference());
    mMoviesFolderE->setReference(mMainForm.mMoviesFolder.getReference());    
}

//---------------------------------------------------------------------------
void __fastcall TSettingsForm::mASStartBtnClick(TObject *Sender)
{
	if(mASStartBtn->Caption == "Start")
    {
    	mMainForm.mLightsArduinoClient.connect(mArduinoServerPortE->getValue());
        mASStartBtn->Caption == "Connecting";
    }
    else
    {
    	mMainForm.mLightsArduinoClient.disConnect();
    }
}

//--------------------------------------------------------------------------
void __fastcall TSettingsForm::mUIUpdateTimerTimer(TObject *Sender)
{
   	mASStartBtn->Caption 			= mMainForm.mLightsArduinoClient.isConnected()	? "Stop" : "Start";
	mArduinoServerPortE->Enabled 	= !mMainForm.mLightsArduinoClient.isConnected();
   	enableDisableGroupBox(LightIntensitiesGB, !mArduinoServerPortE->Enabled);
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
    	mGainTB->Enabled = !cb->Checked;
	    mAutoGainCB->OnClick(Sender);
	    //Enable auto gain control:
	    ret = is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_GAIN, &dEnable, 0);
    }
    else if (cb == mAutoExposureCB)
    {
	    mAutoExposureCB->OnClick(Sender);

	    //Enable auto shutter:
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
	this->Visible = false;
}

//---------------------------------------------------------------------------
void __fastcall TSettingsForm::FormClose(TObject *Sender, TCloseAction &Action)

{
	mUIUpdateTimer->Enabled = false;
}

void __fastcall TSettingsForm::mPairLEDsCBClick(TObject *Sender)
{
	mPairLEDsCB->OnClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TSettingsForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
}

//---------------------------------------------------------------------------
void __fastcall TSettingsForm::BrowseForFolder(TObject *Sender)
{
	//Open Browse for folder dialog

	TButton* b = dynamic_cast<TButton*>(Sender);
    if(b == mBrowseForImagesFolderBtn)
    {
        string f = browseForFolder(mMainForm.mSnapShotFolder);
        if(!f.size())
        {
            return;
        }

    	mPhotoOutputBaseFolder->setValue(f);
    }
    else if(b == mBrowseForMoviesFolderBtn)
    {
        string f = browseForFolder(mMainForm.mSnapShotFolder);
        if(!f.size())
        {
            return;
        }

    	mMoviesFolderE->setValue(f);
    }    
}

//---------------------------------------------------------------------------
void __fastcall TSettingsForm::mGammaSBChange(TObject *Sender)
{
	int pos = mGammaSB->Position;
    mGamma->Caption = mtk::toString((double) pos/100.0).c_str();

    HCAM hCam = mMainForm.mCamera.GetCameraHandle();
	int ret = is_SetGamma (hCam, pos);

    switch(ret)
    {
	    case IS_GET_GAMMA:
        	Log(lInfo) << "Gamma setting succeded";
        break;

		case IS_CANT_COMMUNICATE_WITH_DRIVER:
        	Log(lError) << "Communication with the driver failed because no driver has been loaded.";
		break;

        case IS_CANT_OPEN_DEVICE:
        	Log(lError) << "An attempt to initialize or select the camera failed (no camera connected or initialization error).";
    	break;

		case IS_INVALID_CAMERA_HANDLE:
        	Log(lError) << "Invalid camera handle";
        break;

		case IS_INVALID_PARAMETER:
        	Log(lError) << "One of the submitted parameters is outside the \
valid range or is not supported for this sensor or \
is not available in this mode.";
		break;

        case IS_IO_REQUEST_FAILED:
        	Log(lError) << "An IO request from the uc480 driver failed. \
Possibly the versions of the uc480.dll (API) and \
the driver file (uc480_usb.sys) do not match. ";
		break;

        case IS_NO_SUCCESS:
        	Log(lError) << "General error message";
        break;

        case IS_NOT_SUPPORTED:
        	Log(lError) <<"The camera model used here does not support this function or setting.";
		break;

		case IS_SUCCESS:
        	Log(lInfo) << "Function executed successfully";
        break;

        default:
        	Log(lInfo) << "Unknown return value";
        break;
    }
}

//---------------------------------------------------------------------------
void __fastcall TSettingsForm::SettingsChange(TObject *Sender)
{
	TTrackBar* tb = dynamic_cast<TTrackBar*>(Sender);
    if(!tb)
    {
    	return;
    }

   	int pos = tb->Position;
    if(tb == mFrontLEDTB)
    {
    	if(mMainForm.mPairLEDs.getValue() == true)
        {
        	if(mBackLEDTB->Position != mFrontLEDTB->Position)
            {
				mBackLEDTB->Position = mFrontLEDTB->Position;
            }
        }

        if(tb->Tag != 1) //Means we are updating UI from thread
        {
        	stringstream s;
	        s<<"SET_FRONT_LED_INTENSITY="<<pos;
	        mMainForm.mLightsArduinoClient.request(s.str());
        }
        mFrontLEDLbl->Caption = "Front LED (" + IntToStr(pos) + ")";
    }
    else if(tb == mBackLEDTB)
    {
        if(tb->Tag != 1) //Means we are updating UI
        {
	        stringstream s;
	        s<<"SET_BACK_LED_INTENSITY="<<pos;
    	    mMainForm.mLightsArduinoClient.request(s.str());
        }
        mBackLEDLbl->Caption = "Back LED (" + IntToStr(pos) + ")";

    }
    else if(tb == mCoaxTB)
    {
        if(tb->Tag != 1) //Means we are updating UI
        {
			stringstream s;
	        s<<"SET_COAX_INTENSITY="<<pos;
    	    mMainForm.mLightsArduinoClient.request(s.str());
        }
        mCoaxLbl->Caption = "Coax (" + IntToStr(pos) + ")";
    }
}

//---------------------------------------------------------------------------
void __fastcall TSettingsForm::FormHide(TObject *Sender)
{
	mUIUpdateTimer->Enabled = false;
}


//---------------------------------------------------------------------------
void __fastcall TSettingsForm::FormShow(TObject *Sender)
{
	mUIUpdateTimer->Enabled = true;
}


void __fastcall TSettingsForm::mGainTBChange(TObject *Sender)
{
	int pos = mGainTB->Position/10;
    mGainLbl->Caption = mtk::toString(pos).c_str();

    HCAM hCam = mMainForm.mCamera.GetCameraHandle();
	int ret = is_SetHardwareGain(hCam, pos, pos, pos ,pos);

    switch(ret)
    {
	    case IS_GET_GAMMA:
        	Log(lInfo) << "Gamma setting succeded";
        break;

		case IS_CANT_COMMUNICATE_WITH_DRIVER:
        	Log(lError) << "Communication with the driver failed because no driver has been loaded.";
		break;

        case IS_CANT_OPEN_DEVICE:
        	Log(lError) << "An attempt to initialize or select the camera failed (no camera connected or initialization error).";
    	break;

		case IS_INVALID_CAMERA_HANDLE:
        	Log(lError) << "Invalid camera handle";
        break;

		case IS_INVALID_PARAMETER:
        	Log(lError) << "One of the submitted parameters is outside the \
valid range or is not supported for this sensor or \
is not available in this mode.";
		break;

        case IS_IO_REQUEST_FAILED:
        	Log(lError) << "An IO request from the uc480 driver failed. \
Possibly the versions of the uc480.dll (API) and \
the driver file (uc480_usb.sys) do not match. ";
		break;

        case IS_NO_SUCCESS:
        	Log(lError) << "General error message";
        break;

        case IS_NOT_SUPPORTED:
        	Log(lError) <<"The camera model used here does not support this function or setting.";
		break;

		case IS_SUCCESS:
        	Log(lInfo) << "Function executed successfully";
        break;

        default:
        	Log(lInfo) << "Unknown return value";
        break;
    }

}


