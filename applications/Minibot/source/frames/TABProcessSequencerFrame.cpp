#include <vcl.h>
#pragma hdrstop
#include "TABProcessSequencerFrame.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "arraybot/apt/atAPTMotor.h"
#include "arraybot/process/atParallelProcess.h"
#include "arraybot/atArrayBot.h"
#include "arraybot/process/atTimeDelay.h"
#include "UIUtilities.h"
#include "atVCLUtils.h"
#include "forms\TStringInputDialog.h"
#include "TEditSequenceForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "TMotorMoveProcessFrame"
#pragma link "TParallelProcessesFrame"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "TTimeDelayFrame"
#pragma link "TSequenceInfoFrame"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TABProcessSequencerFrame *ABProcessSequencerFrame;
//---------------------------------------------------------------------------

using namespace dsl;
int TABProcessSequencerFrame::mFrameNr = 0;

//---------------------------------------------------------------------------
__fastcall TABProcessSequencerFrame::TABProcessSequencerFrame(ProcessSequencer& ps, const string& appFolder, TComponent* Owner)
	: TFrame(Owner),
    mProcessSequencer(ps),
    mAB(ps.getArrayBot()),
    mAppDataFolder(appFolder)
{
    TFrame::Name = vclstr("Frame_" + replaceCharacter('-', '_', "MoveSequenceFrame") + dsl::toString(++mFrameNr));
    mProcessFileExtension = "abp";
	TSequenceInfoFrame1 = new TSequenceInfoFrame(ps, this);
	TSequenceInfoFrame1->Parent = mLeftPanel;
	TSequenceInfoFrame1->Align = alClient;
    refreshSequencesCB();
}

__fastcall TABProcessSequencerFrame::~TABProcessSequencerFrame()
{
	delete TSequenceInfoFrame1;
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
    }
}

void __fastcall TABProcessSequencerFrame::mDeleteSequenceBtnClick(TObject *Sender)
{
	//Check selected sequence and delete it
    int idx = mSequencesCB->ItemIndex;
    if(idx > -1)
    {
    	string seqName = stdstr(mSequencesCB->Items->Strings[idx]);
        if(MessageDlg("Are you sure you want to delete the sequence: " + String(seqName.c_str()), mtWarning, TMsgDlgButtons() << mbYes<<mbCancel, 0) == mrYes)
        {
            mProcessSequencer.deleteSequence(seqName);
            mSequencesCB->DeleteSelected();
            mSequencesCB->Update();
            if(mSequencesCB->Items->Count)
            {
                mSequencesCB->ItemIndex = 0;
            }
        }
    }

	mSequencesCBChange(Sender);

    //Send a message to main ui to update sequence shortcuts
    if(sendAppMessage(abSequencerUpdate) != true)
    {
        Log(lDebug)<<"Sending sequencer update to UI was unsuccesful";
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mAddSeqBtnClick(TObject *Sender)
{
    //Save current sequence, if any
    mProcessSequencer.saveCurrent();
	ProcessSequence* s = new ProcessSequence(mAB, mProcessSequencer.getArrayCamClient());

    mProcessSequencer.addSequence(s);

	mSequencesCB->Items->Add(vclstr(s->getName()));
	mSequencesCB->ItemIndex = mSequencesCB->Items->IndexOf(vclstr(s->getName()));
	mSequencesCBChange(NULL);

    //Send a message to main ui to update sequence shortcuts
    if(sendAppMessage(abSequencerUpdate) != true)
    {
        Log(lDebug)<<"Sending sequencer update to UI was unsuccesful";
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::refreshSequencesCB()
{
    mSequencesCB->Clear();
    mProcessSequencer.loadAll(joinPath(mAppDataFolder, "sequences"));
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

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::StartBtnClick(TObject *Sender)
{
    if(mStartBtn->Caption == "Start" )
    {
    	//Save current sequence
       	saveSequence();
        mAB.disableJoyStickAxes();
    	mProcessSequencer.start(!mSteppedExecutionCB->Checked);

		mSequenceStatusTimer->Enabled = true;
        string pName = mProcessSequencer.getCurrentProcessName();
        selectAndClickListBoxItem(this->TSequenceInfoFrame1->ProcessesLB, pName);
    }
	else if(startsWith("Resume", stdstr(mStartBtn->Caption)))
    {
        if(mProcessSequencer.resume())
        {
	        mAB.disableJoyStickAxes();
    		mProcessSequencer.continueExecution();
    		mSequenceStatusTimer->Enabled = true;
        	string pName = mProcessSequencer.getCurrentProcessName();
            selectAndClickListBoxItem(this->TSequenceInfoFrame1->ProcessesLB, pName);
        }
        else
        {
        	//Something bad is going on
           	mProcessSequencer.stop();
			mProcessSequencer.reset();
			mSequenceStatusTimer->Enabled = true;
        }
    }
    else if(startsWith("Continue", stdstr(mStartBtn->Caption)))
    {
        if(mProcessSequencer.forward())
        {
	        mAB.disableJoyStickAxes();
    		mProcessSequencer.continueExecution();
    		mSequenceStatusTimer->Enabled = true;
        	string pName = mProcessSequencer.getCurrentProcessName();
            selectAndClickListBoxItem(this->TSequenceInfoFrame1->ProcessesLB, pName);
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

//---------------------------------------------------------------------------
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
    else if(mProcessSequencer.isPaused())
    {
		mStartBtn->Caption = "Resume";
    }
    else
    {
		mSequenceStatusTimer->Enabled = false;
        mAB.enableJoyStickAxes();
	  	mStatusLbl->Caption = "Idle";

        if(mSteppedExecutionCB->Checked)
        {
            //We need to check if we can continue
            if(mProcessSequencer.canContinue())
            {
                stringstream str;
	            str << "\n(" << mProcessSequencer.getNextProcessName() << ")";

        		//Forward the sequence next time
	           	mStartBtn->Caption = "Continue" + vclstr(str.str());

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
void __fastcall TABProcessSequencerFrame::mRewindButtonClick(TObject *Sender)
{
	mProcessSequencer.stop();
    mProcessSequencer.reset();
	mSequenceStatusTimer->Enabled = false;
	mStartBtn->Caption = "Start";
}

//---------------------------------------------------------------------------
string TABProcessSequencerFrame::getCurrentlySelectedSequenceName()
{
	int indx = mSequencesCB->ItemIndex;
    if(indx > -1)
    {
    	return stdstr(mSequencesCB->Items->Strings[indx]);
    }
    else
    {
    	return gNoneString;
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::EditBtnClick(TObject *Sender)
{
	//Open string input form
	//TStringInputDialog* t = new TStringInputDialog(this);
	auto_ptr<TEditSequenceForm> f = auto_ptr<TEditSequenceForm>(new TEditSequenceForm(this));
    f->Caption = "Edit Sequence";

	ProcessSequence* s = mProcessSequencer.getCurrentSequence();
    if(!s)
    {
    	return;
    }

	f->SequenceNameE->setValue(s->getName());
	f->SequenceOrderE->setValue(s->getOrder());
	f->UseProcessControllerCB->Checked = s->getUseProcessController();


    if(f->ShowModal() == mrOk)
    {
		//Rename the currently selected sequence
    	string 	newName(f->SequenceNameE->getValue());
    	int 	newOrder(f->SequenceOrderE->getValue());
        bool	newuseProcessController(f->UseProcessControllerCB->Checked);

        s->setProjectName(newName);
        s->setOrder(newOrder);
        s->setUseProcessController(newuseProcessController);
        saveSequence();

    	//Change name of sequence in CB
        int indx = mSequencesCB->ItemIndex;
        if(updateComboBoxItemCaption(mSequencesCB, indx, newName) == false)
        {
        	//bad..
        }

        mSequencesCB->ItemIndex = selectAndClickComboBoxItem(mSequencesCB, newName);

        //Send a message to main ui to update sequence shortcuts
        if(sendAppMessage(abSequencerUpdate) != true)
        {
            Log(lDebug)<<"Sending sequencer update was unsuccesful";
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::BtnClick(TObject *Sender)
{
	int idx = mSequencesCB->ItemIndex;
    if(mSequencesCB->ItemIndex == -1)
    {
    	return;
    }

  	string seqName = stdstr(mSequencesCB->Items->Strings[idx]);
    mProcessSequencer.saveCurrent();
}


