#ifndef TMLXAboutFormH
#define TMLXAboutFormH
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <StdCtrls.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <Windows.hpp>
#include <System.hpp>

#include "mtkURLLabel.h"
#include <ComCtrls.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <System.Actions.hpp>
#include "mtkApplicationLicenseController.h"
using mtk::ApplicationLicenseController;

//---------------------------------------------------------------------------
class PACKAGE TMLXAboutForm : public TForm
{
__published:
    TLabel *Label2;
    TPanel *Panel2;
    TMemo *verMemo;
    TLabel *Label5;
    TLabel *ProgramLabel;
    TmtkURLLabel *webUrl;
    TImageList *ImageList1;
    TActionList *ActionList1;
    TAction *GoHomeA;
    TStatusBar *StatusBar1;
    TImage *mImage;
    TImage *mCreditsImage;
    TLabel *ProdLicenseLbl;
    TMemo *licenseMemo;
    TLabel *expirationLabel;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall OKButtonClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall GoHomeAExecute(TObject *Sender);
    void __fastcall creditsButtonClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);

private:
    ApplicationLicenseController&       mLicenseController;

public:
                __fastcall              TMLXAboutForm(TComponent *Owner, ApplicationLicenseController& licenseController);
                __fastcall              ~TMLXAboutForm();


    unsigned                            mMainFormHandle;
};

extern PACKAGE TMLXAboutForm *MLXAboutForm;
#endif
