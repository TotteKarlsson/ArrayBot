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
#include "dslLogLevel.h"

//---------------------------------------------------------------------------
class PACKAGE TLoggerForm : public TRegistryForm
{
    friend class TMainForm;
    __published:	// IDE-managed Components
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TToolBar *ToolBar1;
        TBitBtn *mClearLogMemoBtn;
        TComboBox *LogLevelCB;
        TMemo *infoMemo;
	TTimer *ShutDownTimer;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ShutDownTimerTimer(TObject *Sender);
	void __fastcall mClearLogMemoBtnClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall LogLevelCBCloseUp(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


    protected:
        LogFileReader                           mLogFileReader;
		dsl::LogLevel		            		mLogLevel;
        void __fastcall                         logMsg();
		void __fastcall 						LogLevelCBChange(TObject *Sender);

    public:
        						__fastcall 		TLoggerForm(const string& regRoot, TComponent* Owner);
        						__fastcall 		~TLoggerForm();
};

extern PACKAGE TLoggerForm *LoggerForm;

#endif
