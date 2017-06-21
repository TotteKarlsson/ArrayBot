#ifndef TTimeDelayFrameH
#define TTimeDelayFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "arraybot/atArrayBot.h"
#include "TFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "TIntegerLabeledEdit.h"
#include "TSTDStringLabeledEdit.h"

class Process;
class TimeDelay;
//---------------------------------------------------------------------------
class PACKAGE TTimeDelayFrame : public TFrame
{
	__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TIntegerLabeledEdit *mTimeDelayE;
        TSTDStringLabeledEdit *mNameEdit;
        void __fastcall mEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

    private:	// User declarations
		ArrayBot*						mAB;
		TimeDelay*						mTimeDelay;

	public:		// User declarations
							__fastcall  TTimeDelayFrame(TComponent* Owner);

    	void							populate(Process* p);
    	void							rePopulate(Process* p);
};

extern PACKAGE TTimeDelayFrame *TimeDelayFrame;
#endif
