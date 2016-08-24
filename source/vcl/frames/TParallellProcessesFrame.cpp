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
#include "abVCLUtils.h"
#include "mtkMathUtils.h"
#include "abTriggerFunction.h"
#pragma package(smart_init)
#pragma link "TMotorMoveProcessFrame"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"

using namespace mtk;

TParallellProcessesFrame *ParallellProcessesFrame;
//---------------------------------------------------------------------------
__fastcall TParallellProcessesFrame::TParallellProcessesFrame(TComponent* Owner)
	: TFrame(Owner)
{}

void TParallellProcessesFrame::populate(ArrayBot& ab, Process* p)
{
	mAB = &ab;
	rePopulate(p);
}

void TParallellProcessesFrame::rePopulate(Process* pp)
{
	mSubProcessesLB->Clear();
    if(!pp)
    {
    	EnableDisableFrame(this, false);
        return;
    }

	//Populate, update frame with data from process
    mParallell = dynamic_cast<ParallellProcess*>(pp);

	mProcessNameE->setValue(mParallell->getProcessName());

    //Fill out the listbox with moves
    for(int i = 0; i < mParallell->getNumberOfProcesses(); i++)
    {
    	Process* p = mParallell->getProcess(i);
        if(p)
        {
        	mSubProcessesLB->Items->Add(vclstr(p->getProcessName()));
        }
    }

  	EnableDisableFrame(this, true);

    if(mSubProcessesLB->Count)
    {
	    selectAndClickListBoxItem(mSubProcessesLB, 0);
   		EnableDisableFrame(this->TMotorMoveProcessFrame1, true);
    }
    else
    {
		this->TMotorMoveProcessFrame1->Visible = false;
    }
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
    int indx = mSubProcessesLB->Items->Add(lm->getProcessName().c_str());
	mSubProcessesLB->ItemIndex = indx;

	//Select the new process
    selectItem(lm);
}

//---------------------------------------------------------------------------
void __fastcall TParallellProcessesFrame::removeMoveAExecute(TObject *Sender)
{
	//Get selected move
    int index = mSubProcessesLB->ItemIndex;
    if(index != -1)
    {
    	string moveName = stdstr(mSubProcessesLB->Items->Strings[index]);
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

void __fastcall TParallellProcessesFrame::mSubProcessesLBClick(TObject *Sender)
{
	if(mSubProcessesLB->ItemIndex == -1 || mParallell == NULL)
    {
    	return;
    }

	//Get Current itemIndex, retrieve the move and populate the move frame
	string moveName = stdstr(mSubProcessesLB->Items->Strings[mSubProcessesLB->ItemIndex]);
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

//---------------------------------------------------------------------------
void __fastcall TParallellProcessesFrame::mUpdateFinalPositionsAExecute(TObject *Sender)
{
	//Populate, update frame with data from process
    if(!mParallell)
    {
    	return;
    }

    if(mParallell->getNumberOfProcesses() == 0)
    {
    	MessageDlg("There are no moves to update", mtInformation, TMsgDlgButtons() << mbOK, 0);
    }

    //Fill out the listbox with moves
    for(int i = 0; i < mParallell->getNumberOfProcesses(); i++)
    {
    	Process* p = mParallell->getProcess(i);
        if(!p)
        {
        	continue;
        }

        //Check if the process is a move process, and if so check if we can
        //update its final position
        AbsoluteMove* am = dynamic_cast<AbsoluteMove*>(p);
        if(am)
        {
            APTMotor* mtr = mAB->getMotorWithName(am->getMotorName());
            if(mtr && isEqual(am->getPosition(), mtr->getPosition(), 1.e-4) == false)
            {
                stringstream msg;
                msg <<
                "Update final motor position for motor: "<<am->getMotorName() <<
                "\n("<<am->getPosition()<<" -> "<< mtr->getPosition()<<")";

                if(MessageDlg(vclstr(msg.str()), mtConfirmation, TMsgDlgButtons() << mbYes<<mbNo, 0) == mrYes)
                {
                	am->setPosition(mtr->getPosition());

                    //Save updated sequence
                    mAB->getProcessSequencer().saveCurrent();

                }
            }

            //Check if this move has a trigger
            PositionalTrigger* pt = dynamic_cast<PositionalTrigger*>(am->getTrigger());
            if(pt)
            {
            	//Get the trigger function
                MoveAbsolute *fn = dynamic_cast<MoveAbsolute*>(pt->getTriggerFunction());
            	APTMotor* mtr = dynamic_cast<APTMotor*>(pt->getSubject());
                if(mtr && fn)
                {
                    if(mtr && isEqual(fn->getPosition(), mtr->getPosition(), 1.e-4) == false)
                    {
                        stringstream msg;
                        msg <<
                        "Update final TRIGGERED motor position for motor: "<<mtr->getName() <<
                        "\n("<<fn->getPosition()<<" -> "<< mtr->getPosition()<<")";

                        if(MessageDlg(vclstr(msg.str()), mtConfirmation, TMsgDlgButtons() << mbYes<<mbNo, 0) == mrYes)
                        {
                            fn->setPosition(mtr->getPosition());

                            //Save updated sequence
                            mAB->getProcessSequencer().saveCurrent();
                        }
                    }
                }
            }
        }
    }

    //Update UI
	selectAndClickListBoxItem(mSubProcessesLB, 0);
}


