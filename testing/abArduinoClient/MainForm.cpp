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

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "TIntLabel"
#pragma link "mtkFloatLabel"
#pragma link "TPropertyCheckBox"
#pragma resource "*.dfm"
TMain *Main;

extern string           gLogFileLocation;
extern string           gLogFileName;
extern string           gAppDataFolder;
extern bool             gAppIsStartingUp;
using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
	TRegistryForm("ArduinoClient", "MainForm", Owner),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", gLogFileName), &logMsg),
    mIniFile(joinPath(gAppDataFolder, "ArduinoClient.ini"), true, true),
    mLogLevel(lAny)
{
	TMemoLogger::mMemoIsEnabled = false;
   	mLogFileReader.start(true);

	//Setup UI/INI properties
    mProperties.setSection("UI");
	mProperties.setIniFile(&mIniFile);
	mProperties.add((BaseProperty*)  &mLogLevel.setup( 	                    	"LOG_LEVEL",    	 lAny));
	mProperties.add((BaseProperty*)  &mArduinoServerPortE->getProperty()->setup("SERVER_PORT",    	 50000));
    mProperties.read();
	mArduinoServerPortE->update();

	mArduinoClient.assignOnMessageReceivedCallBack(onMessageReceived);
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

	this->Visible = true;
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

	setupUIFrames();
}

//---------------------------------------------------------------------------
void __fastcall	TMain::setupUIFrames()
{
//    mFrames.push_back(af);
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
   	mASStartBtn->Caption 			= mArduinoClient.isConnected()	? "Stop" : "Start";
	mArduinoServerPortE->Enabled 	= !mArduinoClient.isConnected();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mASStartBtnClick(TObject *Sender)
{
	if(mASStartBtn->Caption == "Start")
    {
    	mArduinoClient.connect(mArduinoServerPortE->getValue());
        mASStartBtn->Caption == "Connecting";
        mArduinoClient.getStatus();
    }
    else
    {
    	mArduinoClient.disConnect();
    }
}

void TMain::onMessageReceived(const string& msg)
{
	struct TLocalArgs
    {
        string msg;
        void __fastcall onPufferArduinoMessage()
        {
            if(startsWith(msg, "SECTION_COUNT"))
            {
                //Parse the message
                StringList l(msg, '=');
                if(l.size() == 2)
                {
                    Main->mSectionCountLbl->SetValue(toInt(l[1]));
                }
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

            else if(startsWith(msg, "DESIRED_RIBBON_LENGTH"))
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
//            else if(startsWith(msg, "PIN_8"))
//            {
//                StringList l(msg,'=');
//                if(l.size() == 2)
//                {
////                    Main->mCoaxLEDBtn->Caption = l[1] == "HIGH" ? "Coax LEDs OFF" : "Coax LEDs On";
//                }
//            }
//            else if(startsWith(msg, "PIN_3"))
//            {
//                StringList l(msg,'=');
//                if(l.size() == 2)
//                {
//  //                  Main->mFrontBackLEDBtn->Caption = l[1] == "HIGH" ? "Front/Back LEDs OFF" : "Front/Back LEDs On";
//                }
//            }
        }
    };

    TLocalArgs args;
    args.msg = msg;

    //This causes this fucntion to be called in the UI thread
	TThread::Synchronize(NULL, &args.onPufferArduinoMessage);
}

//---------------------------------------------------------------------------
void __fastcall TMain::mResetCountBtnClick(TObject *Sender)
{
	//Send a request to reset the counter
	mArduinoClient.resetSectionCounter();
}


void __fastcall TMain::mPuffAfterSectionCountEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
    if(Key == vkReturn)
    {
    	mArduinoClient.setPuffAfterSectionCount(mPuffAfterSectionCountE->getValue());
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mAutoPuffCBClick(TObject *Sender)
{
	if(mAutoPuffCB->Checked)
    {
		mArduinoClient.enableAutoPuff();
    }
    else
    {
		mArduinoClient.disableAutoPuff();
    }
}



