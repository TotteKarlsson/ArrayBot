#include <vcl.h>
#pragma hdrstop
#include "abXYZUnitFrame.h"
#include "abXYZUnit.h"
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
    mZMotorFrame(NULL),
    mAngleMotorFrame(NULL)
{}

//---------------------------------------------------------------------------
void TXYZUnitFrame::assignUnit(XYZUnit* u)
{
	mUnit = u;
    mainGB->Caption = vclstr(u->getName());

	//Start motor status timer
    if(mUnit)
    {
    	if(mUnit->getAngleMotor())
        {
        	//Check if we have created a Frame for it
            if(!mAngleMotorFrame)
            {
            	mAngleMotorFrame = new TMotorFrame(mUnit->getAngleMotor()->getSerial(), this);
                mAngleMotorFrame->SetParentComponent(ScrollBox1);
                mAngleMotorFrame->Align = alLeft;
                mAngleMotorFrame->assignMotor(mUnit->getAngleMotor());
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

    }
}

void TXYZUnitFrame::disable()
{
	if(mXMotorFrame)
    {
    	mXMotorFrame->mMotorStatusTimer->Enabled = false;
    }

	if(mYMotorFrame)
    {
    	mYMotorFrame->mMotorStatusTimer->Enabled = false;
    }

	if(mZMotorFrame)
    {
    	mZMotorFrame->mMotorStatusTimer->Enabled = false;
    }

	if(mAngleMotorFrame)
    {
    	mAngleMotorFrame->mMotorStatusTimer->Enabled = false;
    }

}

