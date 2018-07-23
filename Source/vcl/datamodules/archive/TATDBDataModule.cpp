#pragma hdrstop
#include "TATDBDataModule.h"
#include "dslVCLUtils.h"
#include <sstream>
#include "dslLogger.h"
#include <iomanip>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
TatdbDM *atdbDM;

using namespace dsl;
using namespace std;

string zeroPadLeft(int nr, int width);
string zeroPadRight(int nr, int width);

//---------------------------------------------------------------------------
__fastcall TatdbDM::TatdbDM(TComponent* Owner)
	:
    TDataModule(Owner)
{
  	SQLConnection1->Connected = false;
}

__fastcall TatdbDM::~TatdbDM()
{}

//---------------------------------------------------------------------------
bool __fastcall TatdbDM::connect(const string& ip, const string& dbUser, const string& dbPassword, const string& db)
{
    mDataBase = db;
    mDataBaseUser = dbUser;
    mDataBaseUserPassword = dbPassword;
    mDBIP = ip;

    try
    {
        SQLConnection1->KeepConnection = true;
        SQLConnection1->Connected = false;
        SQLConnection1->Params->Values[_D("HostName")] = vclstr(mDBIP);
        SQLConnection1->Params->Values[_D("Database")] = vclstr(mDataBase);
        SQLConnection1->Params->Values[_D("User_Name")] = vclstr(mDataBaseUser);
        SQLConnection1->Params->Values[_D("Password")] = vclstr(mDataBaseUserPassword);

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
    }
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::SQLConnection1BeforeConnect(TObject *Sender)
{
	Log(lInfo) <<"Trying to connect to SQL server:" <<stdstr(SQLConnection1->Params->Values[_D("Database")]);
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::SQLConnection1AfterConnect(TObject *Sender)
{
	afterConnect();
}

void __fastcall TatdbDM::afterConnect()
{
	Log(lInfo) << "Connection established to: "<<mDataBase;
	usersCDS->Active 	    = true;
	specimenCDS->Active 	= true;
	slicesCDS->Active  		= true;
    blocksCDS->Active 	    = true;
    blockIDSCDS->Active     = true;
    mRibbonCDS->Active 	    = true;
    notesCDS->Active   	    = true;
	blockNotesCDS->Active  	= true;
    ribbonNotesCDS->Active  = true;
	slicesCDS->Active  		= true;
    ROnCS_CDS->Active  		= true;
    settingsCDS->Active  	= true;
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::afterDisConnect()
{
	Log(lInfo) << "Closed connection to: "<<mDataBase;
  	usersCDS->Active 	    = false;
	specimenCDS->Active 	= false;
    blocksCDS->Active 	    = false;
    blockIDSCDS->Active     = false;
    notesCDS->Active	    = false;
	blockNotesCDS->Active  	= false;
    ribbonNotesCDS->Active  = false;
	slicesCDS->Active  		= false;
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::cdsAfterPost(TDataSet *DataSet)
{
	TClientDataSet* cds = dynamic_cast<TClientDataSet*>(DataSet);

    if(!cds)
    {
    	return;
    }

	cds->ApplyUpdates(0);
    cds->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::cdsAfterDelete(TDataSet *DataSet)
{
	TClientDataSet* cds = dynamic_cast<TClientDataSet*>(DataSet);

    if(!cds)
    {
    	return;
    }

	cds->ApplyUpdates(0);
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::cdsAfterScroll(TDataSet *DataSet)
{
	if(!SQLConnection1->Connected)// || gAppIsStartingUp)
    {
    	return;
    }

 	if(DataSet == specimenCDS)
    {
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
            mRibbonCDS->Active = false;
        }
        else
        {
            blockNotesCDS->Active = true;
            mRibbonCDS->Active = true;
        }
        cdsAfterRefresh(blocksCDS);
    }

	if(DataSet == mRibbonCDS)
    {
        String rID = mRibbonCDS->FieldByName("id")->AsString;
        if(rID == "")
        {
            ribbonNotesCDS->Active = false;
        }
        else
        {
            ribbonNotesCDS->Active = true;

        }
        cdsAfterRefresh(mRibbonCDS);
    }
}

void __fastcall TatdbDM::cdsAfterRefresh(TDataSet *DataSet)
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
    	if(mRibbonCDS->Active)
        {
    		mRibbonCDS->Refresh();
        }

        if(blockNotesCDS->Active)
        {
			blockNotesCDS->Refresh();
        }
    }
    else if(DataSet == mRibbonCDS)
    {
    	if(ribbonNotesCDS->Active)
        {
        	ribbonNotesCDS->Refresh();
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
void __fastcall TatdbDM::cdsBeforePost(TDataSet *DataSet)
{
	if(DataSet == blocksCDS)
    {
		Log(lInfo) << "Before Posting Block Data";
    }
    else if(DataSet == mRibbonCDS)
    {
		Log(lInfo) << "Before Posting Ribbon Data";
    }
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::mRibbonCDSCalcFields(TDataSet *DataSet)
{
	//Generate barcode as being composed of
	//    	block_id: first 5 digits
    //		ribbon_id: next 7 digits
//	TField* field = blocksCDS->FieldByName("id");
//	if(field)
//	{
//		TField* f = mRibbonCDS->FieldByName("id");
//		if(f)
//		{
//			stringstream s;
//			s << zeroPadRight(blocksCDS->FieldByName("id")->AsInteger,   4);
//			string str = s.str();
//            s << zeroPadLeft(mRibbonCDS->FieldByName("id")->AsInteger, 5);
//            str = s.str();
//			f->Value = toLong(str);
//		}
//	}
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::fixativeTBLAfterPost(TDataSet *DataSet)
{
	fixativeTBL->ApplyUpdates(0);
    slicesCDS->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::blocksCDSCalcFields(TDataSet *DataSet)
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
void __fastcall TatdbDM::blocksCDSblockLabelGetText(TField *Sender, UnicodeString &Text, bool DisplayText)
{
	Text = "Test";
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::TimeStampGetText(TField *Sender, UnicodeString &Text,
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
//    else if	(field == mRibbonCDScreated)
//	{
//		StringList d(stdstr(mRibbonCDScreated->AsString), ' ');
//        if(d.size())
//        {
//			Text = vclstr(d[0]);
//        }
//	}
}
//---------------------------------------------------------------------------
void __fastcall TatdbDM::cdsBeforeRefresh(TDataSet *DataSet)
{
//	if(DataSet == slicesCDS)
//    {
//		slicesCDS->Active = false;
//		slicesCDS->Active = true;
//    }
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::slicesCDSBeforeClose(TDataSet *DataSet)
{
    //delete runtime indices
    Log(lDebug) << "Closing dataset";
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::slicesCDSAfterClose(TDataSet *DataSet)
{
    Log(lDebug) << "Closing dataset";
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::slicesCDSAfterOpen(TDataSet *DataSet)
{
    Log(lDebug) << "After Open";
}

int	__fastcall TatdbDM::getCurrentBlockID()
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
    else
    {
    	return -1;
    }
}

int __fastcall TatdbDM::getIDForSpecie(const string& specie)
{
	if(speciesDS->Active)
    {
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
String __fastcall TatdbDM::createBlockLabel()
{
    String lbl;
    String specie = atdbDM->specimenCDS->FieldByName("Lspecie")->AsString;
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

	lbl = lbl + atdbDM->specimenCDS->FieldByName("animal_id")->AsString + "-" + (atdbDM->blocksCDS->RecordCount + 1);
	return lbl;
}

bool __fastcall	TatdbDM::insertBlockNote(int userID, int blockID, const string& note)
{
    try
    {
        //Query DB and show some info
        TSQLQuery* tq = new TSQLQuery(NULL);
        tq->SQLConnection = atdbDM->SQLConnection1;

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

    	atdbDM->blockNotesCDS->Refresh();
	    atdbDM->blockNotesCDS->Last();
        return true;
    }
    catch(...)
    {
        Log(lError) << "There was a DB exception..";
        //handleMySQLException();
        return false;
    }
}

bool __fastcall	TatdbDM::insertRibbonNote(int userID, const string& ribbonID, const string& note)
{
    try
    {
        //Query DB and show some info
        TSQLQuery* tq = new TSQLQuery(NULL);
        tq->SQLConnection = atdbDM->SQLConnection1;

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
	    atdbDM->ribbonNotesCDS->Refresh();
    	atdbDM->ribbonNotesCDS->Last();

        delete tq;
        return true;
    }
    catch(...)
    {
        Log(lError) << "There was a DB exception..";
	//        handleMySQLException();
		return false;
    }


}
//---------------------------------------------------------------------------
string zeroPadLeft(int nr, int width)
{
	stringstream s;
    s << std::setw(width) << std::setfill( '0' ) << std::right << nr;
    return s.str();
}

//---------------------------------------------------------------------------
string zeroPadRight(int nr, int width)
{
	stringstream s;
    s << std::setw(width) << std::setfill( '0' ) << std::left << nr;
    return s.str();
}


