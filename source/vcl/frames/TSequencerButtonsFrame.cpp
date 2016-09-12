#include <vcl.h>
#pragma hdrstop
#include <Buttons.hpp>
#include "TSequencerButtonsFrame.h"
#include "mtkVCLUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TSequencerButtonsFrame *SequencerButtonsFrame;
//---------------------------------------------------------------------------
__fastcall TSequencerButtonsFrame::TSequencerButtonsFrame(ArrayBot& bot, TComponent* Owner)
	: TFrame(Owner),
    mAB(bot)
{
}
//--------------------------------------------------------------------------
void TSequencerButtonsFrame::update()
{

    for(int i = 0; i < mButtons.size(); i++)
    {
    	delete mButtons[i];
    }

	mButtons.clear();

    ProcessSequencer& psr = mAB.getProcessSequencer();
    ProcessSequences& pss = psr.getSequences();

	ProcessSequence*  current = pss.getCurrent();
    ProcessSequence*  ps = pss.getFirst();

    int nrOfButtons = pss.count();

    while(ps)
    {
        TSpeedButton* btn = new TSpeedButton(this);
        mButtons.push_back(btn);

        btn->Parent = this;
        btn->Caption = vclstr(ps->getName());
        btn->Align = alLeft;
        btn->OnClick = runSequenceBtnClick;
        btn->Font->Size = 14;
        ps = pss.getNext();
        btn->Width = this->Width / nrOfButtons;
    }

    //Restore back to the sequence wich was selected
    pss.select(current);
}

void __fastcall TSequencerButtonsFrame::runSequenceBtnClick(TObject *Sender)
{
	TSpeedButton* b = dynamic_cast<TSpeedButton*>(Sender);
    if(b)
    {
        ProcessSequencer& psr = mAB.getProcessSequencer();
        if(psr.selectSequence(stdstr(b->Caption)))
        {
      		mSequenceStatusTimer->Enabled = true;
            mAB.disableJoyStickAxes();
        	psr.start();
        }
    }
}

void __fastcall TSequencerButtonsFrame::FrameEnter(TObject *Sender)
{
	update();
}

void __fastcall TSequencerButtonsFrame::mSequenceStatusTimerTimer(TObject *Sender)
{
    ProcessSequencer& psr = mAB.getProcessSequencer();
	if(!psr.isRunning())
    {
		mSequenceStatusTimer->Enabled = false;
        mAB.enableJoyStickAxes();
    }
}

