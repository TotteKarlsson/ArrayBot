#include <vcl.h>
#pragma hdrstop
#include "THomeMotorProcessFrame.h"
#include "TPositionalTriggerFrame.h"
#include "arraybot/apt/atMove.h"
#include "arraybot/apt/atAPTMotor.h"
#include "dslVCLUtils.h"
#include "arraybot/atXYZUnit.h"
#include "arraybot/atArrayBot.h"
#include "arraybot/apt/atAbsoluteMove.h"
#include "arraybot/process/atTriggerFunction.h"
#include "vcl/forms/TTextInputDialog.h"
#include "arraybot/apt/atHomeMotor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
THomeMotorProcessFrame *HomeMotorProcessFrame;

static int frameNr = 1;
//---------------------------------------------------------------------------
__fastcall THomeMotorProcessFrame::THomeMotorProcessFrame(ProcessSequencer& ps, TComponent* Owner)
	: TFrame(Owner),
    mProcessSequencer(ps),
    mAB(ps.getArrayBot())
{
    this->Name = this->Name + IntToStr(frameNr++);
}

void THomeMotorProcessFrame::update()
{
	rePopulate(mHomeMotorProcess);
}

void THomeMotorProcessFrame::populate(HomeMotor* m)
{
    MotorsCB->Clear();
	populateMotorCB();
    rePopulate(m);
}

void THomeMotorProcessFrame::rePopulate(HomeMotor* m)
{
	if(!m)
    {
    	return;
    }

    mHomeMotorProcess = m;
    mActionInfo->Caption = vclstr(mHomeMotorProcess->getInfoText());

    APTMotor* mtr = dynamic_cast<APTMotor*>(mHomeMotorProcess->getUnit());
    if(!mtr)
    {
    	//Look for motor
        string unitLbl = mHomeMotorProcess->getMotorName();
		int idx = MotorsCB->Items->IndexOf(unitLbl.c_str());
        if(idx != -1)
        {
        	//Found it, assign it
        	mHomeMotorProcess->assignUnit( (APTMotor*) MotorsCB->Items->Objects[idx] );
			MotorsCB->ItemIndex = idx;
        }
    }
    else
    {
    	int idx = MotorsCB->Items->IndexOf(mtr->getName().c_str());
		MotorsCB->ItemIndex = idx;
    }
}

//Motor objects are stored in the checkbox list property
void THomeMotorProcessFrame::populateMotorCB()
{
	vector<APTMotor*> motors = mAB.getAllMotors();
    for(int i = 0; i < motors.size(); i++)
    {
    	if(motors[i])
        {
			MotorsCB->Items->InsertObject(MotorsCB->Items->Count, motors[i]->getName().c_str(), (TObject*) motors[i]);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall THomeMotorProcessFrame::MotorsCBChange(TObject *Sender)
{
	//Check if a motor is selected
    ATObject* obj = (ATObject*) MotorsCB->Items->Objects[MotorsCB->ItemIndex];
    APTMotor* motor = dynamic_cast<APTMotor*>(obj);

    if(motor && mHomeMotorProcess)
    {
        mHomeMotorProcess->assignUnit(motor);
    }
    else
    {
    }

	mProcessSequencer.saveCurrent();
}

//---------------------------------------------------------------------------
void __fastcall THomeMotorProcessFrame::mActionInfoClick(TObject *Sender)
{
    if(!mHomeMotorProcess)
    {
    	return;
    }

	//Open text edit form
	TTextInputDialog* t = new TTextInputDialog(this);

    t->Caption = "Update Action Information";
	Process* p =  mHomeMotorProcess;

    t->setText(mHomeMotorProcess->getInfoText());

    if(t->ShowModal() == mrOk)
    {
		//Rename the currently selected sequence
    	string newText(t->getText());
		mHomeMotorProcess->setInfoText(newText);
		mHomeMotorProcess->write();
        mActionInfo->Caption = vclstr(newText);
    }
    delete t;
}


