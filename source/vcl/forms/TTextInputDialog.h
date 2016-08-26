//---------------------------------------------------------------------------

#ifndef TTextInputDialogH
#define TTextInputDialogH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTextInputDialog : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
	TSTDStringLabeledEdit *STDStringLabeledEdit1;
private:	// User declarations
public:		// User declarations
	__fastcall TTextInputDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTextInputDialog *TextInputDialog;
//---------------------------------------------------------------------------
#endif
