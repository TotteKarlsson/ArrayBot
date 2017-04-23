#ifndef TABProcessSequencerFrameH
#define TABProcessSequencerFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "process/atProcessSequencer.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "frames/TMotorMoveProcessFrame.h"
#include "frames/TParallellProcessesFrame.h"
#include "TSTDStringLabeledEdit.h"
#include "frames/TTimeDelayFrame.h"

#include "frames\TTimeDelayFrame.h"
#include "frames\TSequenceInfoFrame.h"
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------

class ArrayBot;

class PACKAGE TABProcessSequencerFrame : public TFrame
{
    __published:	// IDE-managed Components
        TButton *mStartBtn;
        TComboBox *mSequencesCB;
        TTimer *mSequenceStatusTimer;
        TLabel *mStatusLbl;
        TActionList *Actions;
	TAction *addCombinedMovesProcessA;
        TAction *removeProcessA;
        TGroupBox *GroupBox2;
        TPanel *Panel1;
	TAction *addTimeDelayProcess;
	TPanel *mMainPanel;
	TPanel *mLeftPanel;
	TPanel *Panel2;
	TCheckBox *mSteppedExecutionCB;
	TButton *mRewindButton;
	TArrayBotButton *mAddSeqBtn;
	TArrayBotButton *mDeleteSequenceBtn;
	TArrayBotButton *mRenameButton;
	TScrollBox *mProcessPanel;
	TSplitter *Splitter1;
        void __fastcall mDeleteSequenceBtnClick(TObject *Sender);
        void __fastcall mAddSeqBtnClick(TObject *Sender);
        void __fastcall mStartBtnClick(TObject *Sender);
        void __fastcall mSaveSequenceBtnClick(TObject *Sender);
        void __fastcall mSequencesCBChange(TObject *Sender);
        void __fastcall mSequenceTimerTimer(TObject *Sender);
		void __fastcall mRewindButtonClick(TObject *Sender);
		void __fastcall mRenameButtonClick(TObject *Sender);

	private:	// User declarations
		static int 					mFrameNr;

	    ProcessSequencer&  			mProcessSequencer;
        ArrayBot&					mAB;
        string 						mProcessFileExtension;
        string 						mAppDataFolder;
        string						getCurrentlySelectedSequence();
		void __fastcall 			refreshSequencesCB();
		void						saveSequence();

        							//!The SequenceInfo frame is dynamically allocated
		TSequenceInfoFrame*			TSequenceInfoFrame1;

	public:
						 __fastcall TABProcessSequencerFrame(ProcessSequencer& ps, const string& appFolder, TComponent* Owner);
        void						init();
};

extern PACKAGE TABProcessSequencerFrame *ABProcessSequencerFrame;
#endif
