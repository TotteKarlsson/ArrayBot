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

	stringstream smsg;
	smsg << "SET_DESIRED_RIBBON_LENGTH=" << mDesiredRibbonLengthE->getValue();
   	IPCMessage msg(-1, smsg.str());
	mArduinoServer.postIPCMessage(msg);

    //Setup the server
    mArduinoServer.start(mArduinoServerPortE->getValue());

	//Setup frames for the Arduinos
	setupUIFrames();
	mArduinoServer.broadcastStatus();

//	mGetReadyForZeroCutSound.Create("SHORT_BEEP_2", this->Handle);
//	mSetZeroCutSound.Create("BUTTON_CLICK_2", this->Handle);
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

//This callback is called from the arduino server
void TMain::onUpdatesFromArduinoServer(const string& new_msg)
{
	struct TLocalArgs
    {
        string msg;
        void __fastcall onMsg()
        {
            if(startsWith("SECTION_COUNT", msg))
            {
                StringList l(msg, '=');
                if(l.size() == 2)
                {
					Main->mSectionCountLbl->SetNumber(toInt(l[1]));
                }

                if(Main->mSectionCountLbl->GetValue() == 0 &&  Main->mEnablesoundsCB->Checked)
                {
//	   				Main->mSetZeroCutSound.Stop();
                }
            }
            else if(startsWith("AUTO_PUFF=", msg))
            {
                //Parse the message
                StringList l(msg, '=');
                if(l.size() == 2)
                {
                    Main->mAutoPuffCB->Checked = (toBool(l[1])) ? true : false;
                }
            }
            else if(startsWith("DESIRED_RIBBON_LENGTH", msg))
            {
                //Parse the message
                StringList l(msg, '=');
                if(l.size() == 2)
                {
                    Main->mDesiredRibbonLengthE->setValue(toInt(l[1]));
                }
            }
            else if(startsWith("GET_READY_FOR_ZERO_CUT_1", msg))
            {
                if(Main->mEnablesoundsCB->Checked)
                {
//					Main->mGetReadyForZeroCutSound.Play(0, false);
                }
            }
            else if(startsWith("GET_READY_FOR_ZERO_CUT_2", msg))
            {
                if(Main->mEnablesoundsCB->Checked)
                {
//					Main->mGetReadyForZeroCutSound.Play(0, false);
                }
            }
            else if(startsWith("SET_ZERO_CUT", msg))
            {
//	            Main->mGetReadyForZeroCutSound.Stop();
                if(Main->mEnablesoundsCB->Checked)
                {
//					Main->mSetZeroCutSound.Play(0, false);
                }
            }
            else if(startsWith("DHT22DATA", msg))
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
    args.msg = new_msg;

	//    Log(lDebug5) << "Handling onUpdatesFromArduino message in synchronize:" << new_msg;

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
   	IPCMessage msg(-1, "RESET_SECTION_COUNT");
	mArduinoServer.postIPCMessage(msg);
}

//---------------------------------------------------------------------------
void __fastcall TMain::mPuffRelatedBtnClick(TObject *Sender)
{
	TArrayBotButton* b = dynamic_cast<TArrayBotButton*>(Sender);
    if(b == mPuffNowBtn)
    {
    	IPCMessage msg(-1, "PUFF");
		mArduinoServer.postIPCMessage(msg);
    }
    else if(b == mEnablePuffBtn)
    {
    	IPCMessage msg(-1, "ENABLE_PUFFER");
		mArduinoServer.postIPCMessage(msg);
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
        	mArduinoServer.turnLEDLightOn();
        }
        else
        {
        	mFrontBackLEDBtn->Caption = "Flip LEDs OFF";
            cap = "OFF";
        	mArduinoServer.turnLEDLightOff();
        }
    }
    else if(b == mCoaxLightBtn)
    {
    	static string ccap = "ON";
	   	if(contains("OFF", ccap))
        {
        	mCoaxLightBtn->Caption = "Flip CoaxLight ON";
            ccap = "ON";
        	mArduinoServer.turnCoaxLightOn();
        }
        else
        {
        	mCoaxLightBtn->Caption = "Flip CoaxLight OFF";
            ccap = "OFF";
        	mArduinoServer.turnCoaxLightOff();
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
        IPCMessage msg(-1, smsg.str());
        mArduinoServer.postIPCMessage(msg);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::mSetZeroCutBtnClick(TObject *Sender)
{
	//	mPufferArduino.setCutPreset(1);
	IPCMessage msg(-1, "SET_CUT_PRESET=1");
	mArduinoServer.postIPCMessage(msg);
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
        msg <<"SET_CUT_PRESET="<<indx + 1;
        IPCMessage ipc_msg(-1, msg.str());
        mArduinoServer.postIPCMessage(ipc_msg);
    }
    else
    {
    	Log(lError) <<"Error setting cut preset!";
    }
}

////---------------------------------------------------------------------------
void __fastcall TMain::mStartNewRibbonButtonClick(TObject *Sender)
{
	//Tell Arduino server to start new Ribbon
    stringstream msg;
    msg <<"START_NEW_RIBBON";
    IPCMessage ipc_msg(-1, msg.str());
    mArduinoServer.postIPCMessage(ipc_msg);

}


