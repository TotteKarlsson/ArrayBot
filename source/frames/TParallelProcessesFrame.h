#ifndef TParallelProcessesFrameH
#define TParallelProcessesFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "arraybot/atArrayBot.h"
#include "dslTFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------

class Process;
class ParallelProcess;
class XYZUnit;
class TArduinoServerCommandFrame;
class TArrayCamRequestFrame;
class TMotorMoveProcessFrame;
class THomeMotorProcessFrame;
class TMoveCoverSlipAtAngleProcessFrame;

class PACKAGE TParallelProcessesFrame : public TFrame
{
__published:	// IDE-managed Components
	TListBox *mSubProcessesLB;
	TButton *Button2;
	TGroupBox *GroupBox1;
	TActionList *ActionList1;
	TAction *addMoveA;
	TAction *removeMoveA;
	TArrayBotButton *mRenameBtn;
	TAction *newArrayCamRequestA;
	TPanel *Panel1;
	TAction *HomeMotorA;
	TButton *Button4;
	void __fastcall addMoveAExecute(TObject *Sender);
	void __fastcall SubProcessesLBClick(TObject *Sender);
	void __fastcall removeMoveAExecute(TObject *Sender);
	void __fastcall mRenameBtnClick(TObject *Sender);
	void __fastcall newArrayCamRequestAExecute(TObject *Sender);
	void __fastcall HomeMotorAExecute(TObject *Sender);
	void __fastcall addProcess(TObject *Sender);

    private:
		ProcessSequencer&				        mProcessSequencer;
		ParallelProcess*				        mParallel;
		void					    	        selectItem(Process* mv);
		Process*						        getCurrentlySelectedSubProcess();
		TMotorMoveProcessFrame*			        mTMotorMoveProcessFrame;
		THomeMotorProcessFrame*			        mTHomeMotorProcessFrame;
        TArduinoServerCommandFrame*		        mTArduinoServerCommandFrame;
        TArrayCamRequestFrame*	 		        mArrayCamRequestFrame;
        TMoveCoverSlipAtAngleProcessFrame*		mMoveCoverSlipAtAngleProcessFrame;

	public:
							__fastcall  TParallelProcessesFrame(ProcessSequencer& pss, TComponent* Owner);
							__fastcall  ~TParallelProcessesFrame();
    	void							populate(Process* p);

};

extern PACKAGE TParallelProcessesFrame *ParallelProcessesFrame;
#endif
