#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include "dslLogger.h"
#include "abAddJoyStickSettingForm.h"
#include "sound/atSounds.h"
using namespace dsl;
using namespace std;
using namespace at;
extern bool gAppIsStartingUp;

//---------------------------------------------------------------------------
void __fastcall TMain::mJoyStickRGClick(TObject *Sender)
{
	if(mAB.getJoyStick().enableJoyStickWithID(mJoyStickRG->ItemIndex))
    {
    	mAB.enableJoyStick();
    	Log(lInfo) << "Joystick was enabled.";
    }
    else
    {
    	Log(lError) << "ArrayBot failed to switch the Joystick. Check that the Joystick has power and that its front light is lit.";
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::JSControlClick(TObject *Sender)
{
	//Setup Joystick control
    TSpeedButton* btn = dynamic_cast<TSpeedButton*>(Sender);
    if(btn->Caption == "Enable JS")
    {
		if(!mAB.enableJoyStick())
        {
        	MessageDlg("Failed enabling current JoyStick. \r ", mtWarning, TMsgDlgButtons() << mbOK, 0);
        }
    }
    else
    {
	 	mAB.disableJoyStick();
    }

    if(mAB.getJoyStick().isEnabled())
    {
        //There is a 'bug' regarding speed settings
        //Programatically apply currently selected setting
        if(mJSSpeedFastBtn->Down)
        {
            mJSSpeedFastBtn->Click();
        }

        if(mJSSpeedMediumBtn->Down)
        {
            mJSSpeedMediumBtn->Click();
        }

        if(mJSSpeedSlowBtn->Down)
        {
            mJSSpeedSlowBtn->Click();
        }
    }

    btn->Caption = (mAB.getJoyStick().isEnabled()) ? "Disable JS" : "Enable JS";
}

void __fastcall TMain::JSSpeedBtnClick(TObject *Sender)
{
    TSpeedButton* btn = dynamic_cast<TSpeedButton*>(Sender);
	if(btn == mJSSpeedFastBtn)
    {
    	//Apply "FAST" JS setting
        mAB.applyJoyStickSetting("Fast");
       	mEnableFastSpeedSound.getValueReference().play();
    }
    else if (btn == mJSSpeedMediumBtn)
    {
        mAB.applyJoyStickSetting("Medium");
       	mEnableMediumSpeedSound.getValueReference().play();
    }
    else if (btn == mJSSpeedSlowBtn)
    {
        mAB.applyJoyStickSetting("Slow");
      	mEnableSlowSpeedSound.getValueReference().play();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMain::JoyStickValueEdit(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key != vkReturn)
    {
    	return;
    }

	//Get current setting
    int index = JoyStickSettingsCB->ItemIndex;
    if(index == -1)
    {
    	return;
    }

    JoyStickSetting* jss = (JoyStickSetting*) JoyStickSettingsCB->Items->Objects[index];
    if(!jss)
    {
    	return;
    }

    // Update setting from edits
    jss->set(mMaxXYJogVelocityJoystick->getValue(), mXYJogAccelerationJoystick->getValue(),
			 mMaxZJogVelocityJoystick->getValue(),  mZJogAccelerationJoystick->getValue(),
             mAngleControlVelE->getValue(),         mAngleControllerAccE->getValue()
             );

	mAB.writeINIParameters();
    mIniFile.save();
}

//---------------------------------------------------------------------------
void __fastcall TMain::mXYCtrlRGClick(TObject *Sender)
{
	if(mXYCtrlRG->ItemIndex == 0)//Both X&Y
    {
        mAB.getJoyStick().getY1Axis().enable();
        mAB.getJoyStick().getY2Axis().enable();
        mAB.getJoyStick().getX1Axis().enable();
        mAB.getJoyStick().getX2Axis().enable();
    }
    else if(mXYCtrlRG->ItemIndex == 1)//Only X
    {
        mAB.getJoyStick().getX1Axis().enable();
        mAB.getJoyStick().getX2Axis().enable();
        mAB.getJoyStick().getY1Axis().disable();
        mAB.getJoyStick().getY2Axis().disable();
    }
    else if(mXYCtrlRG->ItemIndex == 2)//Only Z
    {
        mAB.getJoyStick().getY1Axis().enable();
        mAB.getJoyStick().getY2Axis().enable();
        mAB.getJoyStick().getX1Axis().disable();
        mAB.getJoyStick().getX2Axis().disable();
    }
    else
    {
        mAB.getJoyStick().getY1Axis().disable();
        mAB.getJoyStick().getY2Axis().disable();
        mAB.getJoyStick().getX1Axis().disable();
        mAB.getJoyStick().getX2Axis().disable();
    }
}

void TMain::onJSButton9Down()
{
	//Fire the ribbon separator
   	mArrayCamClient.triggerRibbonSeparator();
}

void TMain::onJSButton8Down()
{
	//Don't really do anyting...
}

void TMain::onJSButton5Down()
{
	//ZoomIN navitar
    //Check if jsButton 8 is down
    if(mAB.getJoyStick().getButton(8).isDown())
    {
    	mArrayCamClient.focusIn(300);
    }
    else
    {
    	mArrayCamClient.zoomIn(500);
    }
}

void TMain::onJSButton7Down()
{
	//ZoomIN navitar
    if(mAB.getJoyStick().getButton(8).isDown())
    {
	    mArrayCamClient.focusOut(500);
    }
    else
    {
	    mArrayCamClient.zoomOut(500);
    }
}

void TMain::onJSButton6Click()
{
	//Check speed setting, go from slower to faster
	if(mJSSpeedSlowBtn->Down)
    {
	    mJSSpeedMediumBtn->Down = true;
		mJSSpeedMediumBtn->Click();
    }
	else if(mJSSpeedFastBtn->Down)
    {
	    mJSSpeedSlowBtn->Down = true;
		mJSSpeedSlowBtn->Click();
    }
	else if(mJSSpeedMediumBtn->Down)
    {
	    mJSSpeedFastBtn->Down = true;
		mJSSpeedFastBtn->Click();
    }
}

void TMain::onJSButton14Click()
{
    stopAllAExecute(NULL);
}


void __fastcall TMain::AddJsSettingBtnClick(TObject *Sender)
{
    TAddJoyStickSettingForm* f = new TAddJoyStickSettingForm(NULL);
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
    if(JoyStickSettingsCB->ItemIndex == -1)
    {
    	Log(lInfo) << "No joystick settings are available!";
        return;
    }

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
