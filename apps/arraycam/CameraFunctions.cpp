#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "mtkLogger.h"
#include "mtkUtils.h"
#include "mtkWin32Utils.h"
#include "camera/uc480_tools.h"
#include "vcl/abVCLUtils.h"
#include "database/abDBUtils.h"
using namespace mtk;
using namespace ab;

//---------------------------------------------------------------------------
void __fastcall TMainForm::mCameraStartLiveBtnClick(TObject *Sender)
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

        HCAM hc = mCamera.GetCameraHandle();

		//Setup camera using values from INI file

        //Enable/Disable auto gain control:
        double dEnable = mAutoGain.getValue() ? 1 : 0;
        int ret = is_SetAutoParameter (hc, IS_SET_ENABLE_AUTO_GAIN, &dEnable, 0);

		dEnable = mAutoExposure.getValue() ? 1 : 0;

        //Enable/Disable auto exposure
        ret = is_SetAutoParameter (hc, IS_SET_ENABLE_AUTO_SHUTTER, &dEnable, 0);

        //Set brightness setpoint to 128:
        double nominal = 128;
        ret = is_SetAutoParameter (hc, IS_SET_AUTO_REFERENCE, &nominal, 0);

        //Mirror stuff
		is_SetRopEffect (hc, IS_SET_ROP_MIRROR_LEFTRIGHT, mVerticalMirror.getValue(), 0);
		is_SetRopEffect (hc, IS_SET_ROP_MIRROR_UPDOWN, 	mHorizontalMirror.getValue(), 0);
    }
}

LRESULT TMainForm::OnUSBCameraMessage(TMessage msg)
{
    switch ( msg.WParam )
    {
        case IS_DEVICE_REMOVED:            Beep( 400, 50 );        break;
        case IS_DEVICE_RECONNECTED:        Beep( 400, 50 );        break;

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
	return	mCamera.openCamera(this->Handle);
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


void __fastcall TMainForm::mSnapShotBtnClick(TObject *Sender)
{
	string fldr =  mSnapShotFolder;

    if(!folderExists(fldr))
    {
    	Log(lInfo) << "Creating folder: "<<fldr;
    	createFolder(fldr);
    }

    string ext(".jpg");
    //Count files in folder
    int nrOfShots = countFiles(fldr, "*" + ext) + 1;
    string fName = joinPath(fldr, mtk::toString(nrOfShots) + ext);
    int i = 1;

    while(fileExists(fName))
    {
        nrOfShots = countFiles(fldr, "*" + ext) + ++i;
        fName = joinPath(fldr, mtk::toString(nrOfShots) + ext);
    }

	if(mCamera.SaveImage(fName.c_str()))
    {
    	Log(lError) << "Failed saving snapshot..";
    }
    else
    {
    	Log(lInfo) << "Saved snapshot to file: "<< fName;

		try
        {
	        //save to DB
	        mClientDBSession.insertImageFile(getFileNameNoPath(fName), getCurrentUserID(mUsersCB), "Note..");
        }
        catch(...)
        {
        	handleMySQLException();
        }
    	    DBNavigator1->BtnClick(nbRefresh);
	        DBNavigator1->BtnClick(nbRefresh);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mRecordMovieBtnClick(TObject *Sender)
{
	if(mRecordMovieBtn->Caption == "Record Movie")
    {
        mCaptureVideoTimer->Enabled = true;

        isavi_InitAVI(&mAVIID, mCamera.GetCameraHandle());

        int w = mCamera.mSizeX;
        int h = mCamera.mSizeY;
        int retVal = isavi_SetImageSize(mAVIID, mCamera.mColorMode, w, h, 0, 0, 0);

        if(retVal != IS_AVI_NO_ERR)
        {
            Log(lError) << "There was a SetImageSize AVI error: "<<retVal;
            return;
        }

        retVal = isavi_SetImageQuality(mAVIID, 100);
        if(retVal != IS_AVI_NO_ERR)
        {
            Log(lError) << "There was a SetImageQuality AVI error: "<<retVal;
            return;
        }

        string fldr =  mMoviesFolder; //joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", "movies");
        if(!folderExists(fldr))
        {
            Log(lInfo) << "Creating folder: "<<fldr;
            createFolder(fldr);
        }

        //Count files in folder
        int nrOfMovies = countFiles(fldr, "*.avi") + 1;
        string fName = joinPath(fldr, mtk::toString(nrOfMovies) + ".avi");
        int i = 1;
        while(fileExists(fName))
        {
        	nrOfMovies = countFiles(fldr, "*.avi") + ++i;
        	fName = joinPath(fldr, mtk::toString(nrOfMovies) + ".avi");
        }

        retVal = isavi_OpenAVI(mAVIID, fName.c_str());
        if(retVal != IS_AVI_NO_ERR)
        {
            Log(lError) << "There was a OpenAVI error: "<<retVal;
            return;
        }

        retVal = isavi_SetFrameRate(mAVIID, 25);
        if(retVal != IS_AVI_NO_ERR)
        {
            Log(lError) << "There was a SetFrameRate AVI error: "<<retVal;
            return;
        }

        retVal = isavi_StartAVI(mAVIID);
        if(retVal != IS_AVI_NO_ERR)
        {
            Log(lError) << "There was a StartAVI error: "<<retVal;
            return;
        }
        mRecordMovieBtn->Caption = "Stop Recording";
    }
    else
    {
        mCaptureVideoTimer->Enabled = false;
        mRecordMovieBtn->Caption = "Record Movie";
        int retVal = isavi_StopAVI(mAVIID);
        if(retVal != IS_AVI_NO_ERR)
        {
            Log(lError) << "There was a StopAVI error: "<<retVal;
            return;
        }

        retVal = isavi_CloseAVI(mAVIID);
        if(retVal != IS_AVI_NO_ERR)
        {
            Log(lError) << "There was a CloseAVI error: "<<retVal;
            return;
        }

        retVal = isavi_ExitAVI(mAVIID);
        if(retVal != IS_AVI_NO_ERR)
        {
            Log(lError) << "There was a ExitAVI error: "<<retVal;
            return;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mCaptureVideoTimerTimer(TObject *Sender)
{
	//Todo: this should be executed in its own thread and not in a timer..
    mCaptureVideo = true;
    static int frames(0);

    int retVal = isavi_AddFrame(mAVIID, mCamera.mImageMemory);

    if(retVal != IS_AVI_NO_ERR)
    {
        //Log(lError) << "There was an AddFrame AVI error: "<<retVal;
    }
    else
    {
        frames++;
        Log(lInfo) << "Added frame: "<<frames;
    }
}
