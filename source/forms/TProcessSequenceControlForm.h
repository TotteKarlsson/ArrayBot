#ifndef TProcessSequenceControlFormH
#define TProcessSequenceControlFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class ProcessSequencer;
class PACKAGE TProcessSequenceControlForm : public TForm
{

    __published:	// IDE-managed Components
        TTimer *mStatusTimer;
		TArrayBotButton *mStartResumeButton;
        TPanel *mControlPanel;
        TArrayBotButton *mPauseBtn;
        TArrayBotButton *mStopBtn;
        TLabel *mSequenceNameLbl;
        TLabel *mProcessNameLbl;
        TLabel *mNextProcessNameLbl;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall mStatusTimerTimer(TObject *Sender);
        void __fastcall mStartResumeButtonClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall mStopBtnClick(TObject *Sender);
	void __fastcall mPauseBtnClick(TObject *Sender);

    private:
		enum ProcessStatus {psNotStarted, psRunning, psPaused, psFinished, psUnknown};
    	ProcessSequencer&		mPS;
        ProcessStatus			mStatus;

    public:
        __fastcall TProcessSequenceControlForm(ProcessSequencer& s, TComponent* Owner);
};

extern PACKAGE TProcessSequenceControlForm *ProcessSequenceControlForm;

#endif
