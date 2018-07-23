#ifndef TPrintLabelFormH
#define TPrintLabelFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTIntegerLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "labelprinter/atTSCLIB.h"
//---------------------------------------------------------------------------
class TPrintLabelForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *mLblToPrint;
	TIntegerLabeledEdit *mCopiesLbl;
	TButton *mPrintButton;
	TButton *Button1;
	void __fastcall mPrintButtonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);

private:
        //Label Printer
        TSCLIB	   			mLabelPrinter;

public:
		__fastcall 			TPrintLabelForm(TComponent* Owner);
		void __fastcall    	setup(const string& lbl);
};

extern PACKAGE TPrintLabelForm *PrintLabelForm;
#endif
