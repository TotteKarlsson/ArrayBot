#ifndef TAboutArrayBot_2FrameH
#define TAboutArrayBot_2FrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
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
#include <Vcl.Graphics.hpp>
#include<string>
using std::string;
using namespace mtk;
//---------------------------------------------------------------------------
class PACKAGE TAboutArrayBotFrame_2 : public TFrame
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *versionLabel;
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
	TLabel *logLabel;
	TMemo *Memo1;
	TGroupBox *GroupBox1;
	TPanel *Panel1;
    void __fastcall checkForUpdateAExecute(TObject *Sender);
    void __fastcall ThreadCheckTimerTimer(TObject *Sender);
    void __fastcall retrieveChangeLogAExecute(TObject *Sender);
    void __fastcall showChangeLogExecute(TObject *Sender);
    void __fastcall CloseAExecute(TObject *Sender);

    private:	// User declarations
        bool                                            mStartCheckForChangeLogThread;
        Version                                         mRemoteVersion;
        GetRemoteTextFileDataThread                     mGetRemoteVersionThread;
        GetRemoteTextFileDataThread                     mGetNewestChangeLogThread;

        void                                __fastcall  NotifyAboutUpdate(const string& data);
        void                                __fastcall  NotifyAboutChangeLog(const string& data);

                                                        //This is being repeated from the main form
        string                                          mRemoteDownloadURL;
        void                                            close();


    public:		// User declarations
                                            __fastcall  TAboutArrayBotFrame_2(TComponent* Owner);
        void                                            populate();
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutArrayBotFrame_2 *AboutArrayBotFrame_2;
//---------------------------------------------------------------------------
#endif
