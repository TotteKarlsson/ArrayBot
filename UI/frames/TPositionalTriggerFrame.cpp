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

    //Setup the position
    mPositionE->setValue(mMove->getTrigger().getPosition());

    //Setup the logical operator
    mOpRG->ItemIndex = (int) mMove->getTrigger().getTestOperator();

    //Setup the object to be triggered
    mDevicesCB->Clear();
	populateDevicesCB();

//    //Select the one that is to be triggered
//    int indexOf = mDevicesCB->Items->IndexOf(vclstr(mMove->getTrigger().getObjectToTriggerName()));
//    if(indexOf != -1)
//    {
//		mDevicesCB->ItemIndex = indexOf;
//    }
}

void TPositionalTriggerFrame::populateDevicesCB()
{
	mDevicesCB->Clear();
    APTMotor* mtr = dynamic_cast<APTMotor*>(mMove->getUnit());
    if(!mtr)
    {
    	return;
    }

    vector<APTMotor*> motors = mAB->getAllMotors();
    for(int i = 0; i < motors.size(); i++)
    {
        if(motors[i] && (motors[i]->getName() != mtr->getName()))
        {
        	mDevicesCB->Items->InsertObject(mDevicesCB->Items->Count, motors[i]->getName().c_str(), (TObject*) motors[i]);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TPositionalTriggerFrame::mPositionEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkReturn && mMove)
    {
	    mMove->getTrigger().setPosition(mPositionE->getValue());
    }
}

//---------------------------------------------------------------------------
void __fastcall TPositionalTriggerFrame::mOpRGClick(TObject *Sender)
{
	//Capture state
	if(mMove)
    {
    	LogicOperator lo = toLogicOperator(stdstr(mOpRG->Items->Strings[mOpRG->ItemIndex]));
	    mMove->getTrigger().setTestOperator(lo);
    }
}

//---------------------------------------------------------------------------
void __fastcall TPositionalTriggerFrame::mDevicesCBChange(TObject *Sender)
{
	//Capture device
    if(mDevicesCB->ItemIndex == -1)
    {
    	return;
    }

//	if(mMove)
//    {
//		mMove->getTrigger().setObjectToTriggerName( stdstr(mDevicesCB->Items->Strings[mDevicesCB->ItemIndex]));
//    }
}


