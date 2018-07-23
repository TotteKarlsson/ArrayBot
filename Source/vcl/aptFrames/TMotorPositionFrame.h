#ifndef TMotorPositionFrameH
#define TMotorPositionFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

namespace at{class APTMotor;} using at::APTMotor;

class PACKAGE TMotorPositionFrame : public TFrame
{
    __published:	// IDE-managed Components
	TGroupBox *MotorPositionGB;
	TLabel *mPosL;
        TTimer *PullPosTimer;
        void __fastcall PullPosTimerTimer(TObject *Sender);

    private:
		const APTMotor*			mMotor;
		static int				mFrameNr;

	public:		// User declarations
		__fastcall 				TMotorPositionFrame(TComponent* Owner, const APTMotor* u = NULL);
        void					assignMotor(APTMotor* m);

};

extern PACKAGE TMotorPositionFrame *MotorPositionFrame;
#endif
