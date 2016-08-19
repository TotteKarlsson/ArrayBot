#ifndef TMainH
#define TMainH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "abArrayBotJoyStick.h"
#include "mtkLogFileReader.h"
//---------------------------------------------------------------------------

class TMain : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TMemo *infoMemo;
	TButton *Button1;
	TTimer *ShutDownTimer;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TButton *Button10;
	TButton *Button11;
	TButton *Button12;
	TButton *Button13;
	TButton *Button14;
	TButton *POVButton1;
	TButton *POVButton4;
	TButton *POVButton3;
	TButton *POVButton2;
	TButton *Button15;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ShutDownTimerTimer(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);

	private:	// User declarations
        int 						mJoyStickID;
    	ArrayBotJoyStick 	        mJS;


        void 				        onButton1Down();
        void 				        onButton1Up();
        void 				        onButton2Down();
        void 				        onButton2Up();
        void 				        onButton3Down();
        void 				        onButton3Up();
        void 				        onButton4Down();
        void 				        onButton4Up();
        void 				        onButton5Down();
        void 				        onButton5Up();
        void 				        onButton6Down();
        void 				        onButton6Up();
        void 				        onButton7Down();
        void 				        onButton7Up();
        void 				        onButton8Down();
        void 				        onButton8Up();
        void 				        onButton9Down();
        void 				        onButton9Up();
        void 				        onButton10Down();
        void 				        onButton10Up();
        void 				        onButton11Down();
        void 				        onButton11Up();
        void 				        onButton12Down();
        void 				        onButton12Up();
        void 				        onButton13Down();
        void 				        onButton13Up();
        void 				        onButton14Down();
        void 				        onButton14Up();

        void 				        onX1AxisMove(int pos);
        void 				        onY1AxisMove(int pos);

        void 				        onX2AxisMove(int pos);
        void 				        onY2AxisMove(int pos);

        void 				        onPOVButton1Down();
        void 				        onPOVButton1Up();
        void 				        onPOVButton2Down();
        void 				        onPOVButton2Up();
        void 				        onPOVButton3Down();
        void 				        onPOVButton3Up();
        void 				        onPOVButton4Down();
        void 				        onPOVButton4Up();

        TThreadMethod               logMsgMethod;
        LogFileReader               mLogFileReader;
        void __fastcall             logMsg();

	public:		// User declarations
		__fastcall TMain(TComponent* Owner);
};

extern PACKAGE TMain *Main;
//---------------------------------------------------------------------------
#endif
