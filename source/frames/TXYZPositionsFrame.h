#ifndef TXYZPositionsFrameH
#define TXYZPositionsFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class XYZUnit;
class PACKAGE TXYZPositionsFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *mXPosL;
        TLabel *mYPosL;
        TLabel *mZPosL;
	TLabel *mAnglePosL;
        TTimer *PullPosTimer;
        void __fastcall PullPosTimerTimer(TObject *Sender);

    private:
		const XYZUnit&			mUnit;
		static int				mFrameNr;

public:		// User declarations
	__fastcall TXYZPositionsFrame(TComponent* Owner, const XYZUnit& u);
};

extern PACKAGE TXYZPositionsFrame *XYZPositionsFrame;
#endif
