//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "DbxDevartSQLite.hpp"
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TSQLConnection *SQLConnection1;
	TDBGrid *DBGrid1;
	TDBGrid *DBGrid2;
	TDBNavigator *DBNavigator1;
	TDBGrid *DBGrid3;
	TSQLDataSet *images;
	TDataSetProvider *imagesProvider;
	TClientDataSet *imagesCDS;
	TDataSource *imagesDS;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *imageNoteCDS;
	TDataSource *image_note;
	TSQLQuery *imageNote;
	TSQLQuery *imageNotesQ;
	TDataSetProvider *DataSetProvider2;
	TClientDataSet *imageNotesCDS;
	TDataSource *imageNotes;
	TDBMemo *DBMemo1;
	TDBNavigator *DBNavigator2;
	void __fastcall imagesCDSAfterScroll(TDataSet *DataSet);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
