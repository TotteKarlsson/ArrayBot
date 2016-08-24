#include <vcl.h>
#pragma hdrstop
#include "TABProcessSequencerFrame.h"
#include "abXYZUnit.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "abAPTMotor.h"
#include "abParallellProcess.h"
#include "abArrayBot.h"
#include "abTimeDelay.h"
#include "abApplicationMessages.h"
#include "UIUtilities.h"
#include "abVCLUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "TMotorMoveProcessFrame"
#pragma link "TParallellProcessesFrame"
#pragma link "TSTDStringLabeledEdit"
#pragma link "TTimeDelayFrame"
#pragma link "TSequenceInfoFrame"
#pragma resource "*.dfm"
TABProcessSequencerFrame *ABProcessSequencerFrame;
//---------------------------------------------------------------------------

extern string gAppDataFolder;
using namespace mtk;

int TABProcessSequencerFrame::mFrameNr = 0;
__fastcall TABProcessSequencerFrame::TABProcessSequencerFrame(ArrayBot& ab, const string& appFolder, TComponent* Owner)
	: TFrame(Owner),
    mAB(ab),
    mProcessSequencer(mAB.getProcessSequencer())
{
    TFrame::Name = vclstr("Frame_" + replaceCharacter('-', '_', "MoveSequenceFrame") + mtk::toString(++mFrameNr));
    mProcessFileExtension = "abp";
    TSequenceInfoFrame1->assignArrayBot(&ab);
    refreshSequencesCB();
}

void TABProcessSequencerFrame::init()
{
    if(mSequencesCB->Items->Count)
    {
        mSequencesCB->ItemIndex = 0;
		mSequencesCBChange(NULL);
    }
    else
    {
    	mDeleteSequenceBtn->Enabled = false;
		mSaveSequenceBtn->Enabled = false;
    }
}

void __fastcall TABProcessSequencerFrame::mDeleteSequenceBtnClick(TObject *Sender)
{
	//Check selected sequence and delete it
    int idx = mSequencesCB->ItemIndex;
    if(idx > -1)
    {
    	string seqName = stdstr(mSequencesCB->Items->Strings[idx]);
        mProcessSequencer.deleteSequence(seqName);
		mSequencesCB->DeleteSelected();
        mSequencesCB->Update();
		if(mSequencesCB->Items->Count)
        {
	        mSequencesCB->ItemIndex = 0;
        }
    }

	mSequencesCBChange(Sender);

    //Send a message to main ui to update sequence shortcuts
    if(sendAppMessage(abSequencerUpdate) != true)
    {
        Log(lDebug)<<"Sending sequencer update was unsuccesful";
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mAddSeqBtnClick(TObject *Sender)
{
    //Save current sequence, if any
    mProcessSequencer.saveCurrent();

	ProcessSequence* s = new ProcessSequence(mAB);
    mProcessSequencer.addSequence(s);

	mSequencesCB->Items->Add(vclstr(s->getName()));
	mSequencesCB->ItemIndex = mSequencesCB->Items->IndexOf(vclstr(s->getName()));
	mSequencesCBChange(NULL);

    //Send a message to main ui to update sequence shortcuts
    if(sendAppMessage(abSequencerUpdate) != true)
    {
        Log(lDebug)<<"Sending sequencer update was unsuccesful";
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::refreshSequencesCB()
{
    mSequencesCB->Clear();
    mProcessSequencer.loadAll(joinPath(gAppDataFolder, "sequences"));
    ProcessSequences& seqs = mProcessSequencer.getSequences();
   	ProcessSequence* s = seqs.getFirst();
    while(s)
	{
    	mSequencesCB->Items->Add(s->getName().c_str());
        s = seqs.getNext();
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mSequencesCBChange(TObject *Sender)
{
	//Load the sequence
    int index = mSequencesCB->ItemIndex;
    if(index == -1)
    {
        TSequenceInfoFrame1->populate(NULL);
    	return;
    }

    mDeleteSequenceBtn->Enabled = true;
    mSaveSequenceBtn->Enabled 	= true;

    string sName(stdstr(mSequencesCB->Items->Strings[index]));

    //Repopulate the listbox
	if(mProcessSequencer.selectSequence(sName))
    {
    	//Fill out sequence frame
		ProcessSequence* seq = mProcessSequencer.getCurrentSequence();
        if(!seq)
        {
        	return;
        }

        TSequenceInfoFrame1->populate(seq, mProcessPanel);
    }
    else
    {
    	stringstream ss;
        ss << "Failed loading the sequence:" << sName <<". See logfile for more details";
        MessageDlg(ss.str().c_str(), mtError, TMsgDlgButtons() << mbOK, 0);
    }
}

void __fastcall TABProcessSequencerFrame::mStartBtnClick(TObject *Sender)
{
    if(mStartBtn->Caption == "Start" )
    {
    	//Save current sequence
       	saveSequence();
        mAB.disableJoyStickAxes();
    	mProcessSequencer.start(mContinousExecutionCB->Checked);

		mSequenceStatusTimer->Enabled = true;
        string pName = mProcessSequencer.getCurrentProcessName();
        selectAndClickListBoxItem(this->TSequenceInfoFrame1->mProcessesLB, pName);
    }
    else if(mStartBtn->Caption == "Continue")
    {
        if(mProcessSequencer.forward())
        {
	        mAB.disableJoyStickAxes();
    		mProcessSequencer.continueExecution();
    		mSequenceStatusTimer->Enabled = true;
        	string pName = mProcessSequencer.getCurrentProcessName();
            selectAndClickListBoxItem(this->TSequenceInfoFrame1->mProcessesLB, pName);
        }
        else
        {
        	//Something bad is going on
           	mProcessSequencer.stop();
			mProcessSequencer.reset();
			mSequenceStatusTimer->Enabled = true;
        }
    }
    else
    {
    	mProcessSequencer.stop();
	}
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mSaveSequenceBtnClick(TObject *Sender)
{
	saveSequence();
}

void TABProcessSequencerFrame::saveSequence()
{
    mProcessSequencer.saveCurrent();
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mSequenceTimerTimer(TObject *Sender)
{
	if(mProcessSequencer.isRunning())
    {
    	mStartBtn->Caption = "Stop";
        mStatusLbl->Caption = "Working on: " + vclstr(mProcessSequencer.getCurrentProcessName());
    }
    else
    {
		mSequenceStatusTimer->Enabled = false;
        mAB.enableJoyStickAxes();
	  	mStatusLbl->Caption = "Idle";

        if(!mContinousExecutionCB->Checked)
        {
            //We need to check if we can continue
            if(mProcessSequencer.canContinue())
            {
        		//Forward the sequence next time
	           	mStartBtn->Caption = "Continue";
            }
            else
            {
		    	mStartBtn->Caption = "Start";
            }
        }
        else
        {
	    	mStartBtn->Caption = "Start";
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mSequenceNameEKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift)
{
	if(Key == vkReturn)
    {
    	//Change name of sequence in CB
        int indx = mSequencesCB->ItemIndex;
		mSequencesCB->Items->Strings[indx] = vclstr(TSequenceInfoFrame1->mSequenceNameE->getValue());
		mSequencesCB->ItemIndex = indx;
		ProcessSequence* s = mProcessSequencer.getCurrentSequence();
        s->setProjectName(TSequenceInfoFrame1->mSequenceNameE->getValue());
        saveSequence();

        //Send a message to main ui to update sequence shortcuts
        if(sendAppMessage(abSequencerUpdate) != true)
        {
            Log(lDebug)<<"Sending sequencer update was unsuccesful";
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mRewindButtonClick(TObject *Sender)
{
	mProcessSequencer.stop();
    mProcessSequencer.reset();
	mSequenceStatusTimer->Enabled = false;
	mStartBtn->Caption = "Start";
}
