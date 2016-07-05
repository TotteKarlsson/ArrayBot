#include <vcl.h>
#pragma hdrstop
#include "abAddLiftForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma resource "*.dfm"

TAddLiftSettingForm *AddLiftSettingForm;

__fastcall TAddLiftSettingForm::TAddLiftSettingForm(TComponent* Owner)
	: TForm(Owner)
{}

PairedMove	TAddLiftSettingForm::getSetting()
{
	return PairedMove(
    mSettingsNameE->getValue(),  mDistanceE->getValue(),
    mVelocityE->getValue(), mAcc->getValue())
    ;
}

