#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "TArrayBotBtn.h"
#include "mtkLogFileReader.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *mInfoMemo;
	TTimer *mShutDownTimer;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall mShutDownTimerTimer(TObject *Sender);

private:	// User declarations
        LogFileReader                           mLogFileReader;
        void __fastcall                         logMsg();


public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};

extern PACKAGE TForm1 *Form1;
#endif
