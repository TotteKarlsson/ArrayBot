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

namespace ab
{
	class Move;
}

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
	void __fastcall mMovePosEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

    private:	// User declarations
        ab::Move* 		 			mMove;
        ArrayBot*					mAB;
		void 						populateMotorCB();

    public:		// User declarations
                        __fastcall TMotorMoveProcessFrame(TComponent* Owner);
        void            		   populate(ArrayBot* ab, ab::Move* m);
        void            		   rePopulate(ab::Move* m);
};

extern PACKAGE TMotorMoveProcessFrame *MotorMoveProcessFrame;
#endif
