#include <vcl.h>
#pragma hdrstop
#include "TParallellProcessesFrame.h"
#include "mtkVCLUtils.h"
#include "core/atProcess.h"
#include "arraybot/apt/atMove.h"
#include "arraybot/process/atParallellProcess.h"
#include "mtkLogger.h"
#include "arraybot/atArrayBot.h"
#include "arraybot/apt/atAPTMotor.h"
#include "arraybot/apt/atAbsoluteMove.h"
#include "atVCLUtils.h"
#include "mtkMathUtils.h"
#include "arraybot/process/atTriggerFunction.h"
#include "vcl/forms/TStringInputDialog.h"
#include "arduino/atArduinoServerCommand.h"
#include "vcl/frames/TArduinoServerCommandFrame.h"
#include "vcl/forms/TYesNoForm.h"
#include "frames/TArrayCamRequestFrame.h"
#include "arraybot/process/atArrayCamRequestProcess.h"

#pragma package(smart_init)
#pragma link "TMotorMoveProcessFrame"
#pragma link "TSTDStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"

using namespace mtk;

TParallellProcessesFrame *ParallellProcessesFrame;
//---------------------------------------------------------------------------
__fastcall TParallellProcessesFrame::TParallellProcessesFrame(ProcessSequencer& ps, TComponent* Owner)
	: TFrame(Owner),
    mProcessSequencer(ps)
{
	mTMotorMoveProcessFrame 	= new TMotorMoveProcessFrame(mProcessSequencer, Owner);
    mTMotorMoveProcessFrame->Parent = this;
    mTMotorMoveProcessFrame->Visible = false;
    mTMotorMoveProcessFrame->Align 	 = alClient;

    mTArduinoServerCommandFrame = new TArduinoServerCommandFrame(mProcessSequencer.getArrayBot(), Owner);
    mTArduinoServerCommandFrame->Parent = this;
    mTArduinoServerCommandFrame->Visible = false;
    mTArduinoServerCommandFrame->Align = alClient;

    mArrayCamRequestFrame = new TArrayCamRequestFrame(mProcessSequencer, Owner);
    mArrayCamRequestFrame->Visible = false;
    mArrayCamRequestFrame->Parent = this;
    mArrayCamRequestFrame->Align = alClient;
}

__fastcall TParallellProcessesFrame::~TParallellProcessesFrame()
{
	delete mTArduinoServerCommandFrame;
    delete mTMotorMoveProcessFrame;
}

void TParallellProcessesFrame::populate(Process* pp)
{
	mSubProcessesLB->Clear();
    if(!pp)
    {
    	EnableDisableFrame(this, false);
        return;
    }

    stringstream c;
    c << "Update Final Process Positions \n";
    c << "("<<pp->getProcessName()<<")";
	mUpdateFinalPositionsA->Caption =  vclstr(c.str());

	//Populate, update frame with data from process
    mParallell = dynamic_cast<ParallellProcess*>(pp);

    //Fill out the listbox with moves
    for(int i = 0; i < mParallell->getNumberOfProcesses(); i++)
    {
    	Process* p = mParallell->getProcess(i);
        if(p)
        {
        	mSubProcessesLB->Items->AddObject(vclstr(p->getProcessName()), (TObject*) p);
        }
    }

  	EnableDisableFrame(this, true);

    if(mSubProcessesLB->Count)
    {
	    selectAndClickListBoxItem(mSubProcessesLB, 0);
    }
    else
    {
		mTMotorMoveProcessFrame->Visible = false;
        mTArduinoServerCommandFrame->Visible = false;
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

    lm->assignProcessSequence(mParallell->getProcessSequence());
    mParallell->write();

    //Add move to Listbox
    int indx = mSubProcessesLB->Items->AddObject(lm->getProcessName().c_str(), (TObject*) lm);
	mSubProcessesLB->ItemIndex = indx;

	//Select the new process
    selectItem(lm);
}

//---------------------------------------------------------------------------
void __fastcall TParallellProcessesFrame::newArrayCamRequestAExecute(TObject *Sender)
{
	//Add a move to current process
    if(!mParallell)
    {
    	Log(lError) << "This is something else...!";
        return;
    }

   	Process* p = new ArrayCamRequestProcess(mProcessSequencer.getArrayCamClient(), "ArrayCam Process");

    //Add the move to the container.. this will give the move a name
    mParallell->addProcess(p);

    p->assignProcessSequence(mParallell->getProcessSequence());
    mParallell->write();

    //Add move to Listbox
    int indx = mSubProcessesLB->Items->AddObject(p->getProcessName().c_str(), (TObject*) p);
	mSubProcessesLB->ItemIndex = indx;

	//Select the new process
    selectItem(p);
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
        mParallell->write();
		populate(mParallell);
    }
}

void TParallellProcessesFrame::selectItem(Process* p)
{
    mTMotorMoveProcessFrame->Visible = false;
   	mTArduinoServerCommandFrame->Visible = false;
    mArrayCamRequestFrame->Visible = false;

	if(dynamic_cast<AbsoluteMove*>(p))
    {
	        mTMotorMoveProcessFrame->populate(dynamic_cast<AbsoluteMove*>(p));
        mTMotorMoveProcessFrame->Visible = true;
	    EnableDisableFrame(mTMotorMoveProcessFrame, true);
    }
    else if(dynamic_cast<ArduinoServerCommand*>(p))
    {
        mTArduinoServerCommandFrame->populate(dynamic_cast<ArduinoServerCommand*>(p));
        mTArduinoServerCommandFrame->Visible = true;
        EnableDisableFrame(mTArduinoServerCommandFrame, true);
    }
    else if(dynamic_cast<ArrayCamRequestProcess*>(p) != NULL)
    {
        mArrayCamRequestFrame->populate(dynamic_cast<ArrayCamRequestProcess*>(p));
        mArrayCamRequestFrame->Visible = true;
    }
}

void __fastcall TParallellProcessesFrame::mSubProcessesLBClick(TObject *Sender)
{
	if(mSubProcessesLB->ItemIndex == -1 || mParallell == NULL)
    {
    	return;
    }

	//Get Current itemIndex, retrieve the move and populate the move frame
    Process* subProcess = (Process*) mSubProcessesLB->Items->Objects[mSubProcessesLB->ItemIndex];

    Process* p = mParallell->getProcess(subProcess);
    selectItem(p);
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
            APTMotor* mtr = mProcessSequencer.getArrayBot().getMotorWithName(am->getMotorName());
            if(mtr && isEqual(am->getPosition(), mtr->getPosition(), 1.e-4) == false)
            {
                stringstream msg;
                msg <<"Update final motor position for motor, device: "<<am->getMotorName() <<"\n("
                	<<am->getPosition()<<" -> "<< mtr->getPosition()<<")";

                TYesNoForm* f = new TYesNoForm(this);
                f->Caption = "";
                f->mInfoLabel->Caption = msg.str().c_str();
                int res = f->ShowModal();

                if(res == mrYes)
                {
                	am->setPosition(mtr->getPosition());

                    //Save updated sequence
                    mProcessSequencer.saveCurrent();
                }
                delete f;
            }
            else
            {
            	if(!mtr)
                {
            		MessageDlg("We failed to get a reference to the selected motor.\nMake sure the motor are connected!", mtError, TMsgDlgButtons() << mbOK, 0);
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
                    if(isEqual(fn->getPosition(), mtr->getPosition(), 1.e-4) == false)
                    {
                        stringstream msg;
                        msg <<
                        "Update final TRIGGERED motor position for motor: "<<mtr->getName() <<
                        "\n("<<fn->getPosition()<<" -> "<< mtr->getPosition()<<")";

                        if(MessageDlg(vclstr(msg.str()), mtConfirmation, TMsgDlgButtons() << mbYes<<mbNo, 0) == mrYes)
                        {
                            fn->setPosition(mtr->getPosition());

                            //Save updated sequence
                            mProcessSequencer.saveCurrent();
                        }
                    }
                }
            }
        }
    }

    //Update UI
	selectAndClickListBoxItem(mSubProcessesLB, 0);
}

//---------------------------------------------------------------------------
void __fastcall TParallellProcessesFrame::mRenameBtnClick(TObject *Sender)
{
	//Open string input form
	TStringInputDialog* t = new TStringInputDialog(this);

    t->Caption = "Rename Action";
	Process* p =  getCurrentlySelectedSubProcess();
    if(!p)
    {
    	return;
    }
    t->setText(p->getProcessName());

    if(t->ShowModal() == mrOk)
    {
		//Rename the currently selected sequence
    	string newName(t->getText());

		p->setProcessName(newName);
		p->write();

        int indx = mSubProcessesLB->ItemIndex;
        if(updateListBoxItemCaption(mSubProcessesLB, indx, newName) == false)
        {

        }

        if(selectAndClickListBoxItem(mSubProcessesLB, newName) == false)
        {
        	//bad..
        }
    }
    delete t;
}

Process* TParallellProcessesFrame::getCurrentlySelectedSubProcess()
{
	if(mSubProcessesLB->Count > 0 && mSubProcessesLB->ItemIndex != -1)
    {
	    Process* p = (Process*) mSubProcessesLB->Items->Objects[mSubProcessesLB->ItemIndex];
        return p;
    }
    return NULL;
}



