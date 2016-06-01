#ifndef Unit1H
#define Unit1H
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "abJoyStickEx.h"
//---------------------------------------------------------------------------



class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


	private:	// User declarations
		JoyStickEx 			mJS;

	public:		// User declarations
		__fastcall TForm1(TComponent* Owner);
};

extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
