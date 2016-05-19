#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "mtkLogger.h"
#include "abAPTMotor.h"
#include "abAddJoyStickSetting.h"
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

void __fastcall TMain::AddJsSettingBtnClick(TObject *Sender)
{
    TJoyStickSettingForm* f = new TJoyStickSettingForm(NULL);
    int mr = f->ShowModal();
    if(mr == mrOk)
    {
    	//Create a new setting
        JoyStickSetting jss(f->getSetting());
	 	JoyStickSettings& js = mAB.getJoyStickSettings();
        JoyStickSetting* jsp = js.add(jss);

	    //Update the drop down
        if(jsp)
        {
        	int index = JoyStickSettingsCB->Items->AddObject(jsp->getLabel().c_str(), (TObject*) jsp);
			JoyStickSettingsCB->ItemIndex = index;
        }
    }
    delete f;
}

//---------------------------------------------------------------------------
void __fastcall TMain::JoyStickSettingsCBChange(TObject *Sender)
{
	//Update edits
	JoyStickSetting* js = (JoyStickSetting*) JoyStickSettingsCB->Items->Objects[JoyStickSettingsCB->ItemIndex];
    if(js)
    {
		vector<double> s(js->get());
        if(s.size() == 4)
        {
			mMaxXYJogVelocityJoystick->setValue(s[0]);
			mXYJogAccelerationJoystick->setValue(s[1]);
			mMaxZJogVelocityJoystick->setValue(s[2]);
			mZJogAccelerationJoystick->setValue(s[3]);
        }
    }
}



