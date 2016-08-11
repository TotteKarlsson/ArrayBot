#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "TMemoLogger.h"
#include "mtkStringList.h"
#include "abUtilities.h"
#include "abAPTMotor.h"
#include "abTCubeDCServo.h"
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
#pragma resource "*.dfm"
TMain *Main;

extern string           gLogFileLocation;
extern string           gLogFileName;
extern string           gAppDataFolder;
extern TSplashForm*  	gSplashForm;
extern bool             gAppIsStartingUp;
using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
	TRegistryForm("Test", "MainForm", Owner),
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
	mProperties.add((BaseProperty*)  &mPuffAfterSectionCountE->getProperty()->setup("PUFF_AFTER_SECTION_COUNT",    	 25));

    mProperties.read();
	mArduinoServerPortE->update();
    mPuffAfterSectionCountE->update();

    mArduinoServer.assignOnUpdateCallBack(onUpdatesFromArduinoServer);
    mArduinoServer.setPuffAfterSectionCount(mPuffAfterSectionCountE->getValue());
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

    //Setup the server
    mArduinoServer.start(mArduinoServerPortE->getValue());

	//Setup frames for the Arduinos
	setupUIFrames();
	mArduinoServer.broadcastStatus();
}

//---------------------------------------------------------------------------
void __fastcall	TMain::setupUIFrames()
{
    mPufferArduino.setName("PUFFER_ARDUINO");

    //Create ArduinoFrames
    TPufferArduinoBoardFrame* af1 = new TPufferArduinoBoardFrame(mPufferArduino, mIniFile, this);
    af1->Parent =  mArduinoSB;
    af1->Align = alTop;
    af1->ConnectBtnClick(NULL);
    mFrames.push_back(af1);

    mSensorArduino.setName("SENSOR_ARDUINO");
    TSensorAndLightArduinoFrame* af2 = new TSensorAndLightArduinoFrame(mSensorArduino, mIniFile, this);
    af2->Parent =  mArduinoSB;
    af2->Align = alTop;
    af2->ConnectBtnClick(NULL);
    mFrames.push_back(af2);

}

//This callback is called from the
void TMain::onUpdatesFromArduinoServer(const string& msg)
{
	struct TLocalArgs
    {
        string msg;
        void __fastcall onPufferArduinoMessage()
        {
            if(startsWith(msg, "SECTION_COUNT"))
            {
				Main->mSectionCount->SetNumber(Main->mArduinoServer.getSectionCount());
            }
            else if(startsWith(msg, "AUTO_PUFF="))
            {
                //Parse the message
                StringList l(msg, '=');
                if(l.size() == 2)
                {
                    Main->mAutoPuffCB->Checked = (toBool(l[1])) ? true : false;
                }
            }
            else if(startsWith(msg, "PUFF_AFTER_SECTION_COUNT"))
            {
                //Parse the message
                StringList l(msg, '=');
                if(l.size() == 2)
                {
                    Main->mPuffAfterSectionCountE->setValue(toInt(l[1]));
                }
            }
            else if(startsWith(msg, "DHT22DATA"))
            {
                //Parse the message
                StringList l(msg,',');
                if(l.size() == 3)
                {
                    Main->mTemperatureLbl->SetValue(toDouble(l[1]));
                    Main->mHumidityE->SetValue(toDouble(l[2]));
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
	mArduinoServer.resetSectionCount();
}

//---------------------------------------------------------------------------
void __fastcall TMain::PuffNowBtnClick(TObject *Sender)
{
	mPufferArduino.send("p");
    mSectionCount->SetValue(0);
}

//---------------------------------------------------------------------------
void __fastcall TMain::LigthsBtnsClick(TObject *Sender)
{
	TButton* b = dynamic_cast<TButton*>(Sender);
    if(b == mFrontBackLEDBtn )
    {
    	static string cap = "ON";
	   	if(contains("OFF", cap))
        {

        	mFrontBackLEDBtn->Caption = "Flip LEDs ON";
        	mArduinoServer.turnLEDLightOn();
            cap = "ON";
        }
        else
        {
        	mFrontBackLEDBtn->Caption = "Flip LEDs OFF";
        	mArduinoServer.turnLEDLightOff();
            cap = "OFF";
        }
    }
    else if(b == mCoaxLightBtn)
    {
    	static string ccap = "ON";
	   	if(contains("OFF", ccap))
        {

        	mCoaxLightBtn->Caption = "Flip CoaxLight ON";
        	mArduinoServer.turnCoaxLightOn();
            ccap = "ON";
        }
        else
        {
        	mCoaxLightBtn->Caption = "Flip CoaxLight OFF";
        	mArduinoServer.turnCoaxLightOff();
            ccap = "OFF";
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

//---------------------------------------------------------------------------
void __fastcall TMain::mPuffAfterSectionCountEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
    if(Key == vkReturn)
    {
    	mArduinoServer.setPuffAfterSectionCount(mPuffAfterSectionCountE->getValue());
    }
}


