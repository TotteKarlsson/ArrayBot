#ifndef TSQLiteDBFrameH
#define TSQLiteDBFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TIntLabel.h"
#include "TSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "mtkSQLite.h"
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
using mtk::SQLite;
class TSQLiteDBFrame : public TFrame
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TSTDStringLabeledEdit *DBNameE;
    TIntLabel *NrOfOrdersLbl;
    TLabel *Label1;
    TButton *Button1;
    void __fastcall Button1Click(TObject *Sender);

private:	// User declarations
    string                  mDBName;
    SQLite                  mDB;
	void                    updateFrame();

public:		// User declarations
                __fastcall  TSQLiteDBFrame(TComponent* Owner);
    void                    setDBName(const string& name);

};
//---------------------------------------------------------------------------
extern PACKAGE TSQLiteDBFrame *SQLiteDBFrame;
//---------------------------------------------------------------------------
#endif
