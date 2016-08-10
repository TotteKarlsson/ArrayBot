#include <vcl.h>
#pragma hdrstop
#include "TSettingsForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TIntegerLabeledEdit"
#pragma resource "*.dfm"
TSettingsForm *SettingsForm;

//---------------------------------------------------------------------------
__fastcall TSettingsForm::TSettingsForm(TMainForm& mf)
	: TForm(&mf),
    mMainForm(mf)
{
	UIUpdateTimer->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TSettingsForm::mASStartBtnClick(TObject *Sender)
{
	if(mASStartBtn->Caption == "Start")
    {
    	mMainForm.mArduinoClient.connect(mArduinoServerPortE->getValue());
        mASStartBtn->Caption == "Connecting";
        mMainForm.mArduinoClient.getStatus();
    }
    else
    {
    	mMainForm.mArduinoClient.disConnect();
    }
}

//--------------------------------------------------------------------------
void __fastcall TSettingsForm::UIUpdateTimerTimer(TObject *Sender)
{
   	mASStartBtn->Caption 			= mMainForm.mArduinoClient.isConnected()	? "Stop" : "Start";
	mArduinoServerPortE->Enabled 	= !mMainForm.mArduinoClient.isConnected();
}


