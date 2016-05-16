#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
using namespace mtk;
using namespace std;

//---------------------------------------------------------------------------
void __fastcall TMain::JMXYMove(TMessage &msg)
{
	if(!mAB.getJoyStick().isEnabled())
    {
    	return;
    }

    JoyStickAxis& x = mAB.getJoyStick().getXAxis();
    JoyStickAxis& y = mAB.getJoyStick().getYAxis();

    x.Move(msg.LParamLo);
    y.Move(msg.LParamHi);
}

//---------------------------------------------------------------------------
void __fastcall TMain::JMZMove(TMessage &msg)
{
	if(!mAB.getJoyStick().isEnabled())
    {
    	return;
    }

//	double fullVelRange = 5.0;
//    int nrOfSteps = 5;
//	double step = fullVelRange / nrOfSteps;
//
//	double scalingFactor = fullVelRange/ 65535.0;
//	double pos = (msg.LParamLo * scalingFactor - fullVelRange/2.0) * 2.0;
//
//    mRunningZAverage = (mAlpha * pos) + (1.0 - mAlpha) * mRunningZAverage;
//
//    JoystickZPosition->Caption 	= "Z Position = " + FloatToStrF(pos, ffFixed, 4,2);
//    JoystickAvgZPos->Caption 	= "Z Average Position = " + FloatToStrF(mRunningZAverage, ffFixed, 4,2);

//    mAB.getJoyStick().getZAxis().Move(msg);
}

void __fastcall TMain::JMButtonUpUpdate(TMessage &msg)
{
    if(msg.WParam & JOY_BUTTON3CHG)
    {
    	mAB.getJoyStick().getButton(3).up();
    }

    if(msg.WParam & JOY_BUTTON4CHG)
    {
    	mAB.getJoyStick().getButton(4).up();
    }
}

void __fastcall TMain::JMButtonDownUpdate(TMessage &msg)
{
    if(msg.WParam & JOY_BUTTON3CHG)
    {
    	mAB.getJoyStick().getButton(3).down();
    }

    if(msg.WParam & JOY_BUTTON4CHG)
    {
    	mAB.getJoyStick().getButton(4).down();
    }
}

