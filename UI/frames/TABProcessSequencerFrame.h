#ifndef TABProcessSequencerFrameH
#define TABProcessSequencerFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "abProcessSequencer.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "frames/TMotorMoveProcessFrame.h"
#include "frames/TParallellProcessesFrame.h"
#include "TSTDStringLabeledEdit.h"
#include "frames/TTimeDelayFrame.h"

#include "TTimeDelayFrame.h"
#include "TSequenceInfoFrame.h"
//---------------------------------------------------------------------------

class ArrayBot;

class TABProcessSequencerFrame : public TFrame
{
    __published:	// IDE-managed Components
        TButton *mStartBtn;
        TComboBox *mSequencesCB;
        TButton *mDeleteSequenceBtn;
        TButton *mAddSeqBtn;
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
	TSequenceInfoFrame *TSequenceInfoFrame1;
	TPanel *mProcessPanel;
	TPanel *Panel2;
	TCheckBox *mContinousExecutionCB;
	TButton *mRewindButton;
	TButton *Button1;
        void __fastcall mDeleteSequenceBtnClick(TObject *Sender);
        void __fastcall mAddSeqBtnClick(TObject *Sender);
        void __fastcall mStartBtnClick(TObject *Sender);
        void __fastcall mSaveSequenceBtnClick(TObject *Sender);
        void __fastcall mSequencesCBChange(TObject *Sender);
        void __fastcall mSequenceTimerTimer(TObject *Sender);
        void __fastcall mSequenceNameEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall mRewindButtonClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);



	private:	// User declarations
        ArrayBot&					mAB;
	    ProcessSequencer&  			mProcessSequencer;
        string 						mProcessFileExtension;
		void __fastcall 			refreshSequencesCB();
		static int 					mFrameNr;
		void						saveSequence();


	public:
						 __fastcall TABProcessSequencerFrame(ArrayBot& ab, const string& appFolder, TComponent* Owner);
        void						init();
};

extern PACKAGE TABProcessSequencerFrame *ABProcessSequencerFrame;
#endif
