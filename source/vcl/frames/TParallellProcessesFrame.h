#ifndef TParallellProcessesFrameH
#define TParallellProcessesFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TMotorMoveProcessFrame.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "abArrayBot.h"
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>

class Process;
class ParallellProcess;
class XYZUnit;

//---------------------------------------------------------------------------
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
	TPanel *Panel1;
	TSTDStringLabeledEdit *mProcessNameE;
	TGroupBox *GroupBox2;
	TMotorMoveProcessFrame *TMotorMoveProcessFrame1;
	TAction *mUpdateFinalPositionsA;
	void __fastcall addMoveAExecute(TObject *Sender);
	void __fastcall mSubProcessesLBClick(TObject *Sender);
	void __fastcall removeMoveAExecute(TObject *Sender);
	void __fastcall mProcessNameEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall mUpdateFinalPositionsAExecute(TObject *Sender);

    private:	// User declarations
		ArrayBot*						mAB;
		ParallellProcess*				mParallell;
		void					    	selectItem(Process* mv);

	public:		// User declarations
							__fastcall  TParallellProcessesFrame(TComponent* Owner);

    	void							populate(ArrayBot& ab, Process* p);
    	void							rePopulate(Process* p);
};

extern PACKAGE TParallellProcessesFrame *ParallellProcessesFrame;
#endif
