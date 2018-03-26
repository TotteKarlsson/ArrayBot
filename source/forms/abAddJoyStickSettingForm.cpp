#include <vcl.h>
#pragma hdrstop
#include "abAddJoyStickSettingForm.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
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

