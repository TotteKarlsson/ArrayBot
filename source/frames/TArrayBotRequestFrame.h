#ifndef TArrayBotRequestFrameH
#define TArrayBotRequestFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "arraybot/atArrayBot.h"
#include <Vcl.ExtCtrls.hpp>
#include "TSTDStringLabeledEdit.h"
#include "TFloatLabeledEdit.h"
#include "TIntegerLabeledEdit.h"

class Process;
class ArrayBotRequestProcess;
//---------------------------------------------------------------------------
class PACKAGE TArrayBotRequestFrame : public TFrame
{
	__published:
        TGroupBox *GroupBox1;
	TSTDStringLabeledEdit *NameEdit;
	TComboBox *ArrayCamRequestCB;
	TGroupBox *FocusZoomGB;
	TIntegerLabeledEdit *FocusE;
	TIntegerLabeledEdit *ZoomE;
	TGroupBox *LEDIntensityGB;
	TIntegerLabeledEdit *LEDIntensityE;
        void __fastcall EditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ArrayCamRequestCBCloseUp(TObject *Sender);
	void __fastcall IntEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


    private:
        ProcessSequencer&				mProcessSequencer;
		ArrayCamRequestProcess*			mArrayCamRequest;
		static int						mFrameNr;
	public:
							__fastcall  TArrayBotRequestFrame(ProcessSequencer& ps, TComponent* Owner);
    	void							populate(Process* p);

};

extern PACKAGE TArrayBotRequestFrame *ArrayBotRequestFrame;
#endif
