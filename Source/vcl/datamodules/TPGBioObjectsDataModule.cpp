#pragma hdrstop
#include "TPGBioObjectsDataModule.h"
#include <sstream>
#include <iomanip>
#include "dslVCLUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
#pragma link "DbxDevartPostgreSQL"

TpgBioObjectsDM *pgBioObjectsDM;
using namespace dsl;
using namespace std;

//---------------------------------------------------------------------------
__fastcall TpgBioObjectsDM::TpgBioObjectsDM(TComponent* Owner)
	:
    TDataModule(Owner)
{
	if(SQLConnection1)
    {
  		SQLConnection1->Connected = false;
    }
}

__fastcall TpgBioObjectsDM::~TpgBioObjectsDM()
{}

bool TpgBioObjectsDM::isConnected()
{
	return SQLConnection1->Connected;
}
//---------------------------------------------------------------------------
void __fastcall TpgBioObjectsDM::SQLConnection1BeforeConnect(TObject *Sender)
{
    string h = stdstr(SQLConnection1->Params->Values[_D("HostName")]);
    string d = stdstr(SQLConnection1->Params->Values[_D("Database")]);
    string u = stdstr(SQLConnection1->Params->Values[_D("User_Name")]);
    string p = stdstr(SQLConnection1->Params->Values[_D("Password")]);
    mCredentials.setup(h,d,u,p);

	Log(lInfo) <<"Before connecting to SQL server:" <<d;
}

//---------------------------------------------------------------------------
void __fastcall TpgBioObjectsDM::SQLConnection1AfterConnect(TObject *Sender)
{
	try
    {
		afterConnect();
    }
    catch(TDBXError& e)
    {
    	Log(lError) << " Failed to connect...";
    }
}

void __fastcall TpgBioObjectsDM::afterConnect()
{
	Log(lInfo) << "Connection established to: "<< mCredentials.getHost();

	data_setCDS->Active 			= true;
    volumeCDS->Active 				= true;
    bioObjectCollectionCDS->Active 	= true;
    bioObjectCDS->Active 			= true;
}

//---------------------------------------------------------------------------
void __fastcall TpgBioObjectsDM::afterDisConnect()
{
	Log(lInfo) << "Closed connection to: "<<mCredentials.getHost();
}

//---------------------------------------------------------------------------
void __fastcall TpgBioObjectsDM::SQLConnection1AfterDisconnect(TObject *Sender)
{
	afterDisConnect();
}

//---------------------------------------------------------------------------
void __fastcall TpgBioObjectsDM::cdsAfterPost(TDataSet *DataSet)
{
	TClientDataSet* cds = dynamic_cast<TClientDataSet*>(DataSet);

    if(!cds)
    {
    	return;
    }
 	else
    {
    	Log(lDebug) << "Executing \"After post\" for Client Dataset: " << stdstr(DataSet->Name);
    }

	cds->ApplyUpdates(0);
    cds->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TpgBioObjectsDM::cdsbeforeDelete(TDataSet *DataSet)
{
	TClientDataSet* cds = dynamic_cast<TClientDataSet*>(DataSet);

    if(!cds)
    {
    	return;
    }
	Log(lInfo) << "Deleting..";
}


//---------------------------------------------------------------------------
void __fastcall TpgBioObjectsDM::cdsAfterDelete(TDataSet *DataSet)
{
	TClientDataSet* cds = dynamic_cast<TClientDataSet*>(DataSet);

    if(!cds)
    {
    	return;
    }

	cds->ApplyUpdates(0);
}

//---------------------------------------------------------------------------
void __fastcall TpgBioObjectsDM::cdsAfterScroll(TDataSet *DataSet)
{
	if(!SQLConnection1->Connected)// || gAppIsStartingUp)
    {
    	return;
    }

 	if(DataSet == volumeCDS)
    {
	    //specimenCDS->Refresh();
    	if(bioObjectCollectionCDS->Active)
        {
        	bioObjectCollectionCDS->Refresh();
        }
    }

 	if(DataSet == bioObjectCollectionCDS)
    {
		bioObjectCDS->Refresh();
    }
}

void __fastcall TpgBioObjectsDM::bioObjectCollectionCDSAfterRefresh(TDataSet *DataSet)
{
 	if(DataSet == volumeCDS)
    {
	    //specimenCDS->Refresh();
    	if(bioObjectCollectionCDS->Active)
        {
        	bioObjectCollectionCDS->Refresh();
        }
    }
}
void __fastcall TpgBioObjectsDM::cdsAfterRefresh(TDataSet *DataSet)
{
//	if(DataSet == slicesCDS)
//    {
//    	if(blocksCDS->Active)
//        {
//    		blocksCDS->Refresh();
//        }
//    }
}

//---------------------------------------------------------------------------
void __fastcall TpgBioObjectsDM::cdsBeforePost(TDataSet *DataSet)
{
//	if(DataSet == blocksCDS)
//    {
//		Log(lInfo) << "Before Posting Block Data";
//    }
//    else if(DataSet == ribbonsCDS)
//    {
//		Log(lInfo) << "Before Posting Ribbon Data";
//    }
}

//---------------------------------------------------------------------------
void __fastcall TpgBioObjectsDM::cdsBeforeRefresh(TDataSet *DataSet)
{
//	if(DataSet == slicesCDS)
//    {
//		slicesCDS->Active = false;
//		slicesCDS->Active = true;
//    }
}

//---------------------------------------------------------------------------
StringList TpgBioObjectsDM::getTableNames()
{
   if(!pgBioObjectsDM->SQLConnection1)
    {
        Log(lError) << "No SQL connection...";
        return StringList();
    }

    TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = pgBioObjectsDM->SQLConnection1;

    stringstream q;
    q <<"SELECT table_name \
		 FROM information_schema.tables \
         WHERE table_schema='public' \
         AND table_type='BASE TABLE' \
         ORDER BY 1" ;

    Log(lDebug) << "Get table names query: " <<q.str();

    tq->SQL->Add(q.str().c_str());
	tq->Open();
    int nrRows = tq->RecordCount;
	tq->First();

	StringList res;
    while(!tq->Eof)
    {
        string val = stdstr(tq->FieldByName("table_name")->AsString);
        res.append(val);
		tq->Next();
    }

    return res;
}

//---------------------------------------------------------------------------
void __fastcall TpgBioObjectsDM::bioObjectCDSBeforeRefresh(TDataSet *DataSet)

{
    Log(lInfo) << "Refreshing BioObject table";
}

//---------------------------------------------------------------------------
void __fastcall TpgBioObjectsDM::bioObjectCDSBeforeScroll(TDataSet *DataSet)

{
    Log(lInfo) << "Scrolling BioObject table";
}

//---------------------------------------------------------------------------
void __fastcall TpgBioObjectsDM::bioObjectCDSBeforeGetRecords(TObject *Sender,
          OleVariant &OwnerData)
{
    Log(lInfo) << "Before getting records";
}


