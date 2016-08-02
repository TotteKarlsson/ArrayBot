#include <vcl.h>
#pragma hdrstop
#include "MainFrame.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "mtkWin32Utils.h"

using namespace mtk;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

extern string gLogFileName;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner),
    	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), &logMsg)
{
   	mLogFileReader.start(true);
}

//This one is called from the reader thread
void __fastcall TMainForm::logMsg()
{
    infoMemo->Lines->Insert(0, (vclstr(mLogFileReader.getData())));
    mLogFileReader.purge();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
	Log(lDebug) << "Init camera..";

	//Live
	if( !mCamera.IsInit() )
        openCamera();

    if( mCamera.IsInit() )
    {
        mCamera.CaptureVideo( IS_WAIT );
//		Timer1->Enabled = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	mDisplayHandle 	= this->Panel1->Handle;
}

//LRESULT TMainForm::OnUSBCameraMessage( WPARAM wParam)//, LPARAM lParam )
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
                mCamera.RenderBitmap(mCamera.mMemoryId, mDisplayHandle, IS_RENDER_FIT_TO_WINDOW);
        break;
    }

    return 0;
}

//---------------------------------------------------------------------------
bool TMainForm::openCamera()
{
	mCamera.openCamera(this->Handle);
}

void TMainForm::exitCamera()
{
	mCamera.exitCamera() ;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
	    exitCamera();
    	Close();
    }
}

HWND TMainForm::GetSafeHwnd()
{
	return this->Handle;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
    if(mCamera.mImageMemory != NULL)
    {
        mCamera.RenderBitmap(mCamera.mMemoryId, mDisplayHandle, IS_RENDER_FIT_TO_WINDOW);
    }
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
    	exitCamera();
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


void __fastcall TMainForm::CheckBox1Click(TObject *Sender)
{
    HCAM hCam = mCamera.GetCameraHandle();
    //Enable auto gain control:
    double dEnable = CheckBox1->Checked ? 1 : 0;
    int ret = is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_GAIN, &dEnable, 0);

    //Set brightness setpoint to 128:
    double nominal = 128;
    ret = is_SetAutoParameter (hCam, IS_SET_AUTO_REFERENCE, &nominal, 0);

    //Return shutter control limit:
    double maxShutter;
    ret = is_SetAutoParameter (hCam, IS_GET_AUTO_SHUTTER_MAX, &maxShutter, 0);
}
//---------------------------------------------------------------------------

