#ifndef TAboutArrayBotFrameH
#define TAboutArrayBotFrameH
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
class PACKAGE TAboutArrayBotFrame : public TFrame
{
__published:	// IDE-managed Components
    TLabel *Label1;
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
	TImage *Image2;
    void __fastcall CloseAExecute(TObject *Sender);

    private:	// User declarations
        void                                            close();


    public:		// User declarations
                                            __fastcall  TAboutArrayBotFrame(TComponent* Owner);
        void                                            populate();
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutArrayBotFrame *AboutArrayBotFrame;
//---------------------------------------------------------------------------
#endif
