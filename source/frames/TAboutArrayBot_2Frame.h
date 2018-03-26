#ifndef TAboutArrayBot_2FrameH
#define TAboutArrayBot_2FrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslApplicationLicenseController.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "dslGetRemoteTextFileDataThread.h"
#include "dslVersion.h"
#include "dslTURLLabel.h"
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Graphics.hpp>
#include<string>
using std::string;
using namespace dsl;

//---------------------------------------------------------------------------
class PACKAGE TAboutArrayBotFrame_2 : public TFrame
{
__published:	// IDE-managed Components
	TLabel *AppNameLabel;
    TLabel *versionLabel;
    TActionList *ActionList1;
    TAction *StartUnlockProcedureA;
    TAction *ValidateKeyAction;
    TAction *checkForUpdateA;
    TAction *retrieveChangeLogA;
    TAction *showLicenseTextA;
    TAction *showChangeLog;
    TAction *CloseA;
    TImage *Image1;
	TLabel *logLabel;
	TMemo *Memo1;
	TGroupBox *GroupBox1;
	TPanel *Panel1;
    void __fastcall CloseAExecute(TObject *Sender);

    private:	// User declarations
        void                                            close();


    public:		// User declarations
                                            __fastcall  TAboutArrayBotFrame_2(TComponent* Owner);
        void                                            populate();
};


extern PACKAGE TAboutArrayBotFrame_2 *AboutArrayBotFrame_2;
#endif
