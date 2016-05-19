#include <vcl.h>
#pragma hdrstop
#include "abAddJoyStickSetting.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TJoyStickSettingForm *JoyStickSettingForm;
//---------------------------------------------------------------------------
__fastcall TJoyStickSettingForm::TJoyStickSettingForm(TComponent* Owner)
	: TForm(Owner)
{}

JoyStickSetting	TJoyStickSettingForm::getSetting()
{
	return JoyStickSetting(
    mSettingsNameE->getValue(),  mMaxXYVelocityE->getValue(),
    mXYAcc->getValue(), mMaxZVelocityE->getValue(), mZAccE->getValue())
    ;
}

