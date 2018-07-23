#pragma hdrstop
#include "TLoggerForm.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTLogMemoFrame"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TLoggerForm *LoggerForm;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TLoggerForm::TLoggerForm(const string& regRoot, TComponent* Owner)
	:
TRegistryForm(regRoot, "LoggerForm", Owner)
{
	Log(lInfo) << "Starting logfile reader";
    TLogMemoFrame1->init();
}

__fastcall TLoggerForm::~TLoggerForm()
{}

void __fastcall TLoggerForm::FormShow(TObject *Sender)
{
    TLogMemoFrame1->init();
	readRegistry();
}

//---------------------------------------------------------------------------
void __fastcall TLoggerForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Log(lInfo) << "In FormClose";
    TRegistryForm::FormClose(Sender, Action);
}

//---------------------------------------------------------------------------
void __fastcall TLoggerForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = true;
}

//---------------------------------------------------------------------------
void __fastcall TLoggerForm::ShutDownTimerTimer(TObject *Sender)
{
    ShutDownTimer->Enabled = false;
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TLoggerForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}
