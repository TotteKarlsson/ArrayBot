#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslTMemoLogger.h"
#include "forms/TSplashForm.h"
#include "dslStringList.h"
#include "core/atUtilities.h"
#include "arraybot/apt/atAPTMotor.h"
#include "arraybot/apt/atTCubeDCServo.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include <bitset>
#include "dslMathUtils.h"
#include "core/atExceptions.h"
#include "sound/atSounds.h"
#include "core/atCore.h"
#include "TABProcessSequencerFrame.h"
#include "TXYZUnitFrame.h"
#include "TSequencerButtonsFrame.h"
#include "UIUtilities.h"
#include "arraybot/apt/atAbsoluteMove.h"
#include "TPGDataModule.h"
#include "TSelectIntegerForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TUC7StagePositionFrame"
#pragma link "TFFMPEGFrame"
#pragma link "THDMIStreamerFrame"
#pragma link "TPGConnectionFrame"
#pragma link "TSoundsFrame"
#pragma link "dslTFloatLabel"
#pragma link "TMoviesFrame"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TMainForm *MainForm;

extern string           gLogFileLocation;
extern string           gLogFileName;
extern string           gAppDataFolder;
extern TSplashForm*  	gSplashForm;
extern bool             gAppIsStartingUp;
extern string 			gApplicationRegistryRoot;
extern string 			gAppName;
extern string   		gApplicationStyle;

using namespace dsl;
string gDiveProcessName = "Dive";
string gLiftProcessName = "Lift";

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
:
        TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),
        mLogFileReader(joinPath(gAppDataFolder, gLogFileName), &logMsg),
        mInitBotThread(),
        mIniFile(joinPath(gAppDataFolder, gAppName + ".ini"), true, true),
        mLogLevel(lAny),
        mAB(mIniFile, gAppDataFolder),
        mProcessSequencer(mAB, mArrayCamClient, gAppDataFolder),
        mABProcessSequencerFrame(NULL),
        mSequencerButtons1(NULL),
        mLocalDBName(""),
        mUC7(Handle),
        mUC7COMPort(0),
        mCountTo(0),
	    mDBUserID(0),
        mStopCutterMode(0),
	    mBlockID(0),
	    mKnifeID(0),
	    mZebraCOMPort(17),
    	mZebraBaudRate(9600),
	    mZebra(),
        mKnifeStageMaxPos(0),
        mKnifeStageJogStep(0),
        mKnifeStageResumeDelta(0),
        mKnifeCuttingSound(ApplicationSound("")),
		mKnifeBeforeCuttingSound(ApplicationSound("")),
		mBeforeKnifeBackOffSound(ApplicationSound("")),
        mKnifeAfterCuttingSound(ApplicationSound("")),
		mArmRetractingSound(ApplicationSound("")),
        mHandWheelPositionForm(NULL)
{
    //Init the CoreLibDLL -> give intra messages their ID's
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


	TMemoLogger::mMemoIsEnabled = false;
   	mLogFileReader.start(true);

    setupProperties();
    mGeneralProperties.read();

    //The loglevel is read from ini file
	gLogger.setLogLevel(mLogLevel);

    //Give all sounds a Handle (create a sound container..)
	mKnifeBeforeCuttingSound.getReference().setHandle(this->Handle);
	mBeforeKnifeBackOffSound.getReference().setHandle(this->Handle);
    mKnifeCuttingSound.getReference().setHandle(this->Handle);
	mKnifeAfterCuttingSound.getReference().setHandle(this->Handle);
	mArmRetractingSound.getReference().setHandle(this->Handle);

    /******** Update UI controls *************/
    //Todo, put these in a container and call update in a loop

  	mCountToE->update();
    mPresetFeedRateE->update();
    mUC7.setFeedRatePreset(mPresetFeedRateE->getValue());

    PresetReturnSpeedE->update();
    SlowReturnSpeedE->update();
    UltraSlowReturnSpeedE->update();

    mStageMoveDelayE->update();
	mZeroCutsE->update();
	mUC7ComportCB->ItemIndex = mUC7COMPort - 1;

    MaxStagePosFrame->setValue(mKnifeStageMaxPos.getValue());
//    BackOffStepFrame->setValue(mKnifeStageJogStep.getValue());
    ResumeDeltaDistanceFrame->setValue(mKnifeStageResumeDelta.getValue());
    mUC7.setKnifeStageResumeDelta(mKnifeStageResumeDelta.getValue());
    mUC7.setKnifeStageJogStepPreset(mKnifeStageJogStep.getValue());

	mZebraCOMPortCB->ItemIndex = mZebraCOMPort - 1;

    //Find out which item in the CB that should be selected
    for(int i = 0; i < mZebraBaudRateCB->Items->Count; i++)
    {
		if(mZebraBaudRateCB->Items->Strings[i].ToInt() == mZebraBaudRate)
        {
			mZebraBaudRateCB->ItemIndex = i;
            break;
        }
    }


	//Load motors in a thread
    mInitBotThread.assingBot(&mAB);
    mInitBotThread.onFinishedInit = this->onFinishedInitBot;

    //We will setup UI frames after the bot is initialized
	mInitBotThread.start();
	WaitForDeviceInitTimer->Enabled = true;
}

//---------------------------------------------------------------------------
void TMainForm::enableDisableUI(bool e)
{
	MainPC->Visible = e;
	enableDisablePanel(MiddlePanel, e);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::UIUpdateTimerTimer(TObject *Sender)
{
	if(MainPC->ActivePage == MainTS)
    {
//    	DummyFocus();
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
void __fastcall TMainForm::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	static bool wasAborted(false);
    //Get the motor and jog it
    APTMotor* m = mAB.getMotorWithName("COVERSLIP UNIT_Z");
    if(!m)
    {
        Log(lError) << "Failed getting Coverslip UnitZ motor";
    }

    if(m && m->isActive())
    {
		mProcessSequencer.getCurrentSequence()->getCurrent()->stop();
        wasAborted = true;
		return;
    }


    if(Key == 'l' || Key == 'L')
    {
		LiftBtn->Click();
    }
    else if(Key == 'd' || Key == 'D')
    {
	    DiveButton->Click();
    }
    else if(Key == 't' || Key == 'T')
    {
    	//Toggle sequence

    	//Check for current process sequence
    	string cSeqName = mProcessSequencer.getSequences().getCurrentSequenceName();
        if(wasAborted && cSeqName == gDiveProcessName)
        {
			cSeqName = gLiftProcessName;
        }
        else if(wasAborted && cSeqName == gLiftProcessName)
        {
			cSeqName = gDiveProcessName;
        }
        else if(cSeqName == gDiveProcessName)
        {
			cSeqName = gLiftProcessName;
        }
        else
        {
			cSeqName = gDiveProcessName;
        }

        if(cSeqName == gDiveProcessName)
        {
            DiveButton->Click();
        }
        else
        {
            LiftBtn->Click();
        }
    }
    wasAborted = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    //Get the motor and jog it
    APTMotor* m = mAB.getMotorWithName("COVERSLIP UNIT_Z");
    if(!m)
    {
        Log(lError) << "Failed getting Coverslip UnitZ motor";
    }

	if(Key == vkEscape)
    {
    	Close();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if(Key == VK_UP || Key == VK_DOWN)
    {
       	//Get the motor and jog it
        APTMotor* m = mAB.getMotorWithName("COVERSLIP UNIT_Z");
        if(!m)
        {
            Log(lError) << "Failed getting Coverslip UnitZ motor";
            return;
        }

        if(m->getJogMoveMode() == jmContinuous)
        {
            m->stop();
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::WndProc(TMessage& Message)
{
	bool jogUp(false);
    bool jogDown(false);

	switch (Message.Msg)
    {
    	case WM_GETDLGCODE:
	    	Log(lInfo) << "Got WM_GETDLGCODE";
		    Message.Result = 1;
        break;

		case CM_DIALOGKEY:
        {
			Log(lInfo) << "Got CM_DIALOGKEY";
            switch (reinterpret_cast<TCMDialogKey&>(Message).CharCode)
        	{
    	        case VK_UP:  	jogUp 	= true;  break;
        	    case VK_DOWN:	jogDown = true;  break;
                case VK_LEFT:
                case VK_RIGHT:
                	Message.Result = 1;
                break;

        	}
        }
        break;
		case CM_WANTSPECIALKEY:
        {
	    	Log(lInfo) << "Got WM_WANTSPECIALKEY";
            switch (reinterpret_cast<TCMWantSpecialKey&>(Message).CharCode)
            {
    	        case VK_UP:  	jogUp 	= true;  break;
        	    case VK_DOWN:	jogDown = true;  break;
                case VK_LEFT:
                case VK_RIGHT:
               		Message.Result = 1;
                break;
            }
        }
        break;
    }

    if(jogUp || jogDown)
    {
		if(jogUp)
        {
        	JogMotorMouseDown(FillMoreBtn, mbLeft, TShiftState(), 0,0);
        }
        if(jogDown)
        {
        	JogMotorMouseDown(FillLessBtn, mbLeft, TShiftState(), 0,0);
        }

       	JogMotorMouseUp(FillLessBtn, mbLeft, TShiftState(), 0,0);
        Log(lInfo) << "Joggin up or down..";
	    Message.Result = 1;
    }

    if(Message.Result != 1)
    {
		TForm::WndProc(Message);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::WaitForDeviceInitTimerTimer(TObject *Sender)
{
	if(!mInitBotThread.isRunning()) //Not waiting for devices any more
    {
		WaitForDeviceInitTimer->Enabled = false;

        setupUIFrames();
        enableDisableUI(true);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::reInitBotAExecute(TObject *Sender)
{
	mAB.initialize();

    if(mXYZUnitFrame1)
    {
		mXYZUnitFrame1->assignUnit(&mAB.getCoverSlipUnit());
    }

    //ArrayBotJoyStick stuff.....
    ReInitBotBtn->Action = ShutDownA;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::stopAllAExecute(TObject *Sender)
{
	mAB.stopAll();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::MainPCChange(TObject *Sender)
{
	//Check what tab got selected
    TTabSheet* currentTab = MainPC->ActivePage;

	if(currentTab == SequencesTS && mABProcessSequencerFrame != NULL)
    {
    	//Reload the currently selected sequence
		mABProcessSequencerFrame->mSequencesCBChange(Sender);
    }

    else if(currentTab == MainTS)
    {
        if(mSequencerButtons1)
        {
        	mSequencerButtons1->update();
        }
    }
    else if(currentTab == MotorsTS)
    {
		//Disable joystick
	 	mAB.disableJoyStick();

        //Disable motor status timers
        mXYZUnitFrame1->enable();
    }

	else if(currentTab== AboutTS)
    {
		TAboutArrayBotFrame_21->populate();
    }

    if(currentTab != MotorsTS)
    {
   	 	mAB.enableJoyStick();

        //Disable motor status timers
        mXYZUnitFrame1->disable();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::HomeAllDevicesAExecute(TObject *Sender)
{
	if(MessageDlg("ATTENTION: Make sure all motors have a free path to their home position before executing!", mtWarning, TMsgDlgButtons() << mbOK<<mbCancel, 0) == mrOk)
    {
		mAB.homeAll();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mClearLogWindowBtnClick(TObject *Sender)
{
	if(infoMemo)
    {
    	infoMemo->Clear();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DiveButtonClick(TObject *Sender)
{
	//Run a sequence
	mProcessSequencer.selectSequence("Dive");
    mProcessSequencer.start();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::LiftBtnClick(TObject *Sender)
{
	//Run a sequence
	mProcessSequencer.selectSequence("Lift CS");
    mProcessSequencer.start();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::JogMotorMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   //Get the motor and stop it
    APTMotor* m = mAB.getMotorWithName("COVERSLIP UNIT_Z");
    if(!m)
    {
    	Log(lError) << "Failed getting Coverslip UnitZ motor";
        return;
    }

	if(m->getJogMoveMode() == jmContinuous)
    {
    	m->stop();
    }
    this->SetFocus();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::JogMotorMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	TArrayBotButton* btn = dynamic_cast<TArrayBotButton*>(Sender);
    if(!btn)
    {
    	Log(lError) << "Failed to cast button";
    	return;
    }

    //Get the motor and jog it
    APTMotor* m = mAB.getMotorWithName("COVERSLIP UNIT_Z");
    if(!m)
    {
    	Log(lError) << "Failed getting Coverslip UnitZ motor";
        return;
    }

    if(mProcessSequencer.getSequences().getCurrentSequenceName() != gDiveProcessName)
    {
		return;
    }

    if(btn == FillMoreBtn)
    {
	    updateDivePosition(m->getPosition() - m->getJogStep());
        m->jogReverse();

    }
    else if(btn == FillLessBtn)
    {
	    updateDivePosition(m->getPosition() + m->getJogStep());
        //Get the motor and jog it
    	m->jogForward();
    }
}

void TMainForm::updateDivePosition(double pos)
{
    APTMotor* m = mAB.getMotorWithName("COVERSLIP UNIT_Z");
    if(!m)
    {
    	Log(lError) << "Failed getting Coverslip UnitZ motor";
        return;
    }

    //Get the dive sequence
    if(mProcessSequencer.getSequences().getCurrentSequenceName() != gDiveProcessName)
    {
    	return;
    }

    Log(lInfo) << "Found sequence: \""<< gDiveProcessName <<"\"";
    ProcessSequence* s = mProcessSequencer.getSequences().getCurrent();
    if(s && s->getProcessWithName(gDiveProcessName))
    {
	    Process* p = s->getProcessWithName(gDiveProcessName);
        if(p && p->getProcessName() == gDiveProcessName)
        {
            AbsoluteMove* am = dynamic_cast<AbsoluteMove*>(p);
            if(am)
            {
                am->setPosition(pos);
                mProcessSequencer.saveCurrent();
            }
            else
            {
                Log(lError) << "Failed to cast to an AbsoluteMove process..";
            }
        }
        else
        {
            Log(lError) << "Failed getting process with name: "<<gDiveProcessName;
        }
    }
    else
    {
        Log(lError) << "Failed getting process: " <<gDiveProcessName;
    }
}


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

void __fastcall TMainForm::mStartupTimerTimer(TObject *Sender)
{
	mStartupTimer->Enabled = false;
    try
    {
        TPGConnectionFrame1->init(&mIniFile, "POSTGRESDB_CONNECTION");
        TPGConnectionFrame1->ConnectA->Execute();

        ConnectZebraBtnClick(Sender);

        //Connect to the UC7
        mConnectUC7Btn->Click();

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
void __fastcall TMainForm::ClearBarcodeBtnClick(TObject *Sender)
{
	//Clear the Barcode
    BarcodeLbl->Caption = "";
	ClearBarcodeBtn->Visible = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ThemesRGClick(TObject *Sender)
{
    if(ThemesRG->ItemIndex < 0)
    {
        return;
    }

	String theme = ThemesRG->Items->Strings[ThemesRG->ItemIndex];
    if(theme == TStyleManager::ActiveStyle->Name)
    {
        return;
    }

	TStyleManager::SetStyle(theme);

	//Write to registry
	gApplicationStyle = stdstr(theme);
	writeStringToRegistry(gApplicationRegistryRoot, "", "Theme", gApplicationStyle);
}


