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
#pragma link "mtkSTDStringEdit"
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
	TRegistryForm("Test", "MainForm", Owner),
	mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArduinoServer", gLogFileName), &logMsg),
    mIniFile(joinPath(gAppDataFolder, "ArduinoServer.ini"), true, true),
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

    //Setup the server
    //mAS.start(mArduinoServerPortE->getValue());

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
//   	mASStartBtn->Caption 			= mAS.isRunning() 		? "Stop" : "Start";
//	mArduinoServerPortE->Enabled = !mAS.isRunning();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mASStartBtnClick(TObject *Sender)
{
	if(mASStartBtn->Caption == "Stop")
    {
//    	mAS.stop();
    }
    else
    {
//    	mAS.start(mArduinoServerPortE->getValue());
    }
}
