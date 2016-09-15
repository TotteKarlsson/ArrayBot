#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "TMemoLogger.h"
#include "mtkStringList.h"
#include "abUtilities.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
#include <bitset>
#include "mtkMathUtils.h"
#include "abExceptions.h"
#include "TSplashForm.h"
#include "TPufferArduinoBoardFrame.h"
#include "TSensorAndLightArduinoFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "mtkFloatLabel"
#pragma link "TIntLabel"
#pragma link "TPropertyCheckBox"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TMain *Main;

extern string           gLogFileLocation;
extern string           gLogFileName;
extern string           gAppDataFolder;
extern TSplashForm*  	gSplashForm;
extern string 			gApplicationRegistryRoot;
extern bool             gAppIsStartingUp;
using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
	TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), &logMsg),
    mIniFile(joinPath(gAppDataFolder, "ArduinoController.ini"), true, true),
    mLogLevel(lAny),
    mArduinoServer(-1),
    mPufferArduino(mArduinoServer.getPufferArduino()),
    mSensorArduino(mArduinoServer.getSensorArduino())
{
	TMemoLogger::mMemoIsEnabled = false;
   	mLogFileReader.start(true);

	//Setup UI/INI properties
    mProperties.setSection("UI");
	mProperties.setIniFile(&mIniFile);
	mProperties.add((BaseProperty*)  &mLogLevel.setup( 	                    		"LOG_LEVEL",    	 lAny));
	mProperties.add((BaseProperty*)  &mArduinoServerPortE->getProperty()->setup(	"SERVER_PORT",    	 50000));
	mProperties.add((BaseProperty*)  &mDesiredRibbonLengthE->getProperty()->setup(	"DESIRED_RIBBON_LENGTH",    	 25));

    mProperties.read();
	mArduinoServerPortE->update();
    mDesiredRibbonLengthE->update();

    //This will update the UI from a thread
    mArduinoServer.assignOnUpdateCallBack(onUpdatesFromArduinoServer);
}

__fastcall TMain::~TMain()
{
	mProperties.write();
    mIniFile.save();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender)
{
	setupWindowTitle();
	gAppIsStartingUp = false;

	TMemoLogger::mMemoIsEnabled = true;
	gSplashForm->mMainAppIsRunning = true;

	this->Visible = true;
	while(gSplashForm->isOnShowTime() == true)
	{
       	Application->ProcessMessages();

		//In order to show whats going on on the splash screen
		if(gSplashForm->Visible == false)
		{
			break;
		}
	}

	gSplashForm->Close();
	gLogger.setLogLevel(mLogLevel);

	LogLevelCB->ItemIndex = mLogLevel.getValue() - 2;

	TMemoLogger::mMemoIsEnabled = true;
    UIUpdateTimer->Enabled = true;

	stringstream msg;
	msg << "SET_DESIRED_RIBBON_LENGTH=" << mDesiredRibbonLengthE->getValue();
	mArduinoServer.request(msg.str());

    //Setup the server
    mArduinoServer.start(mArduinoServerPortE->getValue());

	//Setup frames for the Arduinos
	setupUIFrames();
}

//---------------------------------------------------------------------------
void __fastcall	TMain::setupUIFrames()
{
    mPufferArduino.setName("PUFFER_ARDUINO");

    //Create ArduinoFrames
    TPufferArduinoBoardFrame* af1 = new TPufferArduinoBoardFrame(mArduinoServer, mPufferArduino, mIniFile, this);
    af1->Parent =  mArduinoSB;
    af1->Align = alLeft;
    af1->ConnectBtnClick(NULL);
    mFrames.push_back(af1);

    mSensorArduino.setName("SENSOR_ARDUINO");
    TSensorAndLightArduinoFrame* af2 = new TSensorAndLightArduinoFrame(mArduinoServer, mSensorArduino, mIniFile, this);
    af2->Parent =  mArduinoSB;
    af2->Align = alLeft;
    af2->ConnectBtnClick(NULL);
    mFrames.push_back(af2);
}

//This callback is called from the arduino server
//Its purpose is to update the servers UI.
void TMain::onUpdatesFromArduinoServer(const string& new_msg)
{
	struct TLocalArgs
    {
        string msg;
        void __fastcall onMsg()
        {
            //Parse the message
        	StringList l(msg, '=');
            if(startsWith("SECTION_COUNT", msg))
            {
                if(l.size() == 2)
                {
					Main->mSectionCountLbl->SetNumber(toInt(l[1]));
                }
            }
            else if(startsWith("AUTO_PUFF=", msg))
            {
                if(l.size() == 2)
                {
                    Main->mAutoPuffCB->Checked = (toBool(l[1])) ? true : false;
                }
            }
            else if(startsWith("AUTO_ZERO_CUT=", msg))
            {
                if(l.size() == 2)
                {
                    Main->mAutoZeroCutCB->Checked = (toBool(l[1])) ? true : false;
                }
            }

            else if(startsWith("DESIRED_RIBBON_LENGTH", msg))
            {
                if(l.size() == 2)
                {
                    Main->mDesiredRibbonLengthE->setValue(toInt(l[1]));
                }
            }
        }
    };

    TLocalArgs args;
    args.msg = new_msg;


    //This causes this function to be called in the UI thread
 	TThread::Synchronize(NULL, &args.onMsg);
}

//---------------------------------------------------------------------------
void __fastcall TMain::UIUpdateTimerTimer(TObject *Sender)
{
   	mArduinoServerStartBtn->Caption = mArduinoServer.isRunning() 		? "Stop" : "Start";
	mArduinoServerPortE->Enabled 	= !mArduinoServer.isRunning();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mArduinoServerStartBtnClick(TObject *Sender)
{
	if(mArduinoServerStartBtn->Caption == "Stop")
    {
    	mArduinoServer.stop();
    }
    else
    {
    	mArduinoServer.start(mArduinoServerPortE->getValue());
    }
}

void __fastcall TMain::mResetCounterBtnClick(TObject *Sender)
{
	mArduinoServer.request("RESET_SECTION_COUNT");
}

//---------------------------------------------------------------------------
void __fastcall TMain::mPuffRelatedBtnClick(TObject *Sender)
{
	TArrayBotButton* b = dynamic_cast<TArrayBotButton*>(Sender);
    if(b == mPuffNowBtn)
    {
		mArduinoServer.request("PUFF");
    }
    else if(b == mEnablePuffBtn)
    {
		mArduinoServer.request("ENABLE_PUFFER");
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::LigthsBtnsClick(TObject *Sender)
{
	TArrayBotButton* b = dynamic_cast<TArrayBotButton*>(Sender);
    if(b == mFrontBackLEDBtn )
    {
    	static string cap = "ON";
	   	if(contains("OFF", cap))
        {
        	mFrontBackLEDBtn->Caption = "Flip LEDs ON";
            cap = "ON";
        	mArduinoServer.request("TURN_ON_LED_LIGHTS");
        }
        else
        {
        	mFrontBackLEDBtn->Caption = "Flip LEDs OFF";
            cap = "OFF";
        	mArduinoServer.request("TURN_OFF_LED_LIGHTS");
        }
    }
    else if(b == mCoaxLightBtn)
    {
    	static string ccap = "ON";
	   	if(contains("OFF", ccap))
        {
        	mCoaxLightBtn->Caption = "Flip CoaxLight ON";
            ccap = "ON";
        	mArduinoServer.request("TURN_ON_COAX_LIGHT");
        }
        else
        {
        	mCoaxLightBtn->Caption = "Flip CoaxLight OFF";
            ccap = "OFF";
        	mArduinoServer.request("TURN_OFF_COAX_LIGHT");
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mAutoPuffCBClick(TObject *Sender)
{
	if(mAutoPuffCB->Checked)
    {
		mArduinoServer.enableAutoPuff();
    }
    else
    {
		mArduinoServer.disableAutoPuff();
    }
}

void __fastcall TMain::mAutoZeroCutCBClick(TObject *Sender)
{
	if(mAutoZeroCutCB->Checked)
    {
		mArduinoServer.enableAutoZeroCut();
    }
    else
    {
		mArduinoServer.disableAutoZeroCut();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mDesiredRibbonLengthEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
    if(Key == vkReturn)
    {
    	stringstream smsg;
        smsg << "SET_DESIRED_RIBBON_LENGTH=" << mDesiredRibbonLengthE->getValue();
        mArduinoServer.request(smsg.str());
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mSetZeroCutBtnClick(TObject *Sender)
{
	mArduinoServer.request("SET_CUT_THICKNESS_PRESET=1");
}

//---------------------------------------------------------------------------
void __fastcall TMain::mSetPresetCutBtnClick(TObject *Sender)
{
	//Check the listbox for current preset
    String txt  = mLeicaCutThicknessLB->Text;
    int indx = mLeicaCutThicknessLB->Items->IndexOf(txt);
    if(indx != -1)
    {
        stringstream msg;
        msg <<"SET_CUT_THICKNESS_PRESET="<<indx + 1;
        mArduinoServer.request(msg.str());
    }
    else
    {
    	Log(lError) <<"Error setting cut preset!";
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mStartNewRibbonButtonClick(TObject *Sender)
{
	//Tell Arduino server to start new Ribbon
    stringstream msg;
    msg <<"START_NEW_RIBBON";
    mArduinoServer.request(msg.str());
}


