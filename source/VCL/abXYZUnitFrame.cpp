#include <vcl.h>
#pragma hdrstop
#include "abXYZUnitFrame.h"
#include "mtkVCLUtils.h"
#include "abAPTMotor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TSTDStringLabeledEdit"
#pragma link "abMotorFrame"
#pragma resource "*.dfm"

TXYZUnitFrame *XYZUnitFrame;

using namespace mtk;
//---------------------------------------------------------------------------
__fastcall TXYZUnitFrame::TXYZUnitFrame(TComponent* Owner)
	: TFrame(Owner),
    mUnit(NULL),
    mXMotorFrame(NULL),
    mYMotorFrame(NULL),
    mZMotorFrame(NULL)
{}

//---------------------------------------------------------------------------
void TXYZUnitFrame::assignUnit(XYZUnit* u)
{
	mUnit = u;
    mainGB->Caption = vclstr(u->getName());


	//Start motor status timer
    mMotorStatusTimer->Enabled = true;
}


//---------------------------------------------------------------------------
void __fastcall TXYZUnitFrame::mMotorStatusTimerTimer(TObject *Sender)
{
	//Check motor status
    if(mUnit)
    {
    	if(mUnit->getXMotor())
        {
        	//Check if we have created a Frame for it
            if(!mXMotorFrame)
            {
            	mXMotorFrame = new TMotorFrame(mUnit->getXMotor()->getSerial(), this);
                mXMotorFrame->SetParentComponent(ScrollBox1);
                mXMotorFrame->Align = alLeft;
                mXMotorFrame->assignMotor(mUnit->getXMotor());
            }
        }

    	if(mUnit->getYMotor())
        {
        	//Check if we have created a Frame for it
            if(!mYMotorFrame)
            {
            	mYMotorFrame = new TMotorFrame(mUnit->getYMotor()->getSerial(), this);
                mYMotorFrame->SetParentComponent(ScrollBox1);
                mYMotorFrame->Align = alLeft;
                mYMotorFrame->assignMotor(mUnit->getYMotor());
            }
        }

    	if(mUnit->getZMotor())
        {
        	//Check if we have created a Frame for it
            if(!mZMotorFrame)
            {
            	mZMotorFrame = new TMotorFrame(mUnit->getZMotor()->getSerial(), this);
                mZMotorFrame->SetParentComponent(ScrollBox1);
                mZMotorFrame->Align = alLeft;
                mZMotorFrame->assignMotor(mUnit->getZMotor());
            }
        }
    }
}


