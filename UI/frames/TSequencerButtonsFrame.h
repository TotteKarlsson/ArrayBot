#ifndef TSequencerButtonsFrameH
#define TSequencerButtonsFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "abArrayBot.h"
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------


class TSequencerButtonsFrame : public TFrame
{
    __published:	// IDE-managed Components
	void __fastcall runSequenceBtnClick(TObject *Sender);
	void __fastcall FrameEnter(TObject *Sender);

    private:	// User declarations
		ArrayBot&				mAB;
        vector<TSpeedButton *> 	mButtons;

	public:
					__fastcall 	TSequencerButtonsFrame(ArrayBot& bot, TComponent* Owner);
    	void					update();
};

//---------------------------------------------------------------------------
extern PACKAGE TSequencerButtonsFrame *SequencerButtonsFrame;
//---------------------------------------------------------------------------
#endif
