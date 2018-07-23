#include <vcl.h>
#pragma hdrstop
#include "TArduinoServerCommandFrame.h"
#include "arduino/atArduinoServerCommand.h"
#include "dslVCLUtils.h"
#include "arraybot/atArrayBot.h"
#include "forms/TTextInputDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTStdStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TArduinoServerCommandFrame *ArduinoServerCommandFrame;

using namespace at;
//---------------------------------------------------------------------------
__fastcall TArduinoServerCommandFrame::TArduinoServerCommandFrame(ArrayBot& ab, TComponent* Owner)
	:
    TFrame(Owner),
    mAB(ab)
{}

void TArduinoServerCommandFrame::populate(ArduinoServerCommand* m)
{
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


