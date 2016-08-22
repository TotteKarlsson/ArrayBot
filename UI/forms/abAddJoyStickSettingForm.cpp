#include <vcl.h>
#pragma hdrstop
#include "abAddJoyStickSettingForm.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"
TAddJoyStickSettingForm *AddJoyStickSettingForm;


__fastcall TAddJoyStickSettingForm::TAddJoyStickSettingForm(TComponent* Owner)
	: TForm(Owner)
{}

JoyStickSetting	TAddJoyStickSettingForm::getSetting()
{
	return JoyStickSetting(
    mSettingsNameE->getValue(),  mMaxXYVelocityE->getValue(),
    mXYAcc->getValue(), mMaxZVelocityE->getValue(), mZAccE->getValue());
}

