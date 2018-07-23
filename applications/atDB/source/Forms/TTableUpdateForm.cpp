#include <vcl.h>
#pragma hdrstop
#include "TTableUpdateForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTableUpdateForm *TableUpdateForm;
//---------------------------------------------------------------------------
__fastcall TTableUpdateForm::TTableUpdateForm(TSQLConnection* c, TComponent* Owner)
	: TForm(Owner),
    mDBConnection(c)
{
	SQLDataSet1->SQLConnection = mDBConnection;
    SQLDataSet1->CommandText = "SELECT * FROM blockstatus ORDER by ID";
    DataSetProvider1->DataSet = SQLDataSet1;
    ClientDataSet1->ProviderName = DataSetProvider1->Name;
    DBGrid1->DataSource = DataSource1;
    DataSource1->DataSet = ClientDataSet1;
}

//---------------------------------------------------------------------------
void __fastcall TTableUpdateForm::FormShow(TObject *Sender)
{
	if(!mDBConnection || mDBConnection->Connected == false)
    {
    	MessageDlg("You need to conenct to remote ATDB database!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        return;
    }

	try
    {
	    SQLDataSet1->Active = true;
    	ClientDataSet1->Active = true;
    }
    catch(...)
    {}
}

//---------------------------------------------------------------------------
void __fastcall TTableUpdateForm::tableCBChange(TObject *Sender)
{
	String tableName = tableCB->Text;
	SQLDataSet1->Active = false;
    ClientDataSet1->Active = false;
    SQLDataSet1->CommandText = "SELECT * FROM " + tableName + " ORDER by ID";

	SQLDataSet1->Active = true;
    ClientDataSet1->Active = true;
    ClientDataSet1->Refresh();
}


void __fastcall TTableUpdateForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == vkEscape)
    {
    	Close();
    }
}
//---------------------------------------------------------------------------

