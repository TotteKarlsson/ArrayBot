#ifndef TMainFormH
#define TMainFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArrayBotBtn.h"
#include "TFFMPEGFrame.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include "dslLogFileReader.h"
#include <Vcl.ExtCtrls.hpp>
#include "dslLogLevel.h"
#include "dslIniFile.h"
#include "atVideoCompressorThread.h"
#include "dslTIntLabel.h"
#include <Vcl.FileCtrl.hpp>
#include "TSTDStringEdit.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.StdActns.hpp>
#include <list>
using dsl::IniFile;
using dsl::LogLevel;
using std::list;
class TFFMPEGOutputFrame;
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
    __published:	// IDE-managed Components
        TFFMPEGFrame *TFFMPEGFrame1;
	TArrayBotButton *CompressBtn;
	TMemo *infoMemo;
	TTimer *ShutDownTimer;
	TTimer *CleanupTimer;
	TFileListBox *FileListBox1;
	TGroupBox *GroupBox1;
	TSTDStringEdit *MovieFolder;
	TPanel *TopPanel;
	TFlowPanel *MPEGPanel;
	TPanel *Panel1;
	TButton *Button1;
	TActionList *ActionList1;
	TBrowseForFolder *BrowseForFolder1;
	void __fastcall ShutDownTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CompressBtnClick(TObject *Sender);
	void __fastcall CleanupTimerTimer(TObject *Sender);
	void __fastcall BrowseForFolder1Accept(TObject *Sender);

    private:	// User declarations
        LogFileReader                       mLogFileReader;
        LogLevel							mLogLevel;
        void __fastcall                     logMsg();
        IniFile						        mIniFile;
	    void __fastcall 	                onCompressionFinished(TFFMPEGOutputFrame* f);
        list<TFFMPEGOutputFrame*>			mCompressionFrames;
		bool						        isThisFileBeingCompressed(const string& fName);

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};

extern PACKAGE TMainForm *MainForm;
#endif
