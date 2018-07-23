#ifndef TXYZProcessSequencerFrameH
#define TXYZProcessSequencerFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "atProcessSequencer.h"
//---------------------------------------------------------------------------

class XYZUnit;
class ArrayBot;

class TXYZProcessSequencerFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TGroupBox *GroupBox2;
	TLabel *Label2;
	TFloatLabeledEdit *mMovePosE;
	TFloatLabeledEdit *mMaxVelE;
	TFloatLabeledEdit *mAccE;
	TFloatLabeledEdit *mPostDwellTimeE;
	TComboBox *MotorsCB;
	TButton *mStartBtn;
	TListBox *mMovesLB;
	TComboBox *mSequencesCB;
	TButton *mSaveSequenceBtn;
	TButton *mAddMoveBtn;
	TButton *mDeleteSequenceBtn;
	TButton *mAddSeqBtn;
	TButton *mDeleteMoveBtn;
	TTimer *mSequenceStatusTimer;
	TLabel *mStatusLbl;
	TFloatLabeledEdit *mPreDwellTimeE;
	void __fastcall mAddMoveBtnClick(TObject *Sender);
	void __fastcall mDeleteMoveBtnClick(TObject *Sender);
	void __fastcall mDeleteSequenceBtnClick(TObject *Sender);
	void __fastcall mAddSeqBtnClick(TObject *Sender);
	void __fastcall mStartBtnClick(TObject *Sender);
	void __fastcall mSaveSequenceBtnClick(TObject *Sender);
	void __fastcall mSequencesCBChange(TObject *Sender);
	void __fastcall mMovesLBClick(TObject *Sender);
	void __fastcall moveParEdit(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall MotorsCBChange(TObject *Sender);
	void __fastcall mSequenceTimerTimer(TObject *Sender);

private:	// User declarations
	    ProcessSequencer  			mProcessSequencer;
        XYZUnit*					mXYZUnit;
        ArrayBot*					mAB;
        string 						mMovesFileExtension;
		void __fastcall 			refreshSequencesCB();
		static int 					mFrameNr;
		void						saveSequence();

public:
						 __fastcall TXYZProcessSequencerFrame(XYZUnit* u, ArrayBot* ab, const string& appFolder, TComponent* Owner);
        void						init();
};

extern PACKAGE TXYZProcessSequencerFrame *XYZProcessSequencerFrame;
#endif
