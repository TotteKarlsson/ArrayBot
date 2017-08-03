#ifndef TParallellProcessesFrameH
#define TParallellProcessesFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TMotorMoveProcessFrame.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "arraybot/atArrayBot.h"
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------

class Process;
class ParallellProcess;
class XYZUnit;
class TArduinoServerCommandFrame;
class TArrayCamRequestFrame;

class PACKAGE TParallellProcessesFrame : public TFrame
{
__published:	// IDE-managed Components
	TListBox *mSubProcessesLB;
	TButton *Button1;
	TButton *Button2;
	TGroupBox *GroupBox1;
	TActionList *ActionList1;
	TAction *addMoveA;
	TAction *removeMoveA;
	TAction *mUpdateFinalPositionsA;
	TArrayBotButton *mRenameBtn;
	TButton *Button3;
	TAction *newArrayCamRequestA;
	TPanel *Panel1;
	void __fastcall addMoveAExecute(TObject *Sender);
	void __fastcall mSubProcessesLBClick(TObject *Sender);
	void __fastcall removeMoveAExecute(TObject *Sender);
	void __fastcall mUpdateFinalPositionsAExecute(TObject *Sender);
	void __fastcall mRenameBtnClick(TObject *Sender);
	void __fastcall newArrayCamRequestAExecute(TObject *Sender);

    private:
		ProcessSequencer&				mProcessSequencer;
		ParallellProcess*				mParallell;
		void					    	selectItem(Process* mv);
		Process*						getCurrentlySelectedSubProcess();
		TMotorMoveProcessFrame*			mTMotorMoveProcessFrame;
        TArduinoServerCommandFrame*		mTArduinoServerCommandFrame;
        TArrayCamRequestFrame*	 		mArrayCamRequestFrame;

	public:
							__fastcall  TParallellProcessesFrame(ProcessSequencer& pss, TComponent* Owner);
							__fastcall  ~TParallellProcessesFrame();
    	void							populate(Process* p);

};

extern PACKAGE TParallellProcessesFrame *ParallellProcessesFrame;
#endif
