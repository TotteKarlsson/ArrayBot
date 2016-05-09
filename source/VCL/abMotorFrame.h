#ifndef abMotorFrameH
#define abMotorFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------

class APTMotor;

class TMotorFrame : public TFrame
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
private:	// User declarations
	APTMotor*		mMotor;

public:		// User declarations
	__fastcall TMotorFrame(TComponent* Owner);
    void			assignMotor(APTMotor* m);
};
//---------------------------------------------------------------------------
extern PACKAGE TMotorFrame *MotorFrame;
//---------------------------------------------------------------------------
#endif
