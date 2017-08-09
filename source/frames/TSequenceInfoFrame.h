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
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------

class ProcessSequence;
class TParallellProcessesFrame;
class TTimeDelayFrame;
class TArrayCamRequestFrame;
class Process;
class ArrayBot;
class ProcessSequencer;

class PACKAGE TSequenceInfoFrame : public TFrame
{
    __published:	// IDE-managed Components
	TActionList *mSequenceAL;
        TAction *RemoveProcessA;
	TAction *AddCombinedMoveA;
	TListBox *mProcessesLB;
	TGroupBox *MasterProcessGB;
	TArrayBotButton *mRenameBtn;
	TArrayBotButton *mAddMoveBtn;
	TArrayBotButton *mDeleteMoveBtn;
	TArrayBotButton *mMoveSequenceDownBtn;
	TArrayBotButton *mMoveSequenceUpBtn;
	TArrayBotButton *mUpdatePositionsBtn;
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
	void __fastcall mProcessesLBClick(TObject *Sender);
	void __fastcall AddCombinedMoveAExecute(TObject *Sender);
	void __fastcall mUpdatePositionsBtnClick(TObject *Sender);
	void __fastcall mRenameBtnClick(TObject *Sender);
	void __fastcall CategoryCBCloseUp(TObject *Sender);
	void __fastcall NewSequenceCategoryBtnClick(TObject *Sender);
	void __fastcall LogXML1Click(TObject *Sender);

    private:
		ProcessSequence*		        mSequence;
        string					        mSequencesFolder;
        ProcessSequencer&  		        mProcessSequencer;
        TScrollBox*					    mProcessPanel;
        TParallellProcessesFrame*		mParallellProcessesFrame;
        TTimeDelayFrame*				mTimeDelayFrame;
        TArrayCamRequestFrame*	 		mArrayCamRequestFrame;

		void		__fastcall          empty();
        void							disableEnableButtons(bool enabled);
		void       				        updateSequenceArrows();
        Process*				        getCurrentlySelectedProcess();

    public:
        			__fastcall 	        TSequenceInfoFrame(ProcessSequencer& ps, TComponent* Owner);
		bool					        populate(ProcessSequence* seq, TScrollBox* processPanel = NULL);
};

extern PACKAGE TSequenceInfoFrame *SequenceInfoFrame;
#endif
