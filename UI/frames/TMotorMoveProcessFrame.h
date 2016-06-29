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
private:	// User declarations
	LinearMove* 			mMove;

public:		// User declarations
					__fastcall TMotorMoveProcessFrame(TComponent* Owner);
    void            			populate(LinearMove* m);
};

extern PACKAGE TMotorMoveProcessFrame *MotorMoveProcessFrame;
#endif
