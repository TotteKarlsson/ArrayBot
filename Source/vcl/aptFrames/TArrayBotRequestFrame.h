#ifndef TArrayBotRequestFrameH
#define TArrayBotRequestFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "arraybot/atArrayBot.h"
#include <Vcl.ExtCtrls.hpp>
#include "dslTFloatLabeledEdit.h"
#include "dslTSTDStringLabeledEdit.h"
#include "dslTIntegerLabeledEdit.h"
//---------------------------------------------------------------------------

namespace at
{
	class Process;
	class ArrayBotRequestProcess;
}
using at::ProcessSequencer;
using at::Process;
using at::ArrayBotRequestProcess;

//---------------------------------------------------------------------------
class PACKAGE TArrayBotRequestFrame : public TFrame
{
	__published:
        TGroupBox *GroupBox1;
	TSTDStringLabeledEdit *NameEdit;
	TComboBox *ArrayBotRequestCB;
	TGroupBox *FocusZoomGB;
	TIntegerLabeledEdit *FocusE;
	TIntegerLabeledEdit *ZoomE;
	TGroupBox *LEDIntensityGB;
	TIntegerLabeledEdit *LEDIntensityE;
        void __fastcall EditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ArrayBotRequestCBCloseUp(TObject *Sender);
	void __fastcall IntEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


    private:
        ProcessSequencer&				mProcessSequencer;
		ArrayBotRequestProcess*			mArrayBotRequest;
		static int						mFrameNr;
	public:
							__fastcall  TArrayBotRequestFrame(ProcessSequencer& ps, TComponent* Owner);
    	void							populate(Process* p);

};

extern PACKAGE TArrayBotRequestFrame *ArrayBotRequestFrame;
#endif
