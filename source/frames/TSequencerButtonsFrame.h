#ifndef TSequencerButtonsFrameH
#define TSequencerButtonsFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "arraybot/atArrayBot.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "TArrayBotBtn.h"
//---------------------------------------------------------------------------


class PACKAGE TSequencerButtonsFrame : public TFrame
{
    __published:
        TTimer *mSequenceStatusTimer;
        void __fastcall mSequenceStatusTimerTimer(TObject *Sender);
        void __fastcall click(TObject *Sender);

    private:
		ProcessSequencer&	  		mProcessSequencer;
		ArrayBot&					mAB;
        vector<TArrayBotButton*> 	mButtons;

	public:
					__fastcall 		TSequencerButtonsFrame(ProcessSequencer& ps, TComponent* Owner);
    	void						update();
};


extern PACKAGE TSequencerButtonsFrame *SequencerButtonsFrame;
#endif
