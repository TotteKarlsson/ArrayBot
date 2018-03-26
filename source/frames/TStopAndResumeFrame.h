#ifndef TStopAndResumeFrameH
#define TStopAndResumeFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "dslTFloatLabeledEdit.h"
#include "dslTSTDStringLabeledEdit.h"

class Process;
class StopAndResumeProcess;
class ArrayBot;
//---------------------------------------------------------------------------
class PACKAGE TStopAndResumeFrame : public TFrame
{
	__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TSTDStringLabeledEdit *mNameEdit;
	TLabel *mActionInfo;
        void __fastcall mEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall mActionInfoClick(TObject *Sender);

    private:
		ArrayBot*						mAB;
		StopAndResumeProcess*			mStopAndResume;

	public:
							__fastcall  TStopAndResumeFrame(TComponent* Owner);

    	void							populate(Process* p);
    	void							rePopulate(Process* p);
};

extern PACKAGE TStopAndResumeFrame *StopAndResumeFrame;
#endif
