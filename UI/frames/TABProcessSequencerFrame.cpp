#include <vcl.h>
#pragma hdrstop
#include "TABProcessSequencerFrame.h"
#include "abXYZUnit.h"
#include "mtkLogger.h"
#include "mtkVCLUtils.h"
#include "abAPTMotor.h"
#include "abCombinedMove.h"
#include "abArrayBot.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "TMotorMoveProcessFrame"
#pragma link "TCombinedMoveFrame"
#pragma link "mtkSTDStringEdit"
#pragma resource "*.dfm"
TABProcessSequencerFrame *ABProcessSequencerFrame;
//---------------------------------------------------------------------------

extern string gAppDataFolder;
using namespace mtk;

int TABProcessSequencerFrame::mFrameNr = 0;
__fastcall TABProcessSequencerFrame::TABProcessSequencerFrame(ArrayBot& ab, const string& appFolder, TComponent* Owner)
	: TFrame(Owner),
    mAB(ab),
	mCoverSlipUnit(mAB.getCoverSlipUnit()),
	mWhiskerUnit(mAB.getWhiskerUnit()),
    mProcessSequencer(ab, appFolder)
{
    TFrame::Name = vclstr("Frame_" + replaceCharacter('-', '_', "MoveSequenceFrame") + mtk::toString(++mFrameNr));

    GroupBox1->Caption = "ArrayBot Process Sequencer";
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
		mSequencesCB->DeleteSelected();
		mProcessesLB->Clear();
        removeFile(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "ArrayBot", seqName + "." + mProcessFileExtension));
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
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::refreshSequencesCB()
{
    mSequencesCB->Clear();
    mProcessSequencer.loadAll(gAppDataFolder);
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

	if(mProcessSequencer.selectSequence(sName))
    {
    	//Fill out listbox
		ProcessSequence* seq = mProcessSequencer.getCurrentSequence();
        if(!seq)
        {
        	return;
        }

        mSequenceNameE->SetString(seq->getName());

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
        mWhiskerUnit.disableJSAxes();
        mCoverSlipUnit.disableJSAxes();

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
    int i = mProcessesLB->ItemIndex;
    if(i == -1)
    {
	    TCombinedMoveFrame1->populate(mAB, NULL);
    	return;
    }

    Process* p = (Process*) mProcessesLB->Items->Objects[i];
    if(p)
    {
    	TCombinedMoveFrame1->populate(mAB, p);
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
        mWhiskerUnit.enableJSAxes();
        mCoverSlipUnit.enableJSAxes();

    	mStartBtn->Caption = "Start";
	  	mStatusLbl->Caption = "Idle";
    }
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::addProcessAExecute(TObject *Sender)
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
}

//---------------------------------------------------------------------------
void __fastcall TABProcessSequencerFrame::mSequenceNameEKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift)
{
	if(Key == vkReturn)
    {
    	//Change name of sequence in CB
        int indx = mSequencesCB->ItemIndex;
		mSequencesCB->Items->Strings[indx] = vclstr(mSequenceNameE->GetString());
		mSequencesCB->ItemIndex = indx;
		ProcessSequence* s = mProcessSequencer.getCurrentSequence();
        s->setProjectName(mSequenceNameE->GetString());
        saveSequence();
    }
}
