#ifndef TAboutAmalyticoFrameH
#define TAboutAmalyticoFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "SKGenerator.hpp"
#include "mtkApplicationLicenseController.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "mtkURLLabel.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "mtkGetRemoteTextFileDataThread.h"
#include "mtkVersion.h"
#include "mtkURLLabel.h"
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include<string>
using std::string;
using namespace mtk;
//---------------------------------------------------------------------------
class PACKAGE TAboutAmalyticoFrame : public TFrame
{
__published:	// IDE-managed Components
    TEdit *Edit5;
    TEdit *Edit4;
    TEdit *Edit3;
    TEdit *Edit1;
    TEdit *Edit2;
    TButton *SubmitKeyButton;
    TLabel *Label1;
    TLabel *ProdLicenseLbl;
    TLabel *expirationLabel;
    TLabel *versionLabel;
    TButton *UnlockBtn;
    TActionList *ActionList1;
    TAction *StartUnlockProcedureA;
    TAction *ValidateKeyAction;
    TAction *checkForUpdateA;
    TTimer *ThreadCheckTimer;
    TAction *retrieveChangeLogA;
    TAction *showLicenseTextA;
    TAction *showChangeLog;
    TAction *CloseA;
    TImage *Image1;
    void __fastcall StartUnlockProcedureAExecute(TObject *Sender);
    void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall ValidateKeyActionExecute(TObject *Sender);
    void __fastcall checkForUpdateAExecute(TObject *Sender);
    void __fastcall ThreadCheckTimerTimer(TObject *Sender);
    void __fastcall retrieveChangeLogAExecute(TObject *Sender);
    void __fastcall showLicenseText(TObject *Sender);
    void __fastcall showChangeLogExecute(TObject *Sender);
    void __fastcall CloseAExecute(TObject *Sender);

    private:	// User declarations
        bool                                            mIsUnlocking;
        bool                                            mStartCheckForChangeLogThread;
        mtk::ApplicationLicenseController&              mLC;
        Version                                         mRemoteVersion;
        TRegistrationFile*                              RegistrationFile1;
        GetRemoteTextFileDataThread                     mGetRemoteVersionThread;
        GetRemoteTextFileDataThread                     mGetNewestChangeLogThread;
        void                                            serialKeyEnteringObjectsVisible(bool setVisibility);

        void                                __fastcall  NotifyAboutUpdate(const string& data);
        void                                __fastcall  NotifyAboutChangeLog(const string& data);

                                                        //This is being repeated from the main form
        string                                          mRemoteDownloadURL;
        void                                            close();


    public:		// User declarations
                                            __fastcall  TAboutAmalyticoFrame(mtk::ApplicationLicenseController& lc, TRegistrationFile* RegistrationFile1, TComponent* Owner);
        void                                            populate();
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutAmalyticoFrame *AboutAmalyticoFrame;
//---------------------------------------------------------------------------
#endif
