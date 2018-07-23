#ifndef TLoggerFormH
#define TLoggerFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include "forms/dslTRegistryForm.h"
#include "dslLogFileReader.h"

#include "dslTLogMemoFrame.h"

//---------------------------------------------------------------------------
class PACKAGE TLoggerForm : public TRegistryForm
{
    __published:
	TTimer *ShutDownTimer;
	TLogMemoFrame *TLogMemoFrame1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ShutDownTimerTimer(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

    protected:

    public:
        						__fastcall 		TLoggerForm(const string& regRoot, TComponent* Owner);
        						__fastcall 		~TLoggerForm();
};

extern PACKAGE TLoggerForm *LoggerForm;

#endif
