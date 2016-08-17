#include <vcl.h>
#pragma hdrstop
#include "TABProcessSequencerFrame.h"
#include "abXYZUnit.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "abAPTMotor.h"
#include "abCombinedMove.h"
#include "abArrayBot.h"
#include "abTimeDelay.h"
#include "abApplicationMessages.h"
#include "UIUtilities.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "TMotorMoveProcessFrame"
#pragma link "TCombinedMoveFrame"
#pragma link "TSTDStringLabeledEdit"
#pragma link "TTimeDelayFrame"
#pragma resource "*.dfm"
TABProcessSequencerFrame *ABProcessSequencerFrame;
//---------------------------------------------------------------------------

extern string gAppDataFolder;
using namespace mtk;

int selectItem(TObject* p, TListBox* lb);

int TABProcessSequencerFrame::mFrameNr = 0;
__fastcall TABProcessSequencerFrame::TABProcessSequencerFrame(ArrayBot& ab, const string& appFolder, TComponent* Owner)
	: TFrame(Owner),
    mAB(ab),
    mProcessSequencer(mAB.getProcessSequencer())
{
    TFrame::Name = vclstr("Frame_" + replaceCharacter('-', '_', "MoveSequenceFrame") + mtk::toString(++mFrameNr));

    mProcessFileExtension = "abp";
    refreshSequencesCB();
}

void TABProcessSequencerFrame::init()
{
    if(mSequencesCB->Items->Count)
    {
        mSequencesCB->ItemIndex = 0;
		mSequencesCBChange(NULL);
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
		mProcessesLB->Clear();
        if(mSequencesCB->Items->Count)
        {
  			mSequencesCB->ItemIndex = 0;
        }
    }

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
    mProcessesLB->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mSequencesCBChange(TObject *Sender)
{
	//Load the sequence
    int index = mSequencesCB->ItemIndex;
    if(index == -1)
    {
    	return;
    }

    mProcessesLB->Clear();
    string sName(stdstr(mSequencesCB->Items->Strings[index]));

    //Repopulate the listbox
	if(mProcessSequencer.selectSequence(sName))
    {
    	//Fill out listbox
		ProcessSequence* seq = mProcessSequencer.getCurrentSequence();
        if(!seq)
        {
        	return;
        }

        mSequenceNameE->setValue(seq->getName());

        Process* p = seq->getFirst();
        while(p)
        {
    		mProcessesLB->Items->AddObject(p->getProcessName().c_str(), (TObject*) p);
            p = seq->getNext();
        }

        //Select the first move in the sequence
        if(mProcessesLB->Count)
        {
	        mProcessesLB->ItemIndex = 0;
        }
        mProcessesLBClick(NULL);
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
    if(mStartBtn->Caption == "Start")
    {
    	//Save current sequence
       	saveSequence();

        mAB.disableJoyStickAxes();
    	mProcessSequencer.start(true);
		mSequenceStatusTimer->Enabled = true;
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
void __fastcall TABProcessSequencerFrame::mProcessesLBClick(TObject *Sender)
{
	//Retrieve current process and populate UI
    //Check what kind of process we have, Pause, or CombinedMove
    int i = mProcessesLB->ItemIndex;
    if(i == -1)
    {
	    TCombinedMoveFrame1->Visible = false;//(mAB, NULL);
	    TTimeDelayFrame1->Visible = false;//(mAB, NULL);
        updateSequenceArrows();
    	return;
    }

    Process* p = (Process*) mProcessesLB->Items->Objects[i];
    if(p)
    {
    	CombinedMove* cm = dynamic_cast<CombinedMove*>(p);
    	TimeDelay* td= dynamic_cast<TimeDelay*>(p);
        if(cm)
        {
            TTimeDelayFrame1->Visible = false;
    		TCombinedMoveFrame1->populate(mAB, cm);
			TCombinedMoveFrame1->Visible = true;
            TCombinedMoveFrame1->Align = alClient;
        }
        else if(td)
        {
			TCombinedMoveFrame1->Visible = false;
            TTimeDelayFrame1->populate(mAB, td);
            TTimeDelayFrame1->Visible = true;
            TTimeDelayFrame1->Align = alClient;
        }
    }

	updateSequenceArrows();
}

void TABProcessSequencerFrame::updateSequenceArrows()
{
	if(mProcessesLB->SelCount < 1 || mProcessesLB->Count <= 1)
    {
		mMoveSequenceUpBtn->Enabled = false;
		mMoveSequenceDownBtn->Enabled = false;
    	return;
    }

	//Depending which item is selected, enable/disable items

	//Last item
    if(mProcessesLB->ItemIndex > 0 && (mProcessesLB->ItemIndex + 1) == mProcessesLB->Count)
    {
		mMoveSequenceUpBtn->Enabled 	= true;
		mMoveSequenceDownBtn->Enabled 	= false;
    }
    //First item
    else if(mProcessesLB->ItemIndex == 0)
    {
		mMoveSequenceUpBtn->Enabled 	= false;
		mMoveSequenceDownBtn->Enabled 	= true;
    }
    else
    {
		mMoveSequenceUpBtn->Enabled 	= true;
		mMoveSequenceDownBtn->Enabled 	= true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::moveParEdit(TObject *Sender, WORD &Key, TShiftState Shift)
{
    saveSequence();
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::MotorsCBChange(TObject *Sender)
{
    int i = mProcessesLB->ItemIndex;
    if(i == -1)
    {
        return;
    }

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

    	mStartBtn->Caption = "Start";
	  	mStatusLbl->Caption = "Idle";
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::addCombinedMovesProcessAExecute(TObject *Sender)
{
	ProcessSequence* s = mProcessSequencer.getCurrentSequence();
	if(!s)
    {
    	Log(lError) << "Tried to add process to NULL sequence";
    	return;
    }

    int nr  = s->getNumberOfProcesses() + 1;

	//Create and add a process to the sequence
	Process *p = new CombinedMove("Process " + mtk::toString(nr));
   	s->add(p);

    //Update LB
    mProcessesLB->Items->AddObject(p->getProcessName().c_str(), (TObject*) p);
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::removeProcessAExecute(TObject *Sender)
{
	ProcessSequence* s = mProcessSequencer.getCurrentSequence();
	if(!s)
    {
    	Log(lError) << "Tried to remove process from NULL sequence";
    	return;
    }

    int i = mProcessesLB->ItemIndex;
    Process* p = (Process*) mProcessesLB->Items->Objects[i];

    s->remove(p);
    mProcessesLB->DeleteSelected();

    if(mProcessesLB->Count > -1)
    {
		mProcessesLB->ItemIndex = 0;
		mProcessesLBClick(NULL);
    }
    saveSequence();
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mSequenceNameEKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift)
{
	if(Key == vkReturn)
    {
    	//Change name of sequence in CB
        int indx = mSequencesCB->ItemIndex;
		mSequencesCB->Items->Strings[indx] = vclstr(mSequenceNameE->getValue());
		mSequencesCB->ItemIndex = indx;
		ProcessSequence* s = mProcessSequencer.getCurrentSequence();
        s->setProjectName(mSequenceNameE->getValue());
        saveSequence();
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::addTimeDelayProcessExecute(TObject *Sender)
{
	ProcessSequence* s = mProcessSequencer.getCurrentSequence();
	if(!s)
    {
    	Log(lError) << "Tried to add process to NULL sequence";
    	return;
    }

    int nr  = s->getNumberOfProcesses() + 1;

	//Create and add a process to the sequence
	Process *p = new TimeDelay("Process " + mtk::toString(nr), Poco::Timespan(1000*Poco::Timespan::MILLISECONDS));
   	s->add(p);

    //Update LB
    int indx = mProcessesLB->Items->AddObject(p->getProcessName().c_str(), (TObject*) p);
    mProcessesLB->ItemIndex = indx;
	mProcessesLBClick(NULL);


    saveSequence();
}


void __fastcall TABProcessSequencerFrame::TTimeDelayFrame1mNameEditKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift)
{
	TTimeDelayFrame1->mEditKeyDown(Sender, Key, Shift);
    if(Key == vkReturn)
    {
	    //Change name of process in CB
	    int indx = mProcessesLB->ItemIndex;
 	   	mProcessesLB->Items->Strings[indx] = vclstr(TTimeDelayFrame1->mNameEdit->getValue());
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::TCombinedMoveFrame1mProcessNameEKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift)
{
	TCombinedMoveFrame1->mProcessNameEKeyDown(Sender, Key, Shift);
    if(Key == vkReturn)
    {
	    //Change name of process in CB
	    int indx = mProcessesLB->ItemIndex;
 	   	mProcessesLB->Items->Strings[indx] = vclstr(TCombinedMoveFrame1->mProcessNameE->getValue());
    }
}


void __fastcall TABProcessSequencerFrame::mMoveSequenceDownBtnClick(TObject *Sender)
{
	//Get selected sequence
    int i = mProcessesLB->ItemIndex;
    Process* p = (Process*) mProcessesLB->Items->Objects[i];
    if(p)
    {
    	mProcessSequencer.getCurrentSequence()->moveForward(p);

        //Rebuild the Listbox
        mSequencesCBChange(Sender);

        //Select process
        int index = selectItem((TObject*) p, mProcessesLB);
    }
}

//---------------------------------------------------------------------------

void __fastcall TABProcessSequencerFrame::mMoveSequenceUpBtnClick(TObject *Sender)
{
	//Get selected sequence
    int i = mProcessesLB->ItemIndex;
    Process* p = (Process*) mProcessesLB->Items->Objects[i];
    if(p)
    {
    	mProcessSequencer.getCurrentSequence()->moveBack(p);

        //Rebuild the Listbox
        mSequencesCBChange(Sender);

        //Select process
        int index = selectItem((TObject*) p, mProcessesLB);
    }
}

//---------------------------------------------------------------------------
int selectItem(TObject* p, TListBox* lb)
{
	//find the item in the list box;
	for(int i = 0; i < lb->Count; i++)
    {
    	if(lb->Items->Objects[i] == p)
        {
        	lb->Selected[i] = true;
            lb->OnClick(NULL);
            return i;
        }
    }
    return -1;
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::TCombinedMoveFrame1Button1Click(TObject *Sender)
{
	TCombinedMoveFrame1->addMoveAExecute(Sender);
    saveSequence();
}


