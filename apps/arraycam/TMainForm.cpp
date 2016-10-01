#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "mtkWin32Utils.h"
#include "mtkUtils.h"
#include "camera/uc480_tools.h"
#include "TSettingsForm.h"
#include "abDBUtils.h"
#include "TATDBDataModule.h"
#include "TATDBImagesAndMoviesDataModule.h"
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
		mRestoreFromZeroCutSound("CLOSING_DOWN_1", 15, 350),
        mSnapShotFolder(""),
        mMoviesFolder(""),
        mLocalDBFile(""),
        mClientDBSession("")
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
    mProperties.add((BaseProperty*)  &mSnapShotFolder.setup(	"SNAP_SHOT_FOLDER",     "C:\\Temp"	));
	mProperties.add((BaseProperty*)  &mMoviesFolder.setup(		"MOVIES_FOLDER",   		"C:\\Temp"	));
	mProperties.add((BaseProperty*)  &mLocalDBFile.setup(		"LOCAL_DB",   			joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", "atdb.db")	));

    mProperties.read();

    mClientDBSession.connect(mLocalDBFile);
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
	string fldr = mMoviesFolder;
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
	string fldr =  mSnapShotFolder;
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
        string fldr =  mMoviesFolder;

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
        string fldr =  mSnapShotFolder;

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
        string fldr  = mMoviesFolder;

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
        string fldr =  mSnapShotFolder;

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
            string fldr =  mMoviesFolder;
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
            string fldr =  mSnapShotFolder;
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
    sf->Show();
//    delete sf;
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
void __fastcall TMainForm::mAddImageFileBtnClick(TObject *Sender)
{
	TButton* b = dynamic_cast<TButton*>(Sender);

    if(b == mAddImageFileBtn)
    {
		//Browse for file
        string f = browseForFile(mSnapShotFolder);
        if(!f.size())
        {
            return;
        }

        //Add this file to DB and open a metadata entry form for the user
        try
        {
            mClientDBSession.insertImageFile(getFileNameNoPath(f), "Note..");
            DBNavigator1->BtnClick(nbRefresh);
            DBNavigator1->BtnClick(nbRefresh);

//			ImagesAndMoviesDM->images->Active = false;
//			ImagesAndMoviesDM->images->Close();
//
//			ImagesAndMoviesDM->images->ExecSQL();
//
//			ImagesAndMoviesDM->images->Open();
//    		ImagesAndMoviesDM->images->Active = true;
        }
        catch(...)
        {
            handleSQLiteException();
        }
    }
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

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	string dBase(mLocalDBFile);
    if(!fileExists(dBase))
    {
	  	Log(lError) << "The db file: "<<dBase<<" do not exist!";

    }
    else
    {
        if (atDM->Connect(dBase))
        {
            Log(lInfo) << "Connected to database: "<<dBase;
           // Connection successfull
        }
        else
        {
            Log(lInfo) << "Failed to connect to database: "<<dBase;
        }
    }
    gAppIsStartingUp = false;
}

void __fastcall TMainForm::DBMemo1Change(TObject *Sender)
{
	//Enable update button
    mUpdateNoteBtn->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mUpdateNoteBtnClick(TObject *Sender)
{
	//Apply and post updates to database
	ImagesAndMoviesDM->notesCDS->ApplyUpdates(-1);
    mUpdateNoteBtn->Enabled = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DBNavigator2Click(TObject *Sender, TNavigateBtn Button)

{
	//
}


void __fastcall TMainForm::DBNavigator2BeforeAction(TObject *Sender, TNavigateBtn Button)

{
	if(Button == nbInsert)
    {


    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
	int imageID = ImagesAndMoviesDM->imagesCDS->Fields->FieldByName("id")->Value;
    Log(lInfo) <<"Current ID: "<<imageID;
	mClientDBSession.insertImageNote(imageID, "New note..");

	ImagesAndMoviesDM->imageNoteCDS->Active = false;
	ImagesAndMoviesDM->imageNoteCDS->Active = true;
    ImagesAndMoviesDM->imageNoteCDS->Refresh();
}

void __fastcall TMainForm::DBMemo1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	mUpdateNoteBtn->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mImagesGridMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ImagesAndMoviesDM->imagesCDS->AfterRefresh(NULL);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mImagesGridCellClick(TColumn *Column)
{
	//Retrieve file name and show the image
//    mImagesGrid->
	String f =	ImagesAndMoviesDM->imagesCDS->FieldByName("file_name")->AsString;
    string fName = joinPath(mSnapShotFolder, stdstr(f));

    if(fileExists(fName))
    {
		Image1->Picture->LoadFromFile(fName.c_str());
    }
    else
    {
    	Log(lError) << "The file: "<<fName<<" could not be found";
    }
}


void __fastcall TMainForm::mImagesGridDblClick(TObject *Sender)
{
//    //Check if we have a valid file
//    string fName = stdstr(lb->Items->Strings[lb->ItemIndex]);
//    string fldr =  mSnapShotFolder;
//
//    fName = joinPath(fldr, fName);
//    if(fileExists(fName))
//    {
//        ShellExecuteA(NULL, NULL, stdstr(fName).c_str(), 0, 0, SW_SHOWNA);
//    }
}


