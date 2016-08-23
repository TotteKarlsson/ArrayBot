#include <vcl.h>
#pragma hdrstop
#include "TSequenceInfoFrame.h"
#include "abProcess.h"
#include "abParallellProcess.h"
#include "abProcessSequence.h"
#include "mtkVCLUtils.h"

#include "abTimeDelay.h"
#include "frames/TMotorMoveProcessFrame.h"
#include "frames/TParallellProcessesFrame.h"
#include "frames/TTimeDelayFrame.h"
#include "abVCLUtils.h"
#include "mtkLogger.h"

using namespace mtk;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TSequenceInfoFrame *SequenceInfoFrame;
//---------------------------------------------------------------------------
__fastcall TSequenceInfoFrame::TSequenceInfoFrame(TComponent* Owner)
	: TFrame(Owner),
    mSequence(NULL),
    mAB(NULL)
{
	mCombinedMoveFrame = new TParallellProcessesFrame(Owner);
    mCombinedMoveFrame->Visible = false;
}

void TSequenceInfoFrame::assignArrayBot(ArrayBot* ab)
{
	mAB = ab;
}

//---------------------------------------------------------------------------
bool TSequenceInfoFrame::populate(ProcessSequence* seq, TPanel* processPanel)
{
	if(!seq)
    {
		empty();
        return false;
    }

    if(processPanel)
    {
    	mProcessPanel = processPanel;
		mCombinedMoveFrame->Parent 	= mProcessPanel;
    }

    mProcessesLB->Clear();
	mSequence = seq;
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

    EnableDisableFrame(this, true);
    mProcessesLBClick(NULL);
	updateSequenceArrows();
    return true;
}

//---------------------------------------------------------------------------
void __fastcall TSequenceInfoFrame::mMoveSequenceUpBtnClick(TObject *Sender)
{
	//Get selected sequence
    int i = mProcessesLB->ItemIndex;
    Process* p = (Process*) mProcessesLB->Items->Objects[i];
    if(p && mSequence)
    {
		mSequence->moveBack(p);
		mSequence->write();
        //Rebuild the Listbox
		populate(mSequence);

        //Select process
        selectAndClickListBoxItem((TObject*) p, mProcessesLB);
    }
}

//---------------------------------------------------------------------------
void __fastcall TSequenceInfoFrame::mMoveSequenceDownBtnClick(TObject *Sender)
{
	//Get selected sequence
    int i = mProcessesLB->ItemIndex;
    Process* p = (Process*) mProcessesLB->Items->Objects[i];
    if(p && mSequence)
    {
    	mSequence->moveForward(p);
		mSequence->write();

        //Rebuild the Listbox
		populate(mSequence);

        //Select process
        selectAndClickListBoxItem((TObject*) p, mProcessesLB);
    }
}

//---------------------------------------------------------------------------
void __fastcall TSequenceInfoFrame::RemoveProcessAExecute(TObject *Sender)
{
	if(!mSequence)
    {
    	Log(lError) << "Tried to remove process from NULL sequence";
    	return;
    }

    int i = mProcessesLB->ItemIndex;
    Process* p = (Process*) mProcessesLB->Items->Objects[i];

    mSequence->remove(p);
    mProcessesLB->DeleteSelected();

    if(mProcessesLB->Count > -1)
    {
		mProcessesLB->ItemIndex = 0;
		mProcessesLBClick(NULL);
    }

    mSequence->write();
}

Process* TSequenceInfoFrame::getCurrentlySelectedProcess()
{
	if(mProcessesLB->Count > 0)
    {
	    Process* p = (Process*) mProcessesLB->Items->Objects[mProcessesLB->ItemIndex];
        return p;
    }
    return NULL;
}

void __fastcall TSequenceInfoFrame::mProcessesLBClick(TObject *Sender)
{
	if(mProcessesLB->Count == 0)
    {
    	disableEnableButtons(false);
    }

	if(mProcessesLB->Count == 1)
    {
	   	disableEnableButtons(false);
		mDeleteMoveBtn->Enabled = true;
    }
	updateSequenceArrows();

    //Check what kind of process we have, Pause, or CombinedMove
    Process* p = getCurrentlySelectedProcess();
    if(p)
    {
    	ParallellProcess* cm = dynamic_cast<ParallellProcess*>(p);
//    	TimeDelay* td= dynamic_cast<TimeDelay*>(p);
        if(cm)
        {
//            mTimeDelayFrame->Visible = false;
            if(mAB)
    		{
            	mCombinedMoveFrame->populate(*mAB, cm);
            }
			mCombinedMoveFrame->Visible = true;
            mCombinedMoveFrame->Align = alClient;
        }
//        else if(td)
//        {
//			mCombinedMoveFrame->Visible = false;
//            if(mAB)
//    		{
//	            mTimeDelayFrame->populate(*mAB, td);
//            }
//
//            mTimeDelayFrame->Visible = true;
//            mTimeDelayFrame->Align = alClient;
//        }
    }
    else
    {
//        mTimeDelayFrame->Visible = false;
		mCombinedMoveFrame->Visible = false;
    }
}

void TSequenceInfoFrame::disableEnableButtons(bool enabled)
{
	mMoveSequenceUpBtn->Enabled = enabled;
	mMoveSequenceDownBtn->Enabled = enabled;
	mDeleteMoveBtn->Enabled = enabled;
}
//---------------------------------------------------------------------------
void __fastcall TSequenceInfoFrame::empty()
{
	mSequenceNameE->Text = "<none>";
	mProcessesLB->Clear();
    EnableDisableFrame(this, false);
}

void __fastcall TSequenceInfoFrame::AddCombinedMoveAExecute(TObject *Sender)
{
	if(!mSequence)
    {
    	Log(lError) << "Tried to add process to NULL sequence";
    	return;
    }

    int nr  = mSequence->getNumberOfProcesses() + 1;

	//Create and add a process to the sequence
	Process *p = new ParallellProcess("Process " + mtk::toString(nr));
   	mSequence->add(p);
    mSequence->write();

    //Update LB
    mProcessesLB->Items->AddObject(p->getProcessName().c_str(), (TObject*) p);
	selectAndClickListBoxItem((TObject*) p, mProcessesLB);
}

////---------------------------------------------------------------------------
//void __fastcall TSequenceInfoFrame::AddTimeDelayProcessAExecute(TObject *Sender)
//{
////	if(!mSequence)
////    {
////    	Log(lError) << "Tried to add process to NULL sequence";
////    	return;
////    }
////
////    int nr  = mSequence->getNumberOfProcesses() + 1;
////
////	//Create and add a process to the sequence
////	Process *p = new TimeDelay("Process " + mtk::toString(nr), Poco::Timespan(1000*Poco::Timespan::MILLISECONDS));
////   	mSequence->add(p);
////    mSequence->write();
////
////    //Update LB
////    int indx = mProcessesLB->Items->AddObject(p->getProcessName().c_str(), (TObject*) p);
////	selectAndClickListBoxItem((TObject*) p, mProcessesLB);
//}

void TSequenceInfoFrame::updateSequenceArrows()
{
	if(mProcessesLB->Count <= 1)
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

////---------------------------------------------------------------------------
//void __fastcall TSequenceInfoFrame::SequenceNameEKeyDown(TObject *Sender, WORD &Key,
//          TShiftState Shift)
//{
//	//Update any info..
//	if(Key == vkReturn && mSequence != NULL)
//    {
//    	//Change name of sequence in CB
//        mSequence->setProjectName(mSequenceNameE->getValue());
//        mSequence->write();
//    }
//}
//
////---------------------------------------------------------------------------
//void __fastcall TSequenceInfoFrame::mSequenceNameEKeyPress(TObject *Sender, System::WideChar &Key)
//{
//	//Update any info..
//	if(Key == vkReturn && mSequence != NULL)
//    {
//    	//Change name of sequence in CB
//        mSequence->setProjectName(mSequenceNameE->getValue());
//        mSequence->write();
//    }
//}
//

