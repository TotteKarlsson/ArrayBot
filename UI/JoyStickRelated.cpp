#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "mtkLogger.h"
#include "abAddJoyStickSettingForm.h"
using namespace mtk;
using namespace std;

void __fastcall TMain::AddJsSettingBtnClick(TObject *Sender)
{
    TAddJoyStickSettingForm* f = new TAddJoyStickSettingForm(NULL);
    int mr = f->ShowModal();
    if(mr == mrOk)
    {
    	//Create a new setting
        JoyStickSetting jss(f->getSetting());
	 	JoyStickSettings& js = mAB->getJoyStickSettings();
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
        if(s.size() == 6)
        {
			mMaxXYJogVelocityJoystick->setValue(s[0]);
			mXYJogAccelerationJoystick->setValue(s[1]);
			mMaxZJogVelocityJoystick->setValue(s[2]);
			mZJogAccelerationJoystick->setValue(s[3]);
			mAngleControlVelE->setValue(s[4]);
			mAngleControllerAccE->setValue(s[5]);

        }
    }
}
