#ifndef TLiftAtAngleProcessFrameH
#define TLiftAtAngleProcessFrameH
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
//---------------------------------------------------------------------------

class LiftAtAngleProcess;
class TPositionalTriggerFrame;
class ProcessSequencer;

class ArrayBot;
class XYZUnit;

//!This should perhaps be reanamed to TAbsoluteMoveFrame
class PACKAGE TLiftAtAngleProcessFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *mMainGB;
	TFloatLabeledEdit *mMovePosE;
	TFloatLabeledEdit *mMaxVelE;
	TFloatLabeledEdit *mAccE;
	TComboBox *MotorsCB;
	TPanel *mTriggerPanel;
	TLabel *Label1;
	TLabel *mActionInfo;
	TPanel *Panel2;
	TArrayBotButton *mAddTriggerBtn;
	TGroupBox *GroupBox1;
	TListBox *mTriggersLB;
	TPanel *Panel1;
	void __fastcall MotorsCBChange(TObject *Sender);
	void __fastcall mMovePosEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall TriggersLBClick(TObject *Sender);
	void __fastcall mDeleteTriggerBClick(TObject *Sender);
	void __fastcall AddTriggerBClick(TObject *Sender);
	void __fastcall mActionInfoClick(TObject *Sender);

    private:	// User declarations
        LiftAtAngleProcess*    		mProcess;
        ProcessSequencer&			mProcessSequencer;
        ArrayBot&					mAB;
		void 						populateMotorCB();
        TPositionalTriggerFrame*	mPosTriggerFrame;

    public:		// User declarations
                        __fastcall TLiftAtAngleProcessFrame(ProcessSequencer& ps, TComponent* Owner);
        void            		   populate(LiftAtAngleProcess* m);
        void            		   rePopulate(LiftAtAngleProcess* m);
};

extern PACKAGE TLiftAtAngleProcessFrame *LiftAtAngleProcessFrame;
#endif
