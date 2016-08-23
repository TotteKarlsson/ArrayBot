#ifndef TSequenceInfoFrameH
#define TSequenceInfoFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TSTDStringLabeledEdit.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class ProcessSequence;
class TCombinedMoveFrame;
class Process;
class ArrayBot;

class PACKAGE TSequenceInfoFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
	TActionList *mSequenceAL;
        TAction *RemoveProcessA;
	TButton *mAddMoveBtn;
	TAction *AddCombinedMoveA;
	TPanel *GroupBox3;
	TButton *mDeleteMoveBtn;
	TButton *mMoveSequenceDownBtn;
	TButton *mMoveSequenceUpBtn;
	TListBox *mProcessesLB;
	TSTDStringLabeledEdit *mSequenceNameE;
	TGroupBox *GroupBox2;
    void __fastcall mMoveSequenceUpBtnClick(TObject *Sender);
    void __fastcall RemoveProcessAExecute(TObject *Sender);
	void __fastcall mMoveSequenceDownBtnClick(TObject *Sender);
	void __fastcall mProcessesLBClick(TObject *Sender);
	void __fastcall AddCombinedMoveAExecute(TObject *Sender);
//	void __fastcall SequenceNameEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
//	void __fastcall mSequenceNameEKeyPress(TObject *Sender, System::WideChar &Key);


    private:	// User declarations
		ProcessSequence*		mSequence;
        string					mSequencesFolder;
        ArrayBot*				mAB;
        TPanel*					mProcessPanel;
        TCombinedMoveFrame*		mCombinedMoveFrame;

		void		__fastcall  empty();
        void					disableEnableButtons(bool enabled);
		void       				updateSequenceArrows();
        Process*				getCurrentlySelectedProcess();

    public:		// User declarations
        			__fastcall 	TSequenceInfoFrame(TComponent* Owner);
		void					assignArrayBot(ArrayBot* ab);
		bool					populate(ProcessSequence* seq, TPanel* processPanel = NULL);
};

extern PACKAGE TSequenceInfoFrame *SequenceInfoFrame;
#endif
