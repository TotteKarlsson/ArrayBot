#ifndef TMainH
#define TMainH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "abJoyStickEx.h"
#include "mtkLogFileReader.h"


//---------------------------------------------------------------------------



class TMain : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TMemo *infoMemo;
	TButton *Button1;
	TTimer *ShutDownTimer;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ShutDownTimerTimer(TObject *Sender);


	private:	// User declarations
		JoyStickEx 			mJS;
        void 				onButton1Down();
        void 				onButton1Up();


        TThreadMethod               logMsgMethod;
        LogFileReader               mLogFileReader;
        void __fastcall             logMsg();




	public:		// User declarations
		__fastcall TMain(TComponent* Owner);
};

extern PACKAGE TMain *Main;
//---------------------------------------------------------------------------
#endif
