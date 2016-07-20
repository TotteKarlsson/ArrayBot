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
#include "TMotorMoveProcessFrame.h"
#include "TCombinedMoveFrame.h"
#include "mtkSTDStringEdit.h"
#include "TTimeDelayFrame.h"
//---------------------------------------------------------------------------

class ArrayBot;

class TABProcessSequencerFrame : public TFrame
{
    __published:	// IDE-managed Components
        TButton *mStartBtn;
        TListBox *mProcessesLB;
        TComboBox *mSequencesCB;
        TButton *mSaveSequenceBtn;
        TButton *mAddMoveBtn;
        TButton *mDeleteSequenceBtn;
        TButton *mAddSeqBtn;
        TButton *mDeleteMoveBtn;
        TTimer *mSequenceStatusTimer;
        TLabel *mStatusLbl;
        TActionList *Actions;
	TAction *addCombinedMovesProcessA;
        TAction *removeProcessA;
        TGroupBox *GroupBox2;
        mtkSTDStringEdit *mSequenceNameE;
        TPanel *Panel1;
	TAction *addTimeDelayProcess;
	TButton *Button1;
	TTimeDelayFrame *TTimeDelayFrame1;
	TPanel *mMainPanel;
	TPanel *mLeftPanel;
	TGroupBox *GroupBox1;
	TCombinedMoveFrame *TCombinedMoveFrame1;
	TButton *mMoveSequenceUpBtn;
	TButton *mMoveSequenceDownBtn;
        void __fastcall mDeleteSequenceBtnClick(TObject *Sender);
        void __fastcall mAddSeqBtnClick(TObject *Sender);
        void __fastcall mStartBtnClick(TObject *Sender);
        void __fastcall mSaveSequenceBtnClick(TObject *Sender);
        void __fastcall mSequencesCBChange(TObject *Sender);
        void __fastcall mProcessesLBClick(TObject *Sender);
        void __fastcall moveParEdit(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall MotorsCBChange(TObject *Sender);
        void __fastcall mSequenceTimerTimer(TObject *Sender);
        void __fastcall addCombinedMovesProcessAExecute(TObject *Sender);
        void __fastcall removeProcessAExecute(TObject *Sender);
        void __fastcall mSequenceNameEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall addTimeDelayProcessExecute(TObject *Sender);
	void __fastcall TTimeDelayFrame1mNameEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall TCombinedMoveFrame1mProcessNameEKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall mMoveSequenceDownBtnClick(TObject *Sender);
	void __fastcall mMoveSequenceUpBtnClick(TObject *Sender);

	private:	// User declarations
        ArrayBot&					mAB;
	    ProcessSequencer&  			mProcessSequencer;
        string 						mProcessFileExtension;
		void __fastcall 			refreshSequencesCB();
		static int 					mFrameNr;
		void						saveSequence();
		void        				updateSequenceArrows();

	public:
						 __fastcall TABProcessSequencerFrame(ArrayBot& ab, const string& appFolder, TComponent* Owner);
        void						init();
};

extern PACKAGE TABProcessSequencerFrame *ABProcessSequencerFrame;
#endif
