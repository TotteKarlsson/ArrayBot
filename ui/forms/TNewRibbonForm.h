//---------------------------------------------------------------------------

#ifndef TNewRibbonFormH
#define TNewRibbonFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TNewRibbonForm : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

private:	// User declarations
public:		// User declarations
	__fastcall TNewRibbonForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNewRibbonForm *NewRibbonForm;
//---------------------------------------------------------------------------
#endif
