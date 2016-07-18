#ifndef TMotorMoveProcessFrameH
#define TMotorMoveProcessFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------

class AbsoluteMove;
class TPositionalTriggerFrame;

class ArrayBot;
class XYZUnit;

class TMotorMoveProcessFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *MainGB;
	TFloatLabeledEdit *mMovePosE;
	TFloatLabeledEdit *mMaxVelE;
	TFloatLabeledEdit *mAccE;
	TComboBox *MotorsCB;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *mTriggersSheet;
	TTabSheet *TabSheet3;
	TGroupBox *GroupBox1;
	TFloatLabeledEdit *mPostDwellTimeE;
	TFloatLabeledEdit *mPreDwellTimeE;
	TPanel *Panel1;
	TButton *mDeleteTriggerB;
	TListBox *mTriggersLB;
	TPanel *Panel2;
	TButton *mAddTriggerB;
	void __fastcall MotorsCBClick(TObject *Sender);
	void __fastcall MotorsCBChange(TObject *Sender);
	void __fastcall mMovePosEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall TriggersLBClick(TObject *Sender);
	void __fastcall mDeleteTriggerBClick(TObject *Sender);
	void __fastcall mAddTriggerBClick(TObject *Sender);

    private:	// User declarations
        AbsoluteMove* 	   			mMove;
        ArrayBot*					mAB;
		void 						populateMotorCB();
        TPositionalTriggerFrame*	mPosTriggerFrame;

    public:		// User declarations
                        __fastcall TMotorMoveProcessFrame(TComponent* Owner);
        void            		   populate(ArrayBot* ab, AbsoluteMove* m);
        void            		   rePopulate(AbsoluteMove* m);
};

extern PACKAGE TMotorMoveProcessFrame *MotorMoveProcessFrame;
#endif
