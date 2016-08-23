#include <vcl.h>
#pragma hdrstop
#include "TParallellProcessesFrame.h"
#include "mtkVCLUtils.h"
#include "abProcess.h"
#include "abMove.h"
#include "abParallellProcess.h"
#include "mtkLogger.h"
#include "abArrayBot.h"
#include "abAPTMotor.h"
#include "abAbsoluteMove.h"

#pragma package(smart_init)
#pragma link "TMotorMoveProcessFrame"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"

using namespace mtk;

TParallellProcessesFrame *ParallellProcessesFrame;
//---------------------------------------------------------------------------
__fastcall TParallellProcessesFrame::TParallellProcessesFrame(TComponent* Owner)
	: TFrame(Owner)
{
}

void TParallellProcessesFrame::populate(ArrayBot& ab, Process* p)
{
	mAB = &ab;
	rePopulate(p);
}

void TParallellProcessesFrame::rePopulate(Process* p)
{
	mMoveLB->Clear();

	//Populate, update frame with data from process
    mParallell = dynamic_cast<ParallellProcess*>(p);
    if(!p)
    {
    	EnableDisableFrame(this, false);
        return;
    }

	mProcessNameE->setValue(mParallell->getProcessName());
    //Fill out the listbox with moves
    for(int i = 0; i < mParallell->getNumberOfProcesses(); i++)
    {
    	Process* mv = mParallell->getProcess(i);
        if(mv)
        {
        	mMoveLB->Items->Add(vclstr(mv->getProcessName()));
        }
    }

  	EnableDisableFrame(this, true);
   	EnableDisableFrame(this->TMotorMoveProcessFrame1, false);
}

void __fastcall TParallellProcessesFrame::addMoveAExecute(TObject *Sender)
{
	//Add a move to current process
    if(!mParallell)
    {
    	Log(lError) << "This is something else...!";
        return;
    }

    Process* lm = new AbsoluteMove("");

    //Add the move to the container.. this will give the move a name
    mParallell->addProcess(lm);

    //Add move to Listbox
    int indx = mMoveLB->Items->Add(lm->getProcessName().c_str());
	mMoveLB->ItemIndex = indx;

	//Select the new process
    selectItem(lm);
}

//---------------------------------------------------------------------------
void __fastcall TParallellProcessesFrame::removeMoveAExecute(TObject *Sender)
{
	//Get selected move
    int index = mMoveLB->ItemIndex;
    if(index != -1)
    {
    	string moveName = stdstr(mMoveLB->Items->Strings[index]);
        mParallell->removeProcess(moveName);
		rePopulate(mParallell);
    }
}

void TParallellProcessesFrame::selectItem(Process* mv)
{
	if(dynamic_cast<AbsoluteMove*>(mv))
    {
        this->TMotorMoveProcessFrame1->populate(mAB, dynamic_cast<AbsoluteMove*>(mv));
        EnableDisableFrame(this->TMotorMoveProcessFrame1, true);
    }
}

void __fastcall TParallellProcessesFrame::mMoveLBClick(TObject *Sender)
{
	if(mMoveLB->ItemIndex == -1 || mParallell == NULL)
    {
    	return;
    }

	//Get Current itemIndex, retrieve the move and populate the move frame
	string moveName = stdstr(mMoveLB->Items->Strings[mMoveLB->ItemIndex]);
    Process* mv = mParallell->getProcess(moveName);

    selectItem(mv);
}


//---------------------------------------------------------------------------
void __fastcall TParallellProcessesFrame::mProcessNameEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkReturn && mParallell != NULL)
    {
   		mParallell->setProcessName(mProcessNameE->getValue());
    }
}


