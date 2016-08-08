#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "mtkWin32Utils.h"

using namespace mtk;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TPropertyCheckBox"
#pragma resource "*.dfm"
TMainForm *MainForm;

extern string gLogFileName;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner),
    	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), &logMsg)
{
   	mLogFileReader.start(true);
    mRenderMode = IS_RENDER_FIT_TO_WINDOW;
}

//This one is called from the reader thread
void __fastcall TMainForm::logMsg()
{
    infoMemo->Lines->Insert(0, (vclstr(mLogFileReader.getData())));
    mLogFileReader.purge();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mCameraStartLiveBtnClick(TObject *Sender)
{
	if(mCameraStartLiveBtn->Caption == "Start")
    {
        Log(lDebug) << "Init camera..";
        //Live
        if(!mCamera.IsInit())
        {
            openCamera();
        }

        if(mCamera.IsInit())
        {
        	int x, y;
       		mCamera.GetMaxImageSize(&x,&y);
            Log(lInfo) << "Max image size (x,y): ("<<x<<", "<<y<<")";
            mCamera.CaptureVideo( IS_WAIT );
		    mCameraStartLiveBtn->Caption = "Stop";
        }
    }
    else
    {
		mCamera.exitCamera();
	    mCameraStartLiveBtn->Caption = "Start";
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	mDisplayHandle 	= this->mCameraStreamPanel->Handle;
	mCameraStartLiveBtnClick(Sender);
    mAutoGainCB->Checked = true;
	mCameraStreamPanel->Width = 1280;
	mCameraStreamPanel->Height = 1024;
	mCameraStreamPanel->Top = 0;
	mCameraStreamPanel->Left = 0;
	mFitToScreenButtonClick(Sender);
}

LRESULT TMainForm::OnUSBCameraMessage(TMessage msg)
{
    switch ( msg.WParam )
    {
        case IS_DEVICE_REMOVED:
            Beep( 400, 50 );
        break;

        case IS_DEVICE_RECONNECTED:
            Beep( 400, 50 );
        break;

        case IS_FRAME:
            if(mCamera.mImageMemory != NULL)
            {
                mCamera.RenderBitmap(mCamera.mMemoryId, mDisplayHandle, mRenderMode);
            }
        break;
    }

    return 0;
}

//---------------------------------------------------------------------------
bool TMainForm::openCamera()
{
	mCamera.openCamera(this->Handle);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
		mCamera.exitCamera();
    	Close();
    }
}

HWND TMainForm::GetSafeHwnd()
{
	return this->Handle;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if(mLogFileReader.isRunning() || mCamera.IsInit())
    {
        CanClose = false;
        mShutDownTimer->Enabled = true;
        return;
    }

    CanClose = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mShutDownTimerTimer(TObject *Sender)
{
    mShutDownTimer->Enabled = false;
	if(mLogFileReader.isRunning())
    {
		mLogFileReader.stop();
    }

    if( mCamera.IsInit())
    {
    	mCamera.exitCamera();
    }

    Close();
}

void __fastcall TMainForm::TrackBar1Change(TObject *Sender)
{
	//Set brightness
	/* set gamma value to 1.6 */
	INT nGamma = TrackBar1->Position;
    HCAM hCam = mCamera.GetCameraHandle();
	INT nRet = is_Gamma(hCam, IS_GAMMA_CMD_SET, (void*) &nGamma, sizeof(nGamma));
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Button2Click(TObject *Sender)
{
	double fps(0);
	is_GetFramesPerSecond(mCamera.GetCameraHandle(), &fps);
    Log(lInfo) << "Frames per second: " << fps;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mAutoGainCBClick(TObject *Sender)
{
    HCAM hCam = mCamera.GetCameraHandle();

    //Enable auto gain control:
    double dEnable = mAutoGainCB->Checked ? 1 : 0;
    int ret = is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_GAIN, &dEnable, 0);

    //Set brightness setpoint to 128:
    double nominal = 128;
    ret = is_SetAutoParameter (hCam, IS_SET_AUTO_REFERENCE, &nominal, 0);

    //Return shutter control limit:
    double maxShutter;
    ret = is_SetAutoParameter (hCam, IS_GET_AUTO_SHUTTER_MAX, &maxShutter, 0);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mVerticalMirrorCBClick(TObject *Sender)
{
    HCAM hCam = mCamera.GetCameraHandle();
	if(mVerticalMirrorCB->Checked)
    {
		is_SetRopEffect (hCam, IS_SET_ROP_MIRROR_LEFTRIGHT, 1, 0);
    }
    else
    {
		is_SetRopEffect (hCam, IS_SET_ROP_MIRROR_LEFTRIGHT, 0, 0);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mHorizontalMirrorCBClick(TObject *Sender)
{
    HCAM hCam = mCamera.GetCameraHandle();
	if(mHorizontalMirrorCB->Checked)
    {
		is_SetRopEffect (hCam, IS_SET_ROP_MIRROR_UPDOWN, 1, 0);
    }
    else
    {
		is_SetRopEffect (hCam, IS_SET_ROP_MIRROR_UPDOWN, 0, 0);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mOneToTwoBtnClick(TObject *Sender)
{
	mRenderMode = IS_RENDER_DOWNSCALE_1_2;

   	int x, y;
	mCamera.GetMaxImageSize(&x,&y);
	mCameraBackPanel->Width = x/2.;
	mCameraBackPanel->Height = y/2.;
}

void __fastcall TMainForm::mOneToOneBtnClick(TObject *Sender)
{
    mRenderMode = IS_RENDER_FIT_TO_WINDOW;
    mCameraStreamPanel->Invalidate();

   	int x, y;
	mCamera.GetMaxImageSize(&x,&y);
	mCameraBackPanel->Width  = x;
	mCameraBackPanel->Height = y;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mFitToScreenButtonClick(TObject *Sender)
{
	//Check widths and heights
    double wRatio = (double) mMainPanel->Width / mCameraBackPanel->Width;
    double hRatio = (double) mMainPanel->Height / mCameraBackPanel->Height;

    if(hRatio < wRatio)
    {
	    mCameraBackPanel->Height = mMainPanel->Height;
        mCameraBackPanel->Width *= hRatio;
    }
    else
    {
	    mCameraBackPanel->Width = mMainPanel->Width;
        mCameraBackPanel->Height *= wRatio;
    }

    mCameraBackPanel->Invalidate();
    mCameraStreamPanel->Invalidate();
	Log(lInfo) << "W x H = " <<mCameraBackPanel->Width<<","<<mCameraBackPanel->Height<<" Ratio = "<<(double) mCameraBackPanel->Width / mCameraBackPanel->Height;
}


void __fastcall TMainForm::mMainPanelResize(TObject *Sender)
{
//	mFitToScreenButtonClick(Sender);
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::mToggleLogPanelClick(TObject *Sender)
{
	infoMemo->Visible = !infoMemo->Visible;
	mToggleLogPanel->Caption =  (infoMemo->Visible) ? "Hide Logs" : "Show Logs";
	mFitToScreenButtonClick(Sender);
}


