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
        TTimer*						mSequenceStatusTimer;
        void __fastcall 			mSequenceStatusTimerTimer(TObject *Sender);
        void __fastcall 			click(TObject *Sender);


    private:
    	static int				  	mFrameCount;
		ProcessSequencer&	  		mProcessSequencer;
		ArrayBot&					mAB;
        vector<TArrayBotButton*> 	mButtons;
        string						mCategory;

	public:
					__fastcall 		TSequencerButtonsFrame(ProcessSequencer& ps, const string& category, TComponent* Owner);
					__fastcall 		~TSequencerButtonsFrame();
    	void						update();
        string						getCategory();
};


extern PACKAGE TSequencerButtonsFrame *SequencerButtonsFrame;
#endif
