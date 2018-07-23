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
#include <Vcl.DBCtrls.hpp>
#include "TATDBConnectionFrame.h"
#include "TATDBDataModule.h"
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.MPlayer.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <list>
#include "dslStringList.h"


using dsl::IniFile;
using dsl::LogLevel;
using std::list;
using dsl::StringList;
class TFFMPEGOutputFrame;
class TMovieItemFrame;

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
    __published:	// IDE-managed Components
	TMemo *infoMemo;
	TTimer *ShutDownTimer;
	TGroupBox *GroupBox1;
	TSTDStringEdit *MovieFolder;
	TPanel *TopPanel;
	TPanel *Panel1;
	TButton *Button1;
	TActionList *ActionList1;
	TBrowseForFolder *BrowseForFolder1;
	TATDBConnectionFrame *TATDBConnectionFrame1;
	TGroupBox *Panel2;
	TButton *Button2;
	TDBNavigator *DBNavigator1;
	TDBLookupListBox *DBLookupListBox1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet2;
	TFlowPanel *FlowPanel1;
	TScrollBox *ScrollBox1;
	TSQLQuery *SQLQuery1;
	TTimer *RefreshUITimer;
	TPanel *Panel3;
	TLabel *Label1;
	TIntLabel *NrOfRecordsLbl;
	void __fastcall ShutDownTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BrowseForFolder1Accept(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall RefreshUITimerTimer(TObject *Sender);
	void __fastcall DBLookupListBox1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall DBLookupListBox1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall DBLookupListBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBLookupListBox1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);



    private:	// User declarations
        LogFileReader                    		mLogFileReader;
        LogLevel							    mLogLevel;
        void __fastcall                         logMsg();
        IniFile						            mIniFile;
		list<TMovieItemFrame*>                  mMovies;
   		void 									populateMovieFrames(const StringList& l);
		void 									clearMovieFrames();

		StringList								fetchRecords();
	public:		// User declarations
					__fastcall 					TMainForm(TComponent* Owner);
		void       	__fastcall					afterDBServerConnect(System::TObject* Sender);
		void       	__fastcall					afterDBServerDisconnect(System::TObject* Sender);

};

extern PACKAGE TMainForm *MainForm;
#endif
