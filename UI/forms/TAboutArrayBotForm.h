#ifndef TAboutArrayBotFormH
#define TAboutArrayBotFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TAboutArrayBotFrame.h"
#include "mtkApplicationLicenseController.h"
#include "mtkVersion.h"
#include "mtkGetRemoteTextFileDataThread.h"
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
//---------------------------------------------------------------------------

class PACKAGE TAboutArrayBotForm : public TForm
{
__published:	// IDE-managed Components
    TAboutArrayBotFrame *TAboutArrayBotFrame1;
    TPanel *Panel1;
    TButton *Button3;
    TButton *Button4;
    TActionList *ActionList1;
    TAction *checkForUpdateA;
    TAction *retrieveChangeLogA;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall checkForUpdateAExecute(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall retrieveChangeLogAExecute(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

private:	// User declarations
        bool                                            mStartCheckForChangeLogThread;
        Version                                         mRemoteVersion;
        TAboutArrayBotFrame*                           	mAboutFrame;
        GetRemoteTextFileDataThread                     mGetRemoteVersionThread;
        GetRemoteTextFileDataThread                     mGetNewestChangeLogThread;
        string                                          mRemoteDownloadURL;

        void                                __fastcall  NotifyAboutUpdate(const string& data);
        void                                __fastcall  NotifyAboutChangeLog(const string& data);

public:		// User declarations
    __fastcall TAboutArrayBotForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutArrayBotForm *AboutArrayBotForm;
//---------------------------------------------------------------------------
#endif
