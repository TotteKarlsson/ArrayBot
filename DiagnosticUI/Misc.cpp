#include "MainForm.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "abAPTMotor.h"
using namespace mtk;


APTMotor* TMain::getCurrentMotor()
{
    int ii = devicesLB->ItemIndex;
    if(ii > -1)
    {
        APTDevice* device = (APTDevice*) devicesLB->Items->Objects[ii];

        //Check position for current device
        return dynamic_cast<APTMotor*>(device);
    }
    return NULL;
}

//---------------------------------------------------------------------------
void __fastcall TMain::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;
	if(mLogFileReader.isRunning())
	{
		Log(lDebug) << "Shutting down log file reader";
		mLogFileReader.stop();
	}

//    if(mMotorMessageProcessor.isRunning())
//    {
//		Log(lDebug) << "Shutting MotorMessageProcessor";
//    	mMotorMessageProcessor.stop();
//    }

	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Log(lInfo) << "Closing down....";

	//Check if we can close.. abort all threads..
	CanClose = (mLogFileReader.isRunning()) ? false : true;
//	if(mMotorMessageProcessor.isRunning())
//    {
//    	CanClose == false;
//    }

	if(CanClose == false)
	{
		ShutDownTimer->Enabled = true;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	Log(lInfo) << "In FormClose";
}

void __fastcall	TMain::OnException()
{
	Log(lInfo) << "Exception TMain::OnException()";
}

//---------------------------------------------------------------------------
void __fastcall TMain::ApplicationEvents1Exception(TObject *Sender, Exception *E)
{
	Log(lInfo) << "Application Exception...."<<stdstr(E->Message);
}


void __fastcall TMain::BitBtn3Click(TObject *Sender)
{
	infoMemo->Clear();
}

//This one is called from the reader thread
void __fastcall TMain::logMsg()
{
    infoMemo->Lines->Add(vclstr(mLogFileReader.getData()));
    mLogFileReader.purge();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
    {
    	Close();
    }
}



