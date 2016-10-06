#pragma hdrstop
#include "TATDBDataModule.h"
#include "mtkVCLUtils.h"
#include <sstream>
#include "mtkLogger.h"
#include <iomanip>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
TatdbDM *atdbDM;

using namespace mtk;
using namespace std;

extern bool gAppIsStartingUp;

//---------------------------------------------------------------------------
__fastcall TatdbDM::TatdbDM(TComponent* Owner)
	: TDataModule(Owner)
{
  	SQLConnection1->Connected = false;
}

bool __fastcall TatdbDM::connect(const string& db)
{
	try
    {
	    mDataBase = db;
    	SQLConnection1->Connected = false;
       	SQLConnection1->Params->Values[_D("Database")] = vclstr(mDataBase);
       	SQLConnection1->Connected= true;

    }
    catch (const Exception &E)
    {
       Application->MessageBox(E.Message.c_str(), _D("Error connecting to database"),  MB_ICONSTOP | MB_OK);
    }

    return SQLConnection1->Connected;
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
	blocksDS->Active 	    = true;
    blocksCDS->Active 	    = true;
    mRibbonCDS->Active 	    = true;
    notesCDS->Active   	    = true;
	blockNotesCDS->Active  	= true;
}

void __fastcall TatdbDM::afterDisConnect()
{
	Log(lInfo) << "Closed connection to: "<<mDataBase;
  	usersCDS->Active 	    = false;
    blocksCDS->Active 	    = false;
    mRibbonCDS->Active 	    = false;
    notesCDS->Active	    = false;
	blockNotesCDS->Active  	= false;
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::usersCDSAfterPost(TDataSet *DataSet)
{
	usersCDS->ApplyUpdates(0);
    usersCDS->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::usersCDSAfterDelete(TDataSet *DataSet)
{
	usersCDS->ApplyUpdates(0);
}

void __fastcall TatdbDM::usersCDSAfterScroll(TDataSet *DataSet)
{
	;
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::usersCDSAfterCancel(TDataSet *DataSet)
{
;
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::blocksCDSAfterPost(TDataSet *DataSet)
{
	blocksCDS->ApplyUpdates(0);
    blocksDS->Refresh();
    blocksCDS->Refresh();
	updateRibbons();
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::blocksCDSAfterDelete(TDataSet *DataSet)
{
	blocksCDS->ApplyUpdates(0);
	updateRibbons();
}

void TatdbDM::updateRibbons()
{
	int bID = blocksCDS->FieldByName("id")->AsInteger;

    if(bID == 0)
    {
		mRibbonCDS->Active = false;
        return;
    }
    //Fetch associated Ribbons
    mRibbonCDS->Active = false;
    ribbonsQ->SQL->Text = "SELECT * from ribbon where block_id ='" + String(bID) + "'";
    ribbonsQ->Open();
    ribbonsQ->Close();
    mRibbonCDS->Active = true;
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::blocksCDSAfterScroll(TDataSet *DataSet)
{
	if(!SQLConnection1->Connected || gAppIsStartingUp)
    {
    	return;
    }

	int bID = blocksCDS->FieldByName("id")->AsInteger;

    if(bID == 0)
    {
		mRibbonCDS->Active = false;
        return;
    }

    blockNotesQ->Close();
	blockNotesQ->Params->ParamByName("id")->AsInteger = bID;
    blockNotesQ->Open();

    //Get notes
	string note = stdstr(blockNotesQ->FieldByName("note")->AsString);
	Log(lInfo) << "Note is: " << note;
	blockNotesQ->Close();
    blockNotesCDS->Refresh();

//    //Fetch associated Ribbons
    mRibbonCDS->Active = false;
    ribbonsQ->SQL->Text = "SELECT * from ribbon where block_id ='" + String(bID) + "'";
    ribbonsQ->Open();
    mRibbonCDS->Active = true;
    ribbonsQ->Close();
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::blockNotesCDSAfterPost(TDataSet *DataSet)
{
	blockNotesCDS->ApplyUpdates(0);
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::blocksCDSBeforePost(TDataSet *DataSet)
{
	Log(lInfo) << "Before Posting Block Data";
}

void __fastcall TatdbDM::mRibbonCDSAfterPost(TDataSet *DataSet)
{
	mRibbonCDS->ApplyUpdates(0);
}
//---------------------------------------------------------------------------

void __fastcall TatdbDM::mRibbonCDSBeforePost(TDataSet *DataSet)
{
	Log(lInfo) << "Before Posting Ribbon Data";
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::mRibbonCDSAfterDelete(TDataSet *DataSet)
{
	mRibbonCDS->ApplyUpdates(0);
}

string zeroPadLeft(int nr, int width)
{
	stringstream s;
    s << std::setw(width) << std::setfill( '0' ) << std::right << nr;
    return s.str();
}

string zeroPadRight(int nr, int width)
{
	stringstream s;
    s << std::setw(width) << std::setfill( '0' ) << std::left << nr;
    return s.str();
}

void __fastcall TatdbDM::mRibbonCDSCalcFields(TDataSet *DataSet)
{
	//Generate barcode as being composed of
	//    	block_id: first 5 digits
    //		ribbon_id: next 7 digits
	TField* field = blocksCDS->FieldByName("id");
	if(field)
	{
		TField* f = mRibbonCDS->FieldByName("bar_code");
		if(f)
		{
			stringstream s;
			s << zeroPadRight(blocksCDS->FieldByName("id")->AsInteger,   4);
			string str = s.str();
            s << zeroPadLeft(mRibbonCDS->FieldByName("id")->AsInteger, 5);
            str = s.str();
			f->Value = toLong(str);
		}
	}
}


void __fastcall TatdbDM::abImageDSBeforeScroll(TDataSet *DataSet)
{
	if(!SQLConnection1->Connected)
    {
    	return;
    }
//
//	int imageID = mImageClientDS->FieldByName("id")->AsInteger;
//	blockNotesQ->Params->ParamByName("blockID")->AsInteger = imageID;
//    blockNotesQ->Open();
//
//    //Get notes
//	string note = stdstr(blockNotesQ->FieldByName("note")->AsString);
//	Log(lInfo) << "Note is: "<<note;
//	blockNotesQ->Close();
//
//	if(gAppIsStartingUp == false && SQLConnection1->Connected)
//	{
//		//Update customers orders
//		mRibbonCDS->Active = false;
//		TField* field = blocksCDS->FieldByName("id");
//
//		if(field)
//		{
//			String val = field->AsString;
//			ribbonsQ->SQL->Text = "SELECT * from ribbon where block_id ='" + val + "'";
//
////			Log(lDebug) << stdstr((customerOrdersQ->SQL->Text));
//		}
//		mRibbonCDS->Active = true;
//	}

}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::SQLConnection1BeforeConnect(TObject *Sender)
{
	;
}




