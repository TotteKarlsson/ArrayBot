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
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArduinoServer", gLogFileName), &logMsg),
    mIniFile(joinPath(gAppDataFolder, "ArduinoServer.ini"), true, true),
    mLogLevel(lAny),
    mAS(-1),
    mAD1(mAS.getArduinoDevice(1)),
    mAD2(mAS.getArduinoDevice(2))
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

	if(mLogLevel == lInfo)
	{
		LogLevelCB->ItemIndex = 0;
	}
	else if(mLogLevel == lAny)
	{
		LogLevelCB->ItemIndex = 1;
	}

	TMemoLogger::mMemoIsEnabled = true;
    UIUpdateTimer->Enabled = true;

    //Setup the server
    mAS.start(mArduinoServerPortE->getValue());

	//Setup frames for the Arduinos
	setupUIFrames();

    mAD1.assignMessageReceivedCallBack(onPufferArduinoMessage);
    mAD2.assignMessageReceivedCallBack(onSensorArduinoMessage);
}


//---------------------------------------------------------------------------
void __fastcall	TMain::setupUIFrames()
{
    mAD1.setName("PUFFER_ARDUINO");

    //Create ArduinoFrames
    TPufferArduinoBoardFrame* af1 = new TPufferArduinoBoardFrame(mAD1, mIniFile, this);
    af1->Parent =  mArduinoSB;
    af1->Align = alTop;
    af1->ConnectBtnClick(NULL);
    mFrames.push_back(af1);

    mAD2.setName("SENSOR_ARDUINO");
    TSensorAndLightArduinoFrame* af2 = new TSensorAndLightArduinoFrame(mAD2, mIniFile, this);
    af2->Parent =  mArduinoSB;
    af2->Align = alTop;
    af2->ConnectBtnClick(NULL);
    mFrames.push_back(af2);

}

//This callback is called from the
void TMain::onPufferArduinoMessage(const string& msg)
{
//	struct TLocalArgs
//    {
//        string msg;
//        void __fastcall onPufferArduinoMessage()
        {
            //Handle the message..
            //Check what message we got from arduino device
            if(msg == "ArrayBot Puffer Init")
            {
                //Setup variables
                //Puffer duration etc..
                if(Main->mAD1.init)
                {
                    Main->mAD1.init();
                }
            }
            else if (msg == "HALL_SENSOR=HIGH")
            {
                Main->mSectionCount->SetValue(Main->mSectionCount->GetValue() + 1);
                if(Main->mAutoPuffCB->Checked)
                {
                    if(Main->mSectionCount->GetValue() > Main->mPuffAfterSectionCountE->getValue())
                    {
                        //puff
                        Main->mAD1.send("p");

                        //If succesful, reset the counter
                        Main->mSectionCount->SetValue(0);
                    }
                }
            }
		    Main->mAS.broadcast(msg);
        }
//    };
//
//    TLocalArgs args;
//    args.msg = msg;
//
//    //This causes this fucntion to be called in the UI thread
//	TThread::Synchronize(NULL, &args.onPufferArduinoMessage);
}

void TMain::onSensorArduinoMessage(const string& msg)
{
	struct TLocalArgs
    {
        string msg;
        void __fastcall onSensorArduinoMessage()
        {
            //Handle the message..
            //Check what message we got from arduino device
            if(msg == "ArrayBot Lights")
            {
                //Setup variables
                //Puffer duration
                if(Main->mAD2.init)
                {
                    Main->mAD2.init();
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
            else if(startsWith(msg, "PIN_8"))
            {
                StringList l(msg,'=');
                if(l.size() == 2)
                {
                    Main->mCoaxLEDBtn->Caption = l[1] == "HIGH" ? "Coax LEDs OFF" : "Coax LEDs On";
                }
            }

            else if(startsWith(msg, "PIN_3"))
            {
                StringList l(msg,'=');
                if(l.size() == 2)
                {
                    Main->mFrontBackLEDBtn->Caption = l[1] == "HIGH" ? "Front/Back LEDs OFF" : "Front/Back LEDs On";
                }
            }

            Main->mAS.broadcast(msg);
        }
    };

    TLocalArgs args;
    args.msg = msg;

    //This causes this fucntion to be called in the main UI thread
	TThread::Synchronize(NULL, &args.onSensorArduinoMessage);
}

//---------------------------------------------------------------------------
void __fastcall TMain::UIUpdateTimerTimer(TObject *Sender)
{
   	mASStartBtn->Caption 			= mAS.isRunning() 		? "Stop" : "Start";
	mArduinoServerPortE->Enabled 	= !mAS.isRunning();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mASStartBtnClick(TObject *Sender)
{
	if(mASStartBtn->Caption == "Stop")
    {
    	mAS.stop();
    }
    else
    {
    	mAS.start(mArduinoServerPortE->getValue());
    }
}

void __fastcall TMain::mResetCounterBtnClick(TObject *Sender)
{
	mSectionCount->SetValue(0);
}

//---------------------------------------------------------------------------
void __fastcall TMain::PuffNowBtnClick(TObject *Sender)
{
	mAD1.send("p");
    mSectionCount->SetValue(0);
}

//---------------------------------------------------------------------------
void __fastcall TMain::LEDBtnClick(TObject *Sender)
{
	TButton* b = dynamic_cast<TButton*>(Sender);
    if(b == mCoaxLEDBtn)
    {
		//Check Caption
	   	if(contains("ON", stdstr(mCoaxLEDBtn->Caption)))
        {
        	mAD2.send("1");
        }
        else
        {
        	mAD2.send("2");
        }
    }
    else if(b == mFrontBackLEDBtn)
    {
	   	if(contains("ON", stdstr(mFrontBackLEDBtn->Caption)))
        {
        	mAD2.send("3");
        }
        else
        {
         	mAD2.send("4");
        }
    }

}


