#ifndef abMotorFrameH
#define abMotorFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "mtkFloatLabeledEdit.h"
#include "TIntLabel.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class APTMotor;

class PACKAGE TMotorFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *MotorGB;
	TGroupBox *StatusGB;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Lbl;
	TLabel *Lbl2;
	TLabel *mIsActiveLabel;
	TLabel *mIsForwardingLabel;
	TLabel *mIsHomedLabel;
	TLabel *mIsHomingLabel;
	TLabel *mIsReversingLabel;
	TLabel *mVelocityLbl;
	mtkFloatLabeledEdit *mMotorPositionE;
	TTimer *mMotorStatusTimer;
	void __fastcall mMotorStatusTimerTimer(TObject *Sender);
private:	// User declarations
	APTMotor*		mMotor;

public:		// User declarations
	__fastcall 				TMotorFrame(const string& name, TComponent* Owner);
    void					assignMotor(APTMotor* m);
};

extern PACKAGE TMotorFrame *MotorFrame;
#endif
