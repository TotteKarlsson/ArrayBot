#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "core/atCore.h"
#include "ArrayCamMessages.h"
#include "TPGDataModule.h"
#include "dslVCLUtils.h"
#include "TSelectIntegerForm.h"
#include "THandWheelPositionForm.h"
#include "TActionsForm.h"
#include "ArrayCamUtilities.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTFloatLabel"
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTIntLabel"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "TApplicationSoundsFrame"
#pragma link "TArrayBotBtn"
#pragma link "TFFMPEGFrame"
#pragma link "TImagesFrame"
#pragma link "TMoviesFrame"
#pragma link "TNavitarMotorFrame"
#pragma link "TSoundsFrame"
#pragma link "TUC7StagePositionFrame"

#pragma link "THDMIStreamerFrame"
#pragma resource "*.dfm"
TMainForm *MainForm;

extern ArrayCamUtilities acu;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	:
    	TRegistryForm(acu.AppRegistryRoot, "MainForm", Owner),
        mSettingsForm(NULL),
        mAVIID(0),
    	mIniFile(joinPath(acu.AppDataFolder, "ArrayCam.ini"), true, true),
    	mLogLevel(lAny),
        mAutoGain(false),
        mAutoExposure(false),
        mAutoBlackLevel(false),
        mAutoWhiteBalance(false),
        mSoftwareGamma(0.0),
        mVerticalMirror(false),
        mHorizontalMirror(false),
        mPairLEDs(false),
        mLocalDBName(""),
        mReticle(mPB->Canvas),
        mReticle2(mPB->Canvas, TReticle::rtCrossHair, clBlue),
        mServiceCamera1(mCamera1, 1, this->Handle),
        mMovingReticle(false),
        mCheckArduinoServerConnection(true),
        mConnectToArduinoServerThread(mLightsArduinoClient, 50000),
	    mConnectToElloUIThread(mElloUIClient, 50002),
        mUC7COMPort(0),
        mUC7(Handle),
        mCountTo(0),
	    mDBUserID(0),
        mStopCutterMode(0),
	    mBlockID(0),
	    mKnifeID(0),
	    mZebraCOMPort(17),
    	mZebraBaudRate(9600),
	    mZebra(),
        mMainContentPanelWidth(700),
        mACServer(*this, -1),
        mReticleVisible(false),
        mKnifeStageMaxPos(0),
        mKnifeStageJogStep(0),
        mKnifeStageResumeDelta(0),
        mKnifeCuttingSound(ApplicationSound("")),
		mKnifeBeforeCuttingSound(ApplicationSound("")),
		mBeforeKnifeBackOffSound(ApplicationSound("")),
        mKnifeAfterCuttingSound(ApplicationSound("")),
		mArmRetractingSound(ApplicationSound("")),
	    mRenderMode(IS_RENDER_FIT_TO_WINDOW),
        mHandWheelPositionForm(NULL),
        LoggerForm(NULL),
        ActionsForm(NULL),
        mAutoStartKnifeCamera(false),
        mGeneralProperties(shared_ptr<IniFileProperties>(new IniFileProperties)),
        mSoundProperties(shared_ptr<IniFileProperties>(new IniFileProperties))
{
    //Init the DLL -> give intra messages their ID's
	initABCoreLib();

	//Setup references
  	//The following causes the editbox, and its property to reference the counters CountTo value
   	mCountToE->setReference(mUC7.getSectionCounter().getCountToReference());
   	SectionCounterLabel->setReference(mUC7.getSectionCounter().getCountReference());
    RibbonOrderCountLabel->setReference(mUC7.getRibbonOrderCounter().getCountReference());
    mZeroCutsE->setReference(mUC7.getNumberOfZeroStrokesReference());

    mCountToE->update();
    SectionCounterLabel->update();
    RibbonOrderCountLabel->update();
    mZeroCutsE->update();

    //Properties are retrieved and saved to an ini file
    setupProperties();
    mGeneralProperties->read();
    mSoundProperties->read();

    TFFMPEGFrame1->setupProperties(mIniFile);

    //The loglevel is read from ini file
	gLogger.setLogLevel(mLogLevel);

    //Give all sounds a Handle (create a sound container..)
	mKnifeBeforeCuttingSound.getReference().setHandle(this->Handle);
	mBeforeKnifeBackOffSound.getReference().setHandle(this->Handle);
    mKnifeCuttingSound.getReference().setHandle(this->Handle);
	mKnifeAfterCuttingSound.getReference().setHandle(this->Handle);
	mArmRetractingSound.getReference().setHandle(this->Handle);

    //Setup callbacks
	mLightsArduinoClient.assignOnMessageReceivedCallBack(onLightsArduinoMessageReceived);
    mLightsArduinoClient.onConnected 		= onArduinoClientConnected;
	mLightsArduinoClient.onDisconnected 	= onArduinoClientDisconnected;

    mServiceCamera1.onCameraOpen 			= onCameraOpen;
    mServiceCamera1.onCameraClose 			= onCameraClose;

    mElloUIClient.onConnected 		= onElloUIClientConnected;
	mElloUIClient.onDisconnected 	= onElloUIClientDisconnected;

    /******** Update UI controls *************/
    //Todo, put these in a container and call update in a loop

    MainContentPanel->Width = mMainContentPanelWidth;
	mCountToE->update();
    mPresetFeedRateE->update();
    mUC7.setFeedRatePreset(mPresetFeedRateE->getValue());

    PresetReturnSpeedE->update();
    SlowReturnSpeedE->update();
    UltraSlowReturnSpeedE->update();

    mStageMoveDelayE->update();
	mZeroCutsE->update();
	mUC7ComportCB->ItemIndex = mUC7COMPort - 1;
	ArrayCamServerPortE->update();
    MaxStagePosFrame->setValue(mKnifeStageMaxPos.getValue());
    BackOffStepFrame->setValue(mKnifeStageJogStep.getValue());
    ResumeDeltaDistanceFrame->setValue(mKnifeStageResumeDelta.getValue());
    mUC7.setKnifeStageResumeDelta(mKnifeStageResumeDelta.getValue());
    mUC7.setKnifeStageJogStepPreset(mKnifeStageJogStep.getValue());
    MediaFolderE->update();

	mZebraCOMPortCB->ItemIndex = mZebraCOMPort - 1;

	THeaderSection* Section = CameraHC->Sections->Items[2];
    Section->Text = mReticleVisible ? "Hide Reticle" : "Show Reticle";

    //Find out which item in the CB that should be selected
    for(int i = 0; i < mZebraBaudRateCB->Items->Count; i++)
    {
		if(mZebraBaudRateCB->Items->Strings[i].ToInt() == mZebraBaudRate)
        {
			mZebraBaudRateCB->ItemIndex = i;
            break;
        }
    }

	mReticle2.visible(false);

	THDMIStreamerFrame1->getStreamer().assignCallBacks2(
    boost::bind(&TMainForm::onKnifeMovieEnter, 	 	this, _1, _1),
	boost::bind(&TMainForm::onKnifeMovieProgress, 	this, _1, _1),
	boost::bind(&TMainForm::onKnifeMovieExit, 	 	this, _1, _1)
    );
}

__fastcall TMainForm::~TMainForm()
{}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mStartupTimerTimer(TObject *Sender)
{
	mStartupTimer->Enabled = false;

    try
    {
        TPGConnectionFrame1->init(&mIniFile, "POSTGRESDB_CONNECTION", pgDM->SQLConnection1);
        TPGConnectionFrame1->ConnectA->Execute();

        mConnectZebraBtnClick(Sender);

        //Connect to the UC7
        mConnectUC7Btn->Click();

        //Connect navitar motors
        NavitarControllerConnectBtn->Click();
        updateTemperature(-1);
        updateHumidity(-1);
    }
//    catch(const SocketException& e)
//    {
//
//    }
    catch(const TDBXError& e)
    {
        Log(lError) << "There was an exception: "<<stdstr(e.Message);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormResize(TObject *Sender)
{;}

//---------------------------------------------------------------------------
void __fastcall TMainForm::AppInBox(ATWindowStructMessage& msg)
{
    if(msg.lparam == NULL)
    {
        return;
    }

    try
    {
        ApplicationMessageEnum aMsg = (ApplicationMessageEnum) msg.wparam;

        switch(aMsg)
        {
			case atUC7Message:
            {
            	//Cast data
            	UC7Message* m = (UC7Message*) msg.lparam;
                Log(lDebug) << "Handling UC7 message: \"" << m->getMessageNameAsString()<<"\" with data: "<<m->getData();
                bool result = handleUC7Message(*m);
                if(!result)
                {
                	Log(lError) << "The message: "<<m->getFullMessage()<<" was not properly handled!";
                }
                delete m;
            }
            break;

            case atMiscMessage:
            {
            	int* m = (int*) msg.lparam;
                Log(lDebug) << "Handling Misc message: \"" << *m;
            }
            break;
            default:
            break ;
        }
	}
	catch(...)
	{
		Log(lError) << "An exception was thrown in AppInBox.";
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mUsersCBCloseUp(TObject *Sender)
{
	if(!mUsersCB->KeyValue.IsNull())
    {
    	mDBUserID.setValue(mUsersCB->KeyValue);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DB_CBCloseUp(TObject *Sender)
{
	TDBLookupComboBox* b = dynamic_cast<TDBLookupComboBox*>(Sender);
	if(b == BlockIDCB )
    {
    	if(!b->KeyValue.IsNull())
		{
        	mBlockID.setValue(b->KeyValue);
        	pgDM->blockNotesCDS->Active = true;
        }
    }
    else if(b == KnifeIDCB)
    {
    	if(!b->KeyValue.IsNull())
		{
        	mKnifeID.setValue(b->KeyValue);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SendServerStatusMessageBtnClick(TObject *Sender)
{
	mACServer.broadcastStatus();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CountLabelClick(TObject *Sender)
{
	TIntLabel* lbl = dynamic_cast<TIntLabel*>(Sender);

    TSelectIntegerForm* f = new TSelectIntegerForm(this);
    f->setCurrentNumber(lbl->getValue());
    int res = f->ShowModal();
    if(res == mrOk)
    {
    	lbl->setValue(f->mTheNumberLbl->getValue());
    }

    delete f;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::StatusBar1Hint(TObject *Sender)
{
	;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenHandWheelPositionFormAExecute(TObject *Sender)
{
	if(!mHandWheelPositionForm)
    {
    	mHandWheelPositionForm = new THandWheelPositionForm(mUC7.getStatusHistoryRef(), acu.AppRegistryRoot, this);
    }

    if(!mHandWheelPositionForm->Visible)
    {
    	mHandWheelPositionForm->Show();
    }
    else
    {
		mHandWheelPositionForm->Hide();
    }
}

void __fastcall TMainForm::ToggleMainContentPanelAExecute(TObject *Sender)
{
	MainContentPanel->Visible 		= !MainContentPanel->Visible;
	ToggleMainContentBtn->Visible 	= !MainContentPanel->Visible;
    Splitter2->Visible 				= MainContentPanel->Visible;

    if(MainContentPanel->Visible)
    {
		Splitter2->Left = MainContentPanel->Left - 1;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenCloseShortcutFormExecute(TObject *Sender)
{
	if(!ActionsForm)
    {
    	ActionsForm = new TActionsForm(Handle, this);
    }

    if(!ActionsForm->Visible)
    {
    	ActionsForm->Show();
    }
    else
    {
    	ActionsForm->Hide();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenCloseShortcutFormUpdate(TObject *Sender)
{
	if(ActionsForm && ActionsForm->Visible)
    {
		OpenCloseShortcutForm->Caption = "Close Shortcuts";
    }
    else
    {
		OpenCloseShortcutForm->Caption = "Open ShortCuts";
    }
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::mBlockNoteNavigatorClick(TObject *Sender, TNavigateBtn Button)
{
	switch(Button)
    {
    	case TNavigateBtn::nbInsert:
			{
                int uID = pgDM->usersCDS->FieldByName("id")->AsInteger;
                int blockID = pgDM->blocksCDSid->Value;
                string note("Block Note..");
            	pgDM->insertBlockNote(uID, blockID, note);
            }
        break;
    }
}

void __fastcall TMainForm::mRibbonNotesNavigatorClick(TObject *Sender, TNavigateBtn Button)

{
	switch(Button)
    {
    	case TNavigateBtn::nbInsert:
        {
            int uID = getCurrentUserID();
            String rID = pgDM->ribbonsCDSid->Value;
            string note("Ribbon Note..");
           	pgDM->insertRibbonNote(uID, stdstr(rID), note);
        }
        break;

    	case TNavigateBtn::nbDelete:        break;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ToggleControlBarExecute(TObject *Sender)
{
	ControlBar1->Visible = !ControlBar1->Visible;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ToggleControlBarUpdate(TObject *Sender)
{
	ToggleControlBar->Caption = ControlBar1->Visible ? "Hide ControlBar" : "Show ControlBar";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::TakeSnapShotBtnClick(TObject *Sender)
{
	takeSnapShot();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::VideoRecTimerTimer(TObject *Sender)
{
	static int recTime(0);   //(milliseconds)
	if(mCaptureVideoTimer->Enabled)
    {
    	time_t seconds(recTime / 1000.0);
        tm *p = gmtime(&seconds);
        stringstream time;
        time << "Stop Recording \r";
        if(p)
        {
        	time <<"(" << p->tm_min <<":"<<p->tm_sec <<")";
        }
    	RecordVideoBtn->Caption = vclstr(time.str());
        recTime += VideoRecTimer->Interval;
    }
    else
    {
		VideoRecTimer->Enabled = false;
    	RecordVideoBtn->Caption = "Record Whisker Video";
        recTime = 0;
    }

    int maxRecTime = 30 * (60 * 1000); //Minutes
    if(recTime > maxRecTime)
    {
    	Log(lInfo) << "Stoppped movie at: " << recTime;
		stopRecordingMovie();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::RecordVideoBtnClick(TObject *Sender)
{
	startStopRecordingMovie();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ControlBar1StartDrag(TObject *Sender, TDragObject *&DragObject)
{
	this->Align = alNone;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FrontLEDTBChange(TObject *Sender)
{
	TTrackBar* tb = dynamic_cast<TTrackBar*>(Sender);
    if(!tb)
    {
    	return;
    }

   	int pos = tb->Position;
    if(tb == FrontLEDTB)
    {
        if(tb->Tag != 1) //Means we are updating UI from thread
        {
	        setLEDIntensity(pos);
        }
        mFrontLEDLbl->Caption = "Front LED (" + IntToStr(pos) + ")";
    }
}

void TMainForm::setLEDIntensity(int intensity)
{
	TTrackBar* tb = FrontLEDTB;
	//Means we are updating UI from thread
    if(tb->Tag != 1)
    {
        stringstream s;
        s<<"SET_FRONT_LED_INTENSITY="<<intensity;
        mLightsArduinoClient.request(s.str());
	    mACServer.broadcast(acrLEDIntensitySet);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BrowseForFolderClick(TObject *Sender)
{
	//Open Browse for folder dialog
	TButton* b = dynamic_cast<TButton*>(Sender);
    if(b == BrowseForMediaFolderBtn)
    {
        string f = browseForFolder(MediaFolderE->getValue());
        if(!f.size())
        {
            return;
        }

    	MediaFolderE->setValue(f);
    }
}

void __fastcall TMainForm::checkSyncWhiskerCB()
{
	SyncWhiskerCB->Checked = true;
    mACServer.broadcast(acrMoveWhiskerForwardOnSet);
}

void __fastcall TMainForm::unCheckSyncWhiskerCB()
{
	SyncWhiskerCB->Checked = false;
    mACServer.broadcast(acrMoveWhiskerForwardOffSet);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SyncWhiskerCBClick(TObject *Sender)
{
	if(SyncWhiskerCB->Checked)
    {
    	mACServer.broadcast(acrMoveWhiskerForwardOnSet);
    }
    else
    {
       	mACServer.broadcast(acrMoveWhiskerForwardOffSet);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::RunWiperBtnClick(TObject *Sender)
{
    fireRibbonSeparator();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PageControlChange(TObject *Sender)
{
	//Check if we need any processing as a tab changes
	TPageControl* pc = dynamic_cast<TPageControl*>(Sender);

    if(pc == MiscPageControl)
    {

    }

    else if(pc == MainPC)
    {
    	if(pc->TabIndex == 2)//Media tab
        {

        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PageControlExit(TObject *Sender)
{
	//Check if we need any processing as a tab changes
	TPageControl* pc = dynamic_cast<TPageControl*>(Sender);

    if(pc == MiscPageControl)
    {
    }
}

string TMainForm::getCurrentRibbonID()
{
	if(RibbonIDLbl->Caption.Length() < 2)
    {
    	return string("-1");
    }
    return stdstr(RibbonIDLbl->Caption);
}

void __fastcall	TMainForm::fireRibbonSeparator()
{
	Log(lInfo) << "Firing the ribbon separator";
    mElloUIClient.run();
   	mACServer.broadcast(acrRibbonSeparatorTriggered);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::KniveMovieBtnClick(TObject *Sender)
{
    if(KniveMovieBtn->Caption == "Record Knife Video" && THDMIStreamerFrame1)
    {
        //Create new file
        string uuid = getUUID();
        THDMIStreamerFrame1->OutputFileNameE->setValue(uuid + ".ts");
        //Set path, include block id
        THDMIStreamerFrame1->setPathPostFix(dsl::toString(pgDM->getCurrentBlockIDFromAllBlocks()));
    }
    THDMIStreamerFrame1->StartStreamerBtnClick(THDMIStreamerFrame1->StartRecordingBtn);
}

void TMainForm::onKnifeMovieEnter(int i, int j)
{
	struct lclS
    {
        int i, j;
        TMainForm* f;
        void __fastcall fn()
        {
			f->KniveMovieBtn->Caption = "Stop Recording";
        }
    };
	lclS lcl;
    lcl.i = i;
    lcl.j = j;
    lcl.f = this;
    TThread::Synchronize(0, &lcl.fn);
}

void TMainForm::onKnifeMovieProgress(int i, int j)
{
	struct lclS
    {
        int i, j;
        TMainForm* f;
        void __fastcall fn()
        {
        	//Check current file size
        	f->KniveMovieBtn->Caption = "Stop Recording\n" + vclstr(getHumanReadableFileSize(i));
        }
    };
	lclS lcl;
    lcl.i = i;
    lcl.j = j;
    lcl.f = this;
    TThread::Synchronize(0, &lcl.fn);
}

void TMainForm::onKnifeMovieExit(int i, int j)
{
	struct lclS
    {
        int i, j;
        TMainForm* f;
        void __fastcall fn()
        {
			f->KniveMovieBtn->Caption = "Record Knife Video";

            string videoID = getFileNameNoExtension(stdstr(f->THDMIStreamerFrame1->OutputFileNameE->Text));
            string ext     = getFileExtension(stdstr(f->THDMIStreamerFrame1->OutputFileNameE->Text));
            //Register movie here
	        registerVideoInDB(videoID, ext, f->getCurrentUserID(), f->getCurrentCoverSlipID(), f->getCurrentBlockID(), f->getCurrentRibbonID());
        }
    };
	lclS lcl;
    lcl.i = i;
    lcl.j = j;
    lcl.f = this;
    TThread::Synchronize(0, &lcl.fn);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ClearBarcodeBtnClick(TObject *Sender)
{
	//Clear the Barcode
    BarcodeLbl->Caption = "";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ClearRibbonIDBtnClick(TObject *Sender)
{
	RibbonIDLbl->Caption = "";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::MiscTimerTimer(TObject *Sender)
{
	ClearBarcodeBtn->Visible  = (BarcodeLbl->Caption.Length() > 0) 	? true : false;
   	ClearRibbonIDBtn->Visible = (RibbonIDLbl->Caption.Length() > 0) ? true : false;

    if(mAutoStartKnifeCamera)
    {
    	if(THDMIStreamerFrame1->getStreamer().isFinished() == true && THDMIStreamerFrame1->StartRecordingBtn->Caption == "Start Recording")
        {
        	Sleep(1000);
			KniveMovieBtn->Click();
            mAutoStartKnifeCamera = false;
        }
    }
}


void __fastcall TMainForm::MediaFolderEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_RETURN)
    {
    	THDMIStreamerFrame1->OutputFileFolderE->setValue(MediaFolderE->getValue());
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::RibbonsGridCellClick(TColumn *Column)
{
    if(BlockIDCB->KeyValue.IsNull())
    {
        return;
    }

    Poco::Path p(MediaFolderE->getValue());
	TMoviesFrame1->populate(BlockIDCB->KeyValue, stdstr(RibbonID->Caption), p);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::RibbonsNavigatorClick(TObject *Sender, TNavigateBtn Button)
{
    if(BlockIDCB->KeyValue.IsNull())
    {
        return;
    }

    Poco::Path p(MediaFolderE->getValue());
	TMoviesFrame1->populate(BlockIDCB->KeyValue, stdstr(RibbonID->Caption), p);
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::BroadCastStatusBtnClick(TObject *Sender)
{
	mACServer.broadcastStatus();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BroadcastStatusTimerTimer(TObject *Sender)
{
	mACServer.broadcastStatus();
}


void __fastcall TMainForm::ConnectWipterClientBtnClick(TObject *Sender)
{
	//Connect
    if(ConnectWipterClientBtn->Caption == "Connect")
    {
		mConnectToElloUIThread.start();
    }
    else
    {
    	mElloUIClient.disConnect();
    }
}

//Callback from socket client class
void TMainForm::onElloUIClientConnected()
{
    Log(lDebug) << "Ello UI Client was connected..";
    ConnectWipterClientBtn->Caption = "Disconnect";
	RunWiperBtn->Enabled = true;
}

//---------------------------------------------------------------------------
void TMainForm::onElloUIClientDisconnected()
{
    Log(lDebug) << "Ello UI Client was disconnected..";

	//Don't worry if we are closing down..
    if(acu.AppIsClosing != true)
    {
	    ConnectWipterClientBtn->Caption = "Connect";
		RunWiperBtn->Enabled = false;
    }
}


void __fastcall TMainForm::ThemesMenuClick(TObject *Sender)
{
    TMenuItem* menuItem = dynamic_cast<TMenuItem*>(Sender);
    if(!menuItem)
    {
        return;
    }

	//Uncheck any checked items
	for(int i = 0; i < ThemesMenu->Count; i++)
	{
		TMenuItem* menuItem = ThemesMenu->Items[i];
		if(menuItem && menuItem->Checked)
		{
			menuItem->Checked = false;
		}
	}

	TRegistryForm::writeToRegistry();

	TReplaceFlags rFlags(rfIgnoreCase|rfReplaceAll);
	String styleName = StringReplace(menuItem->Caption, "&", "", rFlags);
	TStyleManager::SetStyle(styleName);

	//Check the menu item
	menuItem->Checked = (TStyleManager::ActiveStyle->Name == styleName) ? true : false;

	//Write to registry
	acu.Style = stdstr(styleName);
	writeStringToRegistry(acu.AppRegistryRoot, "", "Theme", acu.Style);

}
//---------------------------------------------------------------------------

