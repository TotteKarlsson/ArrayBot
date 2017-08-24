#ifndef TMoveCoverSlipAtAngleProcessFrameH
#define TMoveCoverSlipAtAngleProcessFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include "TSTDStringLabeledEdit.h"
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
#include "mtkFloatLabel.h"
#include "TPropertyCheckBox.h"
//---------------------------------------------------------------------------

class MoveCoverSlipAtAngleProcess;
class TPositionalTriggerFrame;
class ProcessSequencer;

class ArrayBot;
class XYZUnit;

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
	mtkFloatLabel *LatVelL;
	mtkFloatLabel *LatAccL;
	TPropertyCheckBox *EnableParallelWhiskerMoveCB;
	void __fastcall EditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

	void __fastcall mActionInfoClick(TObject *Sender);

    private:	// User declarations
        MoveCoverSlipAtAngleProcess*        mMoveCoverSlipAtAngleProcess;
        ProcessSequencer&			        mProcessSequencer;
        ArrayBot&					        mAB;
        TPositionalTriggerFrame*	        mPosTriggerFrame;

    public:		// User declarations
                        __fastcall TMoveCoverSlipAtAngleProcessFrame(ProcessSequencer& ps, TComponent* Owner);
        void            		   populate(MoveCoverSlipAtAngleProcess* m);
        void            		   rePopulate(MoveCoverSlipAtAngleProcess* m);
};

extern PACKAGE TMoveCoverSlipAtAngleProcessFrame *MoveCoverSlipAtAngleProcessFrame;
#endif
