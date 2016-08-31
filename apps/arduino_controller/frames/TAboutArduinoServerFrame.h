#ifndef TAboutArduinoServerFrameH
#define TAboutArduinoServerFrameH
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
class PACKAGE TAboutArduinoServerFrame : public TFrame
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *versionLabel;
    TActionList *ActionList1;
    TTimer *ThreadCheckTimer;
    TAction *CloseA;
    TImage *Image1;
	TLabel *logLabel;
	TMemo *mChangeLogMemo;
    void __fastcall CloseAExecute(TObject *Sender);

    private:	// User declarations
                                                        //This is being repeated from the main form
        void                                            close();


    public:		// User declarations
                                            __fastcall  TAboutArduinoServerFrame(TComponent* Owner);
        void                                            populate();
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutArduinoServerFrame *AboutArduinoServerFrame;
//---------------------------------------------------------------------------
#endif
