#pragma hdrstop
#include "TPGDataModule.h"
#include <sstream>
#include <iomanip>
#include "dslVCLUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
#pragma link "DbxDevartPostgreSQL"

TpgDM *pgDM;
using namespace dsl;
using namespace std;

//---------------------------------------------------------------------------
__fastcall TpgDM::TpgDM(TComponent* Owner)
	:
    TDataModule(Owner)
{
	if(SQLConnection1)
    {
  		SQLConnection1->Connected = false;
    }
}

__fastcall TpgDM::~TpgDM()
{}

bool __fastcall TpgDM::connect(const DBCredentials& c)
{
    try    //todo, move this try/catch to higher level)
    {
	    mCredentials = c;
        SQLConnection1->KeepConnection = true;
        SQLConnection1->Connected = false;
        SQLConnection1->Params->Values[_D("HostName")] = vclstr(c.getHost());
        SQLConnection1->Params->Values[_D("Database")] = vclstr(c.getDB());
        SQLConnection1->Params->Values[_D("User_Name")] = vclstr(c.getUserName());
        SQLConnection1->Params->Values[_D("Password")] = vclstr(c.getUserPassword());

        Log(lInfo) <<"Trying to connect to SQL server using parameters:\t"<<
                    "Host="		<<stdstr(SQLConnection1->Params->Values[_D("HostName")])<<"\t"<<
                    "UserNamet="<<stdstr(SQLConnection1->Params->Values[_D("User_Name")])<<"\t"<<
                    "Password="	<<stdstr(SQLConnection1->Params->Values[_D("Password")])<<"\t"<<
                    "Database="	<<stdstr(SQLConnection1->Params->Values[_D("Database")]);

        SQLConnection1->AutoClone      = false;
        SQLConnection1->KeepConnection = true;
        SQLConnection1->Connected = true;
        return SQLConnection1->Connected;
    }
    catch(const TDBXError& e)
    {
    	Log(lWarning) << stdstr(e.Message);
        return false;
    }
}

//---------------------------------------------------------------------------
bool __fastcall TpgDM::connect(const string& host, const string& db, const string& user, const string& pwd)
{
    return connect(DBCredentials(host, db, user, pwd));
}

bool TpgDM::isConnected()
{
	return SQLConnection1->Connected;
}
//---------------------------------------------------------------------------
void __fastcall TpgDM::SQLConnection1BeforeConnect(TObject *Sender)
{
	Log(lInfo) <<"Trying to connect to SQL server:" <<stdstr(SQLConnection1->Params->Values[_D("Database")]);
}

//---------------------------------------------------------------------------
void __fastcall TpgDM::SQLConnection1AfterConnect(TObject *Sender)
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

void __fastcall TpgDM::afterConnect()
{
	Log(lInfo) << "Connection established to: "<< mCredentials.getHost();
	usersCDS->Active 	    = true;
	specimenCDS->Active 	= true;
	slicesCDS->Active  		= true;
    blocksCDS->Active 	    = true;
    blockIDSCDS->Active     = true;
    ribbonsCDS->Active 	    = true;
    notesCDS->Active   	    = true;
	blockNotesCDS->Active  	= true;
    ribbonNotesCDS->Active  = true;
    settingsCDS->Active  	= true;
    knifesCDS->Active  		= true;
	knifeNotesCDS->Active 	= true;
	allBlocksCDS->Active 	= true;
}

//---------------------------------------------------------------------------
void __fastcall TpgDM::afterDisConnect()
{
	Log(lInfo) << "Closed connection to: "<<mCredentials.getHost();
  	usersCDS->Active 	    = false;
	specimenCDS->Active 	= false;
	slicesCDS->Active  		= false;
    blocksCDS->Active 	    = false;
    blockIDSCDS->Active     = false;
    notesCDS->Active	    = false;
	blockNotesCDS->Active  	= false;
    ribbonNotesCDS->Active  = false;
    settingsCDS->Active  	= false;
    knifesCDS->Active  		= false;
	knifeNotesCDS->Active 	= false;
	allBlocksCDS->Active 	= false;
}

//---------------------------------------------------------------------------
void __fastcall TpgDM::SQLConnection1AfterDisconnect(TObject *Sender)
{
	afterDisConnect();
}

//---------------------------------------------------------------------------
void __fastcall TpgDM::cdsAfterPost(TDataSet *DataSet)
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
void __fastcall TpgDM::cdsbeforeDelete(TDataSet *DataSet)
{
	TClientDataSet* cds = dynamic_cast<TClientDataSet*>(DataSet);

    if(!cds)
    {
    	return;
    }
	Log(lInfo) << "Deleting..";
}


//---------------------------------------------------------------------------
void __fastcall TpgDM::cdsAfterDelete(TDataSet *DataSet)
{
	TClientDataSet* cds = dynamic_cast<TClientDataSet*>(DataSet);

    if(!cds)
    {
    	return;
    }

	cds->ApplyUpdates(0);
}

//---------------------------------------------------------------------------
void __fastcall TpgDM::cdsAfterScroll(TDataSet *DataSet)
{
	if(!SQLConnection1->Connected)// || gAppIsStartingUp)
    {
    	return;
    }

 	if(DataSet == specimenCDS)
    {
	    //specimenCDS->Refresh();
    	if(slicesCDS->Active)
        {
        	slicesCDS->Refresh();
        }
    }

 	if(DataSet == slicesCDS)
    {
    	if(blocksCDS->Active)
        {
        	blocksCDS->Refresh();
        }
    }

 	if(DataSet == blocksCDS)
    {
        int bID = blocksCDS->FieldByName("id")->AsInteger;
        if(bID == -1)
        {
            blockNotesCDS->Active = false;
            ribbonsCDS->Active = false;
        }
        else
        {
            blockNotesCDS->Active = true;
            ribbonsCDS->Active = true;
        }
        cdsAfterRefresh(blocksCDS);
    }

 	if(DataSet == allBlocksCDS)
    {
        int bID = blocksCDS->FieldByName("id")->AsInteger;
        if(bID == -1)
        {
            blockNotesCDS->Active = false;
            ribbonsCDS->Active = false;
        }
        else
        {
            blockNotesCDS->Active = true;
            ribbonsCDS->Active = true;
        }
        cdsAfterRefresh(allBlocksCDS);
    }

	if(DataSet == ribbonsCDS)
    {
        String rID = ribbonsCDS->FieldByName("id")->AsString;
        if(rID == "")
        {
            ribbonNotesCDS->Active = false;
        }
        else
        {
            ribbonNotesCDS->Active = true;

        }
        cdsAfterRefresh(ribbonsCDS);
    }

	if(DataSet == knifesCDS)
    {
        int id = knifesCDS->FieldByName("id")->AsInteger;
        if(id == -1)
        {
            knifeNotesCDS->Active = false;
        }
        else
        {
            knifeNotesCDS->Active = true;

        }
        cdsAfterRefresh(knifesCDS);
    }
}

void __fastcall TpgDM::cdsAfterRefresh(TDataSet *DataSet)
{
	if(DataSet == slicesCDS)
    {
    	if(blocksCDS->Active)
        {
    		blocksCDS->Refresh();
        }
    }

	else if(DataSet == blocksCDS)
    {
    	if(ribbonsCDS->Active)
        {
    		ribbonsCDS->Refresh();
        }

        if(blockNotesCDS->Active)
        {
			blockNotesCDS->Refresh();
        }
    }
	else if(DataSet == allBlocksCDS)
    {
    	if(ribbonsCDS->Active)
        {
    		ribbonsCDS->Refresh();
        }

        if(blockNotesCDS->Active)
        {
			blockNotesCDS->Refresh();
        }
    }

    else if(DataSet == ribbonsCDS)
    {
    	if(ribbonNotesCDS->Active)
        {
        	ribbonNotesCDS->Refresh();
        }
    }

	else if(DataSet == knifesCDS)
    {
        if(knifeNotesCDS->Active)
        {
			knifeNotesCDS->Refresh();
        }
    }

//    else if(DataSet == blockIDSCDS)
//    {
//    	if(MoviesByBlockIDCDS->Active)
//        {
//        	MoviesByBlockIDCDS->Refresh();
//        }
//    }

}

//---------------------------------------------------------------------------
void __fastcall TpgDM::cdsBeforePost(TDataSet *DataSet)
{
	if(DataSet == blocksCDS)
    {
		Log(lInfo) << "Before Posting Block Data";
    }
    else if(DataSet == ribbonsCDS)
    {
		Log(lInfo) << "Before Posting Ribbon Data";
    }
}

//---------------------------------------------------------------------------
void __fastcall TpgDM::ribbonsCDSCalcFields(TDataSet *DataSet)
{
	//Generate barcode as being composed of
	//    	block_id: first 5 digits
    //		ribbon_id: next 7 digits
//	TField* field = blocksCDS->FieldByName("id");
//	if(field)
//	{
//		TField* f = ribbonsCDS->FieldByName("id");
//		if(f)
//		{
//			stringstream s;
//			s << zeroPadRight(blocksCDS->FieldByName("id")->AsInteger,   4);
//			string str = s.str();
//            s << zeroPadLeft(ribbonsCDS->FieldByName("id")->AsInteger, 5);
//            str = s.str();
//			f->Value = toLong(str);
//		}
//	}
}

//---------------------------------------------------------------------------
void __fastcall TpgDM::fixativeTBLAfterPost(TDataSet *DataSet)
{
	fixativeTBL->ApplyUpdates(0);
    slicesCDS->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TpgDM::blocksCDSCalcFields(TDataSet *DataSet)
{
	//Generate barcode as being composed of
	TField* field = blocksCDS->FieldByName("id");
	if(field)
	{
		TField* f = blocksCDS->FieldByName("Cblock_label");
		if(f)
		{
        	stringstream s;

            //Capture date with no time
            StringList d(stdstr(blocksCDS->FieldByName("entered_on")->AsString), ' ');
//            if(d.size())
//            {
//	            s << stdstr(d[0]) <<"\n";
//            }

            s << stdstr(blocksCDS->FieldByName("label")->AsString);
            s <<"\n";

			f->Value = String(s.str().c_str());
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TpgDM::blocksCDSblockLabelGetText(TField *Sender, UnicodeString &Text, bool DisplayText)
{
	Text = "Test";
}

//---------------------------------------------------------------------------
void __fastcall TpgDM::TimeStampGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
//	TField* field = dynamic_cast<TField*>(Sender);
//
//	if(field == blocksCDScreated)
//	{
//		StringList d(stdstr(blocksCDScreated->AsString), ' ');
//        if(d.size())
//        {
//			Text = vclstr(d[0]);
//        }
//	}
//    else if	(field == ribbonsCDScreated)
//	{
//		StringList d(stdstr(ribbonsCDScreated->AsString), ' ');
//        if(d.size())
//        {
//			Text = vclstr(d[0]);
//        }
//	}
}
//---------------------------------------------------------------------------
void __fastcall TpgDM::cdsBeforeRefresh(TDataSet *DataSet)
{
//	if(DataSet == slicesCDS)
//    {
//		slicesCDS->Active = false;
//		slicesCDS->Active = true;
//    }
}

//---------------------------------------------------------------------------
void __fastcall TpgDM::slicesCDSBeforeClose(TDataSet *DataSet)
{
    //delete runtime indices
    Log(lDebug) << "Closing dataset";
}

//---------------------------------------------------------------------------
void __fastcall TpgDM::slicesCDSAfterClose(TDataSet *DataSet)
{
    Log(lDebug) << "Closing dataset";
}

//---------------------------------------------------------------------------
void __fastcall TpgDM::slicesCDSAfterOpen(TDataSet *DataSet)
{
    Log(lDebug) << "After Open";
}

int	__fastcall TpgDM::getCurrentBlockID()
{
	if(blocksCDS->Active)
    {
    	try
        {
	    	return blocksCDS->FieldByName("id")->Text.ToInt();
        }
        catch(...)
        {
         	return -1;
        }

    }
   	return -1;
}

int	__fastcall TpgDM::getCurrentBlockIDFromAllBlocks()
{
	if(allBlocksCDS->Active)
    {
    	try
        {
	    	return allBlocksCDS->FieldByName("id")->Text.ToInt();
        }
        catch(...)
        {
         	return -1;
        }

    }
   	return -1;
}


int __fastcall TpgDM::getIDForSpecie(const string& specie)
{
	if(speciesDS->Active)
    {
    	//TODO: use smart pointer
    	TSQLQuery *q = new TSQLQuery(NULL);
        q->SQLConnection = SQLConnection1;
        q->SQL->Add("SELECT id FROM species WHERE name = '" + String(specie.c_str()) + "'");
		q->Open();

        if(q->Fields->Count)
        {
        	int id = (*q->Fields)[0]->AsInteger;
            return id;
        }
    }

    return -1;
}

//---------------------------------------------------------------------------
String __fastcall TpgDM::createBlockLabel()
{
    String lbl;
    String specie = pgDM->specimenCDS->FieldByName("Lspecie")->AsString;
	if(specie == "Human")
    {
    	lbl = "H";
    }
    else if(specie == "Mouse")
    {
    	lbl = "M";
    }
    else if(specie == "Human Surgical")
    {
    	lbl = "HS";
    }

	lbl = lbl + pgDM->specimenCDS->FieldByName("animal_id")->AsString + "-" + (pgDM->blocksCDS->RecordCount + 1);
	return lbl;
}

bool __fastcall	TpgDM::insertBlockNote(int userID, int blockID, const string& note)
{
    try
    {
        //Query DB and show some info
        TSQLQuery* tq = new TSQLQuery(NULL);
        tq->SQLConnection = pgDM->SQLConnection1;

        stringstream q;
        q <<"INSERT INTO notes (created_by, note) VAlUES(" << userID << ",'" << note <<"')";
        Log(lDebug) << "Q: " <<q.str();
        tq->SQL->Add(q.str().c_str());
        tq->ExecSQL();
        q.str("");

        tq->SQL->Clear();
        q << "SELECT MAX(id) FROM notes";
        tq->SQL->Add(q.str().c_str());
        tq->Open();
        q.str("");

        if(tq->Fields->Count)
        {
            int note_id = tq->Fields->FieldByNumber(1)->AsInteger;
            tq->SQL->Clear();
            q << "INSERT INTO block_note (block_id, note_id) VALUES("<<blockID<<","<<note_id <<")";
            tq->SQL->Add(q.str().c_str());
            tq->ExecSQL();
        }

        delete tq;

    	pgDM->blockNotesCDS->Refresh();
	    pgDM->blockNotesCDS->Last();
        return true;
    }
    catch(...)
    {
        Log(lError) << "There was a DB exception..";
        //handleMySQLException();
        return false;
    }
}

bool __fastcall	TpgDM::insertRibbonNote(int userID, const string& ribbonID, const string& note)
{
    try
    {
        //Query DB and show some info
        TSQLQuery* tq = new TSQLQuery(NULL);
        tq->SQLConnection = pgDM->SQLConnection1;

        stringstream q;
        q <<"INSERT INTO notes (created_by, note) VAlUES(" << userID << ",'" << note <<"')";
        Log(lDebug) << "Q: " <<q.str();
        tq->SQL->Add(q.str().c_str());
        tq->ExecSQL();
        q.str("");

        tq->SQL->Clear();
        q << "SELECT MAX(id) FROM notes";
        tq->SQL->Add(q.str().c_str());
        tq->Open();
        q.str("");

        if(tq->Fields->Count)
        {
            int note_id = tq->Fields->FieldByNumber(1)->AsInteger;
            tq->SQL->Clear();
            q << "INSERT INTO ribbon_note (ribbon_id, note_id) VALUES('"<<ribbonID<<"',"<<note_id <<")";
            tq->SQL->Add(q.str().c_str());
            tq->ExecSQL();
        }
	    pgDM->ribbonNotesCDS->Refresh();
    	pgDM->ribbonNotesCDS->Last();

        delete tq;
        return true;
    }
    catch(...)
    {
        Log(lError) << "There was a DB exception..";
		return false;
    }
}

//---------------------------------------------------------------------------
StringList TpgDM::getTableNames()
{
   if(!pgDM->SQLConnection1)
    {
        Log(lError) << "No SQL connection...";
        return StringList();
    }

    TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = pgDM->SQLConnection1;

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

bool TpgDM::addNoteForBlock(int blockID, int userID, const string& note)
{
   if(!pgDM->SQLConnection1)
    {
        Log(lError) << "No SQL connection...";
        return false;
    }

    stringstream q;
    q << "INSERT INTO notes (created_by, note) VALUES(:userID, :theNote) RETURNING id";

    TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = pgDM->SQLConnection1;

    tq->SQL->Add(q.str().c_str());
    tq->Params->ParamByName("userID")->AsInteger = userID;
    tq->Params->ParamByName("theNote")->AsString = note.c_str();
	tq->Open();

    //Get last insert ID for the note cleanCS batch and update coverslips
    int noteID = tq->FieldByName("id")->AsInteger;

	tq->Close();
    //Associate note and block
    tq->SQL->Clear();
	q.str("");
    q << "INSERT INTO block_note (block_id, note_id) VALUES(:bID, :nID)";
    tq->SQL->Add(q.str().c_str());
    tq->ParamByName("bID")->Value 		= blockID;
    tq->ParamByName("nID")->Value 		= noteID;
	tq->ExecSQL();

    delete tq;
    return true;
}

bool TpgDM::addNoteForRibbon(const string& ribbonID, int userID, const string& note)
{
   if(!pgDM->SQLConnection1)
    {
        Log(lError) << "No SQL connection...";
        return false;
    }

    stringstream q;
    q << "INSERT INTO notes (created_by, note) VALUES(:userID, :theNote) RETURNING id";

    TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = pgDM->SQLConnection1;

    tq->SQL->Add(q.str().c_str());
    tq->Params->ParamByName("userID")->AsInteger = userID;
    tq->Params->ParamByName("theNote")->AsString = note.c_str();
	tq->Open();

    //Get last insert ID for the note cleanCS batch and update coverslips
    int noteID = tq->FieldByName("id")->AsInteger;

	tq->Close();

    //Associate note and ribbon
    tq->SQL->Clear();
	q.str("");
    q << "INSERT INTO ribbon_note (ribbon_id, note_id) VALUES(:rID, :nID)";
    tq->SQL->Add(q.str().c_str());
    tq->ParamByName("rID")->Value 		= ribbonID.c_str();
    tq->ParamByName("nID")->Value 		= noteID;
	tq->ExecSQL();

    delete tq;
    return true;
}

bool TpgDM::addNoteForKnife(int knifeID, int userID, const string& note)
{
   if(!pgDM->SQLConnection1)
    {
        Log(lError) << "No SQL connection...";
        return false;
    }

    stringstream q;
    q << "INSERT INTO notes (created_by, note) VALUES(:userID, :theNote) RETURNING id";

    TSQLQuery* tq = new TSQLQuery(NULL);
    tq->SQLConnection = pgDM->SQLConnection1;

    tq->SQL->Add(q.str().c_str());
    tq->Params->ParamByName("userID")->AsInteger = userID;
    tq->Params->ParamByName("theNote")->AsString = note.c_str();
	tq->Open();

    //Get last insert ID for the note cleanCS batch and update coverslips
    int noteID = tq->FieldByName("id")->AsInteger;

	tq->Close();

    //Associate note and ribbon
    tq->SQL->Clear();
	q.str("");
    q << "INSERT INTO knife_notes (knife_id, note_id) VALUES(:kID, :nID)";
    tq->SQL->Add(q.str().c_str());
    tq->ParamByName("kID")->Value 		= knifeID;
    tq->ParamByName("nID")->Value 		= noteID;
	tq->ExecSQL();

    delete tq;
    return true;
}


int __fastcall	TpgDM::updateMovieTableWithRibbonID(const string& rID, int csID)
{
   if(!pgDM->SQLConnection1)
    {
        Log(lError) << "No SQL connection!";
        return false;
    }

    stringstream q;
    q << "UPDATE movies SET ribbon_id = :rID WHERE coverslip_id = :cID AND ribbon_id LIKE '-1'" ;

    auto_ptr<TSQLQuery> tq = auto_ptr<TSQLQuery>(new TSQLQuery(NULL));
    tq->SQLConnection = pgDM->SQLConnection1;

    tq->SQL->Add(q.str().c_str());
    tq->Params->ParamByName("rID")->AsString = rID.c_str();
    tq->Params->ParamByName("cID")->AsInteger = csID;
	return tq->ExecSQL();
}

int __fastcall	TpgDM::updateImagesTableWithRibbonID(const string& rID, int csID)
{
   if(!pgDM->SQLConnection1)
    {
        Log(lError) << "No SQL connection!";
        return false;
    }

    stringstream q;
    q << "UPDATE images SET ribbon_id = :rID WHERE coverslip_id = :cID AND ribbon_id = -1";

    auto_ptr<TSQLQuery> tq = auto_ptr<TSQLQuery>(new TSQLQuery(NULL));

    tq->SQLConnection = pgDM->SQLConnection1;

    tq->SQL->Add(q.str().c_str());
    tq->Params->ParamByName("rID")->AsString = rID.c_str();
    tq->Params->ParamByName("cID")->AsInteger = csID;
	return tq->ExecSQL();
}


