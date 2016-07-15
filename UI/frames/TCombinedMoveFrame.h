#ifndef TCombinedMoveFrameH
#define TCombinedMoveFrameH
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
class CombinedMove;
class XYZUnit;
//---------------------------------------------------------------------------
class TCombinedMoveFrame : public TFrame
{
__published:	// IDE-managed Components
	TListBox *mMoveLB;
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
	void __fastcall addMoveAExecute(TObject *Sender);
	void __fastcall mMoveLBClick(TObject *Sender);
	void __fastcall removeMoveAExecute(TObject *Sender);
	void __fastcall mProcessNameEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


    private:	// User declarations
		ArrayBot*						mAB;
		CombinedMove*					mCombinedMove;
		void					    	selectItem(ab::Move* mv);

	public:		// User declarations
							__fastcall  TCombinedMoveFrame(TComponent* Owner);

    	void							populate(ArrayBot& ab, Process* p);
    	void							rePopulate(Process* p);
};

extern PACKAGE TCombinedMoveFrame *CombinedMoveFrame;
#endif
