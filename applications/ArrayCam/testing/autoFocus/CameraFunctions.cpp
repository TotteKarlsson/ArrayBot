#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "dslFileUtils.h"
#include "camera/uc480_tools.h"
#include "atVCLUtils.h"
#include "TSettingsForm.h"
#include "TReticlePopupForm.h"
#include "ArrayCamUtils.h"
using namespace dsl;

//---------------------------------------------------------------------------
void __fastcall TMainForm::CameraHCSectionClick(THeaderControl *HeaderControl,
          THeaderSection *Section)
{
    POINT p;
    GetCursorPos(&p);

	if(Section == CameraHC->Sections->Items[0])
    {
        //Show popup
        CameraPopup->Popup(p.x, p.y);
    }
    else if(Section == CameraHC->Sections->Items[1])
    {
    }
    else if(Section == CameraHC->Sections->Items[2])
    {
		mReticleVisible = !mReticleVisible;
        Section->Text = mReticleVisible ? "Hide Reticle" : "Show Reticle";
    }
    else if(Section == CameraHC->Sections->Items[3])
    {
	    mReticle.setReticleCenter(0,0);
    }
    else if(Section == CameraHC->Sections->Items[4])
    {
	    if(Section->Text == "Maximize Camera View")
        {
            if(MainContentPanel->Visible)
            {
				ToggleMainContentPanelAExecute(NULL);
            }
			Section->Text = "Show UI Controls";
        }
        else
        {
            if(!MainContentPanel->Visible)
            {
				ToggleMainContentPanelAExecute(NULL);
            }
			Section->Text = "Maximize Camera View";
        }
    }
    else if(Section == CameraHC->Sections->Items[5])
    {
	    if(Section->Text == "Show Image Center")
        {
        	mReticle2.visible(true);
			Section->Text = "Hide Image Center";
        }
        else
        {
	       	mReticle2.visible(false);
			Section->Text = "Show Image Center";
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mPBMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	//If mouse is inside reticle center, allow moving its center
    //Get x, y coordintaes in paintbox coordinates

    int x = X - mPB->Width/2;
    int y = Y - mPB->Height/2;

    Log(lInfo) << "X and Y"<<x<<":"<<y;

    pair<int, int> rCenter = mReticle.getReticleCenter();
    int r = mReticle.getCircleRadius();

    //Check if mouse is inside the reticle circle
    double distance = sqrt(pow((double) x - rCenter.first,2) + pow((double) y - rCenter.second, 2));
    if(distance < r)
    {
		mMovingReticle = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mPBMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	mMovingReticle = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mPBMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	//Update reticle center
	if(mMovingReticle)
    {
    	int x = X - mPB->Width/2;
        int y = Y - mPB->Height/2;
    	mReticle.setReticleCenter(x, y);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mCameraStartLiveBtnClick(TObject *Sender)
{
    Log(lDebug) << "Init camera..";

    //Live
    if(!mCamera1.IsInit())
    {
    	mServiceCamera1.openCamera();
    }
}

//Called from a thread
void __fastcall	TMainForm::onCameraOpen(System::TObject* Sender)
{
	Log(lInfo) << "A Camera was open..";

	Cuc480* camera = (Cuc480*) Sender;

    if(!camera)
    {
    	Log(lError) << "Null camerapointer in onCameraOpen";
    }

   if(camera == &mCamera1 && mCamera1.IsInit())
    {
        int x, y, ret;
        mCamera1.GetMaxImageSize(&x,&y);
        Log(lInfo) << "Max image size (x,y): ("<<x<<", "<<y<<")";
        mCamera1.CaptureVideo( IS_WAIT );

        HCAM hCam = mCamera1.GetCameraHandle();

		//Setup camera using values from INI file

        //Enable/Disable auto gain control:
        double dEnable = mAutoGain.getValue() ? 1 : 0;
        ret = is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_GAIN, &dEnable, 0);

		//Auto exposure
		dEnable = mAutoExposure.getValue() ? 1 : 0;

        //Enable/Disable auto exposure
        ret = is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_SHUTTER, &dEnable, 0);

		//Auto Black Level
		dEnable = mAutoBlackLevel.getValue() ? 1 : 0;

        //Enable/Disable auto black Level
        int nMode = dEnable > 0 ? IS_AUTO_BLACKLEVEL_ON : IS_AUTO_BLACKLEVEL_OFF;
        ret = is_Blacklevel(hCam, IS_BLACKLEVEL_CMD_SET_MODE, (void*)&nMode , sizeof(nMode ));

		//Auto Black Level
		dEnable = mAutoWhiteBalance.getValue() ? 1 : 0;

        //Enable/Disable auto black Level
        ret = is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_WHITEBALANCE, &dEnable, 0);;

        //Set software gamme
		ret = is_SetGamma (hCam, mSoftwareGamma * 100.0);

        //Mirror stuff
		is_SetRopEffect (hCam, IS_SET_ROP_MIRROR_LEFTRIGHT, mVerticalMirror.getValue(), 0);
		is_SetRopEffect (hCam, IS_SET_ROP_MIRROR_UPDOWN, 	mHorizontalMirror.getValue(), 0);
    }
}

//---------------------------------------------------------------------------
void __fastcall	TMainForm::onCameraClose(System::TObject* Sender)
{
	Log(lInfo) << "A Camera was closed..";
}

//---------------------------------------------------------------------------
LRESULT TMainForm::onUSBCameraMessage(TMessage msg)
{
    switch ( msg.WParam )
    {
        case IS_DEVICE_REMOVED:        	Beep( 400, 50 );        break;
        case IS_DEVICE_RECONNECTED:    	Beep( 400, 50 );        break;

        case IS_FRAME:
            if(mCamera1.mImageMemory != NULL)
            {
            	mCamera1.RenderBitmap(mCamera1.mMemoryId, mCamera1DisplayHandle, mRenderMode);

        	    HDC hDC = mPB->Canvas->Handle;

            	//Set 0,0 in the middle
        		MoveWindowOrg(hDC, mPB->Width/2, mPB->Height/2);
				mReticle2.draw(mPB->Width, mPB->Height);
                if(mReticleVisible)
                {
					mReticle.draw(mPB->Width, mPB->Height);
                }

            }
        break;
    }

    return 0;
}

void __fastcall TMainForm::Zoom1To1AExecute(TObject *Sender)
{
    mRenderMode = IS_RENDER_FIT_TO_WINDOW;
    mCamera1BackPanel->Invalidate();

   	int x, y;
	mCamera1.GetMaxImageSize(&x,&y);
	mCamera1BackPanel->Width  = x;
	mCamera1BackPanel->Height = y;
}

void __fastcall TMainForm::Zoom1To2AExecute(TObject *Sender)
{
	mRenderMode = IS_RENDER_DOWNSCALE_1_2;

   	int x, y;
	mCamera1.GetMaxImageSize(&x,&y);
	mCamera1BackPanel->Width = x/2.;
	mCamera1BackPanel->Height = y/2.;
}

void __fastcall TMainForm::FitToScreenAExecute(TObject *Sender)
{
	//Check widths and heights
    double wRatio = (double) mMainPhotoPanel->Width / mCamera1BackPanel->Width;
    double hRatio = (double) mMainPhotoPanel->Height / mCamera1BackPanel->Height;

    if(hRatio < wRatio)
    {
	    mCamera1BackPanel->Height = mMainPhotoPanel->Height;
        mCamera1BackPanel->Width *= hRatio;
    }
    else
    {
	    mCamera1BackPanel->Width = mMainPhotoPanel->Width;
        mCamera1BackPanel->Height *= wRatio;
    }

    mPB->Height = mCamera1BackPanel->Height;
    mPB->Width = mCamera1BackPanel->Width;

    mCamera1BackPanel->Invalidate();
	if(mCamera1BackPanel->Height)
    {
		Log(lInfo) << "W x H = " <<mCamera1BackPanel->Width<<","<<mCamera1BackPanel->Height<<" Ratio = "<<(double) mCamera1BackPanel->Width / mCamera1BackPanel->Height;
    }
}

void __fastcall TMainForm::OpenCameraSettingsAExecute(TObject *Sender)
{
	//Open settings form
    if(!mSettingsForm)
    {
		mSettingsForm = new TSettingsForm(*this);
    }

    mSettingsForm->Show();
}

void __fastcall TMainForm::takeSnapShot()
{
    string ext(".jpg");
	string uuid = getUUID();
	int csID = -1;
    if(csID == -1)
    {
    	csID = 0; //So we can create fileFolder '0'
    }

    int blockID = -1;//pgDM->getCurrentBlockID();
    if(blockID == -1)
    {
    	blockID = 0;
    }

	string base_fldr =  joinPath(MediaFolderE->getValue(), "Images", dsl::toString(blockID));
    string fName = joinPath(base_fldr, uuid + ext);

    if(!folderExists(base_fldr))
    {
    	Log(lInfo) << "Creating folder: "<<base_fldr;
    	createFolder(base_fldr);
    }

	if(mCamera1.SaveImage(fName.c_str()))
    {
    	Log(lError) << "Failed saving snapshot..";
    }
    else
    {
    	Log(lInfo) << "Saved snapshot to file: "<< fName;
    }
}


