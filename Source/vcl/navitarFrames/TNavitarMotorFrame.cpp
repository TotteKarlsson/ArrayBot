#include <vcl.h>
#pragma hdrstop
#include "TNavitarMotorFrame.h"
#include "navitar/atNavitarMotor.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTIntLabel"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTIntLabel"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TNavitarMotorFrame *NavitarMotorFrame;

using namespace dsl;
using namespace at;
//---------------------------------------------------------------------------
__fastcall TNavitarMotorFrame::TNavitarMotorFrame(TComponent* Owner)
	: TFrame(Owner),
    mMotor(NULL)
{
    enableDisableGroupBox(MotorGB, false);
}

//---------------------------------------------------------------------------
void TNavitarMotorFrame::populate(NavitarMotor& m)
{
	mMotor = &m;
	MotorGB->Caption = vclstr(mMotor->getLabel());
    enableDisableGroupBox(MotorGB, true);
    MotorPositionTimer->Enabled = true;

    //Read motors max position
    MaxPosLabel->setValue(mMotor->getMaxPosition());
    PositionTB->Max = MaxPosLabel->getValue();
}

//---------------------------------------------------------------------------
void TNavitarMotorFrame::dePopulate()
{
    MotorPositionTimer->Enabled = true;
	mMotor = NULL;
	MotorGB->Caption = "<none>";
    enableDisableGroupBox(MotorGB, false);
}

void __fastcall TNavitarMotorFrame::FrameBtnClick(TObject *Sender)
{
	if(!mMotor)
    {
    	Log(lError) << "Motor is NULL in ButtonClick";
        return;
    }

	TButton* b = dynamic_cast<TButton*>(Sender);

    if (b == HomeBtn)
    {
    	Log(lError) << "Driving motor " <<mMotor->getLabel()<<" to Home";
    	mMotor->home();
    }
    else if (b == LimitBtn)
    {
    	Log(lInfo) << "Driving motor " <<mMotor->getLabel()<<" to Limit";
    	mMotor->limit();
    }
}

//---------------------------------------------------------------------------
void __fastcall TNavitarMotorFrame::MotorPositionTimerTimer(TObject *Sender)
{
    if(!mMotor)
    {
		MotorPosition->setValue(-1);
        return;
    }
	int pos = mMotor->getPosition();

    if(!MotorPosition->Focused())
    {
		MotorPosition->setValue(pos);
    }
    PositionTB->Position = pos;
}

//---------------------------------------------------------------------------
void __fastcall TNavitarMotorFrame::MotorPositionKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
    if(Key == VK_RETURN)
    {
		Log(lInfo) << "Setting new position to: "<<MotorPosition->getValue();
	    mMotor->setPosition(MotorPosition->getValue());
    }
}


