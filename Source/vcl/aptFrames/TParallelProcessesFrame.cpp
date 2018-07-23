#include <vcl.h>
#pragma hdrstop
#include "TParallelProcessesFrame.h"
#include "dslVCLUtils.h"
#include "core/atProcess.h"
#include "arraybot/apt/atMove.h"
#include "arraybot/process/atParallelProcess.h"
#include "arraybot/process/atMoveCoverSlipAtAngleProcess.h"
#include "dslLogger.h"
#include "arraybot/atArrayBot.h"
#include "arraybot/apt/atAPTMotor.h"
#include "arraybot/apt/atAbsoluteMove.h"
#include "atVCLUtils.h"
#include "dslMathUtils.h"
#include "arraybot/process/atTriggerFunction.h"
#include "vcl/forms/TStringInputDialog.h"
#include "arduino/atArduinoServerCommand.h"
#include "vcl/frames/TArduinoServerCommandFrame.h"
#include "TMotorMoveProcessFrame.h"
#include "THomeMotorProcessFrame.h"
#include "vcl/forms/TYesNoForm.h"
#include "TArrayCamRequestFrame.h"
#include "arraybot/process/atArrayCamRequestProcess.h"
#include "arraybot/apt/atHomeMotor.h"
#include "vcl/forms/TSelectProcessTypeDialog.h"
#include "TMoveCoverSlipAtAngleProcessFrame.h"
#pragma package(smart_init)
#pragma link "TMotorMoveProcessFrame"

#pragma link "dslTSTDStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"

using namespace dsl;
using namespace at;
TParallelProcessesFrame *ParallelProcessesFrame;
//---------------------------------------------------------------------------
__fastcall TParallelProcessesFrame::TParallelProcessesFrame(ProcessSequencer& ps, TComponent* Owner)
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

	mTHomeMotorProcessFrame = new THomeMotorProcessFrame(mProcessSequencer, Owner);
    mTHomeMotorProcessFrame->Visible = false;
    mTHomeMotorProcessFrame->Parent = this;
    mTHomeMotorProcessFrame->Align = alClient;

    mMoveCoverSlipAtAngleProcessFrame  	= new TMoveCoverSlipAtAngleProcessFrame(mProcessSequencer, Owner);
    mMoveCoverSlipAtAngleProcessFrame->Visible = false;
    mMoveCoverSlipAtAngleProcessFrame->Parent = this;
    mMoveCoverSlipAtAngleProcessFrame->Align = alClient;
}

__fastcall TParallelProcessesFrame::~TParallelProcessesFrame()
{
	delete mTArduinoServerCommandFrame;
    delete mTMotorMoveProcessFrame;
    delete mArrayCamRequestFrame;
    delete mTHomeMotorProcessFrame;
}

void TParallelProcessesFrame::populate(Process* pp)
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

	//Populate, update frame with data from process
    mParallel = dynamic_cast<ParallelProcess*>(pp);

    //Fill out the listbox with moves
    for(int i = 0; i < mParallel->getNumberOfProcesses(); i++)
    {
    	Process* p = mParallel->getProcess(i);
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

void __fastcall TParallelProcessesFrame::addMoveAExecute(TObject *Sender)
{
	//Add a move to current process
    if(!mParallel)
    {
    	Log(lError) << "This is something else...!";
        return;
    }

    Process* lm = new AbsoluteMove("");

    //Add the move to the container.. this will give the move a name
    mParallel->addProcess(lm);

    lm->assignProcessSequence(mParallel->getProcessSequence());
    mParallel->write();

    //Add move to Listbox
    int indx = mSubProcessesLB->Items->AddObject(lm->getProcessName().c_str(), (TObject*) lm);
	mSubProcessesLB->ItemIndex = indx;

	//Select the new process
    selectItem(lm);
}

//---------------------------------------------------------------------------
void __fastcall TParallelProcessesFrame::addProcess(TObject *Sender)
{
	if(!mParallel)
    {
    	Log(lError) << "Tried to add process to NULL sequence";
    	return;
    }

    //Ask the user for type of process/event to create
   	TSelectProcessTypeDialog* pTypeForm = new TSelectProcessTypeDialog(this);

    //We will need to disable some items on this form
	pTypeForm->setOpenedForParallelProcess();
   	int mr = pTypeForm->ShowModal();

   	if(mr != mrOk)
	{
    	return;
    }

    Process *p = NULL;

    //get process type
    int pType = pTypeForm->mProcTypeRG->ItemIndex;

    if(pType == 3) //Arraycam Request
    {
    	p = new ArrayCamRequestProcess(mProcessSequencer.getArrayCamClient(), "ArrayCam Process");
    }

    else if(pType == 4) //Absolute move
    {
        p = new AbsoluteMove("");
    }
    else if(pType == 5) //Move at angle
    {
        p = new MoveCoverSlipAtAngleProcess("");
    }

    else if(pType == 6) //Home motor
    {
        p = new HomeMotor("");
    }
    else
    {
        Log(lError) << "Process Type Selection is not Suported!";
        return;
    }

    //Add the move to the container.. this will give the move a name
    mParallel->addProcess(p);

    p->assignProcessSequence(mParallel->getProcessSequence());
    mParallel->write();

    //Add process to Listbox
    int indx = mSubProcessesLB->Items->AddObject(p->getProcessName().c_str(), (TObject*) p);
    mSubProcessesLB->ItemIndex = indx;

    //Select the new process
    selectItem(p);
}


//---------------------------------------------------------------------------
void __fastcall TParallelProcessesFrame::HomeMotorAExecute(TObject *Sender)
{
	//Add a move to current process
    if(!mParallel)
    {
    	Log(lError) << "This is something else...!";
        return;
    }

    Process* hm = new HomeMotor("");

    //Add the move to the container.. this will give the move a name
    mParallel->addProcess(hm);

    hm->assignProcessSequence(mParallel->getProcessSequence());
    mParallel->write();

    //Add process to Listbox
    int indx = mSubProcessesLB->Items->AddObject(hm->getProcessName().c_str(), (TObject*) hm);
	mSubProcessesLB->ItemIndex = indx;

	//Select the new process
    selectItem(hm);
}

//---------------------------------------------------------------------------
void __fastcall TParallelProcessesFrame::newArrayCamRequestAExecute(TObject *Sender)
{
	//Add a move to current process
    if(!mParallel)
    {
    	Log(lError) << "This is something else...!";
        return;
    }

   	Process* p = new ArrayCamRequestProcess(mProcessSequencer.getArrayCamClient(), "ArrayCam Process");

    //Add the move to the container.. this will give the move a name
    mParallel->addProcess(p);

    p->assignProcessSequence(mParallel->getProcessSequence());
    mParallel->write();

    //Add move to Listbox
    int indx = mSubProcessesLB->Items->AddObject(p->getProcessName().c_str(), (TObject*) p);
	mSubProcessesLB->ItemIndex = indx;

	//Select the new process
    selectItem(p);
}

//---------------------------------------------------------------------------
void __fastcall TParallelProcessesFrame::removeMoveAExecute(TObject *Sender)
{
	//Get selected move
    int index = mSubProcessesLB->ItemIndex;
    if(index != -1)
    {
    	string moveName = stdstr(mSubProcessesLB->Items->Strings[index]);
        mParallel->removeProcess(moveName);
        mParallel->write();
		populate(mParallel);
    }
}

void TParallelProcessesFrame::selectItem(Process* p)
{
    mTMotorMoveProcessFrame->Visible = false;
   	mTArduinoServerCommandFrame->Visible = false;
    mArrayCamRequestFrame->Visible = false;
	mTHomeMotorProcessFrame->Visible = false;
    mMoveCoverSlipAtAngleProcessFrame->Visible = false;
	if(dynamic_cast<AbsoluteMove*>(p))
    {
    	mTMotorMoveProcessFrame->populate(dynamic_cast<AbsoluteMove*>(p));
        mTMotorMoveProcessFrame->Visible = true;
	    EnableDisableFrame(mTMotorMoveProcessFrame, true);
    }
	else if(dynamic_cast<HomeMotor*>(p))
    {
    	mTHomeMotorProcessFrame->populate(dynamic_cast<HomeMotor*>(p));
        mTHomeMotorProcessFrame->Visible = true;
	    EnableDisableFrame(mTHomeMotorProcessFrame, true);
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
    else if(dynamic_cast<MoveCoverSlipAtAngleProcess*>(p) != NULL)
    {
        mMoveCoverSlipAtAngleProcessFrame->populate(dynamic_cast<MoveCoverSlipAtAngleProcess*>(p));
        mMoveCoverSlipAtAngleProcessFrame->Visible = true;
    }

}

void __fastcall TParallelProcessesFrame::SubProcessesLBClick(TObject *Sender)
{
	if(mSubProcessesLB->ItemIndex == -1 || mParallel == NULL)
    {
    	return;
    }

	//Get Current itemIndex, retrieve the move and populate the move frame
    Process* subProcess = (Process*) mSubProcessesLB->Items->Objects[mSubProcessesLB->ItemIndex];

    Process* p = mParallel->getProcess(subProcess);
    selectItem(p);
}

//---------------------------------------------------------------------------
void __fastcall TParallelProcessesFrame::mRenameBtnClick(TObject *Sender)
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

Process* TParallelProcessesFrame::getCurrentlySelectedSubProcess()
{
	if(mSubProcessesLB->Count > 0 && mSubProcessesLB->ItemIndex != -1)
    {
	    Process* p = (Process*) mSubProcessesLB->Items->Objects[mSubProcessesLB->ItemIndex];
        return p;
    }
    return NULL;
}
