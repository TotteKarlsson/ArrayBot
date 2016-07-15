#ifndef TMotorMoveProcessFrameH
#define TMotorMoveProcessFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "TPositionalTriggerFrame.h"
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------

class AbsoluteMove;


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
	TTabSheet *TabSheet2;
	TPositionalTriggerFrame *TPositionalTriggerFrame1;
	TTabSheet *TabSheet3;
	TGroupBox *GroupBox1;
	TFloatLabeledEdit *mPostDwellTimeE;
	TFloatLabeledEdit *mPreDwellTimeE;
	void __fastcall MotorsCBClick(TObject *Sender);
	void __fastcall MotorsCBChange(TObject *Sender);
	void __fastcall mMovePosEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

    private:	// User declarations
        AbsoluteMove* 	   			mMove;
        ArrayBot*					mAB;
		void 						populateMotorCB();

    public:		// User declarations
                        __fastcall TMotorMoveProcessFrame(TComponent* Owner);
        void            		   populate(ArrayBot* ab, AbsoluteMove* m);
        void            		   rePopulate(AbsoluteMove* m);
};

extern PACKAGE TMotorMoveProcessFrame *MotorMoveProcessFrame;
#endif
