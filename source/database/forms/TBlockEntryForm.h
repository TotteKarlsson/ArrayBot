#ifndef TBlockEntryFormH
#define TBlockEntryFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TATDBServerEntry.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TBlockEntryForm : public TATDBServerEntry
{
__published:	// IDE-managed Components
	TLabeledEdit *mBlockLabel;
	TLabeledEdit *mBlockNote;
	TComboBox *mUserCB;
	TLabel *Label1;
	void __fastcall FormShow(TObject *Sender);

    private:	// User declarations


    public:		// User declarations
        				__fastcall TBlockEntryForm(ATDBServerSession& dbs, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBlockEntryForm *BlockEntryForm;
//---------------------------------------------------------------------------
#endif
