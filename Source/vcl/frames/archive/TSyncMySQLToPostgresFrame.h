#ifndef TSyncMySQLToPostgresFrameH
#define TSyncMySQLToPostgresFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TSTDStringLabeledEdit.h"
#include <Vcl.CheckLst.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "atSyncMySQLDataToPostgres.h"
#include "dslIniFile.h"
#include "dslIniFileProperties.h"
//---------------------------------------------------------------------------
using dsl::IniFile;
using dsl::IniFileProperties;

class TSyncMySQLToPostgresFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TMemo *SyncLogMemo;
        TButton *SyncButton;
        TGroupBox *GroupBox2;
        TPanel *Panel1;
	TSTDStringLabeledEdit *SyncScriptFile;
	void __fastcall SyncButtonClick(TObject *Sender);

    private:
        SyncMySQLDataToPostgres		mSyncThread;
		IniFile*					mIniFile;
		IniFileProperties       	mProperties;

    public:
        				__fastcall TSyncMySQLToPostgresFrame(TComponent* Owner);
		bool			init(IniFile* inifile, const string& iniFileSection);
		bool 			writeParameters();
        void			setAppArguments(const string& args);
        bool			run();
        void			onStarted(int* a, int* b);
        void			onProgress(int* a, int* b);
        void			onFinished(int* a, int* b);
};

extern PACKAGE TSyncMySQLToPostgresFrame *SyncMySQLToPostgresFrame;

#endif
