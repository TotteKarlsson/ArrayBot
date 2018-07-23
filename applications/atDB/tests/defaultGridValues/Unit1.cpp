#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"


using namespace dsl;


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
extern bool gAppIsStartingUp;
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{

    bool connected = false;
	gAppIsStartingUp = false;
    try
    {
	    connected = atdbDM->connect("127.0.0.1", "atdb_client", "atdb123", "atdb");
	    atdbDM->afterConnect();
    }
    catch (const TDBXError &e)
	{
    	Log(lInfo) << "There was a database connection issue: "<<stdstr(e.Message);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DBNavigator1Click(TObject *Sender, TNavigateBtn Button)

{
	switch(Button)
    {
    	case nbInsert:
        {
                atdbDM->specimenCDS->FieldByName("specimen_id")->Value = "NEW SPECIMEN";
                atdbDM->specimenCDS->FieldByName("entered_by")->Value = 27;

        }
        break;
    }
}


