#ifndef TMainFormH
#define TMainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.OleCtrls.hpp>
#include "AXVLC_OCX.h"
#include "dslLogFileReader.h"
#include "dslLogLevel.h"
#include "THDMIStreamerFrame.h"
#include "TArrayBotBtn.h"

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TBitBtn *BitBtn1;
	TProgressBar *ProgressBar1;
	TMemo *infoMemo;
	TPanel *Panel2;
	TVLCPlugin2 *VLCPlugin21;
	TTimer *ShutDownTimer;
	THDMIStreamerFrame *THDMIStreamerFrame1;
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall VLCPlugin21MediaPlayerEncounteredError(TObject *Sender);
	void __fastcall VLCPlugin21MediaPlayerPlaying(TObject *Sender);
	void __fastcall VLCPlugin21MediaPlayerLengthChanged(TObject *Sender, long cache);
	void __fastcall VLCPlugin21MediaPlayerTimeChanged(TObject *Sender, long cache);
	void __fastcall ShutDownTimerTimer(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

private:	// User declarations
    LogFileReader                           mLogFileReader;
    dsl::LogLevel		            		mLogLevel;
    void __fastcall                         logMsg();


public:		// User declarations
	__fastcall 								TMainForm(TComponent* Owner);
	__fastcall 								~TMainForm();
};


extern PACKAGE TMainForm *MainForm;

#endif
