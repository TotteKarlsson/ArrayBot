#include <vcl.h>
#pragma hdrstop
#include "TPositionalTriggerFrame.h"
#include "abMove.h"
#include "abAPTMotor.h"
#include "abArrayBot.h"
#include "mtkVCLUtils.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma resource "*.dfm"

TPositionalTriggerFrame *PositionalTriggerFrame;

//---------------------------------------------------------------------------
__fastcall TPositionalTriggerFrame::TPositionalTriggerFrame(TComponent* Owner)
	: TFrame(Owner)
{
}


void TPositionalTriggerFrame::populate(ArrayBot& ab, ab::Move* m)
{
	mAB = &ab;
    rePopulate(m);
}

void TPositionalTriggerFrame::rePopulate(ab::Move* m)
{
	if(!m)
    {
    	return;
    }

    mMove = m;

    APTMotor* mtr = dynamic_cast<APTMotor*>(mMove->getUnit());
    if(mtr)
    {
    	MainGB->Caption = "Trigger for: " + vclstr(mtr->getName());
    }

    mDevicesCB->Clear();
	populateDevicesCB();
}

void TPositionalTriggerFrame::populateDevicesCB()
{
	mDevicesCB->Clear();
    APTMotor* mtr = dynamic_cast<APTMotor*>(mMove->getUnit());
    if(mtr)
    {
        vector<APTMotor*> motors = mAB->getAllMotors();
        for(int i = 0; i < motors.size(); i++)
        {
            if(motors[i])
            {
                //Don't insert the device that is being monitored
                if(motors[i]->getName() != mtr->getName())
                {
                	mDevicesCB->Items->InsertObject(mDevicesCB->Items->Count, motors[i]->getName().c_str(), (TObject*) motors[i]);
                }
            }
        }
    }
}



