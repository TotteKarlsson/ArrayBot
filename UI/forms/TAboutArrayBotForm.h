#ifndef TAboutArrayBotFormH
#define TAboutArrayBotFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TAboutArrayBotFrame.h"
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
//---------------------------------------------------------------------------

class PACKAGE TAboutArrayBotForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TButton *Button3;
    TButton *Button4;
    TActionList *ActionList1;
    TAction *checkForUpdateA;
    TAction *retrieveChangeLogA;
	TAboutArrayBotFrame *TAboutArrayBotFrame1;
	TLabel *Label1;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

private:	// User declarations
        bool                                            mStartCheckForChangeLogThread;
        TAboutArrayBotFrame*                           	mAboutFrame;

public:		// User declarations
    __fastcall TAboutArrayBotForm(TComponent* Owner);
};

extern PACKAGE TAboutArrayBotForm *AboutArrayBotForm;
#endif
