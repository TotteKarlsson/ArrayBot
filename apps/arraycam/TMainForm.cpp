#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "mtkWin32Utils.h"
#include "mtkUtils.h"
#include "camera/uc480_tools.h"
#include "TSettingsForm.h"

using namespace mtk;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TPropertyCheckBox"
#pragma link "mtkFloatLabel"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TMainForm *MainForm;

extern string gLogFileName;
extern string gApplicationRegistryRoot;
extern string gLogFileLocation;
extern string gLogFileName;
extern string gAppDataFolder;
extern bool   gAppIsStartingUp;
extern bool   gAppIsClosing;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),
    	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), &logMsg),
        mCaptureVideo(false),
        mAVIID(0),
    	mIniFile(joinPath(gAppDataFolder, "ArrayCam.ini"), true, true),
    	mLogLevel(lAny),
        mAutoGain(false),
        mAutoExposure(false),
        mVerticalMirror(false),
        mHorizontalMirror(false),
        mPairLEDs(false),
		mGetReadyForZeroCutSound("SHORT_BEEP_2", 10, 500),
		mSetZeroCutSound("SHORT_BEEP_2", 25, 150),
		mRestoreFromZeroCutSound("CLOSING_DOWN_1", 15, 350)
{
   	mLogFileReader.start(true);

	//Setup UI/INI properties
    mProperties.setSection("GENERAL");
	mProperties.setIniFile(&mIniFile);
	mProperties.add((BaseProperty*)  &mLogLevel.setup( 	    	"LOG_LEVEL",    		lAny));
	mProperties.add((BaseProperty*)  &mAutoGain.setup(			"AUTO_GAIN",    		false));
	mProperties.add((BaseProperty*)  &mAutoExposure.setup( 		"AUTO_EXPOSURE",    	false));
	mProperties.add((BaseProperty*)  &mVerticalMirror.setup(	"VERTICAL_MIRROR",    	false));
	mProperties.add((BaseProperty*)  &mHorizontalMirror.setup(	"HORIZONTAL_MIRROR",    false));
	mProperties.add((BaseProperty*)  &mHorizontalMirror.setup(	"HORIZONTAL_MIRROR",    false));
	mProperties.add((BaseProperty*)  &mPairLEDs.setup(			"PAIR_LEDS",    		true));

    mProperties.read();

	//Camera rendering mode
    mRenderMode = IS_RENDER_FIT_TO_WINDOW;
	mLightsArduinoClient.assignOnMessageReceivedCallBack(onArduinoMessageReceived);

    mLightsArduinoClient.onConnected 		= onArduinoClientConnected;
	mLightsArduinoClient.onDisconnected 	= onArduinoClientDisconnected;
    gLogger.setLogLevel(mLogLevel);
}

__fastcall TMainForm::~TMainForm()
{
	mProperties.write();
    mIniFile.save();
}

//This one is called from the reader thread
void __fastcall TMainForm::logMsg()
{
    infoMemo->Lines->Insert(0, (vclstr(mLogFileReader.getData())));
    mLogFileReader.purge();
}

//Callback from socket client class
void TMainForm::onArduinoClientConnected()
{
    Log(lDebug) << "ArduinoClient was connected..";

    //Send message to update UI
    mLightsArduinoClient.getBoardStatus();
    enableDisableClientControls(true);
}

void TMainForm::onArduinoClientDisconnected()
{
    Log(lDebug) << "Arduino Client was disconnected..";

	//Don't worry if we are closing down..
    if(gAppIsClosing != true)
    {
    	enableDisableClientControls(false);
    }
}

void TMainForm::enableDisableClientControls(bool enable)
{
	//Disable client related components..
    enableDisableGroupBox(LightIntensitiesGB, enable);
	mToggleCoaxBtn->Enabled = enable;
    mFrontBackLEDBtn->Enabled = enable;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	mDisplayHandle 	= this->mCameraStreamPanel->Handle;
	mCameraStartLiveBtnClick(Sender);

	mCameraStreamPanel->Width = 1280;
	mCameraStreamPanel->Height = 1024;
	mCameraStreamPanel->Top = 0;
	mCameraStreamPanel->Left = 0;
	mFitToScreenButtonClick(Sender);
	updateVideoFileLB();
	updateShotsLB();

    enableDisableClientControls(false);

	//Try to connect to the arduino server..
	mLightsArduinoClient.connect(50000);

	//Setup sounds
	mGetReadyForZeroCutSound.create(this->Handle);
	mSetZeroCutSound.create(this->Handle);
	mRestoreFromZeroCutSound.create(this->Handle);

    //Setup LogLevel CB
    string logLevel = mtk::toString(gLogger.getLogLevel());

    //Find item in CB with this loglevel
    int index = LogLevelCB->Items->IndexOf(vclstr(logLevel));

    if(index > -1)
    {
		LogLevelCB->ItemIndex = index;
    }
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

//HWND TMainForm::GetSafeHwnd()
//{
//	return this->Handle;
//}

void __fastcall TMainForm::mMainPanelResize(TObject *Sender)
{
//	mFitToScreenButtonClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mToggleLogPanelClick(TObject *Sender)
{
	mBottomPanel->Visible = !mBottomPanel->Visible;
	mToggleLogPanelBtn->Caption =  (mBottomPanel->Visible) ? "Hide Bottom Panel" : "Show Bottom Panel";
	mFitToScreenButtonClick(Sender);
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::ClearLogMemo(TObject *Sender)
{
	infoMemo->Clear();
}

void  TMainForm::updateVideoFileLB()
{
	string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", "movies");
    StringList files = getFilesInDir(fldr, "avi");

    for(int i = 0; i < files.count(); i++)
    {
		files[i] = getFileNameNoPath(files[i]);
    }

    files.sort();

	mMoviesLB->Clear();
    for(int i = 0; i < files.count(); i++)
    {
    	mMoviesLB->AddItem( vclstr(files[i]), NULL );
    }
}

void  TMainForm::updateShotsLB()
{
	string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", "snap_shots");
    StringList files = getFilesInDir(fldr, "jpg");

    for(int i = 0; i < files.count(); i++)
    {
		files[i] = getFileNameNoPath(files[i]);
    }

    files.sort();

	mShotsLB->Clear();
    for(int i = 0; i < files.count(); i++)
    {
    	mShotsLB->AddItem( vclstr(files[i]), NULL );
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mMoviesLBDblClick(TObject *Sender)
{

	TListBox* lb = dynamic_cast<TListBox*>(Sender);

    if(lb == mMoviesLB)
    {
        //Check if we have a valid file
        string fName = stdstr(lb->Items->Strings[lb->ItemIndex]);
        string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", "movies");

        fName = joinPath(fldr, fName);
        if(fileExists(fName))
        {
            ShellExecuteA(NULL, NULL, stdstr(fName).c_str(), 0, 0, SW_SHOWNA);
        }
    }
    else if (lb == mShotsLB)
    {
        //Check if we have a valid file
        string fName = stdstr(lb->Items->Strings[lb->ItemIndex]);
        string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", "snap_shots");

        fName = joinPath(fldr, fName);
        if(fileExists(fName))
        {
            ShellExecuteA(NULL, NULL, stdstr(fName).c_str(), 0, 0, SW_SHOWNA);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Delete1Click(TObject *Sender)
{

    TListBox* lb = dynamic_cast<TListBox*>(mMediaPopup->PopupComponent);

   	if(lb && lb->ItemIndex == -1)
    {
		return;
    }

    if(lb == mMoviesLB)
    {
        //Delete current selected item
        string fName = stdstr(lb->Items->Strings[lb->ItemIndex]);
        string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", "movies");

        fName = joinPath(fldr, fName);
        if(fileExists(fName))
        {
            removeFile(fName);
            updateVideoFileLB();
        }
    }
    else if (lb == mShotsLB)
    {
        //Delete current selected item
        string fName = stdstr(lb->Items->Strings[lb->ItemIndex]);
        string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", "snap_shots");

        fName = joinPath(fldr, fName);
        if(fileExists(fName))
        {
            removeFile(fName);
            updateShotsLB();
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DeleteAll1Click(TObject *Sender)
{
    TListBox* lb = dynamic_cast<TListBox*>(mMediaPopup->PopupComponent);

   	if(lb && lb->ItemIndex == -1)
    {
		return;
    }

    if(lb == mMoviesLB)
    {
        while(lb->Count)
        {
            string fName = stdstr(lb->Items->Strings[0]);
            string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", "movies");
            fName = joinPath(fldr, fName);
            if(fileExists(fName))
            {
                removeFile(fName);
                updateVideoFileLB();
            }
        }
    }
    else if (lb == mShotsLB)
    {
        while(lb->Count)
        {
            string fName = stdstr(lb->Items->Strings[0]);
            string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", "snap_shots");
            fName = joinPath(fldr, fName);
            if(fileExists(fName))
            {
                removeFile(fName);
                updateShotsLB();
            }
        }
    }
}

void __fastcall TMainForm::mCameraStreamPanelDblClick(TObject *Sender)
{
//	this->BorderStyle = (this->BorderStyle == bsNone) ? bsSingle : bsNone;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Button2Click(TObject *Sender)
{
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mSettingsBtnClick(TObject *Sender)
{
	//Open settings form
	TSettingsForm* sf = new TSettingsForm(*this);
    sf->ShowModal();
    delete sf;
}

void TMainForm::onArduinoMessageReceived(const string& msg)
{
	struct TLocalArgs
    {
        string msg;
        void __fastcall onPufferArduinoMessage()
        {
        	//If mouse is down.. do not update certain UI objects
            bool isMouseBtnDown = (bool) GetAsyncKeyState(VK_LBUTTON);
            if(startsWith("DHT22_DATA", msg))
            {
                //Parse the message
                StringList l(msg,',');
                if(l.size() == 4)
                {
                    MainForm->mTemperatureLbl->SetValue(toDouble(l[1]));
                    MainForm->mHumidityE->SetValue(toDouble(l[2]));
                }
            }

//            if(startsWith("GET_READY_FOR_ZERO_CUT_1", msg))
//            {
//            	Log(lInfo) <<"Ready for zero cut";
//				MainForm->mGetReadyForZeroCutSound.play();
//            }

            else if(startsWith("GET_READY_FOR_ZERO_CUT_2", msg))
            {
            	Log(lInfo) <<"Steady for zero cut";
                MainForm->stopSounds();
				MainForm->mGetReadyForZeroCutSound.play();
            }

            else if(startsWith("SET_ZERO_CUT", msg))
            {
            	Log(lInfo) <<"Go for zero cut ";
                MainForm->stopSounds();
				MainForm->mSetZeroCutSound.play();
            }

            else if(startsWith("RESTORE_FROM_ZERO_CUT", msg))
            {
				Log(lInfo) <<"Restore from zero Cut ";
                MainForm->stopSounds();
				//MainForm->mRestoreFromZeroCutSound.play();
            }

            else if(startsWith("COAX_DRIVE", msg) && isMouseBtnDown == false )
            {
                StringList l(msg,'=');
                if(l.size() == 2)
                {
	                MainForm->mCoaxTB->Tag = 1;
                    MainForm->mCoaxTB->Position = toInt(l[1]);
	                MainForm->mCoaxTB->Tag = 0;
                }
            }
            else if(startsWith("FRONT_LED_DRIVE", msg) && isMouseBtnDown == false)
            {
                StringList l(msg,'=');
                if(l.size() == 2)
                {
   	                MainForm->mFrontLEDTB->Tag = 1;
                    MainForm->mFrontLEDTB->Position = toInt(l[1]);
   	                MainForm->mFrontLEDTB->Tag = 0;
                }
            }

            else if(startsWith("BACK_LED_DRIVE", msg) && isMouseBtnDown == false)
            {
                StringList l(msg,'=');
                if(l.size() == 2)
                {
   	                MainForm->mBackLEDTB->Tag = 1;
                    MainForm->mBackLEDTB->Position = toInt(l[1]);
   	                MainForm->mBackLEDTB->Tag = 0;
                }
            }
        }
    };

    TLocalArgs args;
    args.msg = msg;

    //This causes this fucntion to be called in the UI thread
	TThread::Synchronize(NULL, &args.onPufferArduinoMessage);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mFrontBackLEDBtnClick(TObject *Sender)
{
	TArrayBotButton* b = dynamic_cast<TArrayBotButton*>(Sender);
    if(b == mFrontBackLEDBtn)
    {
    	mLightsArduinoClient.toggleLED();
    }

    if(b == mToggleCoaxBtn)
    {
    	mLightsArduinoClient.toggleCoax();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::LogLevelCBChange(TObject *Sender)
{
	if(LogLevelCB->ItemIndex == -1)
    {
    	return;
    }

    string lvl = stdstr(LogLevelCB->Items->Strings[LogLevelCB->ItemIndex]);
    mLogLevel = toLogLevel(lvl);
    gLogger.setLogLevel(mLogLevel);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
	TButton* b = dynamic_cast<TButton*>(Sender);

//    if(b == Button1)
//    {
//		mGetReadyForZeroCutSound.play();
//    }
//    else if(b == goButton)
//    {
//		mSetZeroCutSound.play();
//    }
//    else if (b == restoreBtn)
//    {
//		mRestoreFromZeroCutSound.play();
//    }
//    else if (b == stopBtn)
//    {
//        stopSounds();
//    }
}

void TMainForm::stopSounds()
{
    mGetReadyForZeroCutSound.stop();
    mRestoreFromZeroCutSound.stop();
    mSetZeroCutSound.stop();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::IntensityChange(TObject *Sender)
{
	TTrackBar* tb = dynamic_cast<TTrackBar*>(Sender);
    if(!tb)
    {
    	return;
    }

   	int pos = tb->Position;
    if(tb == mFrontLEDTB)
    {
    	if(mPairLEDs.getValue() == true)
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
	        mLightsArduinoClient.request(s.str());
        }
        mFrontLEDLbl->Caption = "Front LED (" + IntToStr(pos) + ")";
    }
    else if(tb == mBackLEDTB)
    {
        if(tb->Tag != 1) //Means we are updating UI
        {
	        stringstream s;
	        s<<"SET_BACK_LED_INTENSITY="<<pos;
    	    mLightsArduinoClient.request(s.str());
        }
        mBackLEDLbl->Caption = "Back LED (" + IntToStr(pos) + ")";

    }
    else if(tb == mCoaxTB)
    {
        if(tb->Tag != 1) //Means we are updating UI
        {
			stringstream s;
	        s<<"SET_COAX_INTENSITY="<<pos;
    	    mLightsArduinoClient.request(s.str());
        }
        mCoaxLbl->Caption = "Coax (" + IntToStr(pos) + ")";
    }
}



