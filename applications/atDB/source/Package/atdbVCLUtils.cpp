#pragma hdrstop
#include "atdbVCLUtils.h"
#include "dslLogger.h"
#include "labelprinter/atTSCLIB.h"
#include "dslStringUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace dsl;

bool SortClientDataSet(TClientDataSet* ClientDataSet,  const String& FieldName)
{
	//from http://edn.embarcadero.com/article/29056
	TField* Field = ClientDataSet->Fields->FindField(FieldName);
	//If invalid field name, exit.
	if(!Field)
    {
		return false;
    }

    if(	dynamic_cast<TObjectField*>(Field) 		||		dynamic_cast<TBlobField*>(Field) 	||
        dynamic_cast<TAggregateField*>(Field) 	||      dynamic_cast<TVariantField*>(Field)	||
        dynamic_cast<TBinaryField*>(Field) 	)
    {
    	Log(lWarning) << "Can't sort this type of field...";
    	return false;
    }

    //Ensure IndexDefs is up-to-date
    ClientDataSet->IndexDefs->Update();

    //If an ascending index is already in use,
    //switch to a descending index
	String  		NewIndexName;
	TIndexOptions   IndexOptions;
    if(ClientDataSet->IndexName == (FieldName + "__IdxA"))
    {
        NewIndexName = FieldName + "__IdxD";
        IndexOptions = TIndexOptions() << ixDescending;
    }
    else
    {
        NewIndexName = FieldName + "__IdxA";
        IndexOptions = TIndexOptions();
    }

    //Look for existing index
    bool Result(false);
    for(int i = 0; i <ClientDataSet->IndexDefs->Count; i++)
    {
    	if( ClientDataSet->IndexDefs->operator [](i)->Name == NewIndexName)
      	{
        	Result = true;
          	break;
      	}
    }
    //If existing index not found, create one
    if(!Result)
    {
        ClientDataSet->AddIndex(NewIndexName, FieldName, IndexOptions);
        Result = True;
    }

    //Set the index
    ClientDataSet->IndexName = NewIndexName;
    return Result;
}

vector<int> getSelectedIDS(TDBGrid* grid, const string& field)
{
	vector<int> p_ids;
	TDataSet* ds = grid->DataSource->DataSet;

    for(int i = 0; i < grid->SelectedRows->Count; i++)
    {
        TBookmarkList* bookMarkList = grid->SelectedRows;
        if(bookMarkList->Count == grid->SelectedRows->Count)
        {
            ds->GotoBookmark((*bookMarkList)[i]);
            int pID = ds->FieldByName(field.c_str())->AsInteger;
            p_ids.push_back(pID);
        }
    }

	return p_ids;
}

int getLastInsertID(TSQLConnection* c)
{
	//Get last insert id, create and associate 'count' coverslips
    TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = c;

    tq->SQL->Add("SELECT LAST_INSERT_ID();");
    tq->Open();
    int id = tq->Fields->operator [](0)->AsInteger;
    tq->Close();
    delete tq;
    return id;
}

bool addNoteToMultipleCoverSlips(const vector<int>& csIDS, TSQLConnection* c, const string& note)
{
    TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = c;

    if(note.size() < 1)
    {
    	Log(lError) << "Can't add an empty note..";
        return false;
    }

	for(int i = 0; i < csIDS.size(); i++)
    {
		stringstream q;
        q<<"UPDATE coverslips set notes = concat('" << "\n\n" << note <<"', COALESCE(notes, '')) WHERE id='"<<csIDS[i]<< "';";
	    tq->SQL->Add(q.str().c_str());
    	tq->ExecSQL(true);
		Log(lInfo) << "Added note..";
		tq->SQL->Clear();
    }
    delete tq;
	return true;

}

bool createAndPrintCoverSlipLabels(BarcodePrintParameters& p, const vector<int>& csIDS, TSQLConnection* c)
{
    TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = c;
	TSCLIB lblPrinter;

    if(!lblPrinter.load("TSCLIB.dll"))
    {
    	Log(lError) << "Failed to load mTSC library..";
        return false;
    }

	for(int i = 0; i < csIDS.size(); i++)
    {
//	    tq->SQL->Text = ("SELECT * FROM coverslips WHERE id='" + IntToStr(csIDS[i]) + "';").c_str();
//    	tq->Open();
	    stringstream lbl;
        lbl <<"C"													//Barcode type: == coverslip
//        	<<"B"<<tq->FieldByName("freshCSBatch")->AsInteger   	//'Fresh' batch #
//        	<<"C"<<tq->FieldByName("cleanCSBatch")->AsInteger       //'Clean batch' #
//           	<<"C"<<tq->FieldByName("carboncoatbatch")->AsInteger    //'Carbon batch'
            <<createZeroPaddedString(7,csIDS[i]);                                        //'CS ID'

		Log(lInfo) << "Printing label: "<<lbl.str();
        lblPrinter.printCoverSlipLabel(p, lbl.str(), 1);
    }

	return true;
}
