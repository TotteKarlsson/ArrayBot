#ifndef TStringInputDialogH
#define TStringInputDialogH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TStringInputDialog : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *Button1;
	TButton *mOkBtn;
	TSTDStringLabeledEdit *STDStringLabeledEdit1;
	void __fastcall STDStringLabeledEdit1Change(TObject *Sender);
	void __fastcall STDStringLabeledEdit1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall STDStringLabeledEdit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations

public:		// User declarations
				__fastcall 	TStringInputDialog(TComponent* Owner);
	string 					getText();
	void					setText(const string& txt);
};

//---------------------------------------------------------------------------
extern PACKAGE TStringInputDialog *StringInputDialog;
//---------------------------------------------------------------------------
#endif
