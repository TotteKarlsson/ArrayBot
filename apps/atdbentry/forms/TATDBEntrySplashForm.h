#ifndef TATDBEntrySplashFormH
#define TATDBEntrySplashFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include "dslTimer.h"
#include "dslMessageContainer.h"
#include "TAboutATDBEntryFrame.h"
#include "dslLogFileReader.h"
#include "TAboutATDBEntryFrame.h"

using Poco::Timespan;
using dsl::MessageContainer;
//---------------------------------------------------------------------------
class PACKAGE TArduinoControllerSplashForm : public TForm
{
	__published:	// IDE-managed Components
    TTimer *closeTimer;
    TLabel *Label1;
	TAboutATDBDataEntryFrame *TAboutATDBDataEntryFrame1;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall closeTimerTimer(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Image2Click(TObject *Sender);

	private:
		void __fastcall                                     CreateParams(TCreateParams& Params);	// User declarations
		Poco::Timespan                                      mMinimumTimeShowing;
		bool                                                mCanClose;
		bool												mShownForAMinimumTime;

        LogFileReader                   					mLogFileReader;
        void __fastcall                 					logMsg();

	public:		// User declarations
										__fastcall          TArduinoControllerSplashForm(TComponent* Owner);
										__fastcall          ~TArduinoControllerSplashForm();
        bool                                                mMainAppIsRunning;

        dsl::Timer                                          mShowTimer;
        bool                                                isOnShowTime();
        void                                                setShowTime(int ms);
        TAboutATDBDataEntryFrame*                          	mAFrame;
	__published:

};

#endif
