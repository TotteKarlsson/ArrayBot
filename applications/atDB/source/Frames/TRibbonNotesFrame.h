#ifndef TRibbonNotesFrameH
#define TRibbonNotesFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>

//---------------------------------------------------------------------------
class TRibbonNotesFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TPanel *Panel15;
        TDBGrid *mRibbonNotesGrid;
        TDBNavigator *RibbonNotesNavigator;
        TPanel *Panel16;
        TDBMemo *mRibbonNoteMemo;
        TDBNavigator *RibbonNoteNavigator;
	TSQLDataSet *NotesForRibbonDS;
	TDataSource *DataSource1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *NotesForRibbonCDS;
	TIntegerField *NotesForRibbonDSid;
	TWideMemoField *NotesForRibbonDSnote;
	TSQLTimeStampField *NotesForRibbonDScreated_on;
	TIntegerField *NotesForRibbonDScreated_by;
	TIntegerField *NotesForRibbonCDSid;
	TWideMemoField *NotesForRibbonCDSnote;
	TSQLTimeStampField *NotesForRibbonCDScreated_on;
	TIntegerField *NotesForRibbonCDScreated_by;
	void __fastcall RibbonNotesNavigatorClick(TObject *Sender, TNavigateBtn Button);

    private:	// User declarations

    public:		// User declarations
	        		__fastcall 	TRibbonNotesFrame(TComponent* Owner);
        void 					populate(const string& ribbonID);
};
extern PACKAGE TRibbonNotesFrame *RibbonNotesFrame;
#endif
