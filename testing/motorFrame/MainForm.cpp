#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "arraybot/apt/atAPTMotor.h"
#include "arraybot/apt/atDeviceManager.h"
#include "core/atUtilities.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "core/atCore.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTLogMemoFrame"
#pragma resource "*.dfm"
TMain *Main;

extern string gLogFileLocation;
extern string gLogFileName;
extern string gAppDataFolder;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
:
	TRegistryForm("Test", "MainForm", Owner),
    mIniFile(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", "motor_frame_tester.ini"), true, true)
{
	initABCoreLib();

	//Setup UI properties
    mProperties.setSection("UI");
	mProperties.setIniFile(&mIniFile);
    mProperties.read();
}

__fastcall TMain::~TMain()
{
	mProperties.write();
    mIniFile.save();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender)
{
	TLogMemoFrame1->init();
    mDeviceManager.connectAllDevices();

    APTDevice* dev = mDeviceManager.getFirst();
    if(dev)
    {
    	dev->setName("test");
    }
	createMotorFrame(dynamic_cast<APTMotor*> (dev));
    while(mDeviceManager.getNext())
    {
		createMotorFrame(dynamic_cast<APTMotor*> (mDeviceManager.getCurrent()));
    }
}

//void __fastcall TMain::WndProc(TMessage& Message)
//{
//    if (Message.Msg == getABCoreMessageID("MOTOR_WARNING_MESSAGE") && getABCoreMessageID("MOTOR_WARNING_MESSAGE") != 0)
//    {
//    	MotorMessageData* msg = reinterpret_cast<MotorMessageData*>(Message.WParam);
//       	APTMotor* mtr = mXYZUnit.getMotorWithSerial(msg->mSerial);
//
//        if(!mtr)
//        {
//        	//real bad....
//        }
//
//		//Handle the warning..
//        if(msg->mCurrentPosition >= msg->mPositionLimits.getValue().getMax())
//        {
//            if(mtr)
//            {
//            	if(mtr->getLastCommand() != mcStopHard)
//                {
//            		mtr->stop();
////	                playATSound(absMotorWarning);
//    	            Log(lInfo) << "Stopped motor: "<<mtr->getName();
//                }
//            }
//        }
//
//        if(mtr->isInDangerZone())
//        {
////        	playABSound(absMotorWarning);
//        }
//
//
//        //Message is now consumed.. delete it
//        delete msg;
//    }
//    else
//    {
//        TForm::WndProc(Message);
//    }
//}

bool TMain::createMotorFrame(APTMotor* mtr)
{
	if(!mtr)
    {
    	return false;
    }
    TMotorFrame *f = new TMotorFrame(mtr->getName(), ScrollBox1);
   	f->assignMotor(mtr);
    f->Parent = ScrollBox1;
    f->Align = alTop;

	f->MotorStatusTimer->Enabled = true;
    return true;
}

