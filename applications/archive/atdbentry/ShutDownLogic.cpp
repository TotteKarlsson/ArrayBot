#pragma hdrstop
#include "MainForm.h"
#include "dslLogger.h"
using namespace dsl;

//---------------------------------------------------------------------------
void __fastcall TMain::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;
	if(mLogFileReader.isRunning())
	{
		Log(lDebug) << "Shutting down log file reader";
		mLogFileReader.stop();
        mLogFileReader.assignOnMessageCallBack(NULL);
	}

//    if(mServerSession.isConnected())
//    {
//    	mServerSession.disConnect();
//    }

    //This will save any ini parameters in the frame
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Log(lInfo) << "Closing down....";

	//Check if active stuff is going on.. if so call the ShutDown in the
    //Timer fire    if(
   	CanClose = (
    			    mLogFileReader.isRunning()
//    			||	mServerSession.isConnected()


                ) ? false : true;


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

