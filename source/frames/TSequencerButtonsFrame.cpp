#include <vcl.h>
#pragma hdrstop
#include <Buttons.hpp>
#include "TSequencerButtonsFrame.h"
#include "mtkVCLUtils.h"
#include "vcl/forms/TYesNoForm.h"
#include <sstream>
#include "mtkLogger.h"
#include "forms/TProcessSequenceControlForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"

using namespace mtk;
using std::stringstream;
TSequencerButtonsFrame *SequencerButtonsFrame;

int TSequencerButtonsFrame::mFrameCount = 0;
//---------------------------------------------------------------------------
__fastcall TSequencerButtonsFrame::TSequencerButtonsFrame(ProcessSequencer& ps, const string& category, TComponent* Owner)
	: TFrame(Owner),
    mProcessSequencer(ps),
    mAB(ps.getArrayBot()),
    mCategory(category)
{
	this->Name = this->Name + "_" + IntToStr(mFrameCount++);
}

__fastcall TSequencerButtonsFrame::~TSequencerButtonsFrame()
{}

string TSequencerButtonsFrame::getCategory()
{
	return mCategory;
}

//--------------------------------------------------------------------------
void TSequencerButtonsFrame::update()
{
    for(int i = 0; i < mButtons.size(); i++)
    {
    	delete mButtons[i];
    }

	mButtons.clear();

    ProcessSequencer& psr = mProcessSequencer;
    ProcessSequences& pss = psr.getSequences();

	ProcessSequence*  current = pss.getCurrent();
    ProcessSequence*  ps = pss.getFirst();

    int nrOfButtons = pss.count();

    int pWidth = this->Width;
    int pHeight = this->Height;

    int btnNr(0);
    while(ps)
    {
    	if(ps->getCategory() == mCategory)
        {
            TArrayBotButton* btn = new TArrayBotButton(this->Parent);
            mButtons.push_back(btn);

            btn->Parent = this;
            btn->Caption = vclstr(ps->getName());
            btn->OnClick = click;
            btn->SoundID = "button_click_5";

            btn->Font->Size = 12;
            btn->Width = 190;
            btn->Height = pHeight;

            if(btnNr == 0)
            {
                btn->Left = 3;
            }
            else
            {
                btn->Left = 3 + btnNr * (btn->Width + btn->Width / 4);
            }

            btn->Top = 0;
            btnNr +=1 ;
        }

        ps = pss.getNext();
    }

    //Restore back to the sequence wich was selected
    pss.select(current);
}

//---------------------------------------------------------------------------
void __fastcall TSequencerButtonsFrame::mSequenceStatusTimerTimer(TObject *Sender)
{
	if(!mProcessSequencer.isRunning())
    {
		mSequenceStatusTimer->Enabled = false;
    }
}

//---------------------------------------------------------------------------
void __fastcall TSequencerButtonsFrame::click(TObject *Sender)
{
	TArrayBotButton* b = dynamic_cast<TArrayBotButton*>(Sender);
    if(!b)
    {
    	Log(lError) << "Bad button on the frame";
    	return;
    }

    ProcessSequencer& psr = mProcessSequencer;
    if(psr.selectSequence(stdstr(b->Caption)))
    {
        mSequenceStatusTimer->Enabled = true;
        mAB.disableJoyStickAxes();
        TProcessSequenceControlForm* f = new TProcessSequenceControlForm(mProcessSequencer, this);
        f->ShowModal();
        delete f;
        mAB.enableJoyStickAxes();
    }
}

