#ifndef TATDBServerEntryH
#define TATDBServerEntryH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "abATDBServerSession.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TATDBServerEntry : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *mSubmitButton;
	TButton *mCancelBtn;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

	private:	// User declarations


    protected:
                ATDBServerSession&					mServerSession;
	public:		// User declarations
						__fastcall TATDBServerEntry(ATDBServerSession& dbs, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TATDBServerEntry *ATDBServerEntry;
//---------------------------------------------------------------------------
#endif
