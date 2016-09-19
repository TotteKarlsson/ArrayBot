#ifndef TAboutArduinoControllerFormH
#define TAboutArduinoControllerFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TAboutArduinoServerFrame.h"
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
//---------------------------------------------------------------------------

class PACKAGE TAboutArduinoControllerForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TButton *Button4;
    TActionList *ActionList1;
    TAction *checkForUpdateA;
    TAction *retrieveChangeLogA;
	TAboutArduinoServerFrame *TAboutArduinoServerFrame1;
	TLabel *Label1;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

private:	// User declarations
        bool                                            mStartCheckForChangeLogThread;
        TAboutArduinoServerFrame*                       mAboutFrame;

public:		// User declarations
    __fastcall TAboutArduinoControllerForm(TComponent* Owner);
};

extern PACKAGE TAboutArduinoControllerForm *AboutArduinoControllerForm;
#endif
