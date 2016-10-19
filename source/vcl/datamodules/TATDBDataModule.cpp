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

//VALID Paramaters
//DriverUnit=Data.DBXMySQL
//DriverPackageLoader=TDBXDynalinkDriverLoader,DbxCommonDriver170.bpl
//DriverAssemblyLoader=Borland.Data.TDBXDynalinkDriverLoader,Borland.Data.DbxCommonDriver,Version=17.0.0.0,Culture=neutral,PublicKeyToken=91d62ebb5b0d1b1b
//MetaDataPackageLoader=TDBXMySqlMetaDataCommandFactory,DbxMySQLDriver170.bpl
//MetaDataAssemblyLoader=Borland.Data.TDBXMySqlMetaDataCommandFactory,Borland.Data.DbxMySQLDriver,Version=17.0.0.0,Culture=neutral,PublicKeyToken=91d62ebb5b0d1b1b
//GetDriverFunc=getSQLDriverMYSQL
//LibraryName=dbxmys.dll
//LibraryNameOsx=libsqlmys.dylib
//VendorLib=LIBMYSQL.dll
//VendorLibWin64=libmysql.dll
//VendorLibOsx=libmysqlclient.dylib
//HostName=localhost
//Database=atdb
//User_Name=atdb_client
//Password=atdb123
//MaxBlobSize=-1
//LocaleCode=0000
//Compressed=False
//Encrypted=False
//BlobSize=-1


bool __fastcall TatdbDM::connect(const string& ip, const string& dbUser, const string& dbPassword, const string& db)
{
	try
    {
	    mDataBase = db;
        mDataBaseUser = dbUser;
        mDataBaseUserPassword = dbPassword;
        mDBIP = ip;

        SQLConnection1->KeepConnection = true;
    	SQLConnection1->Connected = false;
       	SQLConnection1->Params->Values[_D("HostName")] = vclstr(mDBIP);
       	SQLConnection1->Params->Values[_D("Database")] = vclstr(mDataBase);
       	SQLConnection1->Params->Values[_D("User_Name")] = vclstr(mDataBaseUser);
       	SQLConnection1->Params->Values[_D("Password")] = vclstr(mDataBaseUserPassword);
       	SQLConnection1->Connected= true;
    }
    catch (const Exception &E)
    {
       Application->MessageBox(E.Message.c_str(), _D("Error connecting to database"),  MB_ICONSTOP | MB_OK);
    }

    return SQLConnection1->Connected;
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::SQLConnection1BeforeConnect(TObject *Sender)
{
	Log(lInfo) <<"Trying to connect to SQL server:";
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::SQLConnection1AfterConnect(TObject *Sender)
{
	afterConnect();
}

void __fastcall TatdbDM::afterConnect()
{
	if(gAppIsStartingUp)
    {
    	return;
    }

	Log(lInfo) << "Connection established to: "<<mDataBase;
	usersCDS->Active 	    = true;
	specimenCDS->Active  = true;
    blocksCDS->Active 	    = true;

    mRibbonCDS->Active 	    = true;
    notesCDS->Active   	    = true;
	blockNotesCDS->Active  	= true;
    ribbonNotesCDS->Active  = true;
	specimenCDS->Active  = true;
}

void __fastcall TatdbDM::afterDisConnect()
{
	Log(lInfo) << "Closed connection to: "<<mDataBase;
  	usersCDS->Active 	    = false;
    blocksCDS->Active 	    = false;

    notesCDS->Active	    = false;
	blockNotesCDS->Active  	= false;
    ribbonNotesCDS->Active  = false;
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
	if(!SQLConnection1->Connected || gAppIsStartingUp)
    {
    	return;
    }

 	if(DataSet == blocksCDS)
    {
        int bID = blocksCDS->FieldByName("id")->AsInteger;
        if(bID == 0)
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

 	if(DataSet == specimenCDS)
    {
    	if(blocksCDS->Active)
        {
//	        stringstream s;
//            s << "SELECT * FROM block WHERE process_id IN ";
//
//	        blocksCDS->CommandText =
        	blocksCDS->Refresh();
        }
//        if(bID == 0)
//        {
//            blockNotesCDS->Active = false;
//            mRibbonCDS->Active = false;
//        }
//        else
//        {
//            blockNotesCDS->Active = true;
//            mRibbonCDS->Active = true;
//        }
//        cdsAfterRefresh(blocksCDS);
    }

}

void __fastcall TatdbDM::cdsAfterRefresh(TDataSet *DataSet)
{
	if(DataSet == blocksCDS)
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

    if(DataSet == mRibbonCDS)
    {
    	if(ribbonNotesCDS->Active)
        {
        	ribbonNotesCDS->Refresh();
        }
    }
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

//---------------------------------------------------------------------------
void __fastcall TatdbDM::fixativeTBLAfterPost(TDataSet *DataSet)
{
	fixativeTBL->ApplyUpdates(0);
    specimenCDS->Refresh();
}

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

            StringList d(stdstr(blocksCDS->FieldByName("created")->AsString), ' ');
            if(d.size())
            {
	            s << stdstr(d[0]) <<"\n";
            }

            s << stdstr(blocksCDS->FieldByName("label")->AsString) <<"\n";
            string str = s.str();
			f->Value = String(str.c_str());
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::blocksCDSblockLabelGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
	Text = "Test";
}

//---------------------------------------------------------------------------
void __fastcall TatdbDM::blocksCDScreatedGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
	TField* field = dynamic_cast<TField*>(Sender);

	if(field == blocksCDScreated)
	{
		StringList d(stdstr(blocksCDScreated->AsString), ' ');
        if(d.size())
        {
			Text = vclstr(d[0]);
        }
	}

}



