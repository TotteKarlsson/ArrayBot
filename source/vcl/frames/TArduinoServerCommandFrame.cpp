#include <vcl.h>
#pragma hdrstop
#include "TArduinoServerCommandFrame.h"
#include "arduino/abArduinoServerCommand.h"
#include "mtkVCLUtils.h"
#include "abArrayBot.h"
#include "TTextInputDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFloatLabeledEdit"
#pragma link "TSTDStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TArduinoServerCommandFrame *ArduinoServerCommandFrame;

//---------------------------------------------------------------------------
__fastcall TArduinoServerCommandFrame::TArduinoServerCommandFrame(TComponent* Owner)
	: TFrame(Owner),
    mAB(NULL)
{}

void TArduinoServerCommandFrame::populate(ArrayBot* ab, ArduinoServerCommand* m)
{
	mAB = ab;
    rePopulate(m);
}

void TArduinoServerCommandFrame::rePopulate(ArduinoServerCommand* m)
{
	if(!m)
    {
    	return;
    }

    mProcess = m;
    mActionInfo->Caption = vclstr(mProcess->getInfoText());
}

//---------------------------------------------------------------------------
void __fastcall TArduinoServerCommandFrame::mActionInfoClick(TObject *Sender)
{
    if(!mProcess)
    {
    	return;
    }

	//Open text edit form
	TTextInputDialog* t = new TTextInputDialog(this);

    t->Caption = "Update Action Information";
	Process* p =  mProcess;

    t->setText(mProcess->getInfoText());

    if(t->ShowModal() == mrOk)
    {
		//Rename the currently selected sequence
    	string newText(t->getText());
		mProcess->setInfoText(newText);
		mProcess->write();
        mActionInfo->Caption = vclstr(newText);
    }
    delete t;
}


