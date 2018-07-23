#ifndef TMoveCoverSlipAtAngleProcessFrameH
#define TMoveCoverSlipAtAngleProcessFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include "dslTFloatLabeledEdit.h"
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
#include "dslTFloatLabel.h"
#include "dslTPropertyCheckBox.h"
//---------------------------------------------------------------------------


class TPositionalTriggerFrame;

namespace at
{
    class MoveCoverSlipAtAngleProcess;
    class ProcessSequencer;
    class ArrayBot;
    class XYZUnit;
}
using at::MoveCoverSlipAtAngleProcess;

using at::ProcessSequencer;
using at::ArrayBot;
using at::XYZUnit;


//!This should perhaps be reanamed to TAbsoluteMoveFrame
class PACKAGE TMoveCoverSlipAtAngleProcessFrame : public TFrame
{
__published:	// IDE-managed Components
	TFloatLabeledEdit *mLiftVelocityE;
	TFloatLabeledEdit *mLiftAccE;
	TLabel *mActionInfo;
	TGroupBox *GroupBox4;
	TFloatLabeledEdit *mLiftAngleE;
	TGroupBox *GroupBox1;
	TFloatLabeledEdit *mLiftHeightE;
	TPanel *Panel2;
	TLabel *A;
	TLabel *Label1;
	TFloatLabel *LatVelL;
	TFloatLabel *LatAccL;
	TPropertyCheckBox *EnableParallelWhiskerMoveCB;
	TPropertyCheckBox *FetchAngleFromCSAngleMotorCB;
	TGroupBox *StayAtBeachGB;
	TFloatLabeledEdit *DeltaZE;
	TFloatLabeledEdit *YMoveE;
	TPropertyCheckBox *LeaveWhiskeratBeachCB;
	TFloatLabeledEdit *ZMoveE;
	TFloatLabeledEdit *YMoveScalingE;
	void __fastcall EditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

	void __fastcall mActionInfoClick(TObject *Sender);
	void __fastcall EnableParallelWhiskerMoveCBClick(TObject *Sender);
	void __fastcall FetchAngleFromCSAngleMotorCBClick(TObject *Sender);
	void __fastcall LeaveWhiskeratBeachCBClick(TObject *Sender);

    private:	// User declarations
        MoveCoverSlipAtAngleProcess*        mMoveCoverSlipAtAngleProcess;
        ProcessSequencer&			        mProcessSequencer;
        ArrayBot&					        mAB;
        TPositionalTriggerFrame*	        mPosTriggerFrame;

    public:		// User declarations
                        __fastcall 			TMoveCoverSlipAtAngleProcessFrame(ProcessSequencer& ps, TComponent* Owner);
        void            		   			populate(MoveCoverSlipAtAngleProcess* m);
};

extern PACKAGE TMoveCoverSlipAtAngleProcessFrame *MoveCoverSlipAtAngleProcessFrame;
#endif
