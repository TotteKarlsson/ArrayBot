#ifndef TRibbonLifterFrameH
#define TRibbonLifterFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "abRibbonLifter.h"
//---------------------------------------------------------------------------

class TRibbonLifterFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox2;
        TButton *Button1;
        TGroupBox *GroupBox1;

		TFloatLabeledEdit *mLiftLocationXE;
		TFloatLabeledEdit *mLiftLocationYE;
	TFloatLabeledEdit *mInitialLiftSpeedZE;
	TFloatLabeledEdit *mInitialLiftAccZE;
		TFloatLabeledEdit *mWhiskerLiftOffZPositionE;

        TFloatLabeledEdit *mWhiskerXLiftStowPosW;

        TFloatLabeledEdit *mMoveToPickupLocationSpeedE;
        TFloatLabeledEdit *mMoveToPickupLocationAccE;
	TButton *mMove1Btn;

	TFloatLabeledEdit *mInitialLiftSpeedYE;
	TFloatLabeledEdit *mInitialLiftAccYE;
	TTimer *mMove1Timer;
	TLabel *mRunningLbl;
	void __fastcall mMove1BtnClick(TObject *Sender);
	void __fastcall mMove1TimerTimer(TObject *Sender);

    private:	// User declarations
        RibbonLifter					mRibbonLifter;
		TNotifyEvent 					FOnClose;
		void __fastcall					WndProc(TMessage &Message);

    public:		// User declarations
                            __fastcall 	TRibbonLifterFrame(ArrayBot& ab, IniFile& iniFile, TComponent* Owner);
                            __fastcall 	~TRibbonLifterFrame();
		bool							init();
        bool							close();

        								//Check this flag to know when frame is destroyed
        static bool						gIsFrameOpen;


		 __property TNotifyEvent OnClose = {read=FOnClose, write=FOnClose};
};

//---------------------------------------------------------------------------
extern PACKAGE TRibbonLifterFrame *RibbonLifterFrame;
#endif
