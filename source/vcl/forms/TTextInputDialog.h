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
class PACKAGE TTextInputDialog : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *mCancelBtn;
	TButton *mOkBtn;
	TMemo *mInfoMemo;
	void __fastcall mInfoMemoChange(TObject *Sender);
	void __fastcall mInfoMemoClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall mInfoMemoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:	// User declarations

public:		// User declarations
				__fastcall 	TTextInputDialog(TComponent* Owner);
	string 					getText();
	void					setText(const string& txt);
    bool					mProcessReturn;
};

//---------------------------------------------------------------------------
extern PACKAGE TTextInputDialog *TextInputDialog;
//---------------------------------------------------------------------------
#endif
