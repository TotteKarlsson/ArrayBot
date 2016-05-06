#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
using namespace mtk;
using namespace std;

bool sameSign(double x, double y)
{
	return x*y >= 0.0f;
}

//---------------------------------------------------------------------------
void __fastcall TMain::JMXYMove(TMessage &msg)
{
	if(!mJoyStick.isEnabled())
    {
    	return;
    }

    JoyStickAxis& x = mJoyStick.getXAxis();
    JoyStickAxis& y = mJoyStick.getYAxis();

    x.Move(msg.LParamLo);
    y.Move(msg.LParamHi);

    JoystickXPosition->Caption 		= "X = " + FloatToStrF(x.getCurrentVelocity(), ffFixed, 4,2);
    JoystickYPosition->Caption 		= "Y = " + FloatToStrF(y.getCurrentVelocity(), ffFixed, 4,2);
}

//---------------------------------------------------------------------------
void __fastcall TMain::JMZMove(TMessage &msg)
{
	if(!mJoyStick.isEnabled())
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

//    mJoyStick.getZAxis().Move(msg);
}

void __fastcall TMain::JMButtonUpUpdate(TMessage &msg)
{
    // Windows us both sends both JM_BUTTONDOWN an
    // JM_BUTTONUP messages. Both trigger this function
    // This event only happens when a button changes state/
    // you can find out which button was toggled by anding
    // with JOY_BUTTONXCHG where X is the button number
    JoystickButton1->Caption = (msg.WParam & JOY_BUTTON1) ?
    "Button 1 = Pressed" : "Button 1 = Not Pressed";

    JoystickButton2->Caption = (msg.WParam & JOY_BUTTON2) ?
    "Button 2 = Pressed" : "Button 2 = Not Pressed";

    JoystickButton3->Caption = (msg.WParam & JOY_BUTTON3) ?
    "Button 3 = Pressed" : "Button 3 = Not Pressed";

    JoystickButton4->Caption = (msg.WParam & JOY_BUTTON4) ?
    "Button 4 = Pressed" : "Button 4 = Not Pressed";


    if(msg.WParam & JOY_BUTTON3CHG)
    {
    	mJoyStick.getButton(3).up();
    }

    if(msg.WParam & JOY_BUTTON4CHG)
    {
    	mJoyStick.getButton(4).up();
    }
}

void __fastcall TMain::JMButtonDownUpdate(TMessage &msg)
{
    // Windows us both sends both JM_BUTTONDOWN an
    // JM_BUTTONUP messages. Both trigger this function
    // This event only happens when a button changes state/
    // you can find out which button was toggled by anding
    // with JOY_BUTTONXCHG where X is the button number
    JoystickButton1->Caption = (msg.WParam & JOY_BUTTON1) ?
    "Button 1 = Pressed" : "Button 1 = Not Pressed";

    JoystickButton2->Caption = (msg.WParam & JOY_BUTTON2) ?
    "Button 2 = Pressed" : "Button 2 = Not Pressed";

    JoystickButton3->Caption = (msg.WParam & JOY_BUTTON3) ?
    "Button 3 = Pressed" : "Button 3 = Not Pressed";

    JoystickButton4->Caption = (msg.WParam & JOY_BUTTON4) ?
    "Button 4 = Pressed" : "Button 4 = Not Pressed";


    if(msg.WParam & JOY_BUTTON3CHG)
    {
    	mJoyStick.getButton(3).down();
    }

    if(msg.WParam & JOY_BUTTON4CHG)
    {
    	mJoyStick.getButton(4).down();
    }
}

