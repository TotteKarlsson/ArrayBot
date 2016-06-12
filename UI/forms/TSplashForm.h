#ifndef TSplashFormH
#define TSplashFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include "mtkTimer.h"
#include "mtkMessageContainer.h"
#include "dslTSplashMessageProcessor.h"
#include "TAboutAmalyticoFrame.h"
#include "SKGenerator.hpp"
using Poco::Timespan;
using mtk::MessageContainer;
//---------------------------------------------------------------------------
class PACKAGE TSplashForm : public TForm
{
	__published:	// IDE-managed Components
    TTimer *closeTimer;
    TLabel *logLabel;
    TLabel *Label1;
    TRegistrationFile *RegistrationFile1;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall closeTimerTimer(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Image2Click(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);

	private:
		void __fastcall                                     CreateParams(TCreateParams& Params);	// User declarations
		Poco::Timespan                                      mMinimumTimeShowing;
		bool                                                mCanClose;
		bool												mShownForAMinimumTime;

        MessageContainer                                    mLogMessages;
        SplashMessageProcessor                              mMessageProcessor;

	public:		// User declarations
										__fastcall          TSplashForm(TComponent* Owner);
										__fastcall          ~TSplashForm();
        bool                                                mMainAppIsRunning;

        mtk::Timer                                          mShowTimer;
        void                                                addLogMessage(const string& msg);
        void                            __fastcall          onWritingLogMessage();
        bool                                                isOnShowTime();
        void                                                setShowTime(int ms);
        TAboutAmalyticoFrame*                               mAFrame;
//        TRegistrationFile*                                  mRegistrationComponent;
	__published:

};
//---------------------------------------------------------------------------
//extern PACKAGE TSplashForm *SplashForm;

#endif
