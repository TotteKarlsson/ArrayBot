#include <vcl.h>
#pragma hdrstop
#include "TSequenceInfoFrame.h"
#include "arraybot/process/atParallelProcess.h"
#include "arraybot/process/atProcessSequence.h"
#include "arraybot/apt/atAbsoluteMove.h"
#include "dslVCLUtils.h"
#include "vcl/forms/TStringInputDialog.h"
#include "arraybot/process/atTimeDelay.h"
#include "arraybot/process/atArrayCamRequestProcess.h"
#include "arraybot/process/atStopAndResumeProcess.h"
#include "arraybot/process/atMoveCoverSlipAtAngleProcess.h"
#include "arraybot/apt/atHomeMotor.h"
#include "TMotorMoveProcessFrame.h"
#include "TParallelProcessesFrame.h"
#include "TTimeDelayFrame.h"
#include "TArrayCamRequestFrame.h"
#include "TStopAndResumeFrame.h"
#include "TMoveCoverSlipAtAngleProcessFrame.h"
#include "THomeMotorProcessFrame.h"
#include "atVCLUtils.h"
#include "dslLogger.h"
#include "vcl/forms/TSelectProcessTypeDialog.h"
#include "arraybot/apt/atAPTMotor.h"
#include "vcl/forms/TYesNoForm.h"
#include "arraybot/process/atTriggerFunction.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TSequenceInfoFrame *SequenceInfoFrame;
bool updateCurrentProcessState(Process* p, ArrayBot& ab);

using namespace dsl;
using namespace at;
//---------------------------------------------------------------------------
__fastcall TSequenceInfoFrame::TSequenceInfoFrame(ProcessSequencer& ps, TComponent* Owner)
    : TFrame(Owner),
    mSequence(NULL),
    mProcessSequencer(ps)
{
    //Create frames
    mParallelProcessesFrame             = new TParallelProcessesFrame(ps, Owner);
    mTimeDelayFrame                     = new TTimeDelayFrame(Owner);
    mArrayCamRequestFrame               = new TArrayCamRequestFrame(ps, Owner);
    mMotorMoveProcessFrame              = new TMotorMoveProcessFrame(ps, Owner);
    mStopAndResumeFrame                 = new TStopAndResumeFrame(Owner);
    mMoveCoverSlipAtAngleProcessFrame   = new TMoveCoverSlipAtAngleProcessFrame(ps, Owner);
    mHomeMotorProcessFrame              = new THomeMotorProcessFrame(ps, Owner);

    mFrames.push_back(mParallelProcessesFrame);
    mFrames.push_back(mTimeDelayFrame);
    mFrames.push_back(mArrayCamRequestFrame);
    mFrames.push_back(mMotorMoveProcessFrame);
    mFrames.push_back(mStopAndResumeFrame);
    mFrames.push_back(mMoveCoverSlipAtAngleProcessFrame);
    mFrames.push_back(mHomeMotorProcessFrame);

    setFramesVisibility(false);
}

__fastcall  TSequenceInfoFrame::~TSequenceInfoFrame()
{
    mFrames.clear();
    delete mHomeMotorProcessFrame;
    delete mMoveCoverSlipAtAngleProcessFrame;
    delete mStopAndResumeFrame;
    delete mMotorMoveProcessFrame;
    delete mArrayCamRequestFrame;
    delete mTimeDelayFrame;
    delete mParallelProcessesFrame;
}
//---------------------------------------------------------------------------
bool TSequenceInfoFrame::populate(ProcessSequence* seq, TScrollBox* processPanel)
{
    if(!seq)
    {
        empty();
        return false;
    }

    if(processPanel)
    {
        mProcessPanel = processPanel;
        setFramesParent(mProcessPanel);
    }

    ProcessesLB->Clear();
    mSequence = seq;

    Process* p = seq->getFirst();
    while(p)
    {
        ProcessesLB->Items->AddObject(p->getProcessName().c_str(), (TObject*) p);
        p = seq->getNext();
    }

    //Select the first move in the sequence
    if(ProcessesLB->Count)
    {
        ProcessesLB->ItemIndex = 0;
    }

    //Setup the category
    selectItem(CategoryCB, mSequence->getCategory(), true);

    EnableDisableFrame(this, true);
    ProcessesLBClick(NULL);
    updateSequenceArrows();
    return true;
}

//---------------------------------------------------------------------------
void __fastcall TSequenceInfoFrame::mMoveSequenceUpBtnClick(TObject *Sender)
{
    //Get selected sequence
    int i = ProcessesLB->ItemIndex;
    Process* p = (Process*) ProcessesLB->Items->Objects[i];
    if(p && mSequence)
    {
        mSequence->moveBack(p);
        mSequence->write();
        //Rebuild the Listbox
        populate(mSequence);

        //Select process
        selectAndClickListBoxItem(ProcessesLB, (TObject*) p);
    }
}

//---------------------------------------------------------------------------
void __fastcall TSequenceInfoFrame::mMoveSequenceDownBtnClick(TObject *Sender)
{
    //Get selected sequence
    int i = ProcessesLB->ItemIndex;
    Process* p = (Process*) ProcessesLB->Items->Objects[i];
    if(p && mSequence)
    {
        mSequence->moveForward(p);
        mSequence->write();

        //Rebuild the Listbox
        populate(mSequence);

        //Select process
        selectAndClickListBoxItem(ProcessesLB, (TObject*) p);
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

    int i = ProcessesLB->ItemIndex;
    Process* p = (Process*) ProcessesLB->Items->Objects[i];

    mSequence->remove(p);
    ProcessesLB->DeleteSelected();

    if(ProcessesLB->Count > -1)
    {
        ProcessesLB->ItemIndex = 0;
        ProcessesLBClick(NULL);
    }

    mSequence->write();
}

Process* TSequenceInfoFrame::getCurrentlySelectedProcess()
{
    if(ProcessesLB->Count > 0)
    {
        Process* p = (Process*) ProcessesLB->Items->Objects[ProcessesLB->ItemIndex];
        return p;
    }
    return NULL;
}

void __fastcall TSequenceInfoFrame::ProcessesLBClick(TObject *Sender)
{
    if(ProcessesLB->Count == 0)
    {
        disableEnableButtons(false);
    }

    if(ProcessesLB->Count == 1)
    {
        disableEnableButtons(false);
        mDeleteMoveBtn->Enabled = true;
    }

    updateSequenceArrows();

    //Available processtype frames
    setFramesVisibility(false);

    //This button only makes sense for certain actions
    UpdateStateBtn->Visible      = false;

    //Check what kind of process we have
    Process* p = getCurrentlySelectedProcess();
    ProcessType type = p != NULL ? p->getProcessType() : ptUnknown;

    switch(type)
    {
        case ptParallel:
        {
            ParallelProcess* pp = dynamic_cast<ParallelProcess*>(p);
            mParallelProcessesFrame->populate(pp);
            mParallelProcessesFrame->mSubProcessesLB->ItemIndex = 0;
            mParallelProcessesFrame->mSubProcessesLB->OnClick(NULL);
            UpdateStateBtn->Enabled         = true;
            UpdateStateBtn->Visible         = true;
            mParallelProcessesFrame->Visible    = true;
            mParallelProcessesFrame->Align = alClient;
        }
        break;

        case ptMoveCoverSlipAtAngle:
        {
            MoveCoverSlipAtAngleProcess* pp = dynamic_cast<MoveCoverSlipAtAngleProcess*>(p);
            mMoveCoverSlipAtAngleProcessFrame->populate(pp);

            mMoveCoverSlipAtAngleProcessFrame->Visible = true;
            mMoveCoverSlipAtAngleProcessFrame->Align = alClient;
        }
        break;

        case ptTimeDelay:
        {
            TimeDelay* tdp = dynamic_cast<TimeDelay*>(p);
            mTimeDelayFrame->populate(tdp);

            mTimeDelayFrame->Visible = true;
            mTimeDelayFrame->Align = alClient;
        }
        break;

        case ptArrayCamRequest:
        {
            ArrayCamRequestProcess* tdp = dynamic_cast<ArrayCamRequestProcess*>(p);
            mArrayCamRequestFrame->populate(tdp);
            mArrayCamRequestFrame->Visible = true;
            mArrayCamRequestFrame->Align = alClient;
        }
        break;

        case ptAbsoluteMove:
        {
            AbsoluteMove* am = dynamic_cast<AbsoluteMove*>(p);
            mMotorMoveProcessFrame->populate(am);
            mMotorMoveProcessFrame->Visible = true;
            mMotorMoveProcessFrame->Align = alClient;
            UpdateStateBtn->Enabled = true;
            UpdateStateBtn->Enabled = true;
            UpdateStateBtn->Visible = true;
        }
        break;

        case ptStopAndResume:
        {
            StopAndResumeProcess* am = dynamic_cast<StopAndResumeProcess*>(p);
            mStopAndResumeFrame->populate(am);
            mStopAndResumeFrame->Visible = true;
            mStopAndResumeFrame->Align = alClient;
        }
        break;

        case ptHomeMotor:
        {
            HomeMotor* hm = dynamic_cast<HomeMotor*>(p);
            mHomeMotorProcessFrame->populate(hm);
            mHomeMotorProcessFrame->Visible = true;
            mHomeMotorProcessFrame->Align = alClient;
        }
        break;

        default:
        {
            setFramesVisibility(false);
            UpdateStateBtn->Enabled         = false;
            UpdateStateBtn->Visible         = false;
        }
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
    ProcessesLB->Clear();
    EnableDisableFrame(this, false);
}

void __fastcall TSequenceInfoFrame::AddCombinedMoveAExecute(TObject *Sender)
{
    if(!mSequence)
    {
        Log(lError) << "Tried to add process to NULL sequence";
        return;
    }

    //Ask the user for type of process/event to create
    TSelectProcessTypeDialog* pTypeForm = new TSelectProcessTypeDialog(this);

    int mr = pTypeForm->ShowModal();

    if(mr == mrOk)
    {
        Process *p = NULL;
        int nr  = mSequence->getNumberOfProcesses() + 1;

        //get process type
        int pType = pTypeForm->mProcTypeRG->ItemIndex;
        if(pType == 0) //Parallel process
        {
            //Create and add a process to the sequence
            p = new ParallelProcess("Process " + dsl::toString(nr));
        }
        else if(pType == 1) //Time delay
        {
            p = new TimeDelay("Process " + dsl::toString(nr));
        }
        else if(pType == 2) //Stop and Resume process
        {
            p = new StopAndResumeProcess("Process " + dsl::toString(nr));
        }
        else if(pType == 3) //Arraycam Request
        {
            p = new ArrayCamRequestProcess(mProcessSequencer.getArrayCamClient(), "Process " + dsl::toString(nr));
        }

        else if(pType == 4) //Absolute move
        {
            p = new AbsoluteMove("Process " + dsl::toString(nr));
        }
        else if(pType == 5) //Move at angle
        {
            p = new MoveCoverSlipAtAngleProcess("Process " + dsl::toString(nr));
        }

        else if(pType == 6) //Home motor
        {
            p = new HomeMotor("Process " + dsl::toString(nr));
        }
        else
        {
            Log(lError) << "Process Type Selection is not Suported!";
            return;
        }

        mSequence->add(p);
        mSequence->write();

        //Update LB
        ProcessesLB->Items->AddObject(p->getProcessName().c_str(), (TObject*) p);
        selectAndClickListBoxItem(ProcessesLB, (TObject*) p);
   }
}

void TSequenceInfoFrame::updateSequenceArrows()
{
    if(ProcessesLB->Count <= 1)
    {
        mMoveSequenceUpBtn->Enabled = false;
        mMoveSequenceDownBtn->Enabled = false;
        return;
    }

    //Depending which item is selected, enable/disable items

    //Last item
    if(ProcessesLB->ItemIndex > 0 && (ProcessesLB->ItemIndex + 1) == ProcessesLB->Count)
    {
        mMoveSequenceUpBtn->Enabled     = true;
        mMoveSequenceDownBtn->Enabled   = false;
    }
    //First item
    else if(ProcessesLB->ItemIndex == 0)
    {
        mMoveSequenceUpBtn->Enabled     = false;
        mMoveSequenceDownBtn->Enabled   = true;
    }
    else
    {
        mMoveSequenceUpBtn->Enabled     = true;
        mMoveSequenceDownBtn->Enabled   = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TSequenceInfoFrame::UpdateStateBtnClick(TObject *Sender)
{
    //Check what current process is, AbsoluteMove or a Parallell process?
    Process* p = getCurrentlySelectedProcess();
    if(!p)
    {
        return;
    }

    updateCurrentProcessState(p, mProcessSequencer.getArrayBot());

    if(dynamic_cast<ParallelProcess*>(p))
    {
        //Update UI
        selectAndClickListBoxItem(mParallelProcessesFrame->mSubProcessesLB, 0);
    }
    else if(dynamic_cast<AbsoluteMove*>(p))
    {
        mMotorMoveProcessFrame->update();
    }
    else if(dynamic_cast<ArrayCamRequestProcess*>(p))
    {


    }
    //Save updated sequence
    mProcessSequencer.saveCurrent();
}

bool updateCurrentProcessState(Process* p, ArrayBot& ab)
{
    //Check what current process is, AbsoluteMove or a Parallell process?
    if(!p)
    {
        return false;
    }

    if(dynamic_cast<ParallelProcess*>(p))
    {
        ParallelProcess* pp = dynamic_cast<ParallelProcess*>(p);

        for(int i = 0; i < pp->getNumberOfProcesses(); i++)
        {
            Process* p = pp->getProcess(i);
            if(!p)
            {
                continue;
            }

            //Check if the process is a move process, and if so check if we can
            //update its final position
            AbsoluteMove* am = dynamic_cast<AbsoluteMove*>(p);
            if(am)
            {
                updateCurrentProcessState(am, ab);
            }
        }
    }
    else if(dynamic_cast<AbsoluteMove*>(p))
    {
        AbsoluteMove* am = dynamic_cast<AbsoluteMove*>(p);
        APTMotor* mtr = ab.getMotorWithName(am->getMotorName());

        if(!mtr)
        {
            MessageDlg("We failed to get a reference to the selected motor.\nMake sure the motor is connected!", mtError, TMsgDlgButtons() << mbOK, 0);
            return false;
        }

        if(isEqual(am->getPosition(), mtr->getPosition(), 1.e-4) == false)
        {
            stringstream msg;
            msg <<"Update final motor position for motor, device: "<<am->getMotorName() <<"\n("
                <<am->getPosition()<<" -> "<< mtr->getPosition()<<")";

            TYesNoForm* f = new TYesNoForm(NULL);
            f->Caption = "";
            f->mInfoLabel->Caption = msg.str().c_str();
            int res = f->ShowModal();

            if(res == mrYes)
            {
                am->setPosition(mtr->getPosition());
            }
            delete f;
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
                    }
                }
            }
        }
    }
    else if(dynamic_cast<ArrayCamRequestProcess*>(p))
    {
        //Get focus and zoom from ArrayCam
        ArrayCamRequestProcess* acp = dynamic_cast<ArrayCamRequestProcess*>(p);
        if(acp->getRequest() == acrSetZoomAndFocus)
        {
            //Get current zoom and focus
        }
    }


    return true;
}


//---------------------------------------------------------------------------
void __fastcall TSequenceInfoFrame::mRenameBtnClick(TObject *Sender)
{
    //Open string input form
    TStringInputDialog* t = new TStringInputDialog(this);
    t->Caption = "Rename Process";

    Process* p = getCurrentlySelectedProcess();
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
        mSequence->write();

        //Change name of sequence in ListBox
        int indx = ProcessesLB->ItemIndex;
        if(updateListBoxItemCaption(ProcessesLB, indx, newName) == false)
        {

        }

        if(selectAndClickListBoxItem(ProcessesLB, newName) == false)
        {
            //bad..
            Log(lError) << "Failed to select item: "<<newName;
        }
    }
    delete t;
}

//---------------------------------------------------------------------------
void __fastcall TSequenceInfoFrame::CategoryCBCloseUp(TObject *Sender)
{
    //Change category for the current session
    if(!mSequence)
    {
        Log(lError) << "Tried to change category for NULL sequence";
        return;
    }

    string category = getSelectedItem(CategoryCB);
    mSequence->setCategory(category);
    mSequence->write();
}


void __fastcall TSequenceInfoFrame::NewSequenceCategoryBtnClick(TObject *Sender)
{
    //Change category for the current session
    if(!mSequence)
    {
        Log(lError) << "Tried to change category for NULL sequence";
        return;
    }

    //Open string input form
    TStringInputDialog* t = new TStringInputDialog(this);
    t->Caption = "Add Process Category";

    string currentCategory(mSequence->getCategory());
    t->setText(currentCategory);

    if(t->ShowModal() == mrOk)
    {
        //Rename the currently selected sequence
        string newCategory(t->getText());

        if(newCategory != currentCategory)
        {
            mSequence->setCategory(newCategory);
            mSequence->write();
            CategoryCB->AddItem(vclstr(newCategory), NULL);

            if(selectAndClickComboBoxItem(CategoryCB, newCategory) == false)
            {
                //bad..
                Log(lError) << "Failed to select item: "<<newCategory;
            }
        }
    }
    delete t;
}

//---------------------------------------------------------------------------
void __fastcall TSequenceInfoFrame::LogXML1Click(TObject *Sender)
{
    //Log the process sequence XML.
    //Change category for the current session
    if(!mSequence)
    {
        Log(lError) << "Tried to change category for NULL sequence";
        return;
    }

    StringList s(mSequence->getXML(), '\n');

    //Reverse list
    s.reverse();

    for(int i = 0; i < s.count(); i++)
    {
        Log(lInfo) << s[i];
    }
}

void TSequenceInfoFrame::setFramesVisibility(bool visible)
{
    for(int i = 0; i < mFrames.size(); i++)
    {
        mFrames[i]->Visible = visible;
    }
}

void TSequenceInfoFrame::setFramesParent(TScrollBox* parent)
{
    for(int i = 0; i < mFrames.size(); i++)
    {
        mFrames[i]->Parent = parent;
    }
}
