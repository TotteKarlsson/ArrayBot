#ifndef TSequenceInfoFrameH
#define TSequenceInfoFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTFloatLabeledEdit.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------

class TParallelProcessesFrame;
class TTimeDelayFrame;
class TArrayCamRequestFrame;
class TMotorMoveProcessFrame;
class TStopAndResumeFrame;
class TMoveCoverSlipAtAngleProcessFrame;
class THomeMotorProcessFrame;

namespace at
{
    class ProcessSequence;
    class Process;
    class ArrayBot;
    class ProcessSequencer;
}

using at::ProcessSequence;
using at::ProcessSequencer;
using at::Process;
using at::ArrayBot;


using std::vector;

class PACKAGE TSequenceInfoFrame : public TFrame
{
    __published:	// IDE-managed Components
	TActionList *mSequenceAL;
        TAction *RemoveProcessA;
	TAction *AddCombinedMoveA;
	TListBox *ProcessesLB;
	TGroupBox *MasterProcessGB;
	TArrayBotButton *mRenameBtn;
	TArrayBotButton *mAddMoveBtn;
	TArrayBotButton *mDeleteMoveBtn;
	TArrayBotButton *mMoveSequenceDownBtn;
	TArrayBotButton *mMoveSequenceUpBtn;
	TArrayBotButton *UpdateStateBtn;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TComboBox *CategoryCB;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TArrayBotButton *NewSequenceCategoryBtn;
	TPopupMenu *PopupMenu1;
	TMenuItem *LogXML1;
    void __fastcall mMoveSequenceUpBtnClick(TObject *Sender);
    void __fastcall RemoveProcessAExecute(TObject *Sender);
	void __fastcall mMoveSequenceDownBtnClick(TObject *Sender);
	void __fastcall ProcessesLBClick(TObject *Sender);
	void __fastcall AddCombinedMoveAExecute(TObject *Sender);
	void __fastcall UpdateStateBtnClick(TObject *Sender);
	void __fastcall mRenameBtnClick(TObject *Sender);
	void __fastcall CategoryCBCloseUp(TObject *Sender);
	void __fastcall NewSequenceCategoryBtnClick(TObject *Sender);
	void __fastcall LogXML1Click(TObject *Sender);

    private:
		ProcessSequence*		                mSequence;
        string					                mSequencesFolder;
        ProcessSequencer&  		                mProcessSequencer;
        TScrollBox*					            mProcessPanel;
        vector<TFrame*>					        mFrames;
        								        //!Different Types of processes
        TParallelProcessesFrame*		        mParallelProcessesFrame;
        TTimeDelayFrame*				        mTimeDelayFrame;
        TArrayCamRequestFrame*	 		        mArrayCamRequestFrame;
		TMotorMoveProcessFrame*			        mMotorMoveProcessFrame;
		TStopAndResumeFrame*			        mStopAndResumeFrame;
		TMoveCoverSlipAtAngleProcessFrame*  	mMoveCoverSlipAtAngleProcessFrame;
		THomeMotorProcessFrame*  		  		mHomeMotorProcessFrame;

		void 									setFramesVisibility(bool vis);
		void 									setFramesParent(TScrollBox* p);


		void		__fastcall                  empty();
        void							        disableEnableButtons(bool enabled);
		void       				                updateSequenceArrows();
        Process*				                getCurrentlySelectedProcess();

    public:
        			__fastcall 	                TSequenceInfoFrame(ProcessSequencer& ps, TComponent* Owner);
        			__fastcall 	                ~TSequenceInfoFrame();
		bool					                populate(ProcessSequence* seq, TScrollBox* processPanel = NULL);
};

extern PACKAGE TSequenceInfoFrame *SequenceInfoFrame;
#endif
