#ifndef TAboutATDBEntryH
#define TAboutATDBEntryH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "TAboutATDBEntryFrame.h"
//---------------------------------------------------------------------------

class PACKAGE TAboutATDBEntry : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TButton *Button4;
    TActionList *ActionList1;
    TAction *checkForUpdateA;
    TAction *retrieveChangeLogA;
	TAboutATDBDataEntryFrame *TAboutATDBDataEntryFrame1;
	TLabel *Label1;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

private:	// User declarations
        bool                                            mStartCheckForChangeLogThread;
        TAboutATDBDataEntryFrame*                       mAboutFrame;

public:		// User declarations
    __fastcall TAboutATDBEntry(TComponent* Owner);
};

extern PACKAGE TAboutATDBEntry *AboutATDBEntry;
#endif
