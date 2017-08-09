#include <vcl.h>
#pragma hdrstop
#include "TProcessSequenceControlForm.h"
#include "arraybot/process/atProcessSequencer.h"
#include "mtkVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TProcessSequenceControlForm *ProcessSequenceControlForm;

using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TProcessSequenceControlForm::TProcessSequenceControlForm(ProcessSequencer& s, TComponent* Owner)
	: TForm(Owner),
    mPS(s)
{}

//---------------------------------------------------------------------------
void __fastcall TProcessSequenceControlForm::FormShow(TObject *Sender)
{
	//Fill out current sequence name
	//Start the check sequence status timer
   	mStatus = psUnknown;
	mStatusTimer->Enabled = true;
    mPS.initCurrentSequence();

    mSequenceNameLbl->Caption 		= vclstr(mPS.getCurrentSequenceName());
    mProcessNameLbl->Caption 		= vclstr(mPS.getCurrentProcessName());
    mNextProcessNameLbl->Caption 	= vclstr(mPS.getNextProcessName());
}

//---------------------------------------------------------------------------
void __fastcall TProcessSequenceControlForm::mStatusTimerTimer(TObject *Sender)
{
	static ProcessStatus lastStatus = psFinished;

    if(mPS.isRunning())
    {
	    mStatus = psRunning;
    }
    else if(mPS.isPaused())
    {
    	mStatus = psPaused;
    }
    else if(mPS.isDone())
    {
	    mStatus = psFinished;
    }
    else //Sequence is not started
    {
		mStatus = psNotStarted;
    }

    mSequenceNameLbl->Caption 		= vclstr(mPS.getCurrentSequenceName());
    mProcessNameLbl->Caption 		= vclstr(mPS.getCurrentProcessName());
    mNextProcessNameLbl->Caption 	= vclstr(mPS.getNextProcessName());

    if(lastStatus != mStatus)
    {
        lastStatus = mStatus;
        switch(mStatus)
        {
			case psNotStarted:
                mStartResumeButton->Enabled = true;
                mPauseBtn->Enabled = false;
            break;

            case psRunning:
                mStartResumeButton->Enabled = false;
                mPauseBtn->Enabled = true;
            break;

            case psPaused:
                mStartResumeButton->Caption = "Resume";
                mStartResumeButton->Enabled = true;
                mPauseBtn->Enabled = false;
            break;

            case psFinished:
				mStatusTimer->Enabled = false;
            	Close();
            break;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TProcessSequenceControlForm::mStartResumeButtonClick(TObject *Sender)
{
	if(mStartResumeButton->Caption == "Start")
    {
		mPS.start();
    }
    else if(mStartResumeButton->Caption == "Resume")
    {
		mPS.resume();
    }
}

void __fastcall TProcessSequenceControlForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	mStatusTimer->Enabled = false;
}

//---------------------------------------------------------------------------
void __fastcall TProcessSequenceControlForm::mStopBtnClick(TObject *Sender)
{
    mStatusTimer->Enabled = false;
	mPS.stop();
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TProcessSequenceControlForm::mPauseBtnClick(TObject *Sender)
{
	mPS.pause();
}


