#ifndef TMotorMoveProcessFrameH
#define TMotorMoveProcessFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class LinearMove;
class ArrayBot;
class XYZUnit;

class TMotorMoveProcessFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *MainGB;
	TLabel *Label1;
	TFloatLabeledEdit *mMovePosE;
	TFloatLabeledEdit *mMaxVelE;
	TFloatLabeledEdit *mAccE;
	TFloatLabeledEdit *mPostDwellTimeE;
	TComboBox *MotorsCB;
	TFloatLabeledEdit *mPreDwellTimeE;
	void __fastcall MotorsCBClick(TObject *Sender);
	void __fastcall MotorsCBChange(TObject *Sender);
    private:	// User declarations
        LinearMove* 			mMove;
        ArrayBot*				mAB;
		void 					populateMotorCB();
    public:		// User declarations
                        __fastcall TMotorMoveProcessFrame(TComponent* Owner);
        void            		   populate(ArrayBot* ab, LinearMove* m);
        void            		   rePopulate(LinearMove* m);
};

extern PACKAGE TMotorMoveProcessFrame *MotorMoveProcessFrame;
#endif
