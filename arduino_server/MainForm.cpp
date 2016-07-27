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
    mAD1(mAS.getArduinoDevice(1))
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

	setupUIFrames();
    ArduinoDevice& a1 = mAS.getArduinoDevice(1);
    a1.assignMessageReceivedCallBack(onPufferArduinoMessage);
}


//---------------------------------------------------------------------------
void __fastcall	TMain::setupUIFrames()
{
    ArduinoDevice& a1 = mAS.getArduinoDevice(1);
    a1.setName("PUFFER_ARDUINO");

    //Create an ArduinoFrame
    TPufferArduinoBoardFrame* af = new TPufferArduinoBoardFrame(a1, mIniFile, this);
    af->Parent =  mArduinoSB;
    af->Align = alTop;
    af->ConnectBtnClick(NULL);
    mFrames.push_back(af);
}

void TMain::onPufferArduinoMessage(const string& msg)
{
	//Handle the message..
  	//Check what message we got from arduino device
	if(msg == "ArrayBot Puffer Init")
    {
    	//Setup variables
    	//Puffer duration
        if(mAD1.init)
        {
			mAD1.init();
        }
    }
    else if (msg == "HALL_SENSOR=HIGH")
    {
    	mSectionCount->SetValue(mSectionCount->GetValue() + 1);
        if(mAutoPuffCB->Checked)
        {
        	if(mSectionCount->GetValue() > mPuffAfterSectionCountE->getValue())
            {
            	//puff
                mAD1.send("p");
                //If succesful, reset the counter
                mSectionCount->SetValue(0);
            }
        }
    }
    else if (startsWith(msg, "DHT22DATA"))
    {
    	//Parse the message
        StringList l(msg,',');
        if(l.size() == 3)
        {
        	mTemperatureLbl->SetValue(toDouble(l[1]));
	        mHumidityE->SetValue(toDouble(l[2]));
        }
    }

    mAS.broadcast(msg);
}

void __fastcall TMain::LogLevelCBChange(TObject *Sender)
{
    if(LogLevelCB->ItemIndex == 0)
    {
        mLogLevel = lInfo;
    }
    else if(LogLevelCB->ItemIndex == 1)
    {
        mLogLevel = lAny;
    }

    gLogger.setLogLevel(mLogLevel);
}

//---------------------------------------------------------------------------
void __fastcall TMain::AppInBox(mlxStructMessage &msg)
{
    if(msg.lparam == NULL)
    {
        return;
    }

    try
    {
        ApplicationMessageEnum aMsg = msg.lparam->mMessageEnum;

        switch(aMsg)
        {
            case abSplashWasClosed:
                Log(lDebug2) << "Splash form sent message that it was closed";
                gSplashForm = NULL;
            break;

            default:
            break ;
        }
	}
	catch(...)
	{
		Log(lError) << "Received an unhandled windows message!";
	}
}

//---------------------------------------------------------------------------
void __fastcall TMain::UIUpdateTimerTimer(TObject *Sender)
{
   	mASStartBtn->Caption 			= mAS.isRunning() 		? "Stop" : "Start";
	mArduinoServerPortE->Enabled = !mAS.isRunning();
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



void __fastcall TMain::Button1Click(TObject *Sender)
{
	mSectionCount->SetValue(0);
}
//---------------------------------------------------------------------------


void __fastcall TMain::PuffNowBtnClick(TObject *Sender)
{
	mAD1.send("p");
}
//---------------------------------------------------------------------------

