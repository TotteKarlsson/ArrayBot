#pragma hdrstop
#include "TMainForm.h"
#include "TPGDataModule.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "dslFileUtils.h"
#include "camera/uc480_tools.h"
#include "atVCLUtils.h"
#include "atUtils.h"
#include "TSettingsForm.h"
#include "TReticlePopupForm.h"
#include "TFFMPEGOutputFrame.h"
#include "ArrayCamUtils.h"

using namespace dsl;
using namespace at;

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
		if(mReticleForm.get() == NULL)
        {
        	mReticleForm = auto_ptr<TReticlePopupForm>(new TReticlePopupForm(mReticle, this));
            mReticleForm->mReticleVisibilityCB->setReference(mReticleVisible.getReference());
			mReticleForm->mReticleVisibilityCB->update();
        }

        mReticleForm->Top = p.y;// + mReticleForm->Height;
        mReticleForm->Left = p.x;
        mReticleForm->Show();
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
        	ControlBar1->Visible = false;
            if(MainContentPanel->Visible)
            {
				ToggleMainContentPanelAExecute(NULL);
            }
			Section->Text = "Show UI Controls";
        }
        else
        {
        	ControlBar1->Visible = true;
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
	//If mouse is inside reticle center, allowe moving its center
	mMovingReticle = true;
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
		if(mReticleForm.get() && mReticleForm->Visible)
    	{
        	mReticleForm->mReticleCenterXTB->Position = x;
        	mReticleForm->mReticleCenterYTB->Position = y;
        }
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
	int csID = extractCoverSlipID(stdstr(BarcodeLbl->Caption));
    if(csID == -1)
    {
    	csID = 0; //So we can create fileFolder '0'
    }

    int blockID = pgDM->getCurrentBlockID();
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
        mACServer.broadcast(acrSnapShotTaken);
		try
        {
			if(pgDM->SQLConnection1->Connected == false)
            {
            	MessageDlg("Not connected to the database!\nThis image is not registered!", mtError, TMsgDlgButtons() << mbOK, 0);
                return;
            }

        	//Add image to database
            //Make sure the barcode exists in the database..
            TSQLQuery* tq = new TSQLQuery(NULL);
            tq->SQLConnection = pgDM->SQLConnection1;
            tq->SQLConnection->AutoClone = false;
            stringstream q;
            q <<"INSERT INTO images (id, fileextension, created_by, coverslip_id, block_id) VALUES ('"
            			<<uuid<<"', '"
                        <<getFileExtension(fName)<<"', '"
                        <<getCurrentUserID()<<"', '"
						<<csID<<"', '"
	                    <<blockID<<"')";

            string s(q.str());
			Log(lDebug) <<"Image Insertion Query: "<<s;
            tq->SQL->Add(q.str().c_str());
            tq->ExecSQL();
            tq->Close();
            tq->SQL->Clear();
            q.str("");
        }
        catch(...)
        {
        	MessageDlg("There was a problem registering the snapchot in the database", mtError, TMsgDlgButtons() << mbOK, 0);
        }
    }
}

void __fastcall TMainForm::startRecordingMovie()
{
	if(mCaptureVideoTimer->Enabled == false)
    {
		startStopRecordingMovie();
    }
    else
    {
    	Log(lWarning) << "Can't start recording as recording is already enabled";
    }
}

void __fastcall TMainForm::stopRecordingMovie()
{
	if(mCaptureVideoTimer->Enabled == true)
    {
		startStopRecordingMovie();
    }
    else
    {
    	Log(lWarning) << "Can't stop rectording movie as recording is already disabled";
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::startStopRecordingMovie()
{
	//These are static so we can easily retrieve their values set during start, when stopping.
	static string 	lCurrentVideoFileName;
    static string 	sMovieID;
    static int 		lBlockID;

	if(mCaptureVideoTimer->Enabled == false)
    {
        mCaptureVideoTimer->Enabled = true;
        isavi_InitAVI(&mAVIID, mCamera1.GetCameraHandle());

        Log(lInfo) << "Starting recording movie";

        int w = mCamera1.mSizeX;
        int h = mCamera1.mSizeY;
        int retVal = isavi_SetImageSize(mAVIID, mCamera1.mColorMode, w, h, 0, 0, 0);

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

        string ext(".avi");
        sMovieID = getUUID();

        lBlockID = pgDM->getCurrentBlockIDFromAllBlocks();
        if(lBlockID == -1)
        {
            lBlockID = 0;
        }

        string base_fldr =  joinPath(MediaFolderE->getValue(), dsl::toString(lBlockID));
        string fName = joinPath(base_fldr, sMovieID + ext);

        if(!folderExists(base_fldr))
        {
            Log(lInfo) << "Creating folder: "<<base_fldr;
            if(!createFolder(base_fldr))
            {
	        	Log(lError) << "Failed creating folder: " <<base_fldr;
	    	    Log(lError) << "Failed starting video recording";
    	    	return;
	        }
        }

		lCurrentVideoFileName = fName;

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
        mACServer.broadcast(acrVideoRecorderStarted);
    }
    else
    {
        Log(lInfo) << "Stopping Video Recording";
        mCaptureVideoTimer->Enabled = false;
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

        mACServer.broadcast(acrVideoRecorderStopped);
        //Register in the database
    	Log(lInfo) << "Saving movie to file: "<< lCurrentVideoFileName;

        //Start compression video thread
        startVideoCompression(lCurrentVideoFileName);
        int csID = extractCoverSlipID(stdstr(BarcodeLbl->Caption));

        //We rely on that the compression process finishes! avi -> mp4
        registerVideoInDB(sMovieID, "mp4", getCurrentUserID(), csID, lBlockID, stdstr(RibbonIDLbl->Caption));
        mACServer.broadcast(acrVideoRecorderStopped);
    }

   	if(mCaptureVideoTimer->Enabled)
    {
    	//Enabnle visual indication on the Video Button
		VideoRecTimer->Enabled = true;
    }

  	mACServer.broadcastStatus();
}

bool TMainForm::startVideoCompression(const string& inputName)
{
    Log(lInfo) << "Starting compressing file: " << inputName;
    TFFMPEGOutputFrame* f = new TFFMPEGOutputFrame(this);
    f->Parent = MPEGPanel;
    f->onDone = onCompressionFinished;
    f->setInputFile(inputName);
    f->setCompressionOptions(TFFMPEGFrame1->getOutFileArguments(), TFFMPEGFrame1->DeleteSourceFileCB->Checked, TFFMPEGFrame1->RenameSourceFileCB->Checked);
    f->startCompression();
    mCompressionFrames.push_back(f);
    return true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mCaptureVideoTimerTimer(TObject *Sender)
{
	//Todo: this should be executed in its own thread and not in a timer..
    static int frames(0);

    int retVal = isavi_AddFrame(mAVIID, mCamera1.mImageMemory);

    if(retVal == IS_AVI_NO_ERR)
    {
        frames++;
    }
}

void __fastcall TMainForm::onCompressionFinished(TFFMPEGOutputFrame* f)
{
	//Start deleteFrameTimer
	CleanupTimer->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CleanupTimerTimer(TObject *Sender)
{
	CleanupTimer->Enabled = false;

	//Check for frames to delete
    list<TFFMPEGOutputFrame*>::iterator i;
	for(i = mCompressionFrames.begin(); i != mCompressionFrames.end();)
    {
    	if((*i) && (*i) ->isDone())
        {
        	delete (*i);
            i = mCompressionFrames.erase(i);
        }
        else
        {
        	i++;
        }
    }
}

